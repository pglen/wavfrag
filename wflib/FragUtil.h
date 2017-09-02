
/* =====[ FragUtil.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the FragUtil.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */


#if !defined(AFX_FRAGUTIL_H__B991686E_8835_4198_B9C1_52BA6935E48D__INCLUDED_)
#define AFX_FRAGUTIL_H__B991686E_8835_4198_B9C1_52BA6935E48D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "intarr.h"

//////////////////////////////////////////////////////////////////////////
// Collection of static members to manupulate frags

class CFragUtil  
{
public:
	CFragUtil();
	virtual ~CFragUtil();

	static	void	_FreeArr(CPtrArray *parr);
	static	void	_CleanZeros(CPtrArray *parr, CPtrArray *pclean);
	static	void	_CleanZeros(CPtrArray *parr);
	static	void	_Dup(CPtrArray *parr, CPtrArray *oarr);
	static	void	_DivisorConvert(CIntArr *piarr, CIntArr *poarr);
	static	int		_VisConvStep(CIntArr *piarr, CIntArr *pvarr);
	static	int		_VisConvRat(CIntArr *piarr, CIntArr *pvarr);
	static	int		_VisConvDiv(CIntArr *piarr, CIntArr *pvarr);
	static	int		_VisConv(CIntArr *piarr,  CIntArr *pvarr);
	static	void	_ThickenConvArr(CPtrArray *parr, CPtrArray *pout, int skip);

	static	void	_VisConvArr(CPtrArray *parr, CPtrArray *pout);
	static	void	_DumpSpect(CPtrArray *parr, int start, int len);



};

#endif // !defined(AFX_FRAGUTIL_H__B991686E_8835_4198_B9C1_52BA6935E48D__INCLUDED_)
