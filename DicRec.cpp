
/* =====[ DicRec.cpp ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the DicRec.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/18/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "DicRec.h"
#include "mxpad.h"
#include "support.h"

#include "WavfragDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int	CDicRec::changed = 0;
CPtrArray	CDicRec::dicarr;

CDicRec::CDicRec()

{
	magic = CDicRec_Magic;
	name = new CString;
}

CDicRec::~CDicRec()

{
	delete name;
}

//////////////////////////////////////////////////////////////////////////

int CDicRec::Add(const char *str)

{
	arr.Add(str);

	changed = true;

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CDicRec::Find(CPtrArray *parr)

{
	int ret = 0, dlen = parr->GetSize();

	//CString disp;
	//for(int loopd = 0; loopd < min(16, dlen); loopd++)
	//	{
	//	CContain::CResult *ptr = (CContain::CResult *)parr->GetAt(loopd);
	//	AP2N("%3d %6s\t", ptr->val, *ptr->name);
	//	disp += *ptr->name; disp += " ";
 	//	}
	//AP2N("\r\n");
	//AP2N("CDicRec::Find '%s' in '%s'\r\n", disp, *name);
	
	int alen = arr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString  &val = arr.GetAt(loop);
		CStringArray arr3;	Parse(val, &arr3);
	
		int plen = parr->GetSize();
		int skip = 0;

		//for(int skip = 0; skip < plen; skip += 2)
			{
			int cmp = 0;
			
			cmp = Compare(skip, parr, &arr3);

			//if(cmp == 0)
			//	break;

			//AP2N("	    CDicRec::Compare %5d '%s'\r\n", cmp, val.Left(60));
			//ret = max(ret, cmp);			
			ret = max(ret, cmp);			
			}
		//AP2N("	CDicRec::Find %5d '%s'\r\n", ret, val.Left(60));
 		}

	//AP2N("CDicRec::Find %3d '%s' \r\n", ret, *name);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//

int CDicRec::Compare(int skip, CPtrArray *parr, CStringArray *ref)

{
	//P2N("With:\r\n");
	//for(int loop = 0; loop < ref->GetSize(); loop++)
	//	P2N("'%s'  ", ref->GetAt(loop));
	//P2N("\r\n");

	int lenref = ref->GetSize(), lenstr = parr->GetSize();
	int	ret = 0, len = min(lenref, lenstr);
	int  wobble = len / 4;

	if(wobble)
		{
		for(int loop = 0; loop < len; loop++)
			{
			CString &tmp2 = ref->GetAt(loop);

			int ss = max(0, skip + loop - wobble);
			int ee = min(len, skip + loop + wobble);

			for(int loop2 = ss; loop2 < ee; loop2++)
				{				
				//CContain::CResult *tmp = (CContain::CResult *)parr->GetAt(loop2);

				//P2N("tmp1=%s tmp2=%s\r\n", tmp, tmp2);

				//if(*tmp->name == tmp2)
				//	{
				//	ret += tmp->val;
				//	}	
				}			
			}
		}
	return ret;
}

//////////////////////////////////////////////////////////////////////////

//DEL int CDicRec::Compare(CStringArray *ref, CStringArray *str)
//DEL 
//DEL {
//DEL 	int ret = 0, wobble = 20;
//DEL 	
//DEL 	//P2N("With:\r\n");
//DEL 	//for(int loop = 0; loop < ref->GetSize(); loop++)
//DEL 	//	P2N("'%s'  ", ref->GetAt(loop));
//DEL 	//P2N("\r\n");
//DEL 	
//DEL 	//return 0;
//DEL 
//DEL 	int lenref = ref->GetSize(), lenstr = str->GetSize();
//DEL 	int len = min(lenref, lenstr);
//DEL 
//DEL 	if(wobble)
//DEL 		{
//DEL 		for(int loop = 0; loop < len; loop++)
//DEL 			{
//DEL 			CString &tmp = ref->GetAt(loop);
//DEL 
//DEL 			int cmp = 0;
//DEL 			int ss = max(0, loop - wobble);
//DEL 			int ee = min(len, loop + wobble);
//DEL 
//DEL 			for(int loop2 = ss; loop2 < ee; loop2++)
//DEL 				{
//DEL 				CString &tmp2 = str->GetAt(loop2);
//DEL 
//DEL 				//P2N("tmp1=%s tmp2=%s\r\n", tmp, tmp2);
//DEL 
//DEL 				if(tmp == tmp2)
//DEL 					{
//DEL 					cmp = 1;
//DEL 					}	
//DEL 				}
//DEL 			if(cmp) 
//DEL 				ret++;
//DEL 			}
//DEL 		}
//DEL 	else
//DEL 		{
//DEL 		for(int loop = 0; loop < len; loop++)
//DEL 			{
//DEL 			CString &tmp = ref->GetAt(loop);
//DEL 			CString &tmp2 = str->GetAt(loop);
//DEL 
//DEL 			//P2N("tmp=%s tmp2=%s\r\n", tmp, tmp2);
//DEL 
//DEL 			if(tmp == tmp2)
//DEL 				{
//DEL 				ret++;
//DEL 				}
//DEL 			}
//DEL 		}
//DEL 
//DEL 	return ret;
//DEL }

void CDicRec::Dump()

{
	P2N("Name: %s\r\n", *name);
	
	int alen = arr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString  &val = arr.GetAt(loop);
		P2N("%s\r\n\r\n", val);
		}

	P2N("----------------------------\r\n");
}

//////////////////////////////////////////////////////////////////////////

void CDicRec::Serialize(const char *dir)

{
	//P2N("CDicRec::Serialize %s\r\n", *name);

	CFile fp;

	if(fp.Open(dir, CFile::modeCreate | 
			CFile::modeNoTruncate | CFile::modeWrite) == 0)
		{
		P2N("Cannot create file %s\r\n", dir);
		return;
		}

	fp.SeekToEnd();
	fp.Write(*name, name->GetLength()); fp.Write("\r\n", 2);

	int len = arr.GetSize();

	P2N("CDicRec::Serialize saving '%s' %d entries\r\n", *name, len);

	for(int loop = 0; loop < len; loop++)
		{
		CString &str = arr[loop];		
		fp.Write(str, str.GetLength()); fp.Write("\r\n", 2);
		}
	fp.Write("---------\r\n", 11);
		
	fp.Close();
}

//////////////////////////////////////////////////////////////////////////

void CDicRec::LoadDics(const char *dir)

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	AP2N("Loading dics from %s\r\n", dir);

	CFile fp;

	if(fp.Open(dir, CFile::modeRead) == 0)
		{
		AP2N("Cannot open file %s\r\n", dir);
		return;
		}

	int cnt = 0, cnt2 = 0;

	AP2N("CDicRec::LoadDics: ");	
	CString crlf;
		
	while(true)
		{
		CString line, baseline;

		if(!support.ReadLine(fp, baseline, 512))
			break;

		CDicRec *dr = new CDicRec;	ASSERT(dr);
		dicarr.Add(dr);

		*dr->name = baseline;

		//pwnd->m_tl.AddString(baseline);

		for(int loop = 0; loop < 1000; loop++)
			{
			CString line;

			support.ReadLine(fp, line, 4096); 

			cnt2++;

			if(line.Left(2) == "--")
				break;

			//AP2N("Reading line=%s\r\n", line);						
			dr->Add(line);			
			}
		cnt++;
		}

	changed = false;

	//AP2N("Loaded %d dictionary entries %d strings total.\r\n", cnt, cnt2);
}

//////////////////////////////////////////////////////////////////////////

void	CDicRec::Parse(const char *str, CStringArray *strarr)

{
	CString cstr(str);
	Parse(&cstr, strarr);
}

//////////////////////////////////////////////////////////////////////////
// Parse into an array by spaces

void	CDicRec::Parse(CString *pstr, CStringArray *strarr)

{	
	int rescnt = 0, create = true, len = pstr->GetLength();

	for(int loop = 0; loop < len; loop++)
		{
		char cc = pstr->GetAt(loop);

		if(cc == ' ')
			{
			create = true;
			}
		else
			{
			if(create)
				{
				// New entry
				strarr->Add(""); create = false;
				}
			// Append to last
			CString &str = strarr->ElementAt(strarr->GetUpperBound());
			str += cc;
			}
		}	

	// Dump it
	//int alen = strarr->GetSize();
	//for(int loopd = 0; loopd < alen; loopd++)
	//	{
	//	AP2N("'%s'\t", strarr->GetAt(loopd));
 	//	}
	//AP2N("\r\n");
}

//////////////////////////////////////////////////////////////////////////

void	CDicRec::SaveDics(const char *fname)

{
	if(CDicRec::changed)
		{
		P2N("Serialize dicarr to %s\r\n", fname);

		unlink(fname);

		int len2l = CDicRec::dicarr.GetSize();
		for(int loopw = 0; loopw < len2l; loopw++)
			{
			CDicRec *dr = (CDicRec *)dicarr[loopw];
			dr->Serialize(fname);
			}
		}
}

//////////////////////////////////////////////////////////////////////////
// Delete accumulated learn arrays
// Call explicitly at application destruction

void	CDicRec::DelDics()

{
	int lenla = dicarr.GetSize();
	for(int loopla = 0; loopla < lenla; loopla++)
		{
		CDicRec *dr = (CDicRec*)dicarr[loopla];

		ASSERT(dr->magic == CDicRec_Magic);
		delete(dr);
		}
}

//////////////////////////////////////////////////////////////////////////

void CDicRec::Clear()

{
	arr.RemoveAll();
	changed = true;
}

void	CDicRec::RemLast()

{
	int last = arr.GetUpperBound();
	if(last >= 0)
		{
		arr.RemoveAt(arr.GetUpperBound());
		changed = true;
		}
}
