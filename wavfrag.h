
/* =====[ wavfrag.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the wavfrag.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/24/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_WAVFRAG_H__CB2025B6_7009_4AEE_95D7_9EC043BA2CE9__INCLUDED_)
#define AFX_WAVFRAG_H__CB2025B6_7009_4AEE_95D7_9EC043BA2CE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Comcoll.h"
#include "Command.h"
	
extern	CComColl	comcoll;

extern	HWND	GrabFocus(HWND wto);
extern	HWND	FindNextProc();
extern	HWND	FindPrevProc();
extern	int		SendKeys(const char *keys);
extern	int		xMsgBox(const char *str, const char *title, int yesno, int defa);

// This is the easiest way tpo pass it around
extern	CString		appname, appdir, appdata;


#include "wflib\wflib.h"

/////////////////////////////////////////////////////////////////////////////
// CWavfragApp:
// See wavfrag.cpp for the implementation of this class
//

class CWavfragApp : public CWinApp

{
public:
	CWavfragApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavfragApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);

	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWavfragApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	afx_msg void OnHelp( );
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVFRAG_H__CB2025B6_7009_4AEE_95D7_9EC043BA2CE9__INCLUDED_)
