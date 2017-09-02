#if !defined(AFX_COMCONF_H__D5B0BF1F_023B_4926_9EB7_CEEDFBF63A65__INCLUDED_)
#define AFX_COMCONF_H__D5B0BF1F_023B_4926_9EB7_CEEDFBF63A65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComConf.h : header file
//

#include "label.h"
#include "ComColl.h"

/////////////////////////////////////////////////////////////////////////////
// CComConf dialog

class CComConf : public CDialog
{
// Construction
public:
	CString name;
	CComConf(CWnd* pParent = NULL);   // standard constructor

	CCommand	*curr;

// Dialog Data
	//{{AFX_DATA(CComConf)
	enum { IDD = IDD_DIALOG_COMM };
	CLabel	m_action;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComConf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComConf)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton20();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnCancel2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMCONF_H__D5B0BF1F_023B_4926_9EB7_CEEDFBF63A65__INCLUDED_)
