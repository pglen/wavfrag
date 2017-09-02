
/* =====[ WavCmp.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the WavCmp.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/26/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */


#if !defined(AFX_WAVCMP_H__A69D713D_7870_4F51_9014_7638FC3077F3__INCLUDED_)
#define AFX_WAVCMP_H__A69D713D_7870_4F51_9014_7638FC3077F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "intarr.h"
#include "plot.h"

class CWavCmp  

{

public:

	void	AdjZero(char **buff, int*len);
	
	int		SplitBend(char *ptr, int len, CIntArr *varr, CIntArr *darr);
	void	SplitZcross(short *buff, int slen, CIntArr *parr);

	int		SubCmp(short *buff, int len, short *buff2, int len2);
	void	CmpBuff(char *fbuff, int flen, char *buff, int len, CIntArr *parr);

	int		HitCmp(short *buff, int len, short *buff2, int len2);

	//////////////////////////////////////////////////////////////////////
	
	CWavCmp();
	virtual ~CWavCmp();

	CPlot	*pplot, *pplot2;

//////////////////////////////////////////////////////////////////////////

protected:

	int		divisor, minskip;

//////////////////////////////////////////////////////////////////////////

	int		xGetPeak(short *buff, int len);
	int		xCmpOneBuff(short *fbuff, int flen, short *buff, int len, int *skip);
	int		xHitCmp(short *buff, int len, short *buff2, int len2, int *skip);
		
};

#endif // !defined(AFX_WAVCMP_H__A69D713D_7870_4F51_9014_7638FC3077F3__INCLUDED_)
