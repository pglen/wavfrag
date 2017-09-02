
/* =====[ Recog.h ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the Recog.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/21/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_XRECOG_H__7B484C49_714F_4564_9CE5_BA85AAA3748D__INCLUDED_)
#define AFX_XRECOG_H__7B484C49_714F_4564_9CE5_BA85AAA3748D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wflib.h"

#include "plot.h"
#include "intarr.h"
#include "dsp.h"
#include "AnalProc.h"
#include "AnalRes.h"
#include "Frag.h"
#include "contain.h"
#include "containarr.h"

//////////////////////////////////////////////////////////////////////////
// Main recognition class

class CxRecog  

{

public:

	friend class CFrag;

	//////////////////////////////////////////////////////////////////////
	// Callables and callbacks:

	static	int		_statRec(void *cls, char *buff, int len);
	
	PFUNCSI			_strrec;
	PFUNCSI			_fragrec, _fragrec2;
	PFUNCSI			_ledrec;
	PFUNCSI			_perfrec;
	PFUNCSI			_wavrec, _wavrec2;
	
	PFUNCPII		_spectrec, _spectrec2;
	PFUNCPIII		_plotrec;

	//////////////////////////////////////////////////////////////////////
	// Functions:

	int		Feed(char *buff, int len);
	void	Recognize(int minlen = 4);	
	void	ScanSpectra(char *buff, int len, CAnalRes *pres);


	CAnalProc	analproc;

	CxRecog();
	virtual ~CxRecog();

	//////////////////////////////////////////////////////////////////////
	// Publicly accessable data

	int			FreqCompCnt;				// Number od spectral components
	int			HowManyHits;				// Control output
	int			NoiseLevel;					// Control wav parsing
	int			ChangeTresh;				// Switch length treshold
	int			NumAverage;					// Number of items to avarage
	int			Strictness;

	int			strict, noprompt;			// Settable parameters
	int			meshutdown;					// Shutdown (terminate loops)
	
	CString		trainstr, result; 		

	// Multi thread locking mechanism for wave buffer access
	CCriticalSection lock;
	
	char		*lastbuff;					// Last wave buffer
	int			lastbuflen;					// last buffer passed in
	
protected:

	CFragColl *xpcurrcoll;

	int		xCmpSpectra(CAnalRes *res, CContainArr *pcontarr);
	int		xCmpSpectra2(int skip, CAnalRes *parr,  CContain *cout);
	int		xCmpSpectra3(int ss, int ee, CAnalRes *parr, CContain *pcont);
	int		xPreSel(CAnalRes *parr, int offs, CContain::CContData *pdat);
	void	xGetSigArr(short *ptr, int len2, CAnalRes *pres);
	int		xGetSig(short *ptr, int len2);
	void	xShowPerf(const char *str);

	//////////////////////////////////////////////////////////////////////
	// Private data:

private:

	CPtrArray	xbuffarr; 

	int			xlastlen, xblank, xreenter, xnoised, xsigged, xin_useful;

};

#endif // !defined(AFX_RECOG_H__7B484C49_714F_4564_9CE5_BA85AAA3748F__INCLUDED_)
