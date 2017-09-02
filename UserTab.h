#if !defined(AFX_USERTAB_H__4FBD365B_CD5B_43AD_83A6_964258EAE1BA__INCLUDED_)
#define AFX_USERTAB_H__4FBD365B_CD5B_43AD_83A6_964258EAE1BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserTab.h : header file
//

#include "SelList.h"

/////////////////////////////////////////////////////////////////////////////
// CUserTab dialog

class CUserTab : public CDialog
{
// Construction
public:
	CUserTab(CWnd* pParent = NULL);   // standard constructor

	void InitCombos();

	CSelList	m_users;

// Dialog Data
	//{{AFX_DATA(CUserTab)
	enum { IDD = IDD_DIALOG13 };
	CStatic	m_currsp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void xFillUserCombo();
	void xFillCurrUser();

	// Generated message map functions
	//{{AFX_MSG(CUserTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton32();
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERTAB_H__4FBD365B_CD5B_43AD_83A6_964258EAE1BA__INCLUDED_)
