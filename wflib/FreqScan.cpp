
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

// FreqScan.cpp: implementation of the CFreqScan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wflib.h"
#include "FreqScan.h"
#include "mxpad.h"

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
#define RAMP_ENABLE 1

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

	start_freq	=  100;
	end_freq	=  20000;
	multiplier	=  .03;
	scan_len	=  1000;

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
	xfreq[0] = 200;
	xfreq[1] = 300;
	xfreq[2] = 350;
	xfreq[3] = 400;
	xfreq[4] = 450;
	xfreq[5] = 500;
	xfreq[6] = 550;
	xfreq[7] = 600;
	xfreq[8] = 650;
	xfreq[9] = 700;
	xfreq[10] = 800;
	xfreq[11] = 1200;
	xfreq[12] = 2400;
	xfreq[13] = 4800;
	xfreq[14] = 9600;
	xfreq[15] = 12000;
	xfreq[16] = 0;

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
// Scan horizontally, then copy to output

//DEL void CFreqScan::Scan(short *ptr, int len, CPtrArray  *piarr)
//DEL 
//DEL {
//DEL 	CIntArr arr, resarr;
//DEL 
//DEL 	int cnt = 0, size = len / 400;
//DEL 
//DEL 	// Pre - create output array
//DEL 	for(int loop = 0; loop < size; loop++)
//DEL 		{
//DEL 		CIntArr *tmp = new CIntArr; ASSERT(tmp);
//DEL 		piarr->Add(tmp);
//DEL 		}
//DEL 
//DEL 	double freq = start_freq, prev_samp = 0;
//DEL 
//DEL 	// -------------------------------------------------------------------
//DEL 	
//DEL 	while(true)
//DEL 		{	
//DEL 		int onewave = samplerate / (int)freq;	
//DEL 				
//DEL 		// Only scan if the sample count changed
//DEL 		if(onewave != prev_samp)
//DEL 			{
//DEL 			xScanOneFreq(ptr, len, (int)freq, &arr);
//DEL 
//DEL 			arr.NormArrLen(size);
//DEL 			//arr.NormArrHeight(255);
//DEL 
//DEL 			//AP2N("%-2d freq=%-4d size=%d\t", cnt, (int)freq, arr.GetSize());
//DEL 
//DEL 			// Copy to output array
//DEL 			for(int loopc = 0; loopc < size; loopc++)
//DEL 				{
//DEL 				CIntArr *tmp = (CIntArr *)piarr->GetAt(loopc);
//DEL 
//DEL 				int val = arr.GetAt(loopc);
//DEL 				//tmp->SetAtGrow(cnt, val);
//DEL 				tmp->Add(val);
//DEL 				}
//DEL 			cnt++;
//DEL 			}
//DEL 
//DEL 		prev_samp = onewave;
//DEL 		
//DEL 		freq *= 1 + multiplier; 
//DEL 
//DEL 		if(freq > end_freq)
//DEL 			break;
//DEL 		}	
//DEL }

//DEL int CFreqScan::ScanBuff2(short *ptr, int len, CPtrArray *parr)
//DEL 
//DEL {
//DEL 	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
//DEL 	
//DEL 	CPtrArray arr, tmparr;
//DEL 
//DEL 	//////////////////////////////////////////////////////////////////////
//DEL 	// Turn array to time progression array
//DEL 	//
//DEL 	//  val->Get
//DEL 	//	* * * * * * * parr->Get
//DEL 	//	* * * * * * *
//DEL 	//	* * * * * * *
//DEL 	//	* * * * * * *
//DEL 	//
//DEL 
//DEL 	// Alloc placeholder for results
//DEL 	//int alen = ((CIntArr*)tmparr.GetAt(0))->GetSize();
//DEL 
//DEL 	//int alen = len / 512;
//DEL 	//xNormLen(&tmparr, alen);
//DEL 
//DEL 	int tlen = tmparr.GetSize();
//DEL 	for(int loopt3 = 0; loopt3 < tlen; loopt3 += 1)
//DEL 		{
//DEL 		CIntArr *val = (CIntArr*)tmparr.GetAt(loopt3);
//DEL 	
//DEL 		//val->Plot(&pwnd->plotdlg.m_plot2);
//DEL 		//pwnd->plotdlg.m_plot2.AddMarker();
//DEL 		}
//DEL 
//DEL 	for(int loop = 0; loop < tlen; loop++)
//DEL 		{
//DEL 		CIntArr *tmp = new CIntArr; ASSERT(tmp);
//DEL 		arr.Add(tmp);
//DEL  		}
//DEL 
//DEL 	// Copy from analisys
//DEL 	for(int loop2 = 0; loop2 < tlen; loop2++)
//DEL 		{
//DEL 		CIntArr *targ = (CIntArr*)arr.GetAt(loop2);
//DEL 			
//DEL 		int tlen = tmparr.GetSize();
//DEL 		for(int loop3 = 0; loop3 < tlen; loop3 += 1)
//DEL 			{
//DEL 			CIntArr *val = (CIntArr*)tmparr.GetAt(loop3);
//DEL 			int ival = val->GetAt(loop2);
//DEL 			targ->Add(ival);
//DEL 			}
//DEL 		//targ->NormArrHeight(255);
//DEL  		}
//DEL 
//DEL 	// Free tmp array
//DEL 	int falen = tmparr.GetSize();
//DEL 	for(int floop = 0; floop < falen; floop++)
//DEL 		{
//DEL 		CIntArr *val = (CIntArr *)tmparr.GetAt(floop);
//DEL 		delete val;
//DEL  		}
//DEL 
//DEL 	parr->Copy(arr);
//DEL 
//DEL 
//DEL 	return 0;
//DEL }

