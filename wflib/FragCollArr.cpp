
/* =====[ FragCollArr.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the FragCollArr.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/21/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "io.h"
#include "direct.h"
#include <sys/stat.h>

#include "FragColl.h"
#include "FragCollArr.h"

#include "mxpad.h"

extern CFragCollArr	fragcollarr;
extern CFragColl *pfragcoll;

char CFragCollArr::defname[] = "default";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFragCollArr::CFragCollArr()

{
	xcurridx = -1;
	stop = xchanged = 0;

	// Add the default name and make it the current one
	AddSpeaker("");
	SetCurrSpeaker(defname);
}

CFragCollArr::~CFragCollArr()

{
	ASSERT(xarr.GetSize() == xnames.GetSize());

	Clear();
}

//////////////////////////////////////////////////////////////////////////

int	 CFragCollArr::LoadAll(const char  *fname)

{
	int ret = 0, cnt = 0;

	CString crlf("\r\n");

	//AP2N("CFragCollArr::LoadAll %s\r\n", fname);	

	CFile fp; 
	if(!fp.Open(fname, CFile::modeRead))
		{
		AP2N("CFragCollArr::LoadAll open file %s\r\n", fname);

		// Nothing, start with default user
		int	 rets = AddSpeaker("");
		CFragColl*	 pfc = GetCollPtr("");

		if(pfc)
			{
			ASSERT(pfc->magic == CFragColl_Magic);
			}
		return -1;
		}

	//CFileException fe; fe.m_strFileName = fname;

	while(true)
		{
		CString name;

		int endread = support.ReadLine(fp, name, 200);
		
		if(name.GetLength() > 0)
			{						
			// Remove brackets
			int idx = name.Find("[");
			if(idx >= 0)
				{	
				name = name.Mid(idx + 1);
				int idx2 = name.Find("]");
				if(idx >= 0)
					{	
					name = name.Left(idx2);
					}				
				}

			//AP2N("name= '%s'\r\n", name);

			int	 rets = AddSpeaker(name);
			CFragColl*	 pfc = GetCollPtr(name);

			if(pfc)
				{
				ASSERT(pfc->magic == CFragColl_Magic);

				pfc->user = name;					
				int retr = pfc->xLoad(&fp);
				cnt += retr;
				}
			}
				
		if(endread)
			break;
		}

	//Dump();

	BuildIdx();

	//pfc->DumpFrags();

	xchanged = 0;

	AP2N("CFragCollArr::LoadAll loaded %d items\t\n", cnt);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//

int	 CFragCollArr::SaveAll(const char *fname)

{
	int ret = 0;

	ASSERT(xarr.GetSize() == xnames.GetSize());

	if(!xchanged)
		return 0;

	AP2N("CFragCollArr::SaveAll %s\r\n", fname);

	Dump();

	CFile fp; 
	if(!fp.Open(fname, CFile::modeCreate | CFile::modeWrite))
		{
		AP2N("CFragCollArr::Save - Cannot create file %s\r\n", fname);
		ret = -1;
		return ret;
		}

	CFileException fe; fe.m_strFileName = "file";
			
	//try
		{
		int alen = xnames.GetSize();
		
		for(int loop = 0; loop < alen; loop++)
			{
			CString str = "[";	str += xnames.GetAt(loop);	str += "]\r\n";

			CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);
			ASSERT(pfc->magic == CFragColl_Magic);
			
			AP2N("Saving '%s'", str);

			fp.Write(str, str.GetLength());
			
			pfc->xSave(&fp);

			//CFileException *pfe = new CFileException(true);
			//pfe->m_cause = CFileException::diskFull;

			//fe.m_cause = CFileException::diskFull;
			//throw(&fe);			
 			}
		} 

//	catch (CFileException *fe)
//		{
//		char str[120]; fe->GetErrorMessage(str, 128);
//		fe->ReportError();
//		AP2N("CFileException '%s' %s\r\n", fe->m_strFileName, str);
//		//fe->Delete();
//		}

	fp.Close();

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Add a new user

int	 CFragCollArr::AddSpeaker(const char *name)

{
	CString name2 = name, effname = name;
	
	if(name2 == defname)
		name2 = "";

	if(effname == "")
		effname = defname;

	AP2N("CFragCollArr::AddSpeaker name='%s' effname=%s\r\n", name, effname);

	int ret = 0, alen = xnames.GetSize();

	// Does it exist already?
	for(int loop = 0; loop < alen; loop++)
		{
		CString str = xnames.GetAt(loop);

		if(str == effname)
			{
			ret = -1;
			return ret;
			}
 		}

	CFragColl  *pfc = new CFragColl; ASSERT(pfc);
	pfc->user = effname;

	//////////////////////////////////////////////////////////////////////
	// Create dirs
	
	CString fdirtmp = rootfragdir; fdirtmp += name2;
	support.RepairPath(fdirtmp);

	if(!support.IsDir(fdirtmp))
		{
		AP2N("CFragCollArr::AddSpeaker make frag dir %s\r\n", fdirtmp);

		int res = mkdir(fdirtmp);  //chmod(fdirtmp, _S_IREAD | _S_IWRITE);
		if(res < 0)
			{
			AP2N("CFragCollArr::AddSpeaker -- Cannot make fdir %s\r\n",
				 fdirtmp);

			delete pfc;
			return -1;		
			}
		}

	CString wdirtmp = rootwavdir; wdirtmp += name2;
	support.RepairPath(wdirtmp);

	AP2N("CFragCollArr::AddSpeaker make wav dir %s\r\n", wdirtmp);

	if(!support.IsDir(wdirtmp))
		{
		AP2N("CFragCollArr::AddSpeaker make dir %s\r\n", wdirtmp);

		int res = mkdir(wdirtmp); //chmod(wdirtmp, _S_IREAD | _S_IWRITE);
		if(res < 0)
			{
			AP2N("CFragCollArr::AddSpeaker -- Cannot make wdir %s\r\n",
				 wdirtmp);

			delete pfc;
			return -1;					
			}
		}
	
	xarr.Add(pfc);	ret = xnames.Add(effname); 
		
	xchanged = true;

	//Dump();

	//AP2N("CFragCollArr::AddSpeaker name='%s' wavdir=%s\r\n", name, pfc->wavdir);
	
	return ret;
}

//////////////////////////////////////////////////////////////////////////
//

int	 CFragCollArr::RemoveSpeaker(const char *name)

{
	int ret = 0, alen = xarr.GetSize();

	chdir(rootfragdir);

	for(int loop = 0; loop < alen; loop++)
		{
		CString str = xnames.GetAt(loop);

		if(str.Compare(name) == 0)
			{
			CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);			
			ASSERT(pfc->magic == CFragColl_Magic);

			CString fdir = pfc->GetFragDir(); support.UnRepairPath(fdir);

			pfc->ClearOldFrags(fdir); int rret = rmdir(fdir);

			AP2N("CFragCollArr::RemoveSpeaker %s rm frag dir ret=%d %s\r\n", fdir, rret, 
				strerror(errno));
			
			CString wdir = pfc->GetWavDir(); support.UnRepairPath(wdir);
			pfc->ClearOldWaves(wdir); int wret = rmdir(wdir); 

			AP2N("CFragCollArr::RemoveSpeaker %s rm wav dir ret=%d %s\r\n", wdir, wret,
				strerror(errno));
			
			delete pfc;

			xarr.RemoveAt(loop); xnames.RemoveAt(loop);

			//AP2N("CFragCollArr::Remove at %d (%s)\r\n", loop, str);
			ret = xarr.GetSize();
			xchanged = true;
			break;
			}	
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// NULL if no such user

CFragColl*	 CFragCollArr::GetCollPtr(const char *name)

{
	CString effname = name;

	if(effname == "")
		effname = defname;

	//AP2N("CFragCollArr::Get '%s'\r\n", name);

	ASSERT(xarr.GetSize() == xnames.GetSize());

	CFragColl *ret = NULL;
	int alen = xarr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CString str = xnames.GetAt(loop);

		if(str.Compare(name) == 0)
			{
			ret = (CFragColl*)xarr.GetAt(loop);			
			ASSERT(ret->magic == CFragColl_Magic);
			break;
			}
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int	CFragCollArr::GetSpeakerName(int idx, CString &str)

{
	if(idx < 0 || idx >= xnames.GetSize())
		{
		return -1;
		}

	int ret = 0;

	str = xnames.GetAt(idx);

	return str.GetLength();
}


//////////////////////////////////////////////////////////////////////////

CFragColl*	 CFragCollArr::GetAt(int idx)

{
	CFragColl *ret = NULL;
	
	if(idx >= 0 && idx < xarr.GetSize())
		ret = (CFragColl*)xarr.GetAt(idx);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int	 CFragCollArr::Dump()

{
	int ret = 0;

	ASSERT(xarr.GetSize() == xnames.GetSize());

	CString wavdir  = fragcollarr.rootwavdir;  //wavdir += user;
	CString fragdir = fragcollarr.rootfragdir; //fragdir += user;
	
	int alen = xnames.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString str = xnames.GetAt(loop);
		CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);
		ASSERT(pfc->magic == CFragColl_Magic);
				
		AP2N("'%s' fragdir=%s   wavdir=%s\r\n", str, 
							fragdir + pfc->user, wavdir + pfc->user);

		pfc->DumpFrags();
 		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//

int	CFragCollArr::SetCurrSpeaker(const char *name)

{
	int ret = -1;

	AP2N("CFragCollArr::SetCurrSpeaker %s\r\n", name);

	int alen = xnames.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString str = xnames.GetAt(loop);

		if(str.Compare(name) == 0)
			{
			CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);
			ASSERT(pfc->magic == CFragColl_Magic);

			pfragcoll = pfc;
			xcurridx = ret = loop;
			break;
			}
		}	

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int	CFragCollArr::GetCurrSpeaker(CString &str)

{
	int ret = -1;

	if(xcurridx >= 0 && xcurridx < xnames.GetSize())
		ret = GetSpeakerName(xcurridx, str);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int	CFragCollArr::GetCurrSpeaker()

{
	return xcurridx;
}

//////////////////////////////////////////////////////////////////////////

void    CFragCollArr::SetFragDir(CCHAR *dir)

{
    rootfragdir = dir;
    support.RepairPath(rootfragdir);
}

void    CFragCollArr::SetWaveDir(CCHAR *dir)

{
    rootwavdir = dir;
    support.RepairPath(rootwavdir);
}

//////////////////////////////////////////////////////////////////////////

int	 CFragCollArr::CompileAll()

{
	CString olduser; int ret = -1;

	if(pfragcoll)
		{
		olduser = pfragcoll->user;
		}

	Clear();

	//AP2N("CFragCollArr::Compile %s %s\r\n", rootwavdir, rootfragdir);

	if(!support.IsDir(rootfragdir))
		{
		AP2N("CFragCollArr::Compile no frag dir\r\n");
		return ret;
		}
	if(!support.IsDir(rootwavdir))
		{
		AP2N("CFragCollArr::Compile no wav dir\r\n");
		return ret;
		}

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	if(chdir(rootwavdir) < 0 )
		{
		AP2N("CFragCollArr::Compile Cannot change dir %s\r\n", rootwavdir);

		//CString tmp; 
		//tmp.Format("CFragCollArr::Compile No dir '%s'", rootwavdir);
		return -1;
		}

	// Get default user's files
	int retd = CompileSpeaker("");

	// Iterate directories
	struct _finddata_t c_file;
	long hFile;

	CString wild = "*.*"; int cnt = 0;

	if( (hFile = _findfirst(wild, &c_file )) == -1L )
		goto endd; 
	
	while(true)
        {
		if(c_file.name[0] != '.')
			{
			if(c_file.attrib & _A_SUBDIR)
				{
				//AP2N( " %-12s %.24s  %9ld\r\n",
				//c_file.name, ctime( &c_file.time_write  ), c_file.size );
				
				CompileSpeaker(c_file.name);
				}     		
			}
		// End of dir list
		if( _findnext( hFile, &c_file ) != 0 )
			break;
	
		cnt++;
		}

endd:
	_findclose( hFile );
	chdir(olddir);

	SetCurrSpeaker(olduser);
	
	Dump();

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int	 CFragCollArr::CompileSpeaker(const char *speaker)

{
	int ret = -1;


	// Concept of effspeak
	CString speak = speaker; if(speak == defname) speak = "";	
	CString effspeak = speaker; if(effspeak == "") effspeak = defname;

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	CString wdir(rootwavdir);  wdir += speak; support.RepairPath(wdir);
	CString fdir(rootfragdir); fdir += speak; support.RepairPath(fdir);
 
	AP2N("CFragCollArr::CompileSpeaker %s %s\r\n", wdir, fdir);

	CFragColl *fc = NULL;
	
	fc = GetCollPtr(effspeak);

	if(!fc)
		{
		//AP2N("Speaker does not exist, creating '%s'\r\n", speaker);				
		AddSpeaker(speaker);
		fc = GetCollPtr(effspeak);
		}

 	ASSERT(fc->magic == CFragColl_Magic);

	int	 retf = fc->ParseAllWaves(wdir, fdir, true);
	
	//AP2N("fc->ParseAllWaves ret = %d\r\n", retf);

	int  retx = fc->LoadAllFrags(fdir, false); 

	//AP2N("fc->LoadAllFrags ret = %d\r\n", retx);

	xchanged = true;

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int	 CFragCollArr::StopCompile()

{
	stop = true;

	int alen = xarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);
		ASSERT(pfc->magic == CFragColl_Magic);

		pfc->stop = true;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////

void	CFragCollArr::Clear()

{
	int alen = xarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		//CString str = xnames.GetAt(loop);
		CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);
		ASSERT(pfc->magic == CFragColl_Magic);

		delete pfc;
		}

	xarr.RemoveAll(); xnames.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

void	CFragCollArr::SetChangeFlag(int flag)

{
	xchanged = flag;
}

//////////////////////////////////////////////////////////////////////////

void	CFragCollArr::BuildIdx()

{
	int alen = xarr.GetSize();

	xidx.RemoveAll();

	for(int loop = 0; loop < alen; loop++)
		{
		//CString str = xnames.GetAt(loop);
		CString name = xnames.GetAt(loop);
		CFragColl *pfc = (CFragColl*) xarr.GetAt(loop);
		ASSERT(pfc->magic == CFragColl_Magic);

		//AP2N("%s \r\n", name);		
		}
}

