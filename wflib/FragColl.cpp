
/* =====[ FragColl.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the FragColl.cpp                
                                                                             
                    Defines the behavior for the application.          
					This class compares a portion of the unknown with the
					data loaded into it.
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/25/2010  Peter Glen   Initial version.                         
      0.00  3/14/2010  Peter Glen   Cleanup
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "stdio.h"
#include "io.h"
#include "direct.h"

#include "wflib.h"
#include "FragColl.h"
#include "FragCollArr.h"
#include "frag.h"

#include "mxpad.h"
#include "support.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern	CxRecog		xdllrecog;
extern CFragCollArr	fragcollarr;

#undef P2N		// Async debug only

/// \class CFragColl
/// \brief 
/// This class holds an array of frags for the recognition engine to 
/// search through.
///
/// It is responsible of maintaining a list of frags, and to give 
/// access to the iterator of the compare engine.
///

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFragColl::CFragColl()

{
	magic = CFragColl_Magic;

	maxlen = INT_MIN;	minlen = INT_MAX;

	xfragstrarr = new CStringArray;

	stop = 0;
}
	
//////////////////////////////////////////////////////////////////////////

CFragColl::~CFragColl()

{
	ASSERT(CFragColl_Magic == magic);

	xDelFrags();

	delete xfragstrarr;
}

//////////////////////////////////////////////////////////////////////////
// Free all memory allocated 

void CFragColl::xDelFrags() 

{
	// Delete ALL accumulated frags
	int lenfr = xfragarr.GetSize();
	for(int loopfr = 0; loopfr < lenfr; loopfr++)
		{
		ASSERT(((CFrag*)xfragarr[loopfr])->magic == CFrag_Magic);
		delete( (CFrag*) xfragarr[loopfr]);
		}
	xfragarr.RemoveAll();

	// Release index pointers as well
	int xsize = xidxarr.GetSize();
	for(int loopz = 0; loopz < xsize; loopz++)
		{
		CPtrArray *ptr = (CPtrArray*)xidxarr.GetAt(loopz);
		delete ptr;
		}
	xidxarr.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////
// Load All frags. Must set fragdir and wavdir

int CFragColl::LoadAllFrags(const char *dir, int reload) 

{
	CString strx(dir), strdir(dir);	
	
	//AP2N("CFragColl::LoadAllFrags  from: '%s'\r\n", strx);
	
	//int idx = strx.ReverseFind('\\'); 
	//strx = strx.Mid(idx + 1);	strdir = strdir.Left(idx + 1);

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	if(chdir(strdir) < 0 )
		{
		AP2N("CFrag::LoadAllFrags::Cannot change dir %s\r\n", strdir);

		//CString tmp; tmp.Format("CFrag::LoadAllFrags::Cannot load frags from '%s'", strdir);
		//if(!noprompt)
		//	::MessageBox(NULL, tmp, "WavFrag DLL", MB_OK);

		return -1;
		}

	struct _finddata_t c_file;
    long hFile;

	CString wild = "*"; wild += CFrag::fragext;

	int cnt = 0, arrlen = 0;
	
	// Delete old frags, start anew
	xDelFrags();
	
	// Create a dummy entry
	CFrag  *pfragnull = new CFrag;
	*pfragnull->name = "nx-01";	*pfragnull->shortname = "nx";
	AddFrag(pfragnull);

	if( (hFile = _findfirst(wild, &c_file )) == -1L )
		goto endd;
	
	while(true)
        {
        //AP2N( " %-12s %.24s  %9ld\r\n",
		//	c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

		CFrag  *pfrag = new CFrag;
		pfrag->LoadFrag(c_file.name, reload);	
		
		// Add if there is data
		if(pfrag->GetData()->raw.GetSize())
			{
			AddFrag(pfrag);
			//pfrag->Dump();		

			cnt++;
			}
		else
			{
			// Unload empty one
			AP2N("Unloading empty %s\r\n", *pfrag->name);
			delete pfrag;
			}

		// End of file 
		if( _findnext( hFile, &c_file ) != 0 )
			break;		
		}

endd:
	_findclose( hFile );
	chdir(olddir);

	// Fill in dummy details, so recogonition has a NULL frag
	pfragnull->xres.AddNull(5);
	
	// Dump name array
	//int alens2 = fragstrarr.GetSize();
	//for(int loops2 = 0; loops2 < alens2; loops2++)
	//	{
	//	AP2N("%6s\t", fragstrarr.GetAt(loops2));
	//	}
	
	//DumpFrags();
	//DumpIdx();

	//AP2N("CFragColl::LoadAllFrags %d frags maxlen=%d minlen=%d maxidx=%d onefraglen=%d\r\n", 
	//					cnt, maxlen, minlen, maxidx, 
	//							CFrag::onefraglen);

	return cnt;
}

//////////////////////////////////////////////////////////////////////////
// Not used

int	 CFragColl::SaveAllFrags(const char *dir) 

{
	//ASSERT(false);

	int ret = 0;

	CString strx(dir), strdir(dir);	
	
//	if(dir == NULL)
//		{
//		strx = fragdir, strdir = fragdir;	
//		}
//	else
//		{
//		strx = dir, strdir = dir, fragdir = dir;	
//		}

	//AP2N("CFragColl::SaveAllFrags Saving frags to: '%s'\r\n", strx);

	// Ignore this if no frags loaded or no frag dir
	if(strx == "")
		return 0;
	
	int idx = strx.ReverseFind('\\'); 
	strx = strx.Mid(idx + 1);	strdir = strdir.Left(idx + 1);

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	if(chdir(strdir) < 0 )
		{
		AP2N("CFrag::SaveAllFrags::Cannot change dir %s\r\n", strdir);

		//CString tmp; tmp.Format("CFrag::LoadAllFrags::Cannot load frags from '%s'", strdir);
		//if(!noprompt)
		//	::MessageBox(NULL, tmp, "WavFrag DLL", MB_OK);

		return -1;
		}

	CPtrArray *tmparr = &xfragarr;
	int len2f = tmparr->GetSize();
	
	int cnt = 0, alen = tmparr->GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CFrag *fr = (CFrag *)tmparr->GetAt(loop);

		//if(fr->needsave)
			{
			//AP2N("Save %s len=%d\r\n", *fr->name, fr->frqarr.GetSize());

#if 0
			CFile fp;
			CString fname2(*fr->name); fname2 += CFrag::defext;
			if(fp.Open(fname2, CFile::modeCreate | CFile::modeWrite))
				{	
				int alen = fr->frqarr.GetSize();
				int *data = fr->frqarr.GetData();
				fp.Write(data, alen * sizeof(int));

				int *data2 = fr->volarr.GetData();
				fp.Write(data2, alen * sizeof(int));

				cnt++;
				}
#endif

			}
 		}
	chdir(olddir);

	if(cnt)
		{
		AP2N("CFragColl::SaveAllFrags Saved %d frags\r\n", cnt);
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////

void	CFragColl::DumpFrags()

{
	// Dump frags
	int alenf = xfragarr.GetSize();
	for(int loopf = 0; loopf < alenf; loopf++)
		{
		CFrag *pfr = ((CFrag *)xfragarr.GetAt(loopf));
		ASSERT(pfr->magic == CFrag_Magic);

		AP2N("%-8s  %9s %9s    idx=%-3d raw=%-3d len=%-3d\r\n", user,
					*pfr->name, *pfr->shortname, pfr->idx, 
							pfr->xres.raw.GetSize(),
								pfr->xres.all.GetSize());

		//pfr->DumpLoHi();
		}
}

//////////////////////////////////////////////////////////////////////////
// 

void	CFragColl::DumpIdx()

{
	// Dump indexed frags. Can be used as a template for aloop on recog.

	int alenx = xidxarr.GetSize();
	for(int loopx = 0; loopx < alenx; loopx++)
		{
		CPtrArray *parr = (CPtrArray*)xidxarr.GetAt(loopx);
		int alen = parr->GetSize();

		for(int loop = 0; loop < alen; loop++)
			{
			CFrag *pfr = ((CFrag *)parr->GetAt(loop));
			ASSERT(pfr->magic == CFrag_Magic);

			AP2N("	%9s %6s idx=%-3d len=%-3d\r\n", 
				*pfr->name, *pfr->shortname, pfr->idx, 
						pfr->xres.raw.GetSize());
			}
		AP2N("idx=%d \r\n", loopx);
		}
}

//////////////////////////////////////////////////////////////////////////

int	 CFragColl::ParseAllWaves(CCHAR *wdir, CCHAR *fdir, int reload) 

{
	CString tmp; 
	
	//AP2N("ParseAllWaves from: '%s' to '%s'\r\n", wdir, fdir);
	
	support.SoftMkdir(fdir);
	
	ClearOldFrags(fdir);

	//ClearOldFrags(fdir);

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	if(chdir(wdir) < 0)
		{
		//AP2N("CFragColl::ParseAllFragWaves Cannot change dir %s\r\n", strdir);

		//CString tmp; tmp.Format("CFragColl::ParseAllFragWaves Cannot parse frags from '%s'", strdir);
		//if(!noprompt)
		//	::MessageBox(NULL, tmp, "WavFrag DLL", MB_OK);

		return -1;
		}

	CString wild; wild = "*"; wild += CFrag::wavext;
	struct _finddata_t c_file;  long hFile; int cnt = 0;
	
	stop = false;

	if( (hFile = _findfirst(wild, &c_file )) == -1L )
		goto endd;

	while(true)
        {
        //AP2N( " %-12s %.24s  %9ld\r\n",
		//	c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

		CString str = wdir; str += c_file.name;

		tmp.Format("Parsing '%s' %d bytes", 
											c_file.name, c_file.size);
		if(xdllrecog._fragrec)
			xdllrecog._fragrec(tmp, tmp.GetLength());

		int ret = CFrag::ParseFragWav(c_file.name, wdir, fdir, reload);

		if( _findnext( hFile, &c_file ) != 0 )
			break;
	
		cnt++;

		if(stop)
			break;

		support.YieldToWinEx();
		}

endd:
	_findclose( hFile );

	chdir(olddir);

	// Dump name array
	//int alens2 = fragstrarr.GetSize();
	//for(int loops2 = 0; loops2 < alens2; loops2++)
	//	{
	//	P2N("%6s\t", fragstrarr.GetAt(loops2));
	//	}
	
	//AP2N("Loaded %d frags maxlen=%d minlen=%d\r\n", cnt, maxlen, minlen);
	
	tmp.Format("Parsed %d frags from '%s'\r\n", cnt, wdir);

	if(xdllrecog._fragrec)
		xdllrecog._fragrec(tmp, tmp.GetLength());

	return cnt;
}

//////////////////////////////////////////////////////////////////////////

int CFragColl::Idx2Len(int idx)

{
	int ret = 0, cnt = 0, alen = xfragarr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CFrag *fr = (CFrag *)xfragarr.GetAt(loop);

		if(fr->idx == idx)
			{
			ret += fr->xres.raw.GetSize();
			cnt++;
			}
		}

	if(cnt)
		ret /= cnt;

	return ret;
}

//////////////////////////////////////////////////////////////////////////

CString CFragColl::Idx2Str(int idx, int real)

{
	CString str;

	int cnt = 0, alen = xfragarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CFrag *fr = (CFrag *)xfragarr.GetAt(loop);

		if(fr->idx == idx)
			{
			if(real)
				str = *fr->fname;
			else
				str = *fr->shortname;
			break;
			}
		}
	return str;
}

//////////////////////////////////////////////////////////////////////////
// Add new frag to body and index. Fill in min max values.

void CFragColl::AddFrag(CFrag *pfrag)

{
	// Assign min / max size here
	int flen = pfrag->xres.raw.GetSize();

	if(flen > maxlen)
		maxlen = flen;

	if(flen < minlen && flen != 0)
		minlen = flen;
	
	// Index it
	int tmpidx = 0, found = 0, alens = xfragstrarr->GetSize();
	for(int loops = 0; loops < alens; loops++)
		{
		if(xfragstrarr->GetAt(loops) == *pfrag->shortname)
			{
			tmpidx = loops; found = true; break;
			}
		}

	if(!found)
		tmpidx = xfragstrarr->Add(*pfrag->shortname);
	
	// Mark our index into global strarr
	pfrag->idx = tmpidx;

	// Padd idxarr
	if(xidxarr.GetUpperBound() < tmpidx)
		{
		while(true)
			{
			// Larger than last data, bail		
			if(xidxarr.GetSize() > tmpidx)
				break;

			CPtrArray *ptr = new CPtrArray; ASSERT(ptr);
			xidxarr.Add(ptr);
			}
		}

	// Add frag to index array
	CPtrArray *parr = (CPtrArray*)xidxarr.GetAt(tmpidx);
	parr->Add(pfrag);

	// Fill in colective information
	if(maxidx < pfrag->idx)
		maxidx = pfrag->idx;

	// Add to list of frags
	xfragarr.Add(pfrag);
}

///////////////////////////////////////////////////////////////////////////
/// \brief Delete one wav, and nuke the index if this was the last wave
///
/// Param:
///		
///		CCHAR *pword  - word to look in
///		CCHAR *pentry - frag name to delete
///
/// Return:
/// 
///		1 (true) if deleted OK
///		2 if deleted OK and removed index as well
///		-1 if error, -2 if not found 
///

int		CFragColl::DelFragEntry(CCHAR *pword, CCHAR *pentry)

{
	AP2N("CFragColl::DelFragEntry %s %s\r\n", pword, pentry);

	int ret = 0, idxidx = -1;

	CString wavdir = GetWavDir();	CString fragdir = GetFragDir();
	
	int alen2 = GetData()->GetSize();
	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		CFrag *fr = (CFrag *)GetData()->GetAt(loop2);

		if(fr->shortname->CompareNoCase(pword) == 0)
			{			
			if(fr->name->CompareNoCase(pentry) == 0)
				{
				//AP2N("Found2 to delete entry %s %s\r\n", *fr->name, pword);
				ret = true;
				idxidx = fr->idx;

				CString fname = wavdir + *fr->name + CFrag::wavext;
				int uret = unlink(fname); 
				//AP2N("del %s %d\r\n", fname, uret);	
				
				CString fname2 = fragdir + *fr->name + CFrag::fragext;
				uret = unlink(fname2);
				//AP2N("del %s %d\r\n", fname2, uret);
				
				// Remove index too 
				CPtrArray *parr = (CPtrArray*)GetIdxData()->GetAt(fr->idx);
				int xlen = parr->GetSize();
				for(int loop3 =  xlen - 1; loop3 >= 0; loop3--)
					{
					CFrag *frx = (CFrag *)parr->GetAt(loop3);
					if(fr == frx)
						parr->RemoveAt(loop3);
					}

				// Remove them from loaded frags as well
				delete fr;
				GetData()->RemoveAt(loop2);
				
				// Tell the collection, it has changed

				fragcollarr.SetChangeFlag();
				//fragcollarr.xchanged = true;
				break;
				}
			}
 		}

	// Not found, tell
	if(!ret)
		return -2;

	// See if nuked last entry on strarr
	int found = false, alen3 = GetData()->GetSize();
	for(int loop3 = 0; loop3 < alen3; loop3++)
		{
		CFrag *fr = (CFrag *)GetData()->GetAt(loop3);
		if(fr->shortname->CompareNoCase(pword) == 0)
			{
			found = true;
			break;
			}
		}

	// Yep, nuked last entry on this word
	if(!found)
		{
		ret = 2;
		AP2N("WFL_DelFragEntry Nuking last %s (idx=%d)\r\n", pword, idxidx);

		//CPtrArray *ptr = (CPtrArray *)GetIdxData()->GetAt(idxidx);
		//delete ptr;	
		//GetIdxData()->RemoveAt(idxidx);	

		DelWord(pword);

		//DumpIdx();		
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int		CFragColl::DelWord(CCHAR *pword)

{
	//AP2N("WFL_DelWord %s\r\n", pword);

  	CString wavdir = GetWavDir();	CString fragdir = GetFragDir();

	int ret = 0, alen = xfragstrarr->GetSize();

	for(int idxloop = 0; idxloop < alen; idxloop++)
		{
		CString cstr = xfragstrarr->GetAt(idxloop);

		if(cstr.CompareNoCase(pword) == 0)
			{
			//AP2N("Found %s %s\r\n", cstr, pword);
			break;
			}
 		}

	// Found?
	if(idxloop >= alen)
		return ret;

	AP2N("WFL_DelWord found '%s' at index %d\r\n", pword, idxloop);
	
	int idxidx = -1;

	int alen2 = GetData()->GetSize();
	for(int loop2 = alen2 - 1; loop2 >= 0; loop2--)
		{
		CFrag *fr = GetAt(loop2);

		ASSERT(fr->magic == CFrag_Magic);

		//AP2N("WFL_DelWord frag %s idx=%d\r\n", *fr->name, fr->idx);

		if(fr->shortname->CompareNoCase(pword) == 0)
			{
			AP2N("WFL_DelWord Found frag %s %s idx=%d\r\n", *fr->name, pword, fr->idx);

			idxidx = fr->idx;
			CString fname = wavdir + *fr->name  + CFrag::wavext;
			int uret = unlink(fname);
			//AP2N("del wav %s uret=%d\r\n", fname, uret);	
			
			CString fname2 = fragdir + *fr->name + CFrag::fragext;
			int uret2 = unlink(fname2);
			//AP2N("del file %s uret2=%d\r\n", fname2, uret2);

			// Remove index too 
			xRemoveIdx(fr);

			// Remove them from loaded frags as well (backwards)
			GetData()->RemoveAt(loop2);

			delete fr;
			}		
 		}

	fragcollarr.SetChangeFlag();
	xfragstrarr->RemoveAt(idxloop);		// Remove string	
	
	// Remove index
	CPtrArray *parr = (CPtrArray*)xidxarr.GetAt(idxloop);
	delete parr;  xidxarr.RemoveAt(idxloop);			
	
	DumpIdx();

	return ret;
}

//////////////////////////////////////////////////////////////////////////

void CFragColl::xSave(CFile *pfp) 

{	
	CString crlf("\r\n");

	int alenf = xfragarr.GetSize();

	//AP2N("alenf=%d\r\n", alenf);

	pfp->Write(&alenf, sizeof(alenf));	
		
	for(int loopf = 0; loopf < alenf; loopf++)
		{
		CFrag *pfr = ((CFrag *)xfragarr.GetAt(loopf));
		ASSERT(pfr->magic == CFrag_Magic);

		//AP2N("	%9s %16s idx=%-3d len=%-3d\r\n", 
		//			*pfr->name, *pfr->shortname, pfr->idx, 
		//					pfr->xres.raw.GetSize());

		CString tmp; tmp.Format("   %s %s %d\r\n", 
				*pfr->name, *pfr->shortname, pfr->xres.raw.GetSize());

		pfp->Write(tmp, tmp.GetLength());	
		pfr->Save(pfp);
		pfp->Write(crlf, crlf.GetLength());			
		}
}

//////////////////////////////////////////////////////////////////////////

int CFragColl::xLoad(CFile *pfp) 

{
	int ret = 0, cnt = 0;
	
	int alenf = 0; int rrr = pfp->Read(&alenf, sizeof(alenf));	

	if(rrr != sizeof(alenf))
		{
		AP2N("CFragColl::xLoad Short read\r\n");
		return -1;
		}
		
	//AP2N("alenf=%d\r\n", alenf);

	if(!alenf)
		{
		AP2N("CFragColl::xLoad Empty array\r\n");
		return 0;
		}
		
	while(true)
		{
		CString fragname, name, sname, lenstr, crlf;
	
		// Header
		int endd = support.ReadLine(*pfp, fragname, 64);
			
		if(fragname.GetLength() > 0)
			{
			ret += fragname.GetLength();

			fragname.TrimLeft(); fragname.TrimRight();

			// Parse frag names:
			//AP2N("fragname: '%s'\r\n", fragname);			

			int idx = fragname.Find(" ");
			if(idx >= 0)
				{
				name = fragname.Left(idx);
				fragname = fragname.Mid(idx + 1);
				int idx2 = fragname.Find(" ");
				if(idx2 >= 0)
					{
					sname = fragname.Left(idx2);
					fragname = fragname.Mid(idx2 + 1);

					int idx3 = fragname.Find(" ");
					if(idx3 >= 0)
						{
						lenstr = fragname.Left(idx3);
						}
					else
						{
						lenstr = fragname;
						}
					}				
				}

			//AP2N("name: '%s'  sname: '%s' lenstr: '%s'\r\n", name, sname, lenstr);			

			// Load frag
			CFrag *pfr = new CFrag; ASSERT(pfr);
			
			// Assign
			*pfr->name = name; *pfr->shortname = sname;

			int bytes = pfr->Load(pfp);

			AddFrag(pfr);
			cnt++;

			//AP2N("loaded: %d bytes\r\n", bytes);
			}	
		
		// Read final crlf
		support.ReadLine(*pfp, crlf, 20);	
		ret += crlf.GetLength();

		if(--alenf <= 0)
			break;

		if(endd)
			break;
		}

	//DumpFrags();

	AP2N("FragColl::Load loaded user='%s' - %d frags\r\n", user, cnt);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Compose wav dir

CString CFragColl::GetWavDir()

{
	CString wavdir = fragcollarr.rootwavdir; 

	if(user != fragcollarr.defname)
		{
		wavdir += user; wavdir += "\\";
		}

	//AP2N("CFragColl::GetWavDir '%s'\r\n", wavdir);

	return wavdir;
}

//////////////////////////////////////////////////////////////////////////

CString CFragColl::GetFragDir()

{
	CString fragdir = fragcollarr.rootfragdir; 

	if(user != fragcollarr.defname)
		{
		fragdir += user; fragdir += "\\";
		}

	//AP2N("CFragColl::GetFragDir '%s'\r\n", fragdir);

	return fragdir;
}

//////////////////////////////////////////////////////////////////////////
// Remove index too 

void CFragColl::xRemoveIdx(CFrag *pfr)

{
	CPtrArray *parr = (CPtrArray*)xidxarr.GetAt(pfr->idx);
	int xlen = parr->GetSize();
	for(int loop3 =  xlen - 1; loop3 >= 0; loop3--)
		{
		CFrag *frx = (CFrag *)parr->GetAt(loop3);
		if(pfr == frx)
			{
			parr->RemoveAt(loop3);
			}
		}
}

//////////////////////////////////////////////////////////////////////////
// Clear old frags before reparse

int CFragColl::ClearOldFrags(CCHAR *dir)

{
	//AP2N("CFragColl::xClearFragDir(CCHAR *dir) %s\r\n", dir);

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	CString dir2 = dir; support.RepairPath(dir2);
	
	if(chdir(dir2) < 0)
		{
		AP2N("CFragColl::xClearDir Cannot change dir %s\r\n", dir2);
		return -1;
		}

	struct _finddata_t c_file;  long hFile; int ret = 0;
	CString wild; wild = "*"; wild += CFrag::fragext;

	if( (hFile = _findfirst(wild, &c_file )) == -1L )
		goto endd;

	while(true)
        {        	
		CString str = dir2; str += c_file.name;
		int uret = unlink(str);

		//AP2N("unlink %s %d\r\n", str, uret);
		
		if( _findnext( hFile, &c_file ) != 0 )
			break;
		
		if(stop)
			break;

		support.YieldToWinEx();
		ret++;
		}

endd:

	_findclose( hFile );

	chdir(olddir);

	return ret;
}


//////////////////////////////////////////////////////////////////////////
// Clear old wav-s

int  CFragColl::ClearOldWaves(CCHAR *dir)

{
	AP2N("CFragColl::ClearOldWaves(CCHAR *dir) %s\r\n", dir);

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	CString dir2 = dir; support.RepairPath(dir2);
	
	if(chdir(dir2) < 0)
		{
		AP2N("CFragColl::ClearOldWaves Cannot change dir %s\r\n", dir2);
		return -1;
		}

	struct _finddata_t c_file;  long hFile; int ret = 0;
	CString wild; wild = "*"; wild += CFrag::wavext;

	if( (hFile = _findfirst(wild, &c_file )) == -1L )
		goto endd;

	while(true)
        {        	
		CString str = dir2; str += c_file.name;
		int uret = unlink(str);

		//AP2N("unlink %s %d\r\n", str, uret);
		
		if( _findnext( hFile, &c_file ) != 0 )
			break;
		
		if(stop)
			break;

		support.YieldToWinEx();
		}

endd:
	_findclose( hFile );

	chdir(olddir);

	return ret;
}



#if 0

	//AP2N("CFragColl::ClearOldFrags(CCHAR *dir %s\r\n", dir);

	int ret; 
	stop = false;

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	CString dir2 = dir; support.RepairPath(dir2);
	if(chdir(dir2) < 0)
		{
		AP2N("CFragColl::xClearOldFrags Cannot change dir %s\r\n", dir2);
		return -1;
		}
	
	xClearDir(dir2);

	struct _finddata_t c_file;  long hFile;
	CString wild; wild = "*.*";

	if( (hFile = _findfirst(wild, &c_file )) == -1L )
		goto endd;

	//////////////////////////////////////////////////////////////////////
	
	while(true)
        {
        //AP2N( " %-12s %.24s  %9ld\r\n",
		//	c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

		if(c_file.name[0] != '.')
			{
			if(c_file.attrib & _A_SUBDIR)
				{
				//AP2N( " %-12s %.24s  %9ld\r\n",
				//c_file.name, ctime( &c_file.time_write  ), c_file.size );

				CString str = dir2; str += c_file.name;
				xClearDir(str);
				ret++;
				}
			}

		if( _findnext( hFile, &c_file ) != 0 )
			break;
	
		if(stop)
			break;

		support.YieldToWinEx();
		}

endd:
	_findclose( hFile );
	chdir(olddir);

#endif