//////////////////////////////////////////////////////////////////////////

int CFreqScan::ScanBuff(short *ptr, int len, CPtrArray *parr)

{
	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	// Test deactivation
	//return 0;

	int onescan = scan_len;
	for(int loops = onescan; loops < len - onescan; loops += onescan / 2)
		{
		CIntArr	*piarr = new CIntArr; ASSERT(piarr);
		
		parr->Add(piarr);

		xScanBuff(ptr + loops, onescan, piarr);
		//xScanBuff(ptr + loops - onescan / 4,  onescan + onescan / 2, piarr);
		//xScanBuff(ptr + loops - onescan / 2,  onescan + onescan / 2, piarr);
		//xScanBuff(ptr + loops - onescan,  onescan + onescan, piarr);

		// Cut out the middle
		//int alen = tmparr.GetSize(), sss = 3 * alen / 4;
		//for(loop = alen / 4; loop < sss; loop++)
		//	{
		//	parr->Add(tmparr.GetAt(loop);
		//	}
		//
		
		//piarr->NormArrHeight(255);	
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
	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	int		cnt = 0, prev_samp = 0;
	double	prev_freq = start_freq, freq = start_freq;

	short *wstart = ptr;
	short *wend = ptr + len;

#if 1
	// Skip till zero cross

	short *wlim  = ptr + len / 4;
	short *welim = (ptr + len) - len / 4;

	//////////////////////////////////////////////////////////////////////
	// Do the beginning	
	while(true)
		{
		// Frame boundaries
		if(wstart >= wlim)
			{
			wstart = ptr;
			break;
			}
		
		// Test for zcross
		if( *wstart <= 0 && *(wstart + 1) > 0)
			break;

		wstart++;
		}

	//////////////////////////////////////////////////////////////////////
	// Do the end
	
	while(true)
		{
		// Frame boundaries
		if(wend <  welim)
			{
			wend = ptr + len;
			break;
			}
		
		// Test for zcross
		if( *wend >= 0 && *(wend - 1) < 0)
			break;

		wend--;
		}
	
#endif

	//AP2N("CFreqScan::xScanBuff zcross skip %d eskip %d\r\n", 
	//									wstart - ptr, ptr + len - wend);

	while(true)
		{
		int sss = 0;
		int onewave = samplerate / (int)freq;	
				
		// Only scan if the sample count changed
		if(onewave != prev_samp)
			{
			//sss = xScanOneFreq2(ptr, len, (int)freq);
			sss = xScanOneFreq2(wstart, wend - wstart, (int)freq);

			//AP2N("%-2d freq=%-4d\tonewave=%d len=%d\r\n", 
			//					cnt, (int)freq, onewave, pcurr->GetSize());
			//xBellCurve(&sss);

			piarr->Add(sss);
			}

		prev_samp = onewave;
		freq *= 1 + multiplier; 

		//freq += 50;
		//freq = xfreq[cnt];

		if(freq > end_freq)
			break;

		if(freq == 0)
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

	parr->RemoveAll();

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
		
		sum = sum1 - sum2;
		//sum = (fabs(sum1) - fabs(sum2));
		//sumf = sum1f + sum2f;

		double tmpsum  = fabs(sum);
		//double tmpsum2 = fabs(sumf);		

		//double res = (double)freq * tmpsum;
		//double res = (double)freq * (tmpsum2 + tmpsum);
		//double res = (double)freq * freq * (tmpsum2 + tmpsum);
		//res = sqrt(res);
		
		double res = tmpsum * freq;
		//double res = tmpsum2 + tmpsum;

		res /= 1000000;
		
		if(++putcnt % 1000 == 0)
			{	
			AP2N("CFreqScan::xScanOneFreq %d %d\r\n", freq, (int)res);
			}

		parr->Add(int(res));
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CFreqScan::xScanOneFreq2(short *ptr, int len, int freq)

{
	// Do freq in Hz, assume 44100 sps
	int onewave = samplerate / freq;	
	int halfwave = onewave / 2;
	//int quartwave = onewave / 4;

	if(halfwave == 0)
		{
		AP2N("CFreqScan::xScanOneFreq2 halfwave = 0\r\n");
		return 0;
		}

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
			int tmp = *ptr2++; prog++;		
			
			if(halfwave > 8)
				{
				tmp *= loop;
				tmp /= halfwave;	
				}
			sum += tmp;
			}

		for(int loop2 = 0; loop2 < halfwave; loop2++)
			{
			int tmp = *ptr2++; prog++;
			
			if(halfwave > 8)
				{				
				tmp *= (halfwave - loop2);
				tmp /= halfwave;	
				}
			sum -= tmp;
			}
		}

	sum = fabs(sum);	    	// It is an accumulated SUM
	sum /= onewave;			// Adjust for frequency components
	sum /= 100;				// Adjust for plot range
 
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