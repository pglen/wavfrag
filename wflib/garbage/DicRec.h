
/* =====[ DicRec.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the DicRec.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/28/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_DICREC_H__A9506743_7D13_450A_98FF_B4C204BADFAB__INCLUDED_)
#define AFX_DICREC_H__A9506743_7D13_450A_98FF_B4C204BADFAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ContColl.h"

#define CDicRec_Magic 0x3239393

class CDicRec  

{
	
public:
	CString & GetName();

	static	CString	_ShowArr(CStringArray *pstrarr);
	static	void	_Parse(CString *pstr, CStringArray *strarr);

	int		Add(const char *str);
	void	Clear();
	void	Dump();

	int		CmpDicRec(CContain *pcont);

	int		magic;	

	CDicRec(const char *str);
	virtual ~CDicRec();

protected:

	int		xCompare(int skip, CContain *parr, CStringArray *ref);

	CString			*xname;
	CPtrArray		xptrarr;

};

#endif // !defined(AFX_DICREC_H__A9506743_7D13_450A_98FF_B4C204BADFAB__INCLUDED_)
