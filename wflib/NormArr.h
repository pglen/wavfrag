
/* =====[ NormArr.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the NormArr.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/20/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// NormArr.h: interface for the CNormArr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NORMARR_H__65C2D01F_9156_4DE5_86FC_AAD314C78F1C__INCLUDED_)
#define AFX_NORMARR_H__65C2D01F_9156_4DE5_86FC_AAD314C78F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ANAL_BANDS	3			// How many bands
#define ANAL_TRESH	30			// Noise treshold

#include "intarr.h"


class CNormArr  

{

public:

	CNormArr();
	virtual ~CNormArr();

	void	NormEvery(CPtrArray *parr, int maxrat);
	void	NormAll(CPtrArray *parr, int limfact = 5);
	void	NormAvg(CPtrArray *parr, int limfact = 5);
	void	NormBands(CPtrArray *parr, int bands = ANAL_BANDS, int maxrat = 5);


};

#endif // !defined(AFX_NORMARR_H__65C2D01F_9156_4DE5_86FC_AAD314C78F1C__INCLUDED_)
