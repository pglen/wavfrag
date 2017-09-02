
/* =====[ Donut.cpp ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the Donut.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  5/6/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "Donut.h"
#include "mxpad.h"
#include "RecItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDonut::CDonut()
{

}

CDonut::~CDonut()
{

}

//////////////////////////////////////////////////////////////////////////


int CDonut::xAlike(CString *s1, CString *s2)

{
	if(*s1 == *s2)
		return 8;

#if 0
	//if(s1->GetAt(0) == s2->GetAt(0))
	//	return 2;

	if(*s1 == "AY" && *s2 == "EY")
		return 2;
	
	if(*s1 == "EY" && *s2 == "AY")
		return 2;
	
	if(s1->GetAt(0) == 'F' && s2->GetAt(0) == 'V')
		return 1;

	if(s1->GetAt(0) == 'V' && s2->GetAt(0) == 'F')
		return 1;
#endif

	return 0;	
}

//////////////////////////////////////////////////////////////////////////
// Parse into an array by spaces

void	CDonut::xParse(CString *pstr, CStringArray *strarr)

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
//

int CDonut::Donut(CString *str1, CString *str2, CIntArr *pval)

{	
	CStringArray arr1, arr2;

	//AP2N("CDonut::Donut '%s'\r\n", *str2);
	xParse(str1, &arr1); xParse(str2, &arr2);
	
	int ret = xDonut3(&arr1, &arr2, pval);
	//int ret = Donut(&arr1, &arr2);
	
	//AP2N("CDonut::Donut %d '%s'\r\n'%s'\r\n", ret, *str1, *str2);
	
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Look at the donut, not the donut hole

int CDonut::xDonut4(CStringArray *sarr, CStringArray *darr)

{
	int ret = 0, match = 0;

	CIntArr arr;

	int dlen = darr->GetSize();

	if(!dlen)
		return 0;
	
	CIntArr	seenarr, consarr, valarr;

	for(int loop = 0; loop < dlen; loop++)
		{
		int mid = 0, divi = 0, ss = INT_MAX, ee = INT_MIN;
		
		CString curr = darr->GetAt(loop);

		int seen = 0;
		// Seen this before?
		for(int loops = 0; loops < loop; loops++)
			{
			if(curr == darr->GetAt(loops))
				{
				//AP2N("backward %s\r\n", darr->GetAt(loop2));
				seen = seenarr.SafeGetAt(loops);
				}
			}

		if(seen)
			AP2N("%s seen=%d\r\n", curr, seen);

		//AP2N("%s  ---  ", curr);

		int alen2 = sarr->GetSize();

		//int start = (loop  * alen2) / alen;
		//int end   = ((loop + 1) * alen2) / alen;
		//start = max(start, 0); end = min(end, alen2);

		int start = seen, end = alen2, prev2 = 0;

		//AP2N("Start=%d end=%d\r\n", start, end);

		int onematch = 0;
		for(int loop2 = start; loop2 < end; loop2++)
			{
			CString curr2 = sarr->GetAt(loop2);

			//AP2N("'%s'  ", curr);

			int al = xAlike(&curr, &curr2);
			if(al > 0)
				{
				// Check for big gap
				if((prev2 != 0) && (loop2 - prev2) > 6)
					{
					AP2N("Big gap %s %d -> %d\r\n", curr, prev2 + 1, loop2);
					seenarr.SetAtGrow(loop, prev2 + 1);
					break;
					}

				prev2 = loop2;

				if(ss > loop2) ss = loop2;
				if(ee < loop2) ee = loop2;

				onematch += al;
				//AP2N("%d  ", loop2);				
				mid += loop2; divi++;
				}			
			}

		// Stop runaways
		if(ss > end) ss = 0;
		if(ee < 0) ee = 0;
		
		//onematch = min(onematch, 100);

		match += onematch;
		//if(divi)
		//	mid /= divi;

		mid = ss + (ee-ss)/2;
		arr.Add(mid);

		//AP2N("mid=%d onematch=%d %s\r\n", mid, onematch, curr);
 		}

	// Search for consecutive entries
	int ccount = 1, prev = 0, alenx = arr.GetSize();
	for(int loopx = 0; loopx < alenx; loopx++)
		{
		int val = arr.GetAt(loopx);
		if(val > prev && val && prev)
			{	
			ccount++;
			}
		prev = val;
 		}

	//arr.DumpAll();

	//AP2N("match=%d ccount=%d\r\n", match, ccount);
 
	// The product of the match and consecutive count
	ret = (match * ccount) / dlen;
	
	return ret;		
}

//////////////////////////////////////////////////////////////////////////
// Array of pointers to CRecItem classes

int CDonut::NewDonut(CPtrArray *recarr, int s2, int e2, CStringArray *darr)

{	
	int diff = 1;

#if 1

	//CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;

	
	//pwnd->m_log.AddString("\r\n");

	int reclen = recarr->GetSize();

	CIntArr	seenarr, consarr, valarr;
	
	s2 = 0; e2 = reclen;
	CString teststr;

	int alen = darr->GetSize();

	for(int loops = 0; loops < alen; loops++)
		seenarr.SetAtGrow(loops, s2);		

	for(int loop = 0; loop < alen; loop++)
		{
		int cnt = 0, divi = 0;
		
		CString curr = darr->GetAt(loop);
		teststr += curr; teststr += " ";

		int seen = 0;
		// Seen this before?
		for(int loop2 = 0; loop2 < loop; loop2++)
			{
			if(curr == darr->GetAt(loop2))
				{
				//AP2N("backward %s\r\n", darr->GetAt(loop2));
				seen = seenarr.SafeGetAt(loop2);
				}
			}

		if(seen)
			AP2N("%s seen=%d\r\n", curr, seen);

		int ratsum = 0, midpos = 0, prev = 0, valsum = 0;
	
		//double part = reclen / alen;
		// Scan proportional;
		//int sss = part * loop; ///reclen *  max(0, loop - 1) / alen;
		//int eee = part * (loop + 1); // reclen *  min(alen, loop + 1) / alen;
		//AP2N("reclen=%d sss=%d eee=%d loop=%d\r\n", reclen, sss, eee, loop);

		for(int loop4 = seen; loop4 < e2; loop4++)
			{
			CRecItem *item = (CRecItem*)recarr->GetAt(loop4);

			//CString tmp;
			//tmp.Format("%6s  (%5d-%02d%%)", *item->pstrx, item->mval, item->rat);
			//AP2N("%s\t", tmp);

			if(*item->pstrx == curr)
				{
				// Check for big gap
				if((prev != 0) && (loop4 - prev) > 6)
					{
					//AP2N("Big gap %s %d %d\r\n", curr, loop, prev + 1);
					seenarr.SetAt(loop, prev + 1);
					break;
					}
				prev = loop4;
				midpos += loop4; cnt++;

				CString tmp2; tmp2.Format(
				"%s loop4=%d mval=%d rat=%d\r\n", curr, loop4, item->mval, item->rat);
				//AP2N("%s", tmp2);
				//pwnd->m_log2.AddString(tmp2);
				
				ratsum += item->rat;
				valsum += item->mval;
				}
			}

		if(cnt)
			midpos /= cnt;

		//if(ratsum)
		consarr.Add(midpos);
		valarr.Add(ratsum);
		//valarr.Add(valsum);
		
		//diff += ratsum;

		//Ap2N(" %d\t", curr, ratsum, midpos);
		//pwnd->m_log.printf("%6s ratsum=%d valsum=%d midpos=%d\r\n", curr, ratsum, valsum, midpos);
		}

	//seenarr.DumpAll("SeenArray");
	
	// Calculate consequtive multipier
	int con = 1, conlen = consarr.GetSize();
	for(int loopc = 1; loopc < conlen; loopc++)
		{
		if(consarr.SafeGetAt(loopc-1) < consarr.GetAt(loopc))
			{
			P2N("cons addedd %d %d\r\n", 
						consarr.GetAt(loopc), valarr.GetAt(loopc));

			diff += valarr.GetAt(loopc-1);
			}	
		else
			{
			diff -= valarr.GetAt(loopc-1);
			}
 		}

	diff += valarr.GetAt(loopc-1);

	// Account for non-matches
	for(int loopd = 0; loopd < conlen; loopd++)
		{
		if(consarr.GetAt(loopd) == 0)
			{
			//diff /= 2;
			}
		}

	//consarr.DumpAll();
	//AP2N("Cons Count %d\r\n", con);

	// Make it frag neutral
	//diff /= alen;
	//AP2N("diff=%d\r\n", diff);
	//AP2N("\r\n%d\t%s\r\n", diff, teststr);

#endif

	return diff;
}

//////////////////////////////////////////////////////////////////////////
// sarr = search array ----  darr = dictionary array
// Search time proportional items in the dictionary  
// Time progression is linear in character space

int CDonut::xDonut2(CStringArray *sarr, CStringArray *darr, CIntArr *pval)

{
	int ret = 0;

	//Dump input for checking:

#if 0
	//AP2N("sarr='");
	//for(int loopd = 0; loopd < sarr->GetSize(); loopd++)
	//	AP2N("%s ", sarr->GetAt(loopd));
	//AP2N("'\r\n");

	//AP2N("darr='");
	//for(int loopd2 = 0; loopd2 < darr->GetSize(); loopd2++)
	//	AP2N("%s ", darr->GetAt(loopd2));
	//AP2N("'\r\n");

	//for(int loopd3 = 0; loopd3 < pval->GetSize(); loopd3++)
	//	AP2N("%d ", pval->GetAt(loopd3));
	//AP2N("'\r\n");
#endif

	ASSERT(sarr->GetSize() == pval->GetSize());

	int dlen = darr->GetSize(), slen = sarr->GetSize();

	// Nothing to do
	if(!dlen || !slen)
		return 0;
	
	float	rat = (float)slen / dlen;
	for(int loop = 0; loop < dlen; loop++)
		{
		CString &ref = darr->GetAt(loop);

		int match = 0;
		int ss = int((loop - 1) * rat), ee = int((loop + 2) * rat);

		ss = max(ss, 0); ee = min(ee, slen);
		
		for(int loop2 = ss; loop2 < ee; loop2 += 1)
			{
			//AP2N("%s\t", sarr->GetAt(loop2));		

			int idx = loop2;	
			idx = min(idx, slen); idx = max(idx, 0);

			if(ref == sarr->GetAt(idx) )
				{
				match += pval->GetAt(loop2);
				}
			else
				{
				match -= 10;			// Penalty for mismatch
				}
			}	

		match /= ee - ss;			// Make it length neutral

		// Accumulate it
		ret += match;

		//AP2N("%d -> %d (of %d) %s match=%d\r\n", ss, ee, slen, ref, match);		
		}
	
	return ret;
}

int CDonut::xDonut3(CStringArray *sarr, CStringArray *darr, CIntArr *pval)

{
	int ret = 0;

	//Dump input for checking:

#if 1
	//AP2N("sarr='");
	//for(int loopd = 0; loopd < sarr->GetSize(); loopd++)
	//	AP2N("%s ", sarr->GetAt(loopd));
	//AP2N("'\r\n");

	//AP2N("darr='");
	//for(int loopd2 = 0; loopd2 < darr->GetSize(); loopd2++)
 	//	AP2N("%s ", darr->GetAt(loopd2));
	//AP2N("'\r\n");

	//for(int loopd3 = 0; loopd3 < pval->GetSize(); loopd3++)
	//	AP2N("%d ", pval->GetAt(loopd3));
	//AP2N("'\r\n");
#endif

	ASSERT(sarr->GetSize() == pval->GetSize());

	int dlen = darr->GetSize(), slen = sarr->GetSize();

	// Nothing to do
	if(!dlen || !slen)
		return 0;
	
	int	ppos = 0;

	for(int loop = 0; loop < dlen; loop++)
		{
		CString &ref = darr->GetAt(loop);
		
		int cnt = 0, pos1 = 0, pos2 = 0;

		for(int loop2 = ppos; loop2 < slen; loop2++)
			{
			CString &ref2 = sarr->GetAt(loop2);

			//AP2N("Dic='%s' Str='%s'\r\n", ref, ref2);

			if(ref == ref2)
				{
				//cnt++; 

				cnt += pval->GetAt(loop2);
				
				if(!pos1) pos2 = pos1 = loop2;
				else pos2 = loop2;
				}
			}

		int pos  = (pos1 + pos2) / 2;

		//AP2N("%s  cnt=%d pos=%d pos1=%d pos2=%d\r\n", 
		//					ref, cnt, pos, pos1, pos2);

		if(pos > ppos)
			{
			ret += cnt;
			ppos = pos;
			}
		else
			{
			ret -= 100;
			}
		}

	//AP2N("ret = %d\r\n", ret);

	return ret;
}