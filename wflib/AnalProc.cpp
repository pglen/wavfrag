
/* =====[ AnalProc.cpp ]===================================================
                                                                             
   Description:     The wflib project, implementation of the AnalProc.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/21/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "math.h"

#include "wflib.h"
#include "AnalProc.h"
#include "support.h"
#include "mxpad.h"
#include "frag.h"
#include "xrecog.h"


extern	CxRecog		xdllrecog;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnalProc::CAnalProc()

{
	//xfirstdone = false;
	//procavg = 0;
}

CAnalProc::~CAnalProc()

{

}


#if 0

//////////////////////////////////////////////////////////////////////////
// Function template to copy for a new scanning function

void	CAnalProc::xTemplate(CPtrArray *parr)

{
	int alen = parr->GetSize();

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopb);
		int alenc = tmp->GetSize();

		for(int loop2 = 0; loop2 < alenc; loop2++)
			{
			// Code here
			}	
		}
}

#endif

//////////////////////////////////////////////////////////////////////////
// Entry point to process spectral information to simplified version 
// of the original, and create base and tonal color information
//
// Processing class in place
//
// The volume normalizer is giving the compare algorythm a chance to
// make a fair comparasion between different instances.
//

 void	CAnalProc::ProcSpectra(CAnalRes *pres, int compcnt)

{	
	//AP2N("CAnalProc::ProcSpectra(parr=%p, len=%d\r\n", 
	//											parr, parr->GetSize());

	CPtrArray *parr = pres->raw.GetData();

	// Visualize data (pre)
	VisRaw(parr);

	//xSpecCalcBalance(pres);
	//xSpecBalance(pres);
	//xSpecCalcBalance(pres, true);
	
	// The universe thinks in limits of logarythm
	xLog(pres->raw.GetData()); 
	
	// Visualize data (post)
	VisRaw(parr);
	
	// Equal chance of power contribution (not used, just for display)
	//xNorm(pres->raw.GetData()); //VisRaw(parr);
	
	int alen = pres->raw.GetSize();	

	// Scan thru array of arrays
	for(int loopms = 0; loopms < alen; loopms++)
		{
		CIntArrRec *tmp = pres->raw.GetAt(loopms);		

		CIntArrRec	tmpx(tmp); 		// Create a copy of original
		
		pres->AddOne();				// Create new arrays, add to output
		
		// Kill high highs
		//tmpx.KillSubArr(380, 512);

		// Smooth it. Factor determined experimentally
		xProgSmooth(&tmpx, pres, 2);
			
		// Just to confirm shape
		//xdllrecog._spectrec2(tmpx.GetData(), tmpx.GetSize() );		

		//tmpx.NormArrHeight(255, 5);
		
		// Fill in Full Spectra
		xGetVolArr(&tmpx, pres, compcnt);

		// Get spectral power curve
		xGetPowArr(tmp, pres, compcnt);

		// Get power contribution of this slice
		int avg = tmp->PowAvg(); pres->sig.Add(avg);
				
		//ASSERT(pres->all.GetSize() == pres->vall.GetSize());
		//ASSERT(pres->all.GetSize() == pres->pow.GetSize());
		}

	ASSERT(pres->raw.GetSize() == pres->all.GetSize());
	ASSERT(pres->raw.GetSize() == pres->pow.GetSize());

	//////////////////////////////////////////////////////////////////////
	// Dump resulting output:
	
#if 0
	AP2N("CAnalProc::ProcSpectra  (FREQ / VOL / WIDTH)\r\n");

	for(int loopd = 0; loopd < alen; loopd++)
		{		
		CIntArr *pftmp = pres->all.GetAt(loopd);		
		CIntArr *pvtmp = pres->vall.GetAt(loopd);		
		CIntArr *pptmp = pres->pow.GetAt(loopd);		
	
		int alen3 = pftmp->GetSize();
		CString tmpstr;

		for(int loopd3 = 0; loopd3 < alen3; loopd3++)
			{
			tmpstr.Format("%3d/%3d %d  ", pftmp->GetAt(loopd3),
				pvtmp->GetAt(loopd3), pptmp->GetAt(loopd3));
		
			support.StrPad(&tmpstr, 12);
			AP2N("%s", tmpstr);
			}
	
		if(alen3)
			AP2N("\r\n");

		}
#endif

		//////////////////////////////////////////////////////////////////
		// Dump power distro
#if 0
		for(int loopd3 = 0; loopd3 < alen; loopd3++)
			{		
			CIntArr *ppow = pres->pow.GetAt(loopd3);
			int blen = ppow->GetSize();
	
			for(int loop3 = 0; loop3 < blen; loop3++)
				{
				int val = ppow->GetAt(loop3);
				AP2N("%3d  ", val);
				}
			AP2N("\r\n");
			}
#endif

	// Visually verify output
	Vis(pres->all.GetData(), pres->vall.GetData());

	// Show power curves
	//xdllrecog._plotrec(pres->sig.GetData(), pres->sig.GetSize(), 0);		
	//xdllrecog._plotrec(0, 0, 0);
	
	//xdllrecog._plotrec(pres->sig2.GetData(), pres->sig2.GetSize(), 1);		
	//xdllrecog._plotrec(0, 0, 1);
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::Vis(CPtrArray *parr, CPtrArray *varr)
						 
{
	int alen = parr->GetSize();

 	for(int loopdy = 0; loopdy < alen; loopdy += 1)
 		{
 		if(xdllrecog._spectrec || xdllrecog._spectrec2)
			{
			CIntArr *tmp  = (CIntArr*)parr->GetAt(loopdy);
			CIntArr *vtmp = (CIntArr*)varr->GetAt(loopdy);
			
			CIntArr tmp2; xVisConv(tmp, vtmp, &tmp2);

			if(xdllrecog._spectrec)
				xdllrecog._spectrec(tmp2.GetData(), tmp2.GetSize() );

			if(xdllrecog._spectrec2)
				xdllrecog._spectrec2(tmp2.GetData(), tmp2.GetSize() );
			}
 		}	

	xVisSpace();
}

//////////////////////////////////////////////////////////////////////////
// Convert edge array back to value array

int CAnalProc::xVisConv(CIntArr *piarr, CIntArr *viarr, CIntArr *pvarr)
	
{	
	int arrsize = CFrag::onefraglen;
	
	int alen = piarr->GetSize(); 

	//AP2N("CFrag::_VisConv(CIntArr *piarr, len=%d\r\n", alen);
	//alen = MIN(alen, arrsize);

	pvarr->SetSize(arrsize);

	// Reverse plot
	for(int loopw = 0; loopw < alen; loopw++)
		{
		int idx = piarr->GetAt(loopw);
		int vol = viarr->GetAt(loopw);

		if(idx < arrsize && idx >= 0)
			pvarr->SetAtGrow(idx, vol);
		else
			AP2N("CAnalProc::xVisConv bad value - offs=%d idx=%d\r\n", loopw, idx); 
 		}		
		
	return 0;
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::VisRaw(CPtrArray *parr)
						 
{
	int alen = parr->GetSize();
 	for(int loopdy = 0; loopdy < alen; loopdy += 1)
 		{
 		if(xdllrecog._spectrec || xdllrecog._spectrec2)
			{
			CIntArr *tmp = (CIntArr*)parr->GetAt(loopdy);
			
			if(xdllrecog._spectrec)
				xdllrecog._spectrec(tmp->GetData(), tmp->GetSize() );

			if(xdllrecog._spectrec2)
				xdllrecog._spectrec2(tmp->GetData(), tmp->GetSize() );
			}
 		}	
	xVisSpace();
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::xVisSpace()

{
	if(xdllrecog._spectrec)		
		xdllrecog._spectrec(NULL, 0);

 	if(xdllrecog._spectrec2)		
		xdllrecog._spectrec2(NULL, 0); 
} 


//////////////////////////////////////////////////////////////////////////
// Progressive smooth, give a higher coefficient to the top of spectra

void	CAnalProc::xProgSmooth(CIntArrRec *ptmp, CAnalRes *pres, int scnt)

{
	ptmp->RangeSmooth(scnt);
	ptmp->RangeSmooth(scnt * 4, pres->lowtresh, pres->midtresh);
	ptmp->RangeSmooth(scnt * 24, pres->midtresh, pres->hightresh);
}

//////////////////////////////////////////////////////////////////////////
// Log it 

void	CAnalProc::xLog(CPtrArray *parr)

{
	if(!xfirstdone)
		{
		xfirstdone = true;

#if 0
		AP2N("CAnalProc::xLog()\r\n");

		for(int loop = 0; loop < 1000; loop++)
			{
			AP2N("%3d %d (%d)  -  ", loop, (int)(log(loop) * 40),
												(int)(log10(loop) * 40));
			}
		AP2N("\r\n");
#endif
		}

	//int mxx = 0;
	int alen = parr->GetSize();

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArrRec *tmp = (CIntArrRec *)parr->GetAt(loopb);
		tmp->Log();
		}

	//AP2N("Log max=%d\r\n", mxx);
}

//////////////////////////////////////////////////////////////////////////
// Equal chance of power contribution (not used)

void	CAnalProc::xNorm(CPtrArray *parr)

{
	int alen = parr->GetSize();

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArrRec *tmp = (CIntArrRec *)parr->GetAt(loopb);
	
		tmp->NormArrHeight(255, 5);
		}
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::xHorSmooth(CPtrArray *parr, CPtrArray *pout)

{
	int alen = parr->GetSize(), width = 2;

	for(int loopb = 0; loopb < alen; loopb++)
		{
		//CIntArrRec *tmp = (CIntArrRec *)parr->GetAt(loopb);
		CIntArrRec *tmp2 = new CIntArrRec; ASSERT(tmp2);
		pout->Add(tmp2);
	
		for(int loopc = loopb; loopc < MIN(loopb + width, alen); loopc++)
			{
			CIntArrRec *tmp = (CIntArrRec *)parr->GetAt(loopc);
			xAdd2Arr(tmp, tmp2);
			}		
		}

	// Replace in line
	//for(int loopf = 0; loopf < out.GetSize(); loopf++)
	//	{
	//	delete (CIntArrRec*) parr->GetAt(loopf);
	//	parr->SetAt(loopf, out.GetAt(loopf));		
	//	}
	//VisRaw(parr);
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::xAdd2Arr(CIntArrRec *parr, CIntArrRec *pout)

{
	int tlen = parr->GetSize(), olen = pout->GetSize();

	if(olen != tlen)
		pout->SetSize(tlen);

	for(int loopt = 0; loopt < tlen; loopt++)
		{
		int val  = parr->GetAt(loopt), val2 = pout->GetAt(loopt);
		pout->SetAt(loopt, (val + val2) / 2);
		}
}


//////////////////////////////////////////////////////////////////////////

void	CAnalProc::xGetVolArr(CIntArr *pinarr, CAnalRes *pres, int ccnt)

{		
	// Get peaks
	CIntArr xxx, vvv; pinarr->TurnArr(&xxx, &vvv, true); 
	
	// Located peaks, get top volume values
	CIntArr sss; vvv.Sort(&sss); 
	
	// Limit the number of spectral entries 
	int sslen = sss.GetSize(); sslen = MIN(sslen, ccnt);

	CIntArr *ptmp = pres->all.GetLast(), *pvmp = pres->vall.GetLast();
	
	// Gather and output the top N items
	for(int loopd = 0; loopd < sslen; loopd++)
		{
		int idx = sss.GetAt(loopd);				
		int freq = xxx.GetAt(idx), vol = vvv.GetAt(idx); 		

		//AP2N("%d/%d  ", freq, vol);
		//AP2N("%3d ", freq);

		ptmp->Add(freq);	pvmp->Add(vol);
		}

	//AP2N("\r\n");
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::xGetPowArr(CIntArr *pinarr, CAnalRes *pres, int ccnt)

{
	int divi = 34;  // How many bands to break it into

	int  alen = pinarr->GetSize();	
	int  step = alen / divi, cnt = 0;
	int	 xstep = step / 2;

	//AP2N("CAnalProc::xGetPowArr mstep=%d xtep=%d skew=%f\r\n", mstep, xstep, skew);

	// Calculate expanding proportion
	CIntArr arr, *ppow = pres->pow.GetLast();

	for(int loop = 0; loop < alen; loop += xstep)
		{
		int sum = 0;
		for(int loop2 = 0; loop2 < step; loop2++)
			{
			int idx = loop + loop2;

			if(idx < alen)
				sum += pinarr->GetAt(idx);
			}
		
		arr.Add(sum / xstep);

		// Recalc next step
		if(loop < pres->lowtresh)
			xstep = step;
		else if(loop < pres->midtresh)
			xstep = step;
		else
			xstep = step * 2;

		//AP2N("%d ", xstep);
		cnt++;
		}

	//AP2N("\r\n");

	//AP2N("CAnalProc::xGetPowArr cnt=%d\r\n", cnt);

	// Show power dist
	//xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 0);		
	//xdllrecog._plotrec(0, 0, 0);

	CIntArr xxx; arr.Sort(&xxx);

	for(int loop3 = 0; loop3 < MIN(8, arr.GetSize()); loop3 += 1)
		{
		int idx = xxx.GetAt(loop3);
		//AP2N("%3d / %3d   ", idx, arr.GetAt(idx));
		//AP2N("%3d  ", idx);

		ppow->Add(idx);
		}
	//AP2N("\r\n");
}	

//////////////////////////////////////////////////////////////////////////
//

void	CAnalProc::xSpecCalcBalance(CAnalRes *pres, int second)

{
	CPtrArray *parr = pres->raw.GetData();
	int alen = parr->GetSize();

	CIntArrRec arr;

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArrRec *tmp = (CIntArrRec *)parr->GetAt(loopb);
	
		int tlen = tmp->GetSize();

		if (arr.GetSize() > tlen)
			{	
			arr.SetSize(tlen);
			}

		// Add each element
		for(int loop = 0; loop < tlen; loop++)
			{
			int val = tmp->GetAt(loop);
			arr.AddToVal(loop, val);
			}
		}

	// Divide it back
	int slen = arr.GetSize();
	for(int loops = 0; loops < slen; loops++)
		{
		int val = arr.GetAt(loops);
		arr.SetAt(loops, val / alen);
		}

	//////////////////////////////////////////////////////////////////////////
	// Balance calculation:

	int ll = 0, mm = 0, hh = 0;
	for(int loops2 = 0; loops2 < pres->lowtresh; loops2++)
		{
		ll += arr.GetAt(loops2); 
		}
	ll /= pres->lowtresh;
	
	for(int loops3 = pres->lowtresh; loops3 < pres->midtresh; loops3++)
		{
		mm += arr.GetAt(loops3); 
		}
	mm /= pres->midtresh - pres->lowtresh;
	
	for(int loops4 = pres->midtresh; loops4 < pres->hightresh; loops4++)
		{
		hh += arr.GetAt(loops3); 
		}
	hh /= pres->hightresh - pres->midtresh;

	pres->low = ll; pres->med = mm; pres->high = hh;

	//AP2N("ll=%d mm=%d hh=%d\r\n", ll, mm, hh);

	if(second)
		{
		xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 0);		
		xdllrecog._plotrec(0, 0, 0);	
		}
}

//////////////////////////////////////////////////////////////////////////

void	CAnalProc::xSpecBalance(CAnalRes *pres)

{
	CPtrArray *parr = pres->raw.GetData();
	int alen = parr->GetSize();

	int lowcorr = 1, midcorr = 1, highcorr = 1;

	int midline = pres->low + pres->med + pres->high; midline /= 3;
		
	if(midline / 2 > pres->low)
		{
		lowcorr = pres->low / midline + 1;  lowcorr = MIN(lowcorr, 4);
		//AP2N("Applying low correction %d\r\n", lowcorr);
		}

	if(midline / 2 > pres->med)
		{
		midcorr = pres->low / midline + 1;  midcorr = MIN(midcorr, 4);
		//AP2N("Applying mid correction %d\r\n", midcorr);
		}

	if(midline / 2 > pres->high)
		{
		highcorr = pres->low / midline + 1; highcorr = MIN(highcorr, 4);
		//AP2N("Applying high correction %d\r\n", highcorr);
		}

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArrRec *tmp = (CIntArrRec *)parr->GetAt(loopb);
	
		int tlen = tmp->GetSize();

		if(lowcorr != 1)
			{
			for(int loops2 = 0; loops2 < pres->lowtresh; loops2++)
				{
				int val = tmp->GetAt(loops2); 
				tmp->SetAt(loops2, val * lowcorr); 
				}
			}

		if(midcorr != 1)
			{
			for(int loops3 = pres->lowtresh; loops3 < pres->midtresh; loops3++)
				{
				int val = tmp->GetAt(loops3); 
				tmp->SetAt(loops3, val * midcorr); 
				}
			}

		if(highcorr != 1)
			{
			for(int loops4 = pres->midtresh; loops4 < pres->hightresh; loops4++)
				{
				int val = tmp->GetAt(loops4); 
				tmp->SetAt(loops4, val * highcorr); 
				}
			}
		}
}
