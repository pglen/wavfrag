
/* =====[ CBend.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the CBend.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/17/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// CBend.cpp: implementation of the CBend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"
#include "mxpad.h"
#include "Bend.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#undef P2N

#define NORMALIZE_TO	200
//#define AVGLOOP			2

//////////////////////////////////////////////////////////////////////////
// Tweaking different options

//#define		AVG_ENABLE 1
//#define		NORM_ENABLE 1
//#define		FIND_SILENCE	1
//#define		FIRST_TREND	1
//#define		NORM_SOUND  1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBend::CBend()

{

#ifdef PLOT_ENABLE

	m_plot1 = m_plot2 = m_plot3 = NULL;
	m_plot4 = m_plot5 = m_plot6 = NULL;
	m_plot7 = m_plot1 = NULL;

#endif

	samplerate	= 44100;	// Assuming CD HiFi
	pps			= 50;		// N (def=50) parts per second

	//avgloopcnt	= AVGLOOP;	// Number of times the freq scan avaraged
	//plotmax		= 0;
	//cnt			= 0;

	//shortskip		= 1;
}

//////////////////////////////////////////////////////////////////////////

CBend::~CBend()

{

}

//////////////////////////////////////////////////////////////////////////

int	CBend::xBendFreq(short *ptr, int len, CIntArr *piarr) 

{
	CIntArr	resarr;

	AP2N("xBendFreq(short *ptr, int len=%d\r\n", len);

	CIntArr varr, varrd, darr, darrd;
	
	xProcBuff(ptr, len, &varr, &darr);	
	xConvDist(&darr, &darrd, &varr, &varrd);

	//darrd.Plot(m_plot1); m_plot1->AddMarker();
	//varrd.Plot(m_plot2); m_plot2->AddMarker();
	
	xStatArr(&darrd, &varrd, &resarr);
	
	//CIntArr varr2, darr2, darrd2, varrd2;	
	//xTurnRecurse(&darr, &varr, &darr2, &varr2);
	//xConvDist(&darr2, &darrd2, &varr2, &varrd2);
	//xStatArr(&darrd2, &varrd2, &resarr);
	
	//darrd2.Plot(m_plot3); m_plot3->AddMarker();
	//varrd2.Plot(m_plot4); m_plot4->AddMarker();
	
	//CIntArr varr3, darr3, darrd3, varrd3;
	//xTurnRecurse(&darr2, &varr2, &darr3, &varr3);
	//xConvDist(&darr3, &darrd3);
	
	//CIntArr varr4, darr4, darrd4, varrd4;
	//xTurnRecurse(&darr3, &varr3, &darr4, &varr4);
	//xConvDist(&darr4, &darrd4);
	
#define FILTER

#ifdef FILTER
	piarr->SetSize(255);
	int x1, x2, v1, v2, x3, x4, v3, v4;
	resarr.FindMax4(&x1, &v1, &x2, &v2, &x3, &v3, &x4, &v4);
	
	if(x1 >= 0)	piarr->SetAt(x1, v1);	
	if(x2 >= 0)	piarr->SetAt(x2, v2);
	if(x3 >= 0)	piarr->SetAt(x3, v3);	
	if(x4 >= 0)	piarr->SetAt(x4, v4);
#else
	piarr->Copy(resarr);
	piarr->SetSize(255);

#endif

	piarr->NormArrHeight(255);

	//piarr->Plot(m_plot6); m_plot6->AddMarker();

	return 0;
}


//////////////////////////////////////////////////////////////////////////

void	CBend::xStatArr(CIntArr *darrd2, CIntArr *varrd2, CIntArr *resarr)

{
	int alen2 = darrd2->GetSize();

	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		int val = darrd2->GetAt(loop2);
		int hh  = abs(varrd2->GetAt(loop2));

		//if(val > 0 && hh > 1000)
			{		
			resarr->AddToVal(val, hh * val);
			}
 		}
}

// --------------------------------------------------------------
//
/// \brief   Analize buffer, recursing into  
/// 
/// \details Analize buffer, recursing into the same until reasonable
/// effort has been exhausted to be complete
/// \n  
/// Return type:      void 
/// \n  
/// \param *ptr Arg Type: short 
/// \param len Arg Type: int 
/// \param *parr[] Arg Type: CIntArr 

int	CBend::BendRecurse(short *ptr, int len, CPtrArray *parr) 

{
	AP2N("CBend::CBendRecurse len=%d\r\n", len);

	int step = 500;

	for(int loop = 0; loop < len - step; loop += step)
		{
		CIntArr *piarr = new CIntArr;  ASSERT(piarr);

		//xBendFreq(ptr + loop, step,  piarr);
		xBendSpectra(ptr + loop, step,  piarr);

		parr->Add(piarr);
		}

	return 0;
}

// -----------------------------------------------------------------------
//
/// \brief  CBend::CBendRecurseBuff  Brief Here 
/// 
/// \details CBend::CBendRecurseBuff Descibe Here 
/// \n  
/// Return type:      
/// \n  
/// \param *ptr Arg Type: short 
/// \param len Arg Type: int 
/// \param *parr[] Arg Type: CIntArr 
//
// -----------------------------------------------------------------------

//DEL int	CBend::xBendRecurseBuff(short *ptr, int len, CPtrArray *parr) 
//DEL 
//DEL {
//DEL 	int	step = samplerate / pps;
//DEL 	int len2 = len ; // / sizeof(short);
//DEL 	short *ptrs = ptr;
//DEL 
//DEL 	prevv = 0;
//DEL 
//DEL #ifdef FIND_SILENCE
//DEL 
//DEL 	// Find peak
//DEL 	int peak = 0;
//DEL 	short *ptrp = ptr;
//DEL 	for(int loopp = 0; loopp < len2; loopp++)
//DEL 		{
//DEL 		peak = max(peak, abs(*ptrp));			
//DEL 		ptrp ++;
//DEL 		}
//DEL 
//DEL 	//P2N("Looking at peak %d of %d\r\n", peak, SHRT_MAX);
//DEL 
//DEL 	// Find starting silence boundary
//DEL 	for(int loops = 0; loops < len2; loops++)
//DEL 		{
//DEL 		if(abs(*ptrs) > (peak / 50))
//DEL 			break;
//DEL 		ptrs ++;
//DEL 		}
//DEL 	
//DEL 	len2 -= ptrs - ptr;
//DEL #endif
//DEL 
//DEL 
//DEL 	CIntArr *pcurr = new CIntArr; ASSERT(pcurr);
//DEL 	CIntArr *pcurr2 = new CIntArr; ASSERT(pcurr2);
//DEL 	CIntArr *pcurr3 = new CIntArr; ASSERT(pcurr3);
//DEL 	CIntArr *pcurr4 = new CIntArr; ASSERT(pcurr4);
//DEL 	CIntArr *pcurr5 = new CIntArr; ASSERT(pcurr5);
//DEL 	CIntArr *pcurr6 = new CIntArr; ASSERT(pcurr6);
//DEL 	
//DEL 	parr->Add(pcurr);	parr->Add(pcurr2);
//DEL 	parr->Add(pcurr3);	parr->Add(pcurr4);
//DEL 	parr->Add(pcurr5);	parr->Add(pcurr6);
//DEL 
//DEL 
//DEL 	CIntArr varr, varrx, darr, darrd;
//DEL 
//DEL 	while (true)
//DEL 		{
//DEL 		//ProcBuff(ptrs, step, &darr, &varr);
//DEL 		
//DEL 		xProcBuff(ptrs, len2, &varr, &darr);					
//DEL 		//xConvDist(&darr, &darrd, &varr, &varr2);
//DEL 
//DEL 		FreqImg(&darr, &varr, parr, 0);		
//DEL 
//DEL 		//parr[0]->Copy(darrd);
//DEL 		//Split(&darrd, &varr, parr, 2);			
//DEL 		//Split(&darrd, &varr, parr, 0);		
//DEL 		
//DEL 		// Volume array
//DEL 		//varrx.Copy(varr);	//varrx.ScaleArrLen(.04);	
//DEL 		//varrx.NormArrLen(parr[1]->GetSize());
//DEL 		//varrx.Abs();
//DEL 
//DEL 		//parr[0]->Copy(varrx);		
//DEL 
//DEL #if 0
//DEL 		CIntArr varr2, darr2, darrd2;
//DEL 		CIntArr varr3, darr3, darrd3;
//DEL 		CIntArr varr4, darr4, darrd4;
//DEL 		xTurnRecurse(&darr, &varr, &darr2, &varr2);
//DEL 		//P2N("xTurnRecurse insize=%d ousize=%d\r\n", darr.GetSize(), darr2.GetSize());
//DEL 		//xConvDist(&darr2, &darrd2);
//DEL 		FreqImg(&darr2, &varr2, parr, 1);		
//DEL 		
//DEL 		xTurnRecurse(&darr2, &varr2, &darr3, &varr3);
//DEL 		//xConvDist(&darr3, &darrd3);
//DEL 		FreqImg(&darr3, &varr3, parr, 2);		
//DEL 		
//DEL 		xTurnRecurse(&darr3, &varr3, &darr4, &varr4);
//DEL 		//xConvDist(&darr4, &darrd4);
//DEL 		FreqImg(&darr4, &varr4, parr, 3);		
//DEL #endif
//DEL 
//DEL 		ptrs += step;  len2 -= step;
//DEL 
//DEL 		if(len2 <= 0)
//DEL 			break;
//DEL 
//DEL 		break;	// test
//DEL 		}
//DEL 
//DEL 	return 0;
//DEL }

// -----------------------------------------------------------------------
//
/// \brief   BriefHere 
/// 
/// \details DescHere 
/// \n  
/// Return type:      int 
/// \n  
/// \param *ptr Arg Type: short 
/// \param len Arg Type: int 
/// \param *res[] Arg Type: int 

int CBend::xProcBuff(short *ptr, int len, CIntArr *varr, CIntArr *darr)

{
	//P2N("CBend::ProcBuff %d\r\n", len);

	#define UPT		1
	#define DOWNT	-1
	#define NULLT	0

	short	*data = ptr, prev = 0, lastturn = 0, lastturnd = 0;
	int		prevd = 0, prevh = 0;
	int		pptrend = NULLT, ptrend = NULLT, trend = NULLT;
	int		ndist = 0, len2 = len; // / sizeof(short);

	darr->RemoveAll(); varr->RemoveAll();
	
	int loop1a = 0; //, loop1b = 0;

	for (int loop = loop1a; loop < len2 - (loop1a + 1); loop++)
		{
		short curr = *data;

		//////////////////////////////////////////////////////////////////
		//    |^^^|
		//  __|   |__
		//
		
		short	ddiff = prev - curr;

		if(ddiff > 0) 		
			trend = UPT;
		else if(ddiff < 0)  
			trend = DOWNT;
		else 
			trend = NULLT;
	
		if(ptrend != trend)	
			{
			//int height = abs(curr - lastturn);
			int height = curr - lastturn;
			
			if(trend == UPT && ptrend == DOWNT)
				{
				varr->Add(height);
				darr->Add(loop);
				}
			else if(trend == DOWNT && ptrend == UPT)
				{
				varr->Add(height);
				darr->Add(loop);
				}
			else if(trend == DOWNT && ptrend == NULLT && pptrend == UPT)
				{
				varr->Add(height);
				darr->Add(loop);
				}
			else if(trend == UPT && ptrend == NULLT && pptrend == DOWNT)
				{
				varr->Add(height);
				darr->Add(loop);
				}

			lastturn  = curr;
			lastturnd = loop;

			pptrend = ptrend; 
			ptrend = trend;
			}
		data++;
		prev = curr;	
		}

	//P2N("Produced array len=%d\r\n", darr->GetSize());

	return 0;
}

// --------------------------------------------------------------
//
/// \brief   BriefHere 
/// 
/// \details DescHere 
/// \n  
/// Return type:      int 
/// \n  
/// \param *darr Arg Type: CIntArr 
/// \param *varr Arg Type: CIntArr 
/// \param *darr2 Arg Type: CIntArr 
/// \param *varr2 Arg Type: CIntArr 

int CBend::xTurnRecurse(CIntArr *darr, CIntArr *varr, CIntArr *darr2, CIntArr *varr2)

{
	int len = varr->GetSize();

	// Make sure they are the same size
	ASSERT(len == darr->GetSize());

	if(len < 2)
		return 0;

	int	pprev = 0, nprev = 0, ptrend = 0, ntrend = 0;
	int	pold_trend = 0, nold_trend = 0;
	int oldpoint = 0;

	int changeflag = false;  // true for positive 
	if(varr->GetAt(1) > varr->GetAt(0))
		{
		changeflag = true;
		}

	///////////////////////////////////////////////////////////////
	//
	//          pos                               pos  
	//       ___---   ___                      ___---___
	// ___---      ---   ---___          ___---       
	//                         ---___--- 
	//                            neg
	//   PPP      RRR     NNN                PPP
	//
	///////////////////////////////////////////////////////////////
	
	for( int loop = 0; loop < len; loop++)
		{
		// Observe trend change

		int pval = varr->GetAt(loop);
		int	ptrend = pold_trend, pddiff = pprev - pval;
		
		if(pval > 0)
			{
			if(pddiff > 0) ptrend = 1;
			else if(pddiff < 0) ptrend = -1;

			if(pold_trend != ptrend) 
				{
				if(ptrend == -1)
					{				
					darr2->Add(darr->GetAt(loop));
					varr2->Add(abs(pval - pprev));			
					changeflag = false;
					}
				
				pold_trend = ptrend;
				//oldpoint = newpoint;		
				}
			}
		pprev = pval;
		}


	return 0;
}

// -----------------------------------------------------------------------
//
/// \brief  CBend::Split  Brief Here 
/// 
/// \details CBend::Split Descibe Here 
/// \n  
/// Return type:      int 
/// \n  
/// \param *x1 Arg Type: CIntArr 
/// \param *v1 Arg Type: CIntArr 
/// \param  *arrarr[] Arg Type: CIntArr 
/// \param start Arg Type: int 
//
// -----------------------------------------------------------------------

int CBend::FreqImg(CIntArr *d1, CIntArr *v1, CPtrArray  *arrarr, int start)

{
	ASSERT(arrarr);

	//P2N("CBend::FreqImg inlen=%d  vinlen=%d\r\n", 
	//							d1->GetSize(), v1->GetSize());

	// This (step = 50-200) is an optimum between collecting enough samples for 
	// averaging and still be responsive enough to distinguish wowels

	int	step = 200, alen = d1->GetSize();
	CIntArr	arr1, arr2, arr3, arr4, arr5;
	CIntArr	po1, po2, po3, po4, po5, vo1, vo2, vo3, vo4, vo5; 

	//if(((CPlay*)AfxGetApp()->m_pMainWnd)->record)
	//		d1->Plot(m_plot6);
		
	// -------------------------------------
	//  |        |                        |
	// d1       d1						alen

	//for(int loop = 1; loop + step < alen; loop += step)

	//int prevmax1 = 0,prevmax2 = 0, prevmax3 = 0;

	int stop = false, loop = 1;
	while(true)
		{
		// Terminal point condition from inner
		if(stop) {
			break;
			}

		// Terminal point condition from outer
		if(loop >= alen) {
			stop = true;
			break;
			}

		arr1.RemoveAll(),	arr2.RemoveAll(); arr3.RemoveAll();	
		arr4.RemoveAll();	arr5.RemoveAll();
		
		po1.RemoveAll(), vo1.RemoveAll();
		po2.RemoveAll(), vo2.RemoveAll();
		po3.RemoveAll(), vo3.RemoveAll();
		po4.RemoveAll(), vo4.RemoveAll();
		po5.RemoveAll(), vo5.RemoveAll();

		int	loop2 = 0;
		int startx = d1->GetAt(loop);
		//for(loop2 = 0; loop2 < step; loop2++)

		//P2N("CBend::FreqImg loop=%d\r\n", loop);

		while(true)
			{
			int loop3 = loop + loop2++;

			// Outer boundary break
			if(loop3 >= alen)
				{
				stop = true;
				break;
				}

			// Inner boundary break
			if(d1->GetAt(loop3) > startx + step)
				{
				break;
				}

			int diff = d1->GetAt(loop3) - d1->GetAt(loop3 - 1);
									
			//int val = abs(v1->GetAt(loop3)) ;
			//int val = 1; //diff * diff;
			int val = diff * diff;

			//P2N("  CBend::FreqImg diff=%d val=%d loop3=%d\r\n", diff, val, loop3);

			//int val = diff * diff;

			//static int cnt = 0;
			//if(cnt++ % 100 == 0)
			//	AP2N("val = %d   ", val);

			// Do frequency components
			//if(diff > 0 && diff < 5)
			//	arr4.AddToVal(diff, val); 
			
			//if(val > 1000)
				{
				//if(diff >= 1 && diff < 6)
				//	arr5.AddToVal(diff * 10, val); 
				
				//if(diff >= 6 && diff < 10)
				//	arr4.AddToVal(diff * 3, val); 
				
				//if(diff >= 10 && diff < 14)
				//	arr3.AddToVal(diff, val); 
				
				if(diff >= 1 && diff < 5)
					arr2.AddToVal(diff * 10, val); 

				if(diff >= 1 && diff < 1000)
					arr1.AddToVal(diff, val);										
				}

			//else
				
			// Power tries are exhausted to see if different equations work better
			//if(v1->GetAt(loop3) > 1000)
			// Volume proportional seems to work best
			//arr.AddToVal(diff, abs(v1->GetAt(loop3)));
			//arr.AddToVal(d1->GetAt(loop3), abs(v1->GetAt(loop3)) / d1->GetAt(loop3));		
			//arr.AddToVal(d1->GetAt(loop3), 100);
			}
		loop += loop2;

		arr1.Smooth(1);	arr2.Smooth(1);
		arr3.Smooth(1);	arr4.Smooth(1); arr5.Smooth(1);
		
		xTurnArr(&arr1, &po1, &vo1);
		xTurnArr(&arr2, &po2, &vo2);
		xTurnArr(&arr3, &po3, &vo3);
		xTurnArr(&arr4, &po4, &vo4);
		xTurnArr(&arr5, &po5, &vo5);
		
		//if(((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
			{
			//arr1.Plot(m_plot4); m_plot4->AddMarker();
			//arr2.Plot(m_plot6); m_plot5->AddMarker();
			//arr3.Plot(m_plot5); m_plot6->AddMarker();

			//arr4.Plot(m_plot6);
			//po1.Plot(m_plot6); m_plot6->AddMarker();
			//vo.Plot(m_plot4);
			//po2.Plot(m_plot5); vo2.Plot(m_plot6);
			}
		
		int maxidx, maxval, maxidx2, maxval2, maxidx3, maxval3;
		vo1.FindMax3(&maxidx, &maxval, &maxidx2, &maxval2, &maxidx3, &maxval3);

		maxidx = max(maxidx, 0); maxval = max(maxval, 0);
		maxidx2 = max(maxidx2, 0); maxval2 = max(maxval2, 0);
		maxidx3 = max(maxidx3, 0); maxval3 = max(maxval3, 0);
		
		int maxidxx, maxvalx, maxidxx2, maxvalx2, maxidxx3, maxvalx3;
		vo2.FindMax3(&maxidxx, &maxvalx, &maxidxx2, &maxvalx2, &maxidxx3, &maxvalx3);
		maxidxx = max(maxidxx, 0); maxvalx = max(maxvalx, 0);

		int maxidxy, maxvaly, maxidxy2, maxvaly2, maxidxy3, maxvaly3;
		vo3.FindMax3(&maxidxy, &maxvaly, &maxidxy2, &maxvaly2, &maxidxy3, &maxvaly3);
		maxidxy = max(maxidxy, 0); maxvaly = max(maxvaly, 0);

		int maxidxz, maxvalz, maxidxz2, maxvalz2, maxidxz3, maxvalz3;
		vo4.FindMax3(&maxidxz, &maxvalz, &maxidxz2, &maxvalz2, &maxidxz3, &maxvalz3);
		maxidxz = max(maxidxz, 0); maxvalz = max(maxvalz, 0);

		int maxidxq, maxvalq, maxidxq2, maxvalq2, maxidxq3, maxvalq3;
		vo5.FindMax3(&maxidxq, &maxvalq, &maxidxq2, &maxvalq2, &maxidxq3, &maxvalq3);
		maxidxq = max(maxidxq, 0); maxvalq = max(maxvalq, 0);

		//m_plot5->AddLine(maxidx);
		//m_plot6->AddLine(maxidx2);

		//arr.FindMax3(&maxidx, &maxval, &maxidx2, &maxval2, &maxidx3, &maxval3);
			
		//P2N("  CBend::FreqImg maxidx=%d maxidx2=%d maxidx3=%d\r\n", maxidx, maxidx2, maxidx3);

		//if(((CPlay*)AfxGetApp()->m_pMainWnd)->record)
			{
			//m_plot4->AddLine(maxval);
			//m_plot5->AddLine(maxval2);
			//m_plot6->AddLine(maxval3);
			}
	
#if 0
			int maxidx11 = po1.SafeGetAt(maxidx) * 50;
			int maxidx22 = po1.SafeGetAt(maxidx2) * 50;
		
			((CIntArr*)arrarr->GetAt(0 + start))->Add(maxidx11);				
			((CIntArr*)arrarr->GetAt(1 + start))->Add(maxidx22);							
			((CIntArr*)arrarr->GetAt(2 + start))->Add(maxvalx / 10);				
			((CIntArr*)arrarr->GetAt(3 + start))->Add(maxvaly / 20);				
			((CIntArr*)arrarr->GetAt(4 + start))->Add(maxvalz / 30);
#endif
	
#if 1
			int maxidx11 = po1.SafeGetAt(maxidx) * 100;
			int maxidx111 = po1.SafeGetAt(maxidx2) * 100;
			int maxidx222 = po1.SafeGetAt(maxidx3) * 100;

			//int maxidx22 = po2.SafeGetAt(maxidxx) * 50;
			//int maxidx22 = vo2.SafeGetAt(maxvalx);
			
			//int maxidx33 = po3.SafeGetAt(maxidxy) * 50;
			//int maxidx44 = po4.SafeGetAt(maxidxz) * 20;
			//int maxidx55 = po5.SafeGetAt(maxidxq) * 10;
				
			((CIntArr*)arrarr->GetAt(0 + start))->Add(maxidx11);
			((CIntArr*)arrarr->GetAt(1 + start))->Add(maxidx111);				
			((CIntArr*)arrarr->GetAt(2 + start))->Add(maxidx222);				
			
			//((CIntArr*)arrarr->GetAt(1 + start))->Add(maxvalx / 5);				
			//((CIntArr*)arrarr->GetAt(2 + start))->Add(maxidxy / 5);

			//((CIntArr*)arrarr->GetAt(2 + start))->Add(maxvalx / 100);				
			//((CIntArr*)arrarr->GetAt(4 + start))->Add(maxidx55);				

			//if(maxvaly > 2000)
				
			//else
			//	((CIntArr*)arrarr->GetAt(4 + start))->Add(0);				
#endif
			}
		
	return 0;
}

// -----------------------------------------------------------------------
//
/// \brief  CBend::xConvDist  Convert abs dist arr to relative dist arr
/// 
/// \details CBend::xConvDist Modified to not extract distance of one (noise)
/// \n  
/// Return type:      int 
/// \n  
/// \param *darr Arg Type: CIntArr			in distance
/// \param *varr Arg Type: CIntArr			in volume
/// \param *darr2 Arg Type: CIntArr			out distance
/// \param *varr2 Arg Type: CIntArr			out volume
//
// -----------------------------------------------------------------------

int CBend::xConvDist(CIntArr *darr, CIntArr *darr2, CIntArr *varr, CIntArr *varr2)

{
	darr2->RemoveAll();	varr2->RemoveAll();
	
	int len = darr->GetSize();

	if(!len)
		return -1;

	int prev = 0; //darr->GetAt(0);

	for(int loop = 0; loop < len; loop++)
		{
		int curr = darr->GetAt(loop);
		int diff = curr - prev;

		// It was mostly noise, conveniently ignore it
		if(diff > 1)
			{
			darr2->Add(diff);
			varr2->Add(varr->GetAt(loop));
			}
		prev = curr;
		}

	//if(((CPlay*)AfxGetApp()->m_pMainWnd)->record)
		{
		//varr2->Plot(m_plot5);
		//darr2->Plot(m_plot6);
		}

	//P2N("CBend::xConvDist outlen=%d\r\n", darr2->GetSize());

	return 0;
}

//////////////////////////////////////////////////////////////////////////

void	CBend::xBellCurve(int *ff)

{
	//int diff = *ff - 300;
	//int adiff = abs(diff);

	//if(plotmax)
	//	P2N("SpectAnal::BellCurve in=%d ", *ff);

	*ff = (int)sqrt(100 * (*ff) );

	//if(adiff > 900) 
	//	*ff = 300 + diff / 8;
	//else if(adiff > 600) 
	//	*ff = 300 + diff / 4;
	//else if(adiff > 300) 
	//	*ff = 300 + diff / 2;
	//else
	//	*ff = 300 + diff;

	//if(plotmax)
	//	P2N("out=%d\r\n", *ff);
}

#ifdef FIRST_TREND
	
	// Find first trend change:
	prev = *data++;
	short diff = prev - *(data);
	if(diff > 0) 
		old_trend = 1;
	else if(diff < 0) 
		old_trend = -1;
	
	// Skip to first turn ....
	for (loop1a = 1; loop1a < min(len2, 300); loop1a++)
		{
		short curr = *data;

		// Observe trend change
		short	trend = old_trend,  ddiff = prev - curr;

		if(ddiff > 0) 
			trend = 1;
		else if(ddiff < 0) 
			trend = -1;
	
		if((old_trend != trend)) // && (trend == -1))
			break;
		
		data ++;; 
		prev = curr;
		}

	//if(cnt++ % 100 == 0)
	//	P2N("Skipped from beginning %p %d of %d\r\n", ptr, loop1a, len2);	

	//*data		= SHRT_MIN;

#endif

//////////////////////////////////////////////////////////////////////////

void CBend::xPostPro(CPtrArray *parr)

{
	int alen = parr->GetSize();
	for(int loop6a = alen - 1; loop6a >= 0; loop6a--)
		{
		CIntArr *val = (CIntArr*)parr->GetAt(loop6a);

		// Remove stale buffers
		if(val->GetSize() == 0)
			{
			delete val;
			parr->RemoveAt(loop6a);
			}
		else
			{
			//val->Diff();
			//val->Liftup();
			//val->DeNoise();
			val->Smooth(4);	
			//((CIntArr*)parr->GetAt(loop6a))->NormArrHeight(4000, 4);
			}
		}

	//int begp, endp, minbeg = INT_MAX, maxend = INT_MIN;

	//double rat = ((CIntArr*)parr->GetAt(2))->NormArrHeight(1000);		
	//for(loop6a = 2; loop6a < len; loop6a++)
	//	{
	//	((CIntArr*)parr->GetAt(loop6a))->NormArrHeight(1000, 5);
	//	}

	//((CIntArr*)parr->GetAt(loop6a))->SinkDown();
	//for(loop6a = 0; loop6a < BEND_ARR_COUNT; loop6a++)
	//	{
	//	//parr[loop6a]->NormArrHeight(600);
	//	}

	//double rat = parr[0]->NormArrHeight(1000);
	//for(int loop8c = 1; loop8c < BEND_ARR_COUNT; loop8c++)
	//	{
	//	//parr[loop8c]->Multiply(rat);
	//	}
		
	//parr[0]->NormArrLen(parr[1]->GetSize());
	//parr[2]->NormArrLen(parr[1]->GetSize());

	//parr[0]->Copy(*parr[1]);

	//CIntArr tmp, tmp2, tmp3, tmp4;
	//TurnArr(parr[0], &tmp, &tmp2);
	//xConvDist(&tmp, parr[3], &tmp, &tmp4);
	
	//ChartScript(parr[0], &tmp2, &tmp);
	//ChartScript(parr[0], parr[1], &tmp);
	//parr[0]->RemoveAll();
	//parr[0]->Copy(tmp2);
	//parr[0]->NormArrLen(400);
	
	//ChartScript(parr[1], parr[1], &tmp);
	//ChartScript(parr[2], parr[2], &tmp);
	//parr[1]->Smooth(2);

	// Test by removal of voting components

	//parr[0]->RemoveAll();
	//parr[1]->RemoveAll();
	//parr[2]->RemoveAll();
	//parr[3]->RemoveAll();
	//parr[4]->RemoveAll();
	//parr[5]->RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

void	CBend::xTurnArr(CIntArr *parr, CIntArr *pout, CIntArr *vout)

{
	int len = parr->GetSize(), dist = 0;

	int	pprev = 0, ptrend = 0, pold_trend = 0;
	int oldpoint = 0;

	for( int loop = 1; loop < len; loop++)
		{
		int val = parr->GetAt(loop);
		int	ptrend = pold_trend, pddiff = pprev - val;
		
		if(pddiff > 0) ptrend = 1;
		else if(pddiff < 0) ptrend = -1;

		if(pold_trend != ptrend) 
			{
			if(ptrend == -1)
				{
				//pout->Add(dist);
				// Add Current point
				vout->Add(val);
				pout->Add(loop + 1);
				}
			//else
				{
				//vout->Add(-val);
				//pout->Add(loop);
				}			

			oldpoint = val;
			pold_trend = ptrend;			
			dist = 0;
			}
		dist++;
		pprev = val;
		}

//	if(((CPlay*)AfxGetApp()->m_pMainWnd)->record)
		{
		//pout->Plot(m_plot5);
		//vout->Plot(m_plot6);
		}
}

// -----------------------------------------------------------------------
//
/// \brief  CBend::Split  Brief Here 
/// 
/// \details CBend::Split Descibe Here 
/// \n  
/// Return type:      int 
/// \n  
/// \param *a1 Arg Type: CIntArr 
/// \param *v1 Arg Type: CIntArr 
/// \param *a2 Arg Type: CIntArr 
/// \param *a3 Arg Type: CIntArr 
/// \param *a4 Arg Type: CIntArr 
/// \param *a5 Arg Type: CIntArr 
//
// -----------------------------------------------------------------------

int CBend::xSplit(CIntArr *x1, CIntArr *v1, CIntArr  *arrarr[], int start)

{
	int len = x1->GetSize();

	//P2N("CBend::Split len=%d\r\n", len);

	if(!len)
		return -1;

	//arrarr[0]->RemoveAll();
	//arrarr[1]->RemoveAll();
	//arrarr[2]->RemoveAll();
	//arrarr[3]->RemoveAll();
	//arrarr[4]->RemoveAll();
	//arrarr[5]->RemoveAll();

	int prev = 0; //darr->GetAt(0);

	for(int loop = 0; loop < len; loop++)
		{
		int curr = x1->GetAt(loop);
		int height = v1->GetAt(loop);
		//int height = 100;

		//if(cnt++ % 100 == 0)
		//	P2N("Split curr=%d height=%d\r\n", curr, height);

		if(curr > 32)
			{
			arrarr[start + 0]->Add(height);
			arrarr[start + 1]->Add(0);
			arrarr[start + 2]->Add(0);	
			arrarr[start + 3]->Add(0);
			}			
		else if(curr > 16)
			{
			arrarr[start + 0]->Add(0);
			arrarr[start + 1]->Add(height);
			arrarr[start + 2]->Add(0);	
			arrarr[start + 3]->Add(0);
			}			
		else if(curr > 8)
			{
			arrarr[start + 0]->Add(0);
			arrarr[start + 1]->Add(0);
			arrarr[start + 2]->Add(height);
			arrarr[start + 3]->Add(0);	
			}			
		else if(curr > 4)
			{
			arrarr[start + 0]->Add(0);
			arrarr[start + 1]->Add(0);
			arrarr[start + 2]->Add(0);
			arrarr[start + 3]->Add(height);	
			}			
		else
			{
			arrarr[start + 0]->Add(0);
			arrarr[start + 1]->Add(0);
			arrarr[start + 2]->Add(0);
			arrarr[start + 3]->Add(0);
			}
		}

	//for(int loop6a = 0; loop6a < BEND_ARR_COUNT; loop6a++)
	//	{
	//	arrarr[loop6a]->NormArrLen(200);
	//	arrarr[loop6a]->Smooth(12);
	//	}

	//P2N("Split outlen=%d\r\n", arrarr[0]->GetSize());
	//P2N("Split outlen=%d\r\n", arrarr[1]->GetSize());

	return 0;
}


#if 0
	// Generate accel plot
	int alen = parr[0]->GetSize();
	for(int loop = 0; loop < alen - 1; loop++)
		{
		int diff = parr[0]->GetAt(loop + 1) - parr[0]->GetAt(loop);
		aarr.Add(diff);		
		}

	//parr[0]->Plot(m_plot10);
	//aarr.Plot(m_plot2);

	// Convert accel plot to accel points
	xTurnArr(parr[0], &darr, &varr);

	darr.Plot(m_plot3); 
	varr.Plot(m_plot4);

	// Gen. a descrition of freq flow
	int alen2 = darr.GetSize();
	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		zarr.Add(darr[loop2] * 1000);		
		zarr.Add(varr[loop2]);		
		}

	zarr.Plot(m_plot5);

		//parr[0]->Plot(m_plot10);
	//parr[1]->Plot(m_plot11);

	//parr[0]->Smooth(2);
	//parr[1]->Smooth(2);
	
	//parr[1]->Copy(*parr[0]);
	//parr[1]->Smooth(40);
	
	//CIntArr darr, varr, aarr , zarr; 
	//TurnArr(parr[0], &darr, &varr);

	//darr.Plot(m_plot11);
	//varr.Plot(m_plot12);

	// Dump fuzzy set
	//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->record)
	//	{
	//	int alen = darr.GetSize();
	//	for(int loop = 0; loop < alen; loop++)
	//		{
	//		AP2N("%d:%d   ", darr[loop], varr[loop]);
	//		}
	//	AP2N("\r\n");
	//	}

	// Gen. a descrition of freq flow
	int alen2 = darr.GetSize();
	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		zarr.Add(darr[loop2]);		
		zarr.Add(varr[loop2]);		
		}

	// Dump fuzzy set
	if( ((CPlay*)AfxGetApp()->m_pMainWnd)->record)
		{
		int zlen = zarr.GetSize() / 2;
		for(int zloop = 0; zloop < zlen; zloop++)
			{
			AP2N("%d:%d   ", zarr[2 * zloop], zarr[2 * zloop + 1]);
			}
		AP2N("\r\n");
		}

	parr[0]->RemoveAll();
	parr[1]->RemoveAll();

	parr[0]->Copy(zarr);
	//parr[1]->Copy(varr);


#endif

//////////////////////////////////////////////////////////////////////////
// Get index of maximum error point between two indexes

int CBend::GetMaxErrPoint(CIntArr *inarr, int startp, int endp, int *xerr)

{
	int erridx = 0, errmax = INT_MIN;
	int startval = inarr->GetAt(startp), endval	= inarr->GetAt(endp);
	int dist = endp - startp, delta = endval - startval;

	if(dist <= 0) 
		{
		//AP2N("GetMaxErrPoint - Zero Distance\r\n");
		return 0;		// Avoid short distances DIVZ
		}

	double slope = (double)delta / dist;

	//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
	//	{
	//	AP2N("*** slope=%.0f \r\n", slope);	
	//	AP2N("startval=%d endval=%d\r\n", startval, endval);
	//	}
			
	//int alen = endp;
	for(int loop = startp; loop < endp; loop++)
		{
		int lineinst = startval +  (int)(slope * (loop - startp));
		int errinst =  abs(inarr->GetAt(loop) - lineinst);

		//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
		//	AP2N("lineinst=%d errinst=%d\r\n", lineinst, errinst);	

		if(errmax < errinst)
			{
			errmax = errinst; erridx = loop;
			}
 		}

	//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
	//	AP2N("erridx=%d inidx=%d outidx=%d\r\n", erridx, startp, endp);	
			
	*xerr = errmax;
	return erridx;
}


//////////////////////////////////////////////////////////////////////////
// Simplify graph

void CBend::ChartScript(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr)

{
	CIntArr arr;
	
	// Add the two poles
	arr.Add(0);	arr.Add(inarr->GetUpperBound());

	// Loop over the distance formula
	for(int loop = 0; loop < BEND_ARR_COUNT; loop++)
		{
		int maxerr = INT_MIN;

//		if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
//			AP2N("Looping over %d\r\n", loop);
		
		int alen = arr.GetSize();
		for(int loop2 = 0; loop2 < alen - 1; loop2++)
			{
			int xerr = 0;
			int	erridx = GetMaxErrPoint(inarr, arr[loop2], arr[loop2+1], &xerr);

			//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
			//	AP2N("erridx=%d inidx=%d outidx=%d xerr=%d\r\n", 
			//				erridx, arr[loop2], arr[loop2+1], xerr);	

			// Only add point if error is larger than ...
			if(xerr > 0)
				{	
				loop2++; alen++;
				arr.InsertAt(loop2, erridx);
				}
			
			maxerr = max(maxerr, xerr);

			//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
			//	AP2N("Maxerr %d\r\n", maxerr);
		
			//ouarr->Add(erridx); 
			varr->Add(inarr->GetAt(erridx));
 			}

		//if(maxerr < 50)
		//	break;

		//break;  // test
 		}

	//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
		
	arr.DumpAll();
	varr->DumpAll();

	ouarr->Copy(arr);
}

//////////////////////////////////////////////////////////////////////////
// Produce script in reverse (decompile)

void CBend::UnChartScript(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr)

{
	// Produce script in reverse (decompile)

	ouarr->RemoveAll();

	int alen = inarr->GetSize();
	for(int loop3 = 0; loop3 < alen-1; loop3++)
		{
		int curr = inarr->GetAt(loop3), next = inarr->GetAt(loop3 + 1);

		int ss = inarr->GetAt(curr), ee = inarr->GetAt(next);
		int hh = ee - ss;		//hh  = quantize (hh, 20);
		int dd = next - curr;   //dd = quantize (dd, 80);

		double ramp = (double) hh / dd;

		for(int loop4 = curr; loop4 < next; loop4++)
			{
			ouarr->Add(ss + int(ramp * (loop4 - curr)));
			//ouarr->Add((ss + ee) / 2);
			}
 		}

	ouarr->Smooth(1);

}

//////////////////////////////////////////////////////////////////////////

//DEL void CBend::BuildPlotArr()
//DEL 
//DEL {
//DEL 	plotarr[0] = m_plot1;
//DEL 	plotarr[1] = m_plot2;
//DEL 	plotarr[2] = m_plot3;
//DEL 	plotarr[3] = m_plot4;
//DEL 	plotarr[4] = m_plot5;
//DEL 	plotarr[5] = m_plot6;
//DEL 	plotarr[6] = m_plot7;
//DEL 	plotarr[7] = m_plot8;
//DEL }

//////////////////////////////////////////////////////////////////////////

int	CBend::xBendSpectra(short *ptr, int len, CIntArr *pspec) 

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	pspec->RemoveAll();
	
	CIntArr varr,  varrd,  darr,  darrd;
	xProcBuff(ptr, len, &varr, &darr);
	xConvDist(&darr, &darrd, &varr, &varrd);

	// Three/Four recursion covers most all (unrolled) ...
	//  ... tested with white noise -- mostly even spectra
	
	CIntArr varr2, varrd2, darr2, darrd2;
	xTurnRecurse(&darr, &varr, &darr2, &varr2);
	xConvDist(&darr2, &darrd2, &varr2, &varrd2);

#if 0

	CIntArr varr3, varrd3, darr3, darrd3;
	xTurnRecurse(&darr2, &varr2, &darr3, &varr3);
	xConvDist(&darr3, &darrd3, &varr3, &varrd3);

	CIntArr varr4, varrd4, darr4, darrd4;
	xTurnRecurse(&darr3, &varr3, &darr4, &varr4);
	xConvDist(&darr4, &darrd4, &varr4, &varrd4);

	//darrd.Plot(pwnd->plotarr[0]);
	//darrd2.Plot(pwnd->plotarr[1]);
	//darrd3.Plot(pwnd->plotarr[2]);
	//darrd4.Plot(pwnd->plotarr[3]);

#endif

#if 0
	// Expand the top 
#define	 CALC								\
	if(idx < 1)							    \
		 true; 								\
	else if(idx < 12)						\
		pspec->AddToVal(idx * 2, val);		\
	else									\
		pspec->AddToVal(idx + 12, val);		\

#endif

	#define	 CALC							\
			if(idx > 1) pspec->AddToVal( 2 * idx, val * idx * idx);

			//if(idx > 2) pspec->AddToVal(idx, val);

	// Convert it to spectra
	int loop, idx, val, alen = darrd.GetSize();
	for(loop = 0; loop < alen; loop++)
		{
		idx = darrd.GetAt(loop); 		
		val = abs(varrd.GetAt(loop)); 		
		CALC	
 		}

	alen = darrd2.GetSize();
	for(loop = 0; loop < alen; loop++)
		{
		idx = darrd.GetAt(loop); 		
		val = abs(varrd.GetAt(loop)); 		
		CALC
 		}

#if 0

	alen = darrd3.GetSize();
	for(loop = 1; loop < alen; loop++)
		{
		idx = darrd.GetAt(loop); 		
		val = abs(varrd.GetAt(loop)); 		
		CALC
 		}

	alen = darrd4.GetSize();
	for(loop = 1; loop < alen; loop++)
		{
		idx = darrd.GetAt(loop); 		
		val = abs(varrd.GetAt(loop)); 		
		CALC
 		}
#endif

	pspec->NormArrHeight(255);

	// Post process
	//pspec->NormArrHeight(1000000);
	//pspec->Smooth(5);

	// Compansate for frequency dependence
	//int alenc = pspec->GetSize();
	//for(int loopc = 0; loopc < alenc; loopc++)
	//	{
	//	double mul = 1 - loopc / 50;
	
	//	int val = pspec->GetAt(loopc);
	//	pspec->SetAt(loopc, mul * val);
	//	}

	// Duplicate plot for compare
	//pspec->Plot(pwnd->plotarr[4]);
	//pwnd->plotarr[4]->AddMarker();
	
	//pspec->Plot(pwnd->plotarr[5]);
	//pwnd->plotarr[5]->AddMarker();

	return 0;
}

//////////////////////////////////////////////////////////////////////////

#if 0
	// Dispose of nulls at beginning 
	int len = parr[0]->GetSize();
	for(int loop = 0; loop < len; loop++)
		{
		if(parr[0]->GetAt(loop) > 50)
			{	
			//P2N("Removing begin %d\r\n", loop);
			for(int loop6b = 0; loop6b < BEND_ARR_COUNT; loop6b++)
				parr[loop6b]->RemoveAt(0, loop);

			//parr[0]->RemoveAt(0, loop);

			len = parr[0]->GetSize();
			break;
			}
		}

	// Dispose of nulls at end
	for(int loope = len - 1; loope >= 0; loope--)
		{
		if(parr[0]->GetAt(loope) > 50)
			{
			//P2N("Removing end %d %d\r\n", loope, len - 1);
			for(int loop6c = 0; loop6c < BEND_ARR_COUNT; loop6c++)
				parr[loop6c]->RemoveAt(loope, (len - 1) - loope);

			//parr[0]->RemoveAt(loope, (len - 1) - loope);

			len = parr[0]->GetSize();
			break;
			}
		}
#endif


#if 0

/* Handle several math errors caused by passing a negative argument
 * to log or log10 (_DOMAIN errors). When this happens, _matherr
 * returns the natural or base-10 logarithm of the absolute value
 * of the argument and suppresses the usual error message.
 */

int _matherr( struct _exception *except )

{
    /* Handle _DOMAIN errors for log or log10. */
    if( except->type == _DOMAIN )
		{
		if( strcmp( except->name, "log" ) == 0 )
			{
			except->retval = log( -(except->arg1) );
			P2N( "Special: using absolute value: %s: _DOMAIN "
					 "error\n", except->name );
			return 1;
			}
		else if( strcmp( except->name, "log10" ) == 0 )
			{
			except->retval = log10( -(except->arg1) );
			
			P2N( "Special: using absolute value: %s: _DOMAIN "
						 "error\n", except->name );
			return 1;
			}
		}
    else
		{
		P2N( "Normal: " );
		return 0;    /* Else use the default actions */
		}
	return 0;
}

#endif
