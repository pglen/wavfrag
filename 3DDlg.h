#if !defined(AFX_3DDLG_H__D080A2F6_7962_4491_AC56_5E0B28C630CF__INCLUDED_)
#define AFX_3DDLG_H__D080A2F6_7962_4491_AC56_5E0B28C630CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DDlg.h : header file
//

#include "3DPlot.h"

/////////////////////////////////////////////////////////////////////////////
// C3DDlg dialog

class C3DDlg : public CDialog
{
// Construction
public:
	C3DDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C3DDlg)
	enum { IDD = IDD_DIALOG4 };
	C3DPlot	m_3d;
	//}}AFX_DATA

	int	xgap, ygap;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3DDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DDLG_H__D080A2F6_7962_4491_AC56_5E0B28C630CF__INCLUDED_)
