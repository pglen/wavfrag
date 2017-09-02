
/* =====[ Bend.h ]========================================== 
                                                                             
   Description:     The daco project, implementation of the Bend.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/17/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// Bend.h: interface for the Bend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEND_H__AD131BE1_33F4_4AB2_B9EA_1316AE8A910E__INCLUDED_)
#define AFX_BEND_H__AD131BE1_33F4_4AB2_B9EA_1316AE8A910E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plot.h"
#include "intArr.h"

//////////////////////////////////////////////////////////////////////////
// The following will only compile in test harness setting
// make sure you set the pointers to an actual plot ctrl

#define PLOT_ENABLE	1		// Define this to plot to plotdlg
#define BEND_ARR_COUNT	9

#define DECL_BEND_ARRARR(arrx) \
	CIntArr cmparr1, cmparr2, cmparr3, cmparr4, \
	cmparr5, cmparr6, cmparr7, cmparr8, cmparr9;  \
	CIntArr	*arrx[BEND_ARR_COUNT] = \
	{ &cmparr1, &cmparr2, &cmparr3, &cmparr4, \
		&cmparr5, &cmparr6, &cmparr7, &cmparr8, &cmparr9 }; \


//////////////////////////////////////////////////////////////////////////

class CBend  
{
public:

	CBend();
	virtual ~CBend();

#ifdef PLOT_ENABLE

	CPlot		*m_plot1;
	CPlot		*m_plot2;
	CPlot		*m_plot3;
	CPlot		*m_plot4;
	CPlot		*m_plot5;
	CPlot		*m_plot6;
	CPlot		*m_plot7;
	CPlot		*m_plot8;

	//CPlot		*m_plot12;
	
	CPlot		*plotarr[BEND_ARR_COUNT];

#endif

	
	int		BendRecurse(short *ptr, int len, CPtrArray *parr);
	
private:
	
	int		xProcBuff(short *ptr, int len, CIntArr *varr, CIntArr *darr);
	void	xStatArr(CIntArr *darrd2, CIntArr *varrd2, CIntArr *resarr);
	int		xConvDist(CIntArr *darr, CIntArr *darr2, CIntArr *varr, CIntArr *varr2);
	int		xTurnRecurse(CIntArr *darr, CIntArr *varr, CIntArr *darr2, CIntArr *varr2);

	int		xBendFreq(short *ptr, int len, CIntArr *piarr);
	int		xBendSpectra(short *ptr, int len, CIntArr *pspec);

	int		GetMaxErrPoint(CIntArr *inarr, int startp, int endp, int *xerr);
	void	ChartScript(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr);
	void	UnChartScript(CIntArr *inarr, CIntArr *ouarr, CIntArr *varr);

	int		xSplit(CIntArr *x1, CIntArr *v1, CIntArr  *arrarr[], int start = 0);

	void	xTurnArr(CIntArr *parr, CIntArr *pout, CIntArr *vout);

	void	xPostPro(CPtrArray *parr);
	void	xBellCurve(int *ff);


	//int		ConvDist(CIntArr *darr, CIntArr *darr2);
	//int		ConvDist(CIntArr *darr, CIntArr *varr, CIntArr *darr2, CIntArr *varr2);

	int		FreqImg(CIntArr *d1, CIntArr *v1, CPtrArray  *arrarr, int start = 0);
	
	int		samplerate, pps, prevv;
	
};

#endif // !defined(AFX_BEND_H__AD131BE1_33F4_4AB2_B9EA_1316AE8A910E__INCLUDED_)
