
/* =====[ ArrIntArr.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the ArrIntArr.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/12/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_ARRINTARR_H__1DF9F507_E1A7_4074_981C_C75E0365DF84__INCLUDED_)
#define AFX_ARRINTARR_H__1DF9F507_E1A7_4074_981C_C75E0365DF84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "intarrRec.h"

#define CArrIntArr_Magic 0x11223367

//////////////////////////////////////////////////////////////////////////
// Collection for integer arrays

class CArrIntArr  

{
	struct struct_ms {int magic; int len; };

public:

	int		magic;

	// File ops
	int		ToFile(CFile *fp);
	int		FromFile(CFile *fp);

	// Operations
	int			Add(CIntArrRec *piarr = NULL);
	CIntArrRec *GetAt(int idx);

	// Getters
	inline int			GetSize() { return arrdata.GetSize(); }
	inline CPtrArray*	GetData() { return &arrdata; }

	CIntArrRec *CArrIntArr::GetLast();

	CArrIntArr();
	virtual ~CArrIntArr();

protected:

	CPtrArray arrdata;
};

#endif // !defined(AFX_ARRINTARR_H__1DF9F507_E1A7_4074_981C_C75E0365DF84__INCLUDED_)
