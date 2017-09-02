
/* =====[ FreqScan.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the FreqScan.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/15/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_FREQSCAN_H__ED826AFB_3A5A_4F4A_BB2D_FA3F5232EC47__INCLUDED_)
#define AFX_FREQSCAN_H__ED826AFB_3A5A_4F4A_BB2D_FA3F5232EC47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

#include "plot.h"
#include "intarr.h"

// Obsolete
#define NUM_SCAN_ARRAYS	9

// Define this to plot, will only compile in test harness
#define PLOT_ENABLE	1		

#define DECL_SCAN_ARRARR(arrx) \
	CIntArr cmparr1, cmparr2, cmparr3, cmparr4, \
	cmparr5, cmparr6, cmparr7, cmparr8, cmparr9;  \
	CIntArr	*arrx[NUM_SCAN_ARRAYS] = \
	{ &cmparr1, &cmparr2, &cmparr3, &cmparr4, \
		&cmparr5, &cmparr6, &cmparr7, &cmparr8, &cmparr9 }; \

class CFreqScan  
{
public:

	
#ifdef PLOT_ENABLE

	CPlot		*m_plot9;
	CPlot		*m_plot8;
	CPlot		*m_plot7;
	CPlot		*m_plot6;
	CPlot		*m_plot5;
	CPlot		*m_plot4;
	CPlot		*m_plot3;
	CPlot		*m_plot2;
	CPlot		*m_plot1;

	CPlot		*plotarr[NUM_SCAN_ARRAYS];

#endif

	CIntArr *resarr1;
	CIntArr *resarr2;
	CIntArr *resarr3;
	CIntArr *resarr4;
	CIntArr *resarr5;
	CIntArr *resarr6;
	CIntArr *resarr7;
	CIntArr *resarr8;
	CIntArr *resarr9;

	void	Scan(short *ptr, int len, CIntArr  *piarr);

	//int		is_signal;


	int		start_freq,	end_freq;
	double	multiplier;

	int		scan_len;

	int		ScanBuff(short *ptr, int len, CPtrArray *parr);
	int		ScanBuff2(short *ptr, int len, CPtrArray *parr);

	int		IsSignal(short *ptr, int len, int tresh = 100);


	CFreqScan();
	virtual ~CFreqScan();

private:

	void	xNormLen(CPtrArray *parr, int newlen = 100);
	void	xBellCurveArr(CIntArr *inarr);
	void	xBellCurve(int *ff);
	int		xQuantize(int ii, int dd);
	int		xGetMaxErrPoint(CIntArr *inarr, int startp, int endp, int *xerr);
	int		xScanOneFreq(short *ptr, int len, int freq, CIntArr *parr);
	int		xScanBuff(short *ptr, int len, CIntArr  *piarr);
	void	xPostPro(CPtrArray *parr);
	void	xChartScript2(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr);
	void	xUnChartScript(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr);
	int		xScanOneFreq2(short *ptr, int len, int freq);

// Data:

	int		samplerate, smoothfactor;
};

#endif // !defined(AFX_FREQSCAN_H__ED826AFB_3A5A_4F4A_BB2D_FA3F5232EC47__INCLUDED_)
