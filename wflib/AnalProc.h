
/* =====[ AnalProc.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the AnalProc.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/21/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// AnalProc.h: interface for the CAnalProc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALPROC_H__E727C358_9AB3_4337_BDB8_275069B43ADF__INCLUDED_)
#define AFX_ANALPROC_H__E727C358_9AB3_4337_BDB8_275069B43ADF__INCLUDED_

#include "plot.h"
#include "intarr.h"
#include "dsp.h"
#include "wflib.h"
#include "AnalRes.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////

class CAnalProc  

{
public:

	CAnalProc();
	virtual ~CAnalProc();

	// Operations:
	void	ProcSpectra(CAnalRes *res, int compcnt);

	// Visualizers
	void	Vis(CPtrArray *parr, CPtrArray *varr);
	void	VisRaw(CPtrArray *parr);
	
	//////////////////////////////////////////////////////////////////////
	// Internal parts:

protected:

	// Conversions for visualizer
	int		xVisConv(CIntArr *piarr, CIntArr *viarr, CIntArr *pvarr);
	void	xVisSpace();

	//////////////////////////////////////////////////////////////////////

	void	xNorm(CPtrArray *parr);
	void	xLog(CPtrArray *parr);
	void	xHorSmooth(CPtrArray *parr, CPtrArray *pout);
	
	void	xProgSmooth(CIntArrRec *ptmp, CAnalRes *pres, int scnt);

	void	xGetVolArr(CIntArr *pinarr, CAnalRes *pres, int ccnt);
	void	xGetPowArr(CIntArr *pinarr, CAnalRes *pres, int ccnt);
	void	xAdd2Arr(CIntArrRec *parr, CIntArrRec *pout);

	void	xSpecBalance(CAnalRes *pres);
	void	xSpecCalcBalance(CAnalRes *pres, int second = false);

private:

	int		xfirstdone;
	
};

#endif // !defined(AFX_ANALPROC_H__E727C358_9AB3_4337_BDB8_275069B43ADF__INCLUDED_)
