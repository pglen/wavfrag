
/* =====[ Contain.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Contain.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/23/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "mxpad.h"
#include "xrecog.h"
#include "ContColl.h"
#include "Contain.h"

extern  CxRecog		xdllrecog;
extern	CStrColl	dicstrcoll;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContain::CContain()

{
	magic = CContain_Magic;
	name = new CString;	
}

//////////////////////////////////////////////////////////////////////////

CContain::~CContain()

{
	ASSERT(CContain_Magic == magic);	

	xDelAll();

	delete name;
}

//////////////////////////////////////////////////////////////////////////
// Get item

CContain::CContData* CContain::GetAt(int pos)
	
{
	ASSERT(pos >= 0); ASSERT(pos < xcontarr.GetSize());

	CContain::CContData *ptr = NULL;
	ptr = (CContain::CContData*)xcontarr.GetAt(pos);

	ASSERT(ptr->magic == CContData_Magic);

	return ptr;
}

//////////////////////////////////////////////////////////////////////////
// Add recognized entry

void	CContain::Add(CContain::CContData *ppredat)

{
	ASSERT(ppredat->magic == CContData_Magic);
	ASSERT(CContain_Magic == magic);	

	xcontarr.Add(ppredat);
}

//////////////////////////////////////////////////////////////////////////
// Clear data for a fresh start

void CContain::xDelAll()

{
	ASSERT(CContain_Magic == magic);
		
	int alen = xcontarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CContData *val = (CContData *)xcontarr.GetAt(loop);
		delete val;
 		}
	xcontarr.RemoveAll();

	int alen2 = xfiltarr.GetSize();
	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		CContFilt *val2 = (CContFilt *)xfiltarr.GetAt(loop2);
		delete val2;
 		}
	xcontarr.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

void  CContain::Dump()

{
	AP2N("CContain::Dump() '%s' len=%d (str, val, rat) sig -- sig2\r\n", 
													*name, GetSize());

	
	int alen = xcontarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString sumstr;

		CContData *pval = (CContData *)xcontarr.GetAt(loop);
		ASSERT(pval->magic == CContData_Magic);

		int zval  = 0, sval = sig.GetAt(loop);
		int sval2 = sig2.GetAt(loop);
		int flen = pval->frags.GetSize();

		for(int loop2 = 0; loop2 < flen; loop2++)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(loop2);			
			ASSERT(pfr->magic == CFrag_Magic);

			int rat = 0, val = pval->vals.GetAt(loop2);

			if(loop2 < flen - 1)
				{
				int next = pval->vals.GetAt(loop2 + 1);

				if(next)
					rat = 100 * val / pval->vals.GetAt(loop2 + 1);
				}

			if(loop2 == 0) zval = val;

			CString str;
			str.Format("%8s = %3d / %3d  ",  *pfr->name, val, rat);
			
			sumstr += str;
 			}		

		CString tail;
		tail.Format("  %d -- %d  (%d)\r\n", sval, sval2, sval * sval2);
		sumstr += tail;

		AP2N("%s", sumstr);

		//if(xdllrecog._fragrec)
		//	xdllrecog._fragrec(sumstr, sumstr.GetLength());
		}		
	
	//CString sep("---------");

	//if(xdllrecog._fragrec)
	//		xdllrecog._fragrec(sep, sep.GetLength());
		
	AP2N("\r\n");	
}

//////////////////////////////////////////////////////////////////////////

void  CContain::DumpFilter()

{
	int alen = xfiltarr.GetSize();
	
	AP2N("CContain::DumpFilter() '%s' len=%d (str, val, rat)\r\n", *name, alen);

	for(int loop = 0; loop < alen; loop++)
		{
		CContFilt *pval = (CContFilt *)xfiltarr.GetAt(loop);
		ASSERT(pval->magic == CContFilt_Magic);

		int flen = pval->snames.GetSize();
		for(int loop2 = 0; loop2 < flen; loop2++)
			{
			CString name = pval->snames.GetAt(loop2);

			int rat = 0, val = pval->vals.GetAt(loop2);

			if(loop2 < flen - 1)
				{
				int next = pval->vals.GetAt(loop2 + 1);

				if(next)
					rat = 100 * val / pval->vals.GetAt(loop2 + 1);
				}

			AP2N("%8s = %3d / %3d  ",  name, val, rat);
 			}
		AP2N("\r\n");
		}		

	AP2N("\r\n");	
}

//////////////////////////////////////////////////////////////////////////

CString  CContain::Dump2Str()

{
	CString str, tmp;
	
	int alen = xcontarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString sumstr;

		CContData *pval = (CContData *)xcontarr.GetAt(loop);
		ASSERT(pval->magic == CContData_Magic);

		int zval  = 0, sval = sig.GetAt(loop);
		int sval2 = sig2.GetAt(loop);
		int flen = pval->frags.GetSize();

		for(int loop2 = 0; loop2 < flen; loop2++)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(loop2);			
			ASSERT(pfr->magic == CFrag_Magic);

			int rat = 0, val = pval->vals.GetAt(loop2);

			if(loop2 < flen - 1)
				{
				int next = pval->vals.GetAt(loop2 + 1);

				if(next)
					rat = 100 * val / pval->vals.GetAt(loop2 + 1);
				}

			if(loop2 == 0) zval = val;

			CString str;
			str.Format("%8s = %3d / %3d  ",  *pfr->name, val, rat);
			
			sumstr += str;
 			}		

		CString tail;
		tail.Format("  %d -- %d  (%d)\r\n", sval, sval2, sval * sval2);
		sumstr += tail;

		if(xdllrecog._fragrec2) 
			{
			xdllrecog._fragrec2(sumstr, sumstr.GetLength());
			}

		str +=  sumstr;
		}		

	CString CRLF = "\r\n";
	if(xdllrecog._fragrec2) 
		{
		xdllrecog._fragrec2(CRLF, CRLF.GetLength());
		}

	//AP2N("str=%s\r\n", str);
	return str;
}

//////////////////////////////////////////////////////////////////////////
// Weed out less than half powers

void CContain::Weed()

{
	int mxx2 = 0, mxv2 = 0, alen2 = xcontarr.GetSize();

	if(alen2 == 0)
		return;

#if 0
	// Draw Value Curve
	CIntArr arr;
	for(int loopv = 0; loopv < alen2; loopv++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loopv);

		//arr.Add(pval->val);
		arr.Add(pval->sum);
		//AP2N("%3d %6s\t", pval->val, *pval->str);
		}		

	arr.Smooth(4);		// Factor determined experimentally

	//if(xdllrecog._plotrec)
	//	{
	//	xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 0);
	//	xdllrecog._plotrec(NULL, 0, 0);
	//	}	

	int	px, pv, pv2; arr.FindMax(&px, &pv);  
	
	// Assume dynamic range
	//pv2 = pv / 10;
	
	// or ... Force constant value
	pv2 = 5000;

	// To the left
	for(int loop1 = px; loop1 >= 0; loop1--)
		{		
		if(pv2 > arr[loop1])
			break;
 		}
	// To te right
	for(int loop2 = px; loop2 < alen2; loop2++)
		{
		if(pv2 > arr[loop2])
			break;
 		}
	int sss = max(0, loop1), eee = min(alen2, loop2);

	//AP2N("CContain::Weed sss=%d sss=%d alen2=%d\r\n", sss, eee, alen2);

	CPtrArray tmp;

	// Create new arr within bounds
	for(int loop4 = 0; loop4 < alen2; loop4++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loop4);
		
		if(loop4 >= sss && loop4 <= eee)
			{
			tmp.Add(pval);
			}	
		else
			{
			delete pval;
			}
		}

	xcontarr.RemoveAll(); xcontarr.Copy(tmp);

	len = xcontarr.GetSize();

#endif
}
		
//////////////////////////////////////////////////////////////////////////

CString	CContain::GetConcatStrx()

{
	CString str;

	int alen = xcontarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loop);
		ASSERT(pval->magic == CContData_Magic);

		int flen = pval->frags.GetSize();
		flen = MIN(flen, 1);
		for(int loop2 = 0; loop2 < flen; loop2++)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(loop2);			
			ASSERT(pfr->magic == CFrag_Magic);

			int val = pval->vals.GetAt(loop2);

			str += *pfr->shortname;
			str += " ";
 			}
		}		
	
	return str;
}

//////////////////////////////////////////////////////////////////////////

CString	CContain::GetConcatStrf()

{
	CString str;

	int alen = xfiltarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CContFilt *pval = (CContFilt *)xfiltarr.GetAt(loop);
		ASSERT(pval->magic == CContFilt_Magic);

		int flen = pval->snames.GetSize();
		flen = MIN(flen, 1);
		for(int loop2 = 0; loop2 < flen; loop2++)
			{			
			int val = pval->vals.GetAt(loop2);

			str += pval->snames.GetAt(loop2);
			str += " ";
 			}
		}		
	return str;
}

//////////////////////////////////////////////////////////////////////////

void CContain::WeedNX()

{
	int alen = xcontarr.GetSize();

	CPtrArray tmpa;

	for(int loop = 0; loop < alen; loop++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loop);
		ASSERT(pval->magic == CContData_Magic);

		int flen = pval->frags.GetSize();
		if(flen)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(0);			
			ASSERT(pfr->magic == CFrag_Magic);
		
			//AP2N("%-6s -> %-4d     ",  *pfr->name, val);

			if(*pfr->shortname  != "nx")			
				{
				tmpa.Add(pval);
				}
			else
				{
				delete pval;
				}
			}
		}	
		
	// Commit
	xcontarr.RemoveAll(); xcontarr.Copy(tmpa);
}

//////////////////////////////////////////////////////////////////////////

void CContain::WeedWeak()

{
	int alen = xcontarr.GetSize();

	CPtrArray tmpa;

	// Create sum 
	int sum = 0, cnt = 0;
	for(int loops = 0; loops < alen; loops++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loops);
		ASSERT(pval->magic == CContData_Magic);

		int flen = pval->frags.GetSize();
		if(flen)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(0);			
			ASSERT(pfr->magic == CFrag_Magic);
			
			sum +=  pval->vals.GetAt(0);
			cnt++;
			//AP2N("%-6s -> %-4d     ",  *pfr->name, val);
			}
		}

	if(cnt)
		sum /= cnt ;

	AP2N("CContain::WeedWeak sum = %d\r\n", sum);

	for(int loop = 0; loop < alen; loop++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loop);
		ASSERT(pval->magic == CContData_Magic);

		int flen = pval->frags.GetSize();
		if(flen)
			{			
			if(pval->vals.GetAt(0) > sum)
				{
				tmpa.Add(pval);
				}
			else
				{
				delete pval;
				}
			}
		}	
		
	// Commit
	xcontarr.RemoveAll(); xcontarr.Copy(tmpa);
}

//////////////////////////////////////////////////////////////////////////
// Delete all zero entries

void CContain::WeedNul()

{
	CPtrArray tmpa;

	int alen = xcontarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CContData *pval = GetAt(loop);

		if(pval->vals.GetSize() > 0)
			{
			if(pval->vals.GetAt(0) > 0)
				{
				tmpa.Add(pval);
				}
			else
				{
				delete pval;	
				}
			}
		}

	// Commit
	xcontarr.RemoveAll(); xcontarr.Copy(tmpa);
}
		
//////////////////////////////////////////////////////////////////////////

void CContain::WeedEnds(int tresh)

{
	int mxx2 = 0, mxv2 = 0, alen2 = GetSize();

	if(alen2 == 0)
		return;

	// Draw Value Curve
	CIntArrRec arr;

	for(int loopv = 0; loopv < alen2; loopv++)
		{		
		int val = sig.GetAt(loopv); 
		int val2 = sig2.GetAt(loopv);

		arr.Add(val * val2);
		}		

	arr.Smooth(1);		// Factor determined experimentally

	//if(xdllrecog._plotrec)
	//	{
	//	xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 3);
	//	xdllrecog._plotrec(NULL, 0, 3);
	//	}	

	// Find max value
	int xxx, vvv; arr.FindMax(&xxx, &vvv);

	// Dynamic or ... force constant value
	if(tresh == 0)
		{
		tresh = vvv / 10;
		}

	//AP2N("CContain::WeedEnds xxx=%d vvv=%d (%d)\r\n", xxx, vvv, tresh);

	// To the beginning
	for(int loop2 = xxx; loop2 >= 0; loop2--)
		{		
		if(tresh > arr[loop2])
			break;
 		}

	// Do the end
	for(int loop3 = xxx; loop3 < alen2; loop3++)
		{
		if(tresh > arr[loop3])
			break;
 		}
	
	int sss = MAX(0, loop2), eee = MIN(alen2, loop3);

	//AP2N("CContain::WeedEnds sss=%d eee=%d alen2=%d\r\n", sss, eee, alen2);

	CPtrArray tmp;

	// Weed sigs too
	sig.RemoveAt(eee, sig.GetSize() - eee); sig.RemoveAt(0, sss);
	sig2.RemoveAt(eee, sig2.GetSize() - eee); sig2.RemoveAt(0, sss);

	// Create new arr within bounds, discard not needed ones
	for(int loop4 = 0; loop4 < alen2; loop4++)
		{
		CContData *pval = (CContData*)xcontarr.GetAt(loop4);
		
		if(loop4 >= sss && loop4 <= eee)
			{
			tmp.Add(pval);
			}	
		else
			{
			delete pval;
			}
		}

	// Remove and commit
	xcontarr.RemoveAll(); xcontarr.Copy(tmp);
}

//////////////////////////////////////////////////////////////////////////

CContain::CContData::CContData()

{
	magic = CContData_Magic;
	outlim = 0;
}

//////////////////////////////////////////////////////////////////////////

CContain::CContData::~CContData()

{
	ASSERT(magic == CContData_Magic);
	ASSERT(vals.magic == CIntArr_Magic);
	ASSERT(idxs.magic == CIntArr_Magic);

	// Cannot check if after frag release
#if 0
	// Do not free frags ... just check it
	int alen = frags.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CFrag *pfr = (CFrag*)frags.GetAt(loop);

		ASSERT(pfr->magic == CFrag_Magic);
 		}
#endif

}

//////////////////////////////////////////////////////////////////////////

void CContain::xConvStr(CString &xname)

{
	int idxx = xname.FindOneOf("1234567890-");

	if(idxx >= 0)
		xname = xname.Left(idxx);
	
	xname.MakeLower();
}


//////////////////////////////////////////////////////////////////////////
// Scan for local max

CString CContain::Scan(int start)

{
	CString maxstr; CIntArrRec arr;

	int contlen = GetSize(); if(!contlen) return "";
	
	for(int loopx = 0; loopx < contlen; loopx++)
		{
		CContData *pval =  GetAt(loopx);
		int flen = pval->frags.GetSize();		
	
		for(int loop2 = 0; loop2 < MIN(4, flen); loop2++)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(loop2);			
			ASSERT(pfr->magic == CFrag_Magic);

			int hit = pval->vals.GetAt(loop2);
	
			AP2N("%5s %4d  ", *pfr->name, hit);

			if(loop2 == 0)
				arr.Add(hit);			
			}
		AP2N("\r\n");
		}

	AP2N("\r\n");

	arr.Smooth(4);

	//xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 1);
	//xdllrecog._plotrec(0, 0, 1);

	ASSERT(arr.GetSize() == contlen);

	CIntArrRec xx, vv;	arr.TurnArr(&xx, &vv, true);

	xx.DumpAll("xx");

	int wobble = 3;

	for(int loop3 = 0; loop3 < xx.GetSize(); loop3++)
		{
		int idx = xx.GetAt(loop3);

		int ss = MAX(0, idx - wobble);
		int ee = MIN(contlen, idx + wobble);

		//CString strx = xWalk(ss, ee);		
		//maxstr += strx + " ";		

#if 0
		CContData *pval =  GetAt(idx);
	
		if(pval->vals.GetSize() > 0)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(0);			
			ASSERT(pfr->magic == CFrag_Magic);

			int hit = pval->vals.GetAt(0);

			AP2N("%5s %4d  ", *pfr->name, hit);
			}
#endif

		}
	AP2N("\r\n");
	

	//AP2N("%s\r\n", maxstr);

	return maxstr;
}

//////////////////////////////////////////////////////////////////////////
// Fiter avarages over spans of time

CString CContain::Filter()

{
	CString maxstr;	

	int contlen = GetSize(); if(!contlen) return "";

	int step = 1, wobble = 2;

	for(int loopx = 0; loopx < contlen; loopx++)
		{
		int ss = MAX(0, loopx - wobble);
		int ee = MIN(contlen, loopx + wobble);

		CContFilt *ptr = new CContFilt;
		CString strx = xFilter(ss, ee, ptr);		

		// Apply weighing factors
		//int old = ptr->vals.GetAt(0);
		//old *= sig.GetAt(loopx);	old /= 255;
		//ptr->vals.SetAt(0, old);
		
		xfiltarr.Add(ptr);

		maxstr += strx + " ";				
		}

	//AP2N("%s\r\n", maxstr);

	return maxstr;
}

//////////////////////////////////////////////////////////////////////////
//

CString CContain::xFilter(int start, int endd, CContain::CContFilt *pdata)

{
	//AP2N("CContain::xWalk %d %d\r\n", start, endd);

	CString str; CStringArray strarr; CIntArr iarr;

	int alen = xcontarr.GetSize(); 
	
	if(endd == -1) endd = alen;
	
	start = MAX(start, 0);	endd = MIN(endd, alen);

	for(int loop = start; loop < endd; loop++)
		{
		CContData *pval = (CContData *)xcontarr.GetAt(loop);

		ASSERT(pval->magic == CContData_Magic);

		int flen = pval->frags.GetSize();
		
		//flen = MIN(flen, 4);

		for(int loop2 = 0; loop2 < flen; loop2++)
			{
			CFrag *pfr = (CFrag*)pval->frags.GetAt(loop2);			
			ASSERT(pfr->magic == CFrag_Magic);

			int	idx = xUniqueIdx(pfr->shortname, &strarr);
			int val = pval->vals.GetAt(loop2);
			
			iarr.AddToVal(idx, val);
 			}
		}		

	//iarr.DumpAll("iarr");

	CIntArr siarr; iarr.Sort(&siarr);

	int alens = siarr.GetSize(); alens = MIN(alens, 4);

	for(int loops = 0; loops < alens; loops++)
		{
		int idx = siarr.GetAt(loops);

		int val = iarr.GetAt(idx);
		
		CString strx = strarr.GetAt(idx);	
		pdata->snames.Add(strx); pdata->vals.Add(val);
	
		//AP2N("%5s %4d   ", strx, val);

		if(loops == 0)
			str = strx;
 		}

	//AP2N("\r\n");

	return str;
}

//////////////////////////////////////////////////////////////////////////

int	CContain::xIsUnique(CString *str, CStringArray *pstrarr)

{
	int tmpidx = 0, found = 0, alens = pstrarr->GetSize();
		
	for(int loops = 0; loops < alens; loops++)
		{
		//AP2N("CContain::xIsUnique %s  %s\r\n", *str, pstrarr->GetAt(loops));
	
		if(pstrarr->GetAt(loops) == *str)
			{
			tmpidx = loops; found = true; break;
			}
		}

	if(!found)
		tmpidx = pstrarr->Add(*str);

	return !found;
}

//////////////////////////////////////////////////////////////////////////

int	CContain::xUniqueIdx(CString *str, CStringArray *pstrarr)

{
	int tmpidx = 0, found = 0, alens = pstrarr->GetSize();
		
	for(int loops = 0; loops < alens; loops++)
		{
		
		if(pstrarr->GetAt(loops) == *str)
			{
			//AP2N("CContain::xUniqueIdx %s  %s\r\n", *str, pstrarr->GetAt(loops));
			tmpidx = loops; found = true; break;
			}
		}

	if(!found)
		tmpidx = pstrarr->Add(*str);

	return tmpidx;
}

//////////////////////////////////////////////////////////////////////////
// Create a copy of the container(s)  (obsolete)
// 

void CContain::Copy(CContain *ptr)

{
	ASSERT(true);
}
