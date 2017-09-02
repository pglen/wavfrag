
/* =====[ Smooth.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the Smooth.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/1/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_SMOOTH_H__7EA808F8_F4E6_43D5_A354_E4598D832D5D__INCLUDED_)
#define AFX_SMOOTH_H__7EA808F8_F4E6_43D5_A354_E4598D832D5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "intarr.h"

#define MAX_SMOOTH	24			// Maximum number of smooths to execute

class CSmooth  
{

public:

	CSmooth();
	virtual ~CSmooth();

	// Avarage nighhbours
	void	HorSmooth(CPtrArray *parr, int passes);

	// Apply it to a range
	void	RangeSmooth(CPtrArray *parr, int passes, int start, int endd);

	// Apply it until smotth enough
	void	DynSmooth(CIntArr *tmp, int compcnt);


	// Smooth by averaging
	void	Smooth(CPtrArray *parr, int passes = 1);
	void	Smooth3(CPtrArray *parr, int passes = 1);
	void	Smooth5(CPtrArray *parr, int passes = 1);
};

#endif // !defined(AFX_SMOOTH_H__7EA808F8_F4E6_43D5_A354_E4598D832D5D__INCLUDED_)
