// gatherDlg.h : header file
//

#if !defined(AFX_GATHERDLG_H__ED385B2E_B4D1_4EDE_B714_C4CB339EBBB1__INCLUDED_)
#define AFX_GATHERDLG_H__ED385B2E_B4D1_4EDE_B714_C4CB339EBBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGatherDlg dialog

class CGatherDlg : public CDialog
{
// Construction
public:
	CGatherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGatherDlg)
	enum { IDD = IDD_GATHER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGatherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGatherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GATHERDLG_H__ED385B2E_B4D1_4EDE_B714_C4CB339EBBB1__INCLUDED_)
