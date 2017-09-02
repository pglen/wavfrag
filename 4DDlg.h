#if !defined(AFX_4DDLG_H__C0A89FCF_C21C_42A2_B953_AC475AC1D8F6__INCLUDED_)
#define AFX_4DDLG_H__C0A89FCF_C21C_42A2_B953_AC475AC1D8F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 4DDlg.h : header file
//

#include "4D.h"

/////////////////////////////////////////////////////////////////////////////
// C4DDlg dialog

class C4DDlg : public CDialog
{
// Construction
public:
	C4DDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C4DDlg)
	enum { IDD = IDD_DIALOG11 };
	C4DPlot		m_4d;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C4DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void C4DDlg::SizeControls();


	// Generated message map functions
	//{{AFX_MSG(C4DDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_4DDLG_H__C0A89FCF_C21C_42A2_B953_AC475AC1D8F6__INCLUDED_)
