
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
#include "DicRec.h"

#include "xrecog.h"

#include "wflib.h"

#include "IntArr.h"
#include "mxpad.h"
#include "support.h"

extern	CxRecog			xdllrecog;

#undef P2N

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// Expect the dic entry name as a constructor

CDicRec::CDicRec(const char *str)

{
	magic = CDicRec_Magic;

	//AP2N("CDicRec::CDicRec - %s\r\n", str);

	xname = new CString;		ASSERT(xname);	
	//xarr = new CStringArray;	ASSERT(xarr);

	*xname = str;
}

CDicRec::~CDicRec()

{
	delete xname; 
	Clear();
}

//////////////////////////////////////////////////////////////////////////
// Add a parsed line to the string collection 

int CDicRec::Add(const char *str)

{
	//AP2N("CDicRec::Add - Adding string %s\r\n", str);

	CString tmp(str);	tmp.TrimLeft(); tmp.TrimRight();

	CStringArray *pstrarr = new CStringArray;

	_Parse(&tmp, pstrarr);

	xptrarr.Add(pstrarr);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Compare this array

int CDicRec::CmpDicRec(CStringArray *pstrarr)

{
	//AP2N("CDicRec::CmpDicRec %s => ", *xname);

	int ret = 0;
	
	//CString xxx = _ShowArr(pstrarr); xxx = xxx.Left(64); xxx += " ..."; 
	//AP2N("CDicRec Compare '%s' \r\n", xxx);

	int alen = xptrarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CStringArray  *pval = (CStringArray*)xptrarr.GetAt(loop);
		
		int diff = xCompare2(0, pstrarr, pval);

		ret = MAX(diff, ret);

		// Show string
		//CString tmp = _ShowArr(pval);
		//AP2N("%s --   ", tmp);

		//break;
		}

	//AP2N("\r\n");

	return ret;
}

//////////////////////////////////////////////////////////////////////////
//

int CDicRec::xCompare(int skip, CStringArray *parr, CStringArray *ref)

