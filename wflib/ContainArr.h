
/* =====[ ContainArr.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the ContainArr.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  5/24/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_CONTAINARR_H__CBD170B9_A6B5_4F95_93C9_8904381195DF__INCLUDED_)
#define AFX_CONTAINARR_H__CBD170B9_A6B5_4F95_93C9_8904381195DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CContainArr_Magic	0x11223349

#include "Contain.h"

//////////////////////////////////////////////////////////////////////////

class CContainArr  

{
public:
	CContainArr();

	virtual ~CContainArr();

	int magic;

	void	Add(CContain *ptr);
	void	Clear();
	void	Dump();

protected:

	CPtrArray xarr;

};

#endif // !defined(AFX_CONTAINARR_H__CBD170B9_A6B5_4F95_93C9_8904381195DF__INCLUDED_)
