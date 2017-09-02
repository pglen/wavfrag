// Smooth.cpp: implementation of the CSmooth class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wflib.h"
#include "Smooth.h"
#include "support.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSmooth::CSmooth()
{

}

CSmooth::~CSmooth()
{

}

//////////////////////////////////////////////////////////////////////////
// Horizontal smooth it

void	CSmooth::HorSmooth(CPtrArray *parr, int passes)

{	
	int alen = parr->GetSize();

	for (int loophsm2 = 0; loophsm2 < passes; loophsm2++)
		{
		for(int loophsm = 1; loophsm < alen - 1; loophsm++)
			{
			CIntArr *tmp1 = (CIntArr *)parr->GetAt(loophsm - 1);
			CIntArr *tmp2 = (CIntArr *)parr->GetAt(loophsm);
			CIntArr *tmp3 = (CIntArr *)parr->GetAt(loophsm + 1);

			int slen = tmp1->GetSize(); 
			int slen2 = tmp2->GetSize(); slen = MIN(slen, slen2);
			int slen3 = tmp3->GetSize(); slen = MIN(slen, slen3);

			for(int loops = 0; loops < slen; loops++)
				{
				int val1 = tmp1->GetAt(loops);
 				int val2 = tmp2->GetAt(loops);
 				int val3 = tmp3->GetAt(loops);
 				
				tmp2->SetAt(loops, (val1 + val2 + val3) / 3);
 				}
			}
		}
}

//////////////////////////////////////////////////////////////////////////

void	CSmooth::RangeSmooth(CPtrArray *parr, int passes, int start, int endd)

{
	int alen = parr->GetSize();

	//AP2N("CAnalProc::RangeSmooth\r\n");

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopb);

		int nlen = tmp->GetSize();

		if(nlen <= 2)
			{
			//AP2N("CAnalProc::RangeSmooth - empty array\r\n");
			continue;
			}

		// Contain it to reasonable defaults
		start = MIN(start, nlen - 1); endd = MIN(endd, nlen - 1);
		start = MAX(start, 1);  endd = MAX(start, endd);

		for(int loop3 = 0; loop3 < passes; loop3++)
			{
			for(int loop = start; loop < endd; loop++)
				{
				double val = 0;
				
				// Catch low boundary in the loop specs
				val += (double)tmp->GetAt(loop - 1);
				val += (double)tmp->GetAt(loop);
				val += (double)tmp->GetAt(loop + 1);
							
				tmp->SetAt(loop, (int)(val / 3));
				}
			}
		}

	return;
}


//////////////////////////////////////////////////////////////////////////

void	CSmooth::DynSmooth(CIntArr *tmp, int compcnt)

{	
	CIntArr xx, vv;

	int old = 0, clen = tmp->GetSize();

	//AP2N("CAnalProc::CSmooth smooth: ");

	// Smooth until peak count sufficienttly low
	for (int loopsm = 0; loopsm < MAX_SMOOTH; loopsm++)
		{
		xx.RemoveAll(); vv.RemoveAll();

		tmp->TurnArr(&xx, &vv, true); 

		int peakcnt = xx.GetSize();

		//AP2N("%d ", peakcnt);
		
		// If sample is too simple, stop
		if(peakcnt < 12)
			break;

		// If last pass was ineffective, consider it smooth enough
		//if(peakcnt < 8)
		//	if(old == peakcnt)
		//		break;

		old = peakcnt;

		tmp->Smooth();
		}
		
	//AP2N("\r\n");
}

//////////////////////////////////////////////////////////////////////////

void	CSmooth::Smooth(CPtrArray *parr, int passes)

{
	int alen = parr->GetSize();

	//AP2N("CAnalProc::RangeSmooth\r\n");

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArr tmp2, *tmp = (CIntArr *)parr->GetAt(loopb);

		//tmp->Smooth(passes);

		int nlen = tmp->GetSize();
		tmp2.SetSize(nlen);

		for(int loop3 = 0; loop3 < passes; loop3++)
			{
			for(int loop = 1; loop < nlen - 1; loop++)
				{
				int val = 0;
				
				// Catch low boundary in the loop specs
				val += tmp->GetAt(loop - 1);
				val += tmp->GetAt(loop);
							
				tmp2.SetAt(loop, (val / 2));				
				}
			tmp->Copy(tmp2);
			}
		}
}

//////////////////////////////////////////////////////////////////////////

void	CSmooth::Smooth3(CPtrArray *parr, int passes)

{
	int alen = parr->GetSize();

	//AP2N("CAnalProc::RangeSmooth\r\n");

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArr tmp2, *tmp = (CIntArr *)parr->GetAt(loopb);

		//tmp->Smooth(passes);

		int nlen = tmp->GetSize();
		tmp2.SetSize(nlen);

		for(int loop3 = 0; loop3 < passes; loop3++)
			{
			for(int loop = 1; loop < nlen - 1; loop++)
				{
				int val = 0;
				
				// Catch low boundary in the loop specs
				val += tmp->GetAt(loop - 1);
				val += tmp->GetAt(loop);
				val += tmp->GetAt(loop + 1);
							
				tmp2.SetAt(loop, (val / 3));				
				}
			tmp->Copy(tmp2);
			}
		}
}

//////////////////////////////////////////////////////////////////////////

void	CSmooth::Smooth5(CPtrArray *parr, int passes)

{
	int alen = parr->GetSize();

	//AP2N("CAnalProc::RangeSmooth\r\n");

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArr tmp2, *tmp = (CIntArr *)parr->GetAt(loopb);

		//tmp->Smooth(passes);

		int nlen = tmp->GetSize();
		tmp2.SetSize(nlen);

		for(int loop3 = 0; loop3 < passes; loop3++)
			{
			for(int loop = 2; loop < nlen - 2; loop++)
				{
				int val = 0;
				
				// Catch low boundary in the loop specs
				val += tmp->GetAt(loop - 2);
				val += tmp->GetAt(loop - 1);
				val += tmp->GetAt(loop);
				val += tmp->GetAt(loop + 1);
				val += tmp->GetAt(loop + 2);
							
				tmp2.SetAt(loop, (val / 5));
				}
			tmp->Copy(tmp2);
			}
		}
}

