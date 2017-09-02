
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
//

int CDicRec::CmpDicRec(CContain *pcont)

{
	int ret = 0;
	
	//AP2N("CDicRec::CmpDicRec(CContDataain *pcont) %s  ", *xname);
	int rlen = xptrarr.GetSize();

	// Scan thru the whole ref array
	for(int loop = 0; loop < rlen; loop++)
		{
		CStringArray  *pval = (CStringArray*)xptrarr.GetAt(loop);
		
		int diff = xCompare(0, pcont, pval);

		ret = MAX(diff, ret);
		}

	//AP2N("CDicRec::CmpDicRec(CContData *pcont) %s  %d\r\n", *xname, ret);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Compare filtered entry

//DEL int CDicRec::CmpDicRec2(CContain *pcont)
//DEL 
//DEL {
//DEL 	int ret = 0;
//DEL 	
//DEL 	//AP2N("CDicRec::CmpDicRec2(CContDataain *pcont) %s  ", *xname);
//DEL 
//DEL 	int rlen = xptrarr.GetSize();
//DEL 
//DEL 	// Scan thru the whole ref array
//DEL 	for(int loop = 0; loop < rlen; loop++)
//DEL 		{
//DEL 		CStringArray  *pval = (CStringArray*)xptrarr.GetAt(loop);
//DEL 		
//DEL 		int diff = xCompare2(0, pcont, pval);
//DEL 
//DEL 		ret = MAX(diff, ret);
//DEL 		}
//DEL 
//DEL 	//AP2N("CDicRec::CmpDicRec(CContData *pcont) %s  %d\r\n", *xname, ret);
//DEL 
//DEL 	return ret;
//DEL }

//////////////////////////////////////////////////////////////////////////

void CDicRec::Dump()

{
	AP2N("'%s':\r\n", *xname);
	
	int alen = xptrarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CStringArray  *pval = (CStringArray*)xptrarr.GetAt(loop);
		
		CString tmp = _ShowArr(pval);
		
		AP2N("'%s' --  ", tmp);
		}

	AP2N("\r\n");
}

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

//////////////////////////////////////////////////////////////////////////
// Scan the 

int CDicRec::xCompare(int skip, CContain *parr, CStringArray *ref)

{
	int  ret = 1, rlen = ref->GetSize();
	int  plen = parr->GetData()->GetSize();

	int step = plen / rlen, halfstep = step / 2;

	//AP2N("    CDicRec::xCompare3 %s\r\n", _ShowArr(ref));

	//AP2N("    rlen=%d plen-%d step=%d half=%d\r\n", rlen, plen, step, halfstep);
	//AP2N("'");

	// Scan thru the whole ref array
	for(int loop = 0; loop < rlen; loop++)
		{
		int part = 1;
		CString	&rr = ref->GetAt(loop);

		int ss = loop * step, ee = (loop + 1) * step;

		//AP2N("     %s   ss=%d ee=%d\r\n", rr, ss, ee);
		//if(loop > 0) AP2N(" ");	AP2N("%s", rr);

		for(int loop2 = ss; loop2 < ee; loop2++)
			{
			CContain::CContData *pval = (CContain::CContData *)parr->GetData()->GetAt(loop2);

			int match = 0, flen = pval->frags.GetSize();
			
			flen = MIN(1, flen);

			for(int loop3 = 0; loop3 < flen; loop3++)
				{
				CFrag *pfr = (CFrag*)pval->frags.GetAt(loop3);
				int val = pval->vals.GetAt(loop3);
					
				if(*pfr->shortname == rr)
					{
					//AP2N("        %s  %d\r\n", *pfr->shortname, val);
					match += val;
					//part = MAX(part, pval->val);
					//match = true;
					//break;
					}
				else
					{
					//match -= val / 4;
					}
				}
			//match = MIN(match, 800);
			part += match;
			//if(!match)
			//	part = 1 - part;			
			}
		//ret += part;
		ret *= part;
		}

	ret /= rlen;

	//AP2N("        %4d -> '%s'\r\n", ret, _ShowArr(ref));

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Scan the 

//DEL int CDicRec::xCompare2(int skip, CContain *parr, CStringArray *ref)
//DEL 
//DEL {
//DEL 	int  ret = 1, rlen = ref->GetSize();
//DEL 	int  plen = parr->GetFiltData()->GetSize();
//DEL 
//DEL 	int step = plen / rlen, halfstep = step / 2;
//DEL 
//DEL 	//AP2N("    CDicRec::xCompare2 %s\r\n", _ShowArr(ref));
//DEL 
//DEL 	//AP2N("    rlen=%d plen-%d step=%d half=%d\r\n", rlen, plen, step, halfstep);
//DEL 	//AP2N("'");
//DEL 
//DEL 	// Scan thru the whole ref array
//DEL 	for(int loop = 0; loop < rlen; loop++)
//DEL 		{
//DEL 		int part = 1;
//DEL 		CString	&refstr = ref->GetAt(loop);
//DEL 
//DEL 		int ss = loop * step, ee = (loop + 1) * step;
//DEL 		ss -= halfstep; ee += halfstep;
//DEL 		ss = MAX(ss, 0); ee = MIN(ee, rlen);
//DEL 
//DEL 		//AP2N("     %s   ss=%d ee=%d\r\n", rr, ss, ee);
//DEL 		//if(loop > 0) AP2N(" ");	AP2N("%s", rr);
//DEL 
//DEL 		for(int loop2 = ss; loop2 < ee; loop2++)
//DEL 			{
//DEL 			CContain::CContFilt *pfilt = (CContain::CContFilt *)parr->GetFiltData()->GetAt(loop2);
//DEL 
//DEL 			int match = 0, flen = pfilt->vals.GetSize();
//DEL 			
//DEL 			flen = MIN(1, flen);
//DEL 
//DEL 			for(int loop3 = 0; loop3 < flen; loop3++)
//DEL 				{
//DEL 				CString str = pfilt->snames.GetAt(loop3);
//DEL 				
//DEL 				if(str == refstr)
//DEL 					{
//DEL 					int val = pfilt->vals.GetAt(loop3);
//DEL 					//AP2N("        %s  %d\r\n", str, val);
//DEL 					match += val;
//DEL 					//part = MAX(part, pval->val);
//DEL 					//match = true;
//DEL 					//break;
//DEL 					}
//DEL 				else
//DEL 					{
//DEL 					//match -= val / 4;
//DEL 					}
//DEL 				}
//DEL 			part += match;
//DEL 			//if(!match)
//DEL 			//	part = 1 - part;			
//DEL 			}
//DEL 		//part = MIN(part, 4000);
//DEL 		ret *= part;
//DEL 		}
//DEL 
//DEL 	//ret /= rlen;
//DEL 
//DEL 	//AP2N("        %4d -> '%s'\r\n", ret, _ShowArr(ref));
//DEL 
//DEL 	return ret;
//DEL }