{
	int  ret = 1, rlen = ref->GetSize(), alen = parr->GetSize();

	//AP2N("    With: ");
	//for(int loopd = 0; loopd < rlen; loopd++)
	//	AP2N("'%s'  ", ref->GetAt(loopd));
	//AP2N("\r\n");

	int scan = 0, scanb = alen / rlen, oldmxx = 0;

	// Scan thru the whole ref array
	for(int loop = 0; loop < rlen; loop++)
		{
		int part = 0, dist = 0, start = 0, end = 0, middle = 0;
		CString	&rr = ref->GetAt(loop);
		
		CIntArr dista;	
		dista.SetSize(scan);   // Start the array on offset

		// Scan the unknown
		for(int loop2 = scan; loop2 < scanb * (loop + 1); loop2++)
			{
			CString	&ss = parr->GetAt(loop2);

			if(rr == ss)
				{
				part++;
				}	

			// Estabilish running average
			dista.Add(100 * part / (loop2 + 1));			
			}

		//if(xdllrecog._plotrec)
		//	{
		//	xdllrecog._plotrec(dista.GetData(), dista.GetSize(), 1);
		//	xdllrecog._plotrec(NULL, 0, 1);
		//	}	

		//CIntArr xarr, varr; dista.TurnArr(&xarr, &varr);
		//xarr.DumpAll("xarr");

		int mxx, mxv; dista.FindMax(&mxx, &mxv);

		//AP2N("%s => part=%d mxx=%d scan=%d scanb=%d  len=%d  ", 
		//					rr, part, mxx, scan, scanb * (loop + 1), alen);

		//part = MIN(part, 12);
			
		// Consecutive match in the timeline
		if(mxx >= oldmxx)
			{
			//ret *= MIN(part, 12);		
			//ret *= part + 1;
			ret += part ;
			}
		else 
			{
			//ret -= part + 1; // back off on mismatch
			ret = 0;	// Reset on mismatch
			goto endd;
			}
		scan = mxx;
		}
	
endd:
	ret /= rlen;

	AP2N("%3d - %s\r\n", ret, _ShowArr(ref));

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int CDicRec::xCompare2(int skip, CStringArray *parr, CStringArray *ref)

{
	int  ret = 1, rlen = ref->GetSize(), alen = parr->GetSize();
	CString tmpx;

	//AP2N("CDicRec::xCompare2  With: ");

	//if(rlen < 1)
	//	return 0;

	int step = (alen << 7) / rlen;
	int halfstep = (step) >> 7;

	//AP2N("step=%d ", step);

	// Scan thru the whole ref array
	for(int loop = 0; loop < rlen; loop++)
		{
		int part = 0;
		CString	&rr = ref->GetAt(loop);
				
		// Scan the portion of the unkown
		int ss = ( loop * step) >> 7;  
		int ee = ( (loop + 1) * step) >> 7;
	
		// Extend by half a step
		 ss -= halfstep; ee += halfstep;

		// Contain to array
		ss = MAX(0, ss);	ee = MIN(ee, alen - 1);

		CString tmp; 
		tmp.Format("loop=%d ss=%d ee=%d ", loop, ss, ee);
		tmpx += tmp;

		for(int loop2 = ss; loop2 < ee; loop2++)
			{
			CString	&ss = parr->GetAt(loop2);

			if(rr == ss)
				{
				part++;
				}	
			}
		part = MIN(part, 4);	// Limit participation
		ret *= part;
		}
		
	if(ret)
		{
		AP2N("%s", tmpx);
		AP2N("%3d - %s\r\n", ret, _ShowArr(ref));
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////

void CDicRec::Dump()

{
	AP2N("%s ->", *xname);
	
	int alen = xptrarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CStringArray  *pval = (CStringArray*)xptrarr.GetAt(loop);
		
		CString tmp = _ShowArr(pval);
		
		AP2N("%s --  ", tmp);
		}

	AP2N("\r\n");
}

//////////////////////////////////////////////////////////////////////////

//DEL void CDicRec::Serialize(const char *dir)
//DEL 
//DEL {
//DEL #if 0
//DEL 	//AP2N("CDicRec::Serialize %s\r\n", *name);
//DEL 
//DEL 	CFile fp;
//DEL 
//DEL 	if(fp.Open(dir, CFile::modeCreate | 
//DEL 			CFile::modeNoTruncate | CFile::modeWrite) == 0)
//DEL 		{
//DEL 		AP2N("Cannot create file %s\r\n", dir);
//DEL 		return;
//DEL 		}
//DEL 
//DEL 	fp.SeekToEnd();
//DEL 	fp.Write(*xname, xname->GetLength()); fp.Write("\r\n", 2);
//DEL 
//DEL 	int len = xarr->GetSize();
//DEL 
//DEL 	AP2N("CDicRec::Serialize saving '%s' %d entries\r\n", *xname, len);
//DEL 
//DEL 	for(int loop = 0; loop < len; loop++)
//DEL 		{
//DEL 		CString &str = xarr->GetAt(loop);		
//DEL 		fp.Write(str, str.GetLength()); fp.Write("\r\n", 2);
//DEL 		}
//DEL 	fp.Write("---------\r\n", 11);
//DEL 		
//DEL 	fp.Close();
//DEL 
//DEL #endif
//DEL }

//////////////////////////////////////////////////////////////////////////

CString	CDicRec::_ShowArr(CStringArray *pstrarr)

{
	CString ret;

	int alen = pstrarr->GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CString &str = pstrarr->GetAt(loop);
		ret +=  str; ret += " ";
		}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Parse into an array by spaces

void	CDicRec::_Parse(CString *pstr, CStringArray *strarr)

{	
	//AP2N("CDicRec::xParse '%s'  ", *pstr);

	int rescnt = 0, create = true, len = pstr->GetLength();

	// Walk char by char
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
				// Add new entry
				strarr->Add(""); create = false;
				}
			// Append to last entry to complete str
			CString &str = strarr->ElementAt(strarr->GetUpperBound());
			str += cc;
			}
		}	

	//////////////////////////////////////////////////////////////////////
	// Dump it to check parse correctness

	//int alen = strarr->GetSize();
	//for(int loopd = 0; loopd < alen; loopd++)
	//	{
	//	AP2N("'%s'\t", strarr->GetAt(loopd));
 	//	}
	//AP2N("\r\n");
}

//////////////////////////////////////////////////////////////////////////

void CDicRec::Clear()

{
	int alen = xptrarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CStringArray *val = (CStringArray*)xptrarr.GetAt(loop);
		delete val;
 		}
	xptrarr.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

CString & CDicRec::GetName()

{
	return *xname;
}
