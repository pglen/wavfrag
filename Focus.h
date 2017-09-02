
/* =====[ Focus.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Focus.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/16/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_FOCUS_H__A613B926_1996_463B_9608_CA1BBFCFC0B6__INCLUDED_)
#define AFX_FOCUS_H__A613B926_1996_463B_9608_CA1BBFCFC0B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFocus  

{
	static	BOOL CALLBACK CFocus::EnumWindowsProc( HWND hwnd, LPARAM lParam);

	struct _finproc
		{
		int		found;
		HWND	hwnd_next, hwnd_first;	
	} ;

public:

	HWND	FindNextProc();
	HWND	FindPrevProc();
	HWND	GrabFocus(HWND wto);

	CFocus();
	virtual ~CFocus();

};

#endif // !defined(AFX_FOCUS_H__A613B926_1996_463B_9608_CA1BBFCFC0B6__INCLUDED_)
