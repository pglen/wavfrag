
/* =====[ FreqScan.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the FreqScan.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  10/12/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "FreqScan.h"
#include "mxpad.h"
#include "wavfragDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//double pi		= 3.1415926535; 

double	pi		= 2 * acos(0);
double	halfpi	= acos(0);

//////////////////////////////////////////////////////////////////////////

//#define SINRAMP_ENABLE 1
//#define RAMP_ENABLE 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFreqScan::CFreqScan()

{
	
#ifdef PLOT_ENABLE
	m_plot1 = m_plot2 = m_plot3 = NULL;
	m_plot4 = m_plot5 = m_plot6 = NULL;
	m_plot7 = m_plot8 = m_plot9 = NULL;
#endif

	samplerate	 = 44100;		// Assuming CD HiFi
	smoothfactor = 4;

	//want_len = 0;

	// Configurables here

	start_freq	=  200;
	end_freq	=  20000;
	multiplier	=  .05;
	scan_len	=  1024;

	resarr1 = resarr2 = resarr3 = NULL;
	resarr4 = resarr5 = resarr6 = NULL;
	resarr7 = resarr8 = resarr9 = NULL;

	// Frequency scan for ....
	//freq[0] = 110;
	//freq[1] = 220;
	//freq[2] = 440;
	//freq[3] = 880;
	//freq[4] = 1600;
	//freq[5] = 3200;

	// Frequency scan for ....
	//freq[0] = 220;
	//freq[1] = 330;
	//freq[2] = 440;
	//freq[3] = 550;
	//freq[4] = 660;
	//freq[5] = 1600;
	//freq[6] = 3200;
	//freq[7] = 6400;
}

CFreqScan::~CFreqScan()

{

}

//////////////////////////////////////////////////////////////////////////
// Check if buffer has signal in it
// Scan medium and hight buffers
//
	
int CFreqScan::IsSignal(short *ptr, int len, int tresh)

{
	int is_signal = 0;
	int len2 = len / sizeof(short), start = 0, endd = 0;

	int hitresh = tresh / 2 ;

	CIntArr	medarr, higharr;

	xScanOneFreq(ptr, len2, 440, &medarr);
	int lenn = medarr.GetSize();
	
	xScanOneFreq(ptr, len2, 6400, &higharr);
	higharr.NormArrLen(lenn);

	//medarr.Plot(m_plot8);
	//higharr.Plot(m_plot9);

	//////////////////////////////////////////////////////////////////////////

	int cnt = 0, leny = medarr.GetSize();
	for(int loopz = 0; loopz < leny; loopz++)
		{
		if(medarr.GetAt(loopz) > tresh )
			{	
			cnt++;
			if(cnt > 5)
				{
				is_signal++;
				break;
				}
			}
		}

	int cnt2 = 0, leny2 = higharr.GetSize();
	for(int loopz2 = 0; loopz2 < leny2; loopz2++)
		{
		if(higharr.GetAt(loopz2) > hitresh)
			{	
			cnt2++;
			if(cnt2 > 5)
				{
				is_signal++;
				break;
				}
			}
		}

	//P2N("CFreqScan::IsSignal is_signal=%d\r\n", is_signal);

	return is_signal;
}

//////////////////////////////////////////////////////////////////////////

void CFreqScan::Scan(short *ptr, int len, CIntArr  *piarr)

{
	CIntArr arr, resarr;

	int len2 = len / sizeof(short);

	int cnt = 0;

	double freq = start_freq;

	resarr.SetSize(255);

	//int fstep = end_freq / 255 + 1;

	while(true)
		{		
		xScanOneFreq(ptr, len2, (int)freq, &arr);
		
		//int sum = arr.Sum();
		int sum = arr.Max();
		if(sum < 0) sum = 0;

		//int idx = freq / fstep;

		resarr.SetAt(cnt, sum);
		
		AP2N("%-2d freq=%-4d sum=%d\t", cnt, (int)freq, (int)sum);

		freq *= 1 + multiplier; cnt++;

		if(freq > end_freq)
			break;
		}
	
#define PEAKS2

#ifdef PEAKS
	
	CIntArr d1, v1;

	resarr.Smooth(2);
	resarr.TurnArr(&d1, &v1, 1);

	piarr->SetSize(255);

	int alen = d1.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		int idx = d1.GetAt(loop), val = v1.GetAt(loop);

		piarr->SetAt(idx, val);
 		}

	//int x1, x2, v1, v2, x3, x4, v3, v4;
	//resarr.FindMax4(&x1, &v1, &x2, &v2, &x3, &v3, &x4, &v4);
	
	//if(x1 >= 0)	piarr->SetAt(x1, v1);	
	//if(x2 >= 0)	piarr->SetAt(x2, v2);
	//if(x3 >= 0)	piarr->SetAt(x3, v3);	
	//if(x4 >= 0)	piarr->SetAt(x4, v4);

#else
	piarr->Copy(resarr);
	piarr->SetSize(255);

#endif

	piarr->NormArrHeight(255);
	//piarr->Plot(m_plot6); m_plot6->AddMarker();
	//piarr->NormArrHeight(255);
}


//////////////////////////////////////////////////////////////////////////
//

int CFreqScan::ScanBuff2(short *ptr, int len, CPtrArray *parr)

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	CPtrArray arr, tmparr;

	//////////////////////////////////////////////////////////////////////
	// Turn array to time progression array
	//
	//  val->Get
	//	* * * * * * * parr->Get
	//	* * * * * * *
	//	* * * * * * *
	//	* * * * * * *
	//

	// Alloc placeholder for results
	//int alen = ((CIntArr*)tmparr.GetAt(0))->GetSize();

	//int alen = len / 512;
	//xNormLen(&tmparr, alen);

	int tlen = tmparr.GetSize();
	for(int loopt3 = 0; loopt3 < tlen; loopt3 += 1)
		{
		CIntArr *val = (CIntArr*)tmparr.GetAt(loopt3);
	
		//val->Plot(&pwnd->plotdlg.m_plot2);
		//pwnd->plotdlg.m_plot2.AddMarker();
		}

	for(int loop = 0; loop < tlen; loop++)
		{
		CIntArr *tmp = new CIntArr; ASSERT(tmp);
		arr.Add(tmp);
 		}

	// Copy from analisys
	for(int loop2 = 0; loop2 < tlen; loop2++)
		{
		CIntArr *targ = (CIntArr*)arr.GetAt(loop2);
			
		int tlen = tmparr.GetSize();
		for(int loop3 = 0; loop3 < tlen; loop3 += 1)
			{
			CIntArr *val = (CIntArr*)tmparr.GetAt(loop3);
			int ival = val->GetAt(loop2);
			targ->Add(ival);
			}
		//targ->NormArrHeight(255);
 		}

	// Free tmp array
	int falen = tmparr.GetSize();
	for(int floop = 0; floop < falen; floop++)
		{
		CIntArr *val = (CIntArr *)tmparr.GetAt(floop);
		delete val;
 		}

	parr->Copy(arr);


	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CFreqScan::ScanBuff(short *ptr, int len, CPtrArray *parr)

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	// Test deactivation
	//return 0;

	int onescan = scan_len;
	for(int loops = onescan; loops < len - onescan; loops += onescan)
		{
		CIntArr	*piarr = new CIntArr; ASSERT(piarr);
		parr->Add(piarr);

		//xScanBuff(ptr + loops, onescan, piarr);
		xScanBuff(ptr + loops - onescan / 4,  onescan + onescan / 2, piarr);

		//CPtrArray tmparr;
		//xScanBuff(ptr + loops - onescan / 2, 2 * onescan, &tmparr);

		// Cut out the middle
		//int alen = tmparr.GetSize(), sss = 3 * alen / 4;
		//for(loop = alen / 4; loop < sss; loop++)
		//	{
		//	parr->Add(tmparr.GetAt(loop);
		//	}
		//
		
		piarr->NormArrHeight(255);

		//piarr->Plot(&pwnd->plotdlg.m_plot1);
		//pwnd->plotdlg.m_plot1.AddMarker();
	
		//piarr->Plot(&pwnd->plotdlg.m_plot2);
		//pwnd->plotdlg.m_plot2.AddMarker();
		}

	return 0;
}

// -----------------------------------------------------------------------
//
/// \brief  CFreqScan::PostPro  Brief Here 
/// 
/// \details CFreqScan::PostPro Descibe Here 
/// \n  
/// Return type:      void 
/// \n  
/// \param *parr[] Arg Type: CIntArr 
//
// -----------------------------------------------------------------------

void CFreqScan::xPostPro(CPtrArray *parr)

{	
	//NormScan(parr);

	int loop3a, alen3 = parr->GetSize();

	//for(loop3a = 0; loop3a < alen3; loop3a++)
	//	((CIntArr*)parr->GetAt(loop3a))->Smooth(2);

	//for(loop3a = 0; loop3a < alen3; loop3a++)
	//	((CIntArr*)parr->GetAt(loop3a))->Smooth(4);

#if 1
	// Normalize them to the same len
	int normbase = alen3 / 4;

	//for(int loop3b = 0; loop3b < alen3; loop3b++)
	//	((CIntArr*)parr->GetAt(loop3b))->Smooth(1);	
	
	//if(!want_len)
	//want_len = ((CIntArr*)parr->GetAt(normbase))->GetSize();

	for(loop3a = 0; loop3a < alen3; loop3a++)
		{
		//((CIntArr*)parr->GetAt(loop3a))->NormArrLen(want_len);
		}	
#endif

	//((CIntArr*)parr->GetAt(0))->Smooth(1);	
	
	//for(loop3a = 0; loop3a < alen3; loop3a++)
	//	((CIntArr*)parr->GetAt(loop3a))->Smooth(4);

	//for(loop3a = 0; loop3a < alen3; loop3a++)
	//	((CIntArr*)parr->GetAt(loop3a))->NormArrHeight(4000);

	// Create max array
#if 0
	CIntArr *arr = new CIntArr; ASSERT(arr);
	CIntArr *valx = (CIntArr*)parr->GetAt(0);

	for(int loop4 = 0; loop4 < valx->GetSize(); loop4++)
		{
		int	idx = 0, mm = 0;
		
		for(loop3a = 0; loop3a < alen3; loop3a++)
			{
			CIntArr *val = (CIntArr*)parr->GetAt(loop3a);
			
			if(val->GetAt(loop4) > mm)
				{
				mm =  val->GetAt(loop4);
				idx = loop3a;
				}
			}
		arr->Add(idx);
		}
	parr->Add(arr);
#endif


	// Examine turns
#if 0
	CIntArr turn, vturn;
	((CIntArr*)parr->GetAt(0))->TurnArr(&turn, &vturn, true);

	turn.DumpAll();	
	//vturn.DumpAll();

	int alen4 = turn.GetSize();
	for(int loop = 0; loop < alen4; loop++)
		{
		for(loop3a = 0; loop3a < alen3; loop3a++)
			{
			int val = ((CIntArr*)parr->GetAt(loop3a))->GetAt(turn[loop]);
			AP2N("%d  ", val);
			}
		AP2N("    ");
 		}
	AP2N("\r\n");
#endif
	
	// Test by removing the components
	//parr[0]->RemoveAll();
	//parr[1]->RemoveAll();
	//parr[2]->RemoveAll();
	//parr[3]->RemoveAll();
	//parr[4]->RemoveAll();
	//parr[5]->RemoveAll();

}

// -----------------------------------------------------------------------
//
/// \brief  CFreqScan::ScanBuff2  Brief Here 
/// 
/// \details CFreqScan::ScanBuff2 Descibe Here 
/// \n  
/// Return type:      int 
/// \n  
/// \param *ptr Arg Type: short 
/// \param len Arg Type: int 
/// \param  *ptrarr Arg Type: CPtrArray 
//
// -----------------------------------------------------------------------

int CFreqScan::xScanBuff(short *ptr, int len, CIntArr  *piarr)

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	int		cnt = 0, prev_samp = 0;
	double	prev_freq = start_freq, freq = start_freq;

#if 0
	// Skip till zero cross

	short *wstart = ptr;
	short *wend = ptr + len;
	short *wlim  = ptr + len / 4;
	short *welim = (ptr + len) - len / 4;

	//////////////////////////////////////////////////////////////////////
	// Do the beginning
	
	while(true)
		{
		// Frame boundaries
		if(wstart >= wlim)
			break;
		
		// Test for zcross
		if( *wstart <= 0 && *(wstart + 1) > 0)
			break;

		wstart ++;
		}

	//////////////////////////////////////////////////////////////////////
	// Do the end
	
	while(true)
		{
		// Frame boundaries
		if(wend <  welim)
			break;
		
		// Test for zcross
		if( *wend >= 0 && *(wend -1) < 0)
			break;

		wend--;
		}

	AP2N("CFreqScan::xScanBuff zcross skip %d eskip %d\r\n", 
										wstart - ptr, ptr + len - wend);
#endif

	//CIntArr *pcurr = new CIntArr; ASSERT(pcurr);
		
	while(true)
		{
		int sss = 0;

		int onewave = int(samplerate / freq);	
				
		// Only scan of the sample count changed
		if(onewave != prev_samp)
			{
			sss = xScanOneFreq2(ptr, len, (int)freq);
			//sss = xScanOneFreq2(wstart, wend - wstart, (int)freq);

			//AP2N("%-2d freq=%-4d\tonewave=%d len=%d\r\n", 
			//					cnt, (int)freq, onewave, pcurr->GetSize());
			//xBellCurve(&sss);
			piarr->Add(sss);
			//piarr->Add(sss);			
			}

		prev_samp = onewave;
		freq *= 1 + multiplier; 
		//freq += 50;

		if(freq > end_freq)
			break;

		cnt++;		
		}

	//AP2N("cnt = %d\r\n", cnt);
	
	return 0;
}

// -----------------------------------------------------------------------
//
/// \brief  CFreqScan::ScanOneFreq  Brief Here 
/// 
/// \details CFreqScan::ScanOneFreq Descibe Here 
/// \n  
/// Return type:      int 
/// \n  
/// \param *ptr Arg Type: short 
/// \param len Arg Type: int 
/// \param freq Arg Type: int 
/// \param *parr Arg Type: CIntArr 
//
// -----------------------------------------------------------------------

int CFreqScan::xScanOneFreq(short *ptr, int len, int freq, CIntArr *parr)

{
	double	sumsum = 0, sum1 = 0, sum2 = 0, sum = 0, sumf = 0;
	double	sum1f = 0, sum2f = 0;
	double	sumavg = 0;

	int		len2 = len, putcnt = 0;

	// Do freq Hz, assume 44100 pps
	int onewave = samplerate / freq;
	
	//AP2N("CFreqScan::xScanOneFreq freq=%d onewave=%d\r\n", freq, onewave);

	int halfwave = onewave / 2, quartwave = onewave / 4;

	short *ptr2 = ptr;

	//if(freq == 200)
	//	AP2N("CFreqScan::xScanOneFreq zcross=%d len3=%d len2=%d\r\n", ptr2 - ptr, len-len3, len);

	parr->RemoveAll();

	for(int loop = 0; loop + onewave + halfwave < len2; /* loopop none */ )
		{ 
		sum2  = sum1 = 0;
		sum2f = sum1f = 0;

		for(int loop2 = 0; loop2 < halfwave; loop2++)
			{
			double tmpf = *(ptr2 + quartwave );
			double tmp = *ptr2++;		
		
			// Enabling the ramp cleaned it up substanically

#ifdef  SINRAMP_ENABLE		
			// This is for providing ramp up/down -- 
			if(loop2 < quartwave)
				{
				double ff = sin(loop2 * halfpi / quartwave);
				tmp *= ff;
				tmpf *= ff;
				}
			else
				{
				double ff = sin((halfwave - loop2) * halfpi / quartwave);
				
				tmp *= ff;
				tmpf *= ff;
				}
#endif

#ifdef  RAMP_ENABLE		
			// This is for providing ramp up/down -- 
			if(loop2 < quartwave)
				tmp *= (double)loop2 / quartwave;	
			else
				tmp *= (double)(halfwave - loop2) / quartwave ;
#endif

			sum1f += tmpf;
			sum1 += tmp; loop++; 
			}

		for(loop2 = 0; loop2 < halfwave; loop2++)
			{
			double tmp2f = *(ptr2 + quartwave);
			double tmp2 = *ptr2++;
		
#ifdef  SINRAMP_ENABLE		
			// This is for providing ramp up/down -- 
			if(loop2 < quartwave)
				{	
				double ff = sin(loop2 * halfpi / quartwave);
				tmp2 *=  ff;
				tmp2f *=  ff;
				}
			else
				{
				double ff = sin((halfwave - loop2) * halfpi / quartwave);
				
				tmp2 *= ff;
				tmp2f *= ff;
				}
#endif

#ifdef  RAMP_ENABLE		
			// This is for providing ramp up/down -- 
			if(loop2 < quartwave)
				tmp2 *=  (double)loop2 / quartwave;	
			else
				tmp2 *= (double)(halfwave - loop2) / quartwave;
#endif

			sum2f += tmp2f;
			sum2 += tmp2; loop++; 
			}
		
		sum = (sum1 + sum2);
		//sum = (fabs(sum1) - fabs(sum2));
		sumf = (sum1f + sum2f);

		double tmpsum  = fabs(sum);
		double tmpsum2 = fabs(sumf);		

		//double res = (double)freq * tmpsum;
		//double res = (double)freq * (tmpsum2 + tmpsum);
		//double res = (double)freq * freq * (tmpsum2 + tmpsum);
		//res = sqrt(res);
		
		//double res = tmpsum * freq;
		double res = tmpsum2 + tmpsum;

		res /= 5000;

		parr->Add(int(res));

		//if(++putcnt % 1000 == 0)
		//	{	
		//	AP2N("CFreqScan::xScanOneFreq %d %d\r\n", freq, put);
		//	}

		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CFreqScan::xScanOneFreq2(short *ptr, int len, int freq)

{
	// Do freq in Hz, assume 44100 sps
	int onewave = samplerate / freq;	
	int halfwave = onewave / 2;
	int quartwave = onewave / 4;

	//AP2N("CFreqScan::xScanOneFreq len=%d freq=%d onewave=%d\r\n", 
	//												len, freq, onewave);

	short *ptr2 = ptr;	int prog = 0, lastout = 0;

	double sum  = 0;

	while(true)
		{
		if(prog >= len - onewave)
			break;
		
		for(int loop = 0; loop < halfwave; loop++)
			{
			sum += *ptr2++; prog++;
			}

		for(int loop2 = 0; loop2 < halfwave; loop2++)
			{
			sum -= *ptr2++; prog++;
			}
		}

	sum = fabs(sum);		// It is an accumulated SUM
	sum /= onewave;			// Adjust for frequency components
	sum /= 200;				// Adjust for plot range
 
	return (int)sum;
}

//////////////////////////////////////////////////////////////////////////

//DEL void CFreqScan::BuildPlotArr()
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
// Get index of maximum error point between two indexes

int CFreqScan::xGetMaxErrPoint(CIntArr *inarr, int startp, int endp, int *xerr)

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

#define  NUM_SCANS 8


//////////////////////////////////////////////////////////////////////////
// Produce script in reverse (decompile)

void CFreqScan::xUnChartScript(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr)

{
	// Produce script in reverse (decompile)

	ouarr->RemoveAll();

	int alen = inarr->GetSize();
	for(int loop3 = 0; loop3 < alen-1; loop3++)
		{
		int curr = inarr->GetAt(loop3), next = inarr->GetAt(loop3 + 1);

		int ss = varr->GetAt(loop3), ee = inarr->GetAt(loop3 + 1);
		int hh = ee - ss;		hh  = xQuantize (hh, 200);
		int dd = next - curr;   dd = xQuantize (dd, 200);

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
// Simplify graph

void CFreqScan::xChartScript2(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr)

{
	CIntArr arr;
	
	ouarr->RemoveAll(); varr->RemoveAll();

	if(inarr->GetSize() == 0)
		return;

	// Add the two poles
	arr.Add(0);	arr.Add(inarr->GetUpperBound());

	// Loop over the distance formula
	for(int loop = 0; loop < 6; loop++)
		{
		int maxerr = INT_MIN;

		//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
		//	AP2N("Looping over %d\r\n", loop);
		
		int alen = arr.GetSize();
		for(int loop2 = 0; loop2 < alen - 1; loop2++)
			{
			int xerr = 0;
			int	erridx = xGetMaxErrPoint(inarr, arr[loop2], arr[loop2+1], &xerr);

			//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
			//	AP2N("erridx=%d inidx=%d outidx=%d xerr=%d\r\n", 
			//				erridx, arr[loop2], arr[loop2+1], xerr);	

			// Only add point if error is larger than ...
			if(xerr > 20)
				{	
				loop2++; alen++;
				arr.InsertAt(loop2, erridx);
				}
			
			maxerr = max(maxerr, xerr);

			//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
			//	AP2N("Maxerr %d\r\n", maxerr);
		
			//ouarr->Add(erridx); varr->Add(inarr->GetAt(erridx));
 			}

		//if(maxerr < 50)
		//	break;

		//break;  // test
 		}

	// Output boundary values:
	int xlen = arr.GetSize();
	for(int loopx = 0; loopx < xlen; loopx++)
		{
		int idxx = arr.GetAt(loopx);
		varr->Add(inarr->GetAt(idxx));
		}

	//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
	//	arr.DumpAll();

	// Produce script in reverse

	int alen = arr.GetSize();
	for(int loop3 = 0; loop3 < alen-1; loop3++)
		{
		int curr = arr[loop3], next = arr[loop3 + 1];

		int ss = inarr->GetAt(curr), ee = inarr->GetAt(next);
		int hh = ee - ss;		hh  = xQuantize (hh, 10);
		int dd = next - curr;	dd = xQuantize (dd, 10);

		double ramp = (double) hh / dd;

		for(int loop4 = curr; loop4 < next; loop4++)
			{
			ouarr->Add(ss + int(ramp * (loop4 - curr)));
			}
 		}
}

//////////////////////////////////////////////////////////////////////////
// Quantize in %

int		CFreqScan::xQuantize(int ii, int dd)

{
	int res = ii;

	//res = (res * dd) / dd;

	int ddd = ii * dd / 100;
	if(ddd == 0) ddd = 1;


	if((ii % ddd) > ddd / 2)
		res = ii + (ddd - (ii % ddd));
	else
		res = ii - (ddd - (ii % ddd));

	//if( ((CPlay*)AfxGetApp()->m_pMainWnd)->stablized)
	//	AP2N("Quantize ii=%d res=%d dd=%d\r\n", ii, res, ddd);
		
	return res;

	//return ii;
}

//////////////////////////////////////////////////////////////////////////

void	CFreqScan::xBellCurveArr(CIntArr *inarr)

{
	CIntArr arr;

	int alen = inarr->GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		int val = inarr->GetAt(loop); xBellCurve(&val);
		arr.Add(val);	
 		}
	inarr->RemoveAll(); inarr->Copy(arr);
}

//////////////////////////////////////////////////////////////////////////

void	CFreqScan::xBellCurve(int *ff)

{
	*ff = (int)sqrt(100 * (*ff) );
}

//////////////////////////////////////////////////////////////////////////
// Normalize them to the same len

void CFreqScan::xNormLen(CPtrArray *parr, int newlen)

{	
	int alen3 = parr->GetSize();

	for(int loop3 = 0; loop3 < alen3; loop3++)
		{
		CIntArr *tmp = (CIntArr*)parr->GetAt(loop3);

		ASSERT(tmp->magic == CIntArr_MAGIC);
		tmp->NormArrLen(newlen);
		}	
}