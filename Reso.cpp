
/* =====[ Reso.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Reso.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/15/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "mxpad.h"
#include "Reso.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CReso::CReso()

{
	const double PI		= 2.0 * asin (1.0);
	const double TWOPI  = 4.0 * asin (1.0);

	// Create sine waves
	//support.MarkPerf();

	double decr = 0.03;

	for(int loop2 = 200; loop2 > 0; loop2 *= int(1.0 - decr) )
		{
		CIntArr		*psinarr = new CIntArr;
		
		for(int loop = 0; loop < loop2; loop++)
			{
			psinarr->Add( int(sin(TWOPI / loop2 * loop ) * SHRT_MAX));
			}
		sarrarr.Add(psinarr);
		}

	//AP2N("Genrated Sines %d msec\r\n", support.QueryPerf());

}

//////////////////////////////////////////////////////////////////////////

CReso::~CReso()

{
	for(int loop = 0; loop < sarrarr.GetSize(); loop += 1)
		delete (CIntArr *) sarrarr.GetAt(loop);

}

//////////////////////////////////////////////////////////////////////////

void CReso::DumpSine(CPlot *plot)

{
	for(int loop = 0; loop < sarrarr.GetSize(); loop += 1)
		{
		CIntArr *parr = (CIntArr *) sarrarr.GetAt(loop);
	
		//parr->Plot(plot);
		//plot->AddMarker();
		}
}


//////////////////////////////////////////////////////////////////////////

int CReso::Resonate(short *ptr, int len, CPtrArray *parr)

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	PlotDlg		*pdlg = &pwnd->plotdlg;

	int cnt = 0, step = 600;

	AP2N("CReso::Resonate(short *ptr, int len=%d\r\n", len);

	for(int loop = step; loop < len - step; loop += step)
		{
		CIntArr *piarr = new CIntArr;

		xResonate(ptr + loop - step / 2, step + step , piarr);

		//piarr->NormArrHeight(255, 10); 
		
		//piarr->Plot(&pdlg->m_plot1);

		parr->Add(piarr);
		}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CReso::xResonate(short *ptr, int len, CIntArr *piarr)

{
	for(int loop = 0; loop < sarrarr.GetSize(); loop += 1)
		{
		CIntArr *psarr = (CIntArr*) sarrarr.GetAt(loop);

		int sss = xResonate2(ptr, len, psarr);

		piarr->Add(sss);
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CReso::xResonate2(short *ptr, int len, CIntArr *psarr)

{
	double sum = 0;
	int alen = psarr->GetSize(), step = 20;

	for(int loop = 0; loop < len; loop++)
		{
		int val =	(int)*ptr++;

		// Ramp up / down
		if(loop < step)
			val *= int((1.0 / step) * loop);
		if(len - loop < 10)
			val *= int((1.0 / step) * len - loop);
		
		// Multiply and accumulate
		val *=		psarr->GetAt(loop % alen);
		val /=		SHRT_MAX;
		sum +=		val;		
		}

	int ret = int(sum / 10000);

	return ret > 0 ? ret : -ret;
}

