// LightBoxDlg.h : header file
//

#if !defined(AFX_LIGHTBOXDLG_H__0468F5C0_E594_463B_94C3_4503182F344C__INCLUDED_)
#define AFX_LIGHTBOXDLG_H__0468F5C0_E594_463B_94C3_4503182F344C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GrayDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CLightBoxDlg dialog

class CLightBoxDlg : public CGrayDlg
{
// Construction
public:

	CFont m_font;
			
	int bgcolor;
	int ini_message;
	
	CLightBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLightBoxDlg)
	enum { IDD = IDD_LIGHTBOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLightBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void ExitHere();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
public:
	afx_msg void WhiteScreen();
	afx_msg void GrayScreen();
	afx_msg void DarkGrayScreen();
	afx_msg void DefaultScreen();
	afx_msg void CustomScreen();
	afx_msg void BlackScreen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTBOXDLG_H__0468F5C0_E594_463B_94C3_4503182F344C__INCLUDED_)
