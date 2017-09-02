
/* =====[ DicRecColl.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the DicRecColl.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/28/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_DICRECCOLL_H__E06F3A71_0440_4FA1_A7D0_61C5301C4D0E__INCLUDED_)
#define AFX_DICRECCOLL_H__E06F3A71_0440_4FA1_A7D0_61C5301C4D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 100

#include "DicRec.h"

#define CDicRecColl_Magic 0x21241234

class CDicRecColl  

{
public:
	
	CDicRec *GetAt(int pos);
	CString &GetStrAt(int pos);

	void Dump();
	
	void Empty();

	int	LoadDic(const char *fname);
	int	SaveDic(const char *fname);
	
	int	Cmp(CContain *pcont);

	CPtrArray *GetData() { return &xdicarr; }

	//////////////////////////////////////////////////////////////////////
	
	CDicRecColl();
	virtual ~CDicRecColl();
	
	int magic;

protected:

	int			xchanged;

	CString		lastfile;
	CPtrArray	xdicarr;

};

#endif // !defined(AFX_DICRECCOLL_H__E06F3A71_0440_4FA1_A7D0_61C5301C4D0E__INCLUDED_)
