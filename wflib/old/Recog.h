
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

#if !defined(AFX_RECOG_H__7B484C49_714F_4564_9CE5_BA85AAA3788F__INCLUDED_)
#define AFX_RECOG_H__7B484C49_714F_4564_9CE5_BA85AAA3788F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plot.h"
#include "intarr.h"
#include "dsp.h"
#include "wflib.h"
#include "contain.h"

class CRecog  

{

public:

	//////////////////////////////////////////////////////////////////////
	// Callables and callbacks:

	static	int		_statRec(void *cls, char *buff, int len);
	
	PFUNCSI			_strrec;
	PFUNCSI			_fragrec;
	PFUNCSI			_ledrec;
	PFUNCSI			_perfrec;
	PFUNCSI			_wavrec, _wavrec2;
	
	PFUNCPII		_spectrec,	_spectrec2;
	PFUNCPIII		_plotrec;

	//////////////////////////////////////////////////////////////////////
	// Functions:

	void	Scan(char *buff, int len, CIntArr *piarr, CIntArr *pvarr);
	int		Recognize(char *buff, int len);
	void	Emit(int minlen = 4);	
	
	int		SplitSpectra(CIntArr *piarr, CIntArr *pvarr);
	void	RecombineSpectra(CIntArr *picum, CIntArr *pvcum);

	void	NormalizeWav(char *buff, int len, char *out);

	void	PowerAnal(CIntArr *piarr, int *pss, int *pee);
	void	PowerSplit(char *buff, int len, CPtrArray *parr, CIntArr *iarr);
	void	Powers(char *buff, int len, CIntArr *piarr);
	int		PowerCombine(CPtrArray &sparr, CIntArr &siarr);

	int		IsSignal(char *buff, int len);

	CRecog();
	virtual ~CRecog();

	//////////////////////////////////////////////////////////////////////
	// Publicly accessable data

	int			strict, noprompt;	// Set parameters
	int			change_tresh;		// Set histeresis
	int			meshutdown, noiselevel, bigmatch;

	char		*lastbuff;			// Last wave buffer
	int			lastbuflen;			// last buffer passed in
	int			acnt;				// Averaging count

	CString		result; 
		
	// Multi thread locking mechanism for wave buffer access
	CCriticalSection lock;
	
private:

	void	xFreeArr(CPtrArray *parr);
	void	xScanSpectra(short *ptr, int len, CIntArr *piarr, CIntArr *pvarr);
	int		xCmpSpectra(CIntArr *piarr, CIntArr *pvarr, CContain *cout);
	int		xCmpSpectra2(int skip, CIntArr *piarr, CIntArr *pvarr, CIntArr *priarr, CPtrArray *prparr);

	int		xAddSpectra(CIntArr *piarr, CIntArr *pvarr);
	//void	xRecombineSpectra();

	//////////////////////////////////////////////////////////////////////
	// Private data:

	CPtrArray	buffarr, iarrarr, varrarr;
	
	int		xlastlen, xblank, xreenter, xnoised, xsigged, xin_useful;

	CIntArr resarr;
};

#endif // !defined(AFX_RECOG_H__7B484C49_714F_4564_9CE5_BA85AAA3788F__INCLUDED_)
