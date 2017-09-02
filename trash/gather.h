// gather.h : main header file for the GATHER application
//

#if !defined(AFX_GATHER_H__A5D89FC6_43F6_4F6F_A431_E560D4050B8C__INCLUDED_)
#define AFX_GATHER_H__A5D89FC6_43F6_4F6F_A431_E560D4050B8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGatherApp:
// See gather.cpp for the implementation of this class
//

class CGatherApp : public CWinApp
{
public:
	CGatherApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGatherApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGatherApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GATHER_H__A5D89FC6_43F6_4F6F_A431_E560D4050B8C__INCLUDED_)
