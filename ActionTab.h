
/* =====[ ActionTab.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the ActionTab.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  7/12/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_ACTIONTAB_H__86E88AD2_B7BC_48B9_8757_F86CC081A860__INCLUDED_)
#define AFX_ACTIONTAB_H__86E88AD2_B7BC_48B9_8757_F86CC081A860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActionTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActionTab dialog

class CActionTab : public CDialog
{
// Construction
public:
	CActionTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CActionTab)
	enum { IDD = IDD_DIALOG7 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CActionTab)
	afx_msg void OnButton14();
	afx_msg void OnButton31();
	afx_msg void OnButton33();
	afx_msg void OnButton34();
	afx_msg void OnButton36();
	afx_msg void OnButton37();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIONTAB_H__86E88AD2_B7BC_48B9_8757_F86CC081A860__INCLUDED_)
