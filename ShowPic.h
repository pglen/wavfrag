#if !defined(AFX_SHOWPIC_H__0A3362A6_E721_44CB_AC5A_1FD5305D7081__INCLUDED_)
#define AFX_SHOWPIC_H__0A3362A6_E721_44CB_AC5A_1FD5305D7081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowPic.h : header file
//

#include "Picture.h"
#include "GrayDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CShowPic dialog

class CShowPic : public CGrayDlg
//class CShowPic : public CDialog
{
// Construction
public:
	void LoadPic();
	CShowPic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowPic)
	enum { IDD = IDD_SHOWPIC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CString  fname;
	CPicture pic;

	int		 gotpic, bgcolor;
	int		want_x,want_y, want_w, want_h;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowPic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowPic)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPIC_H__0A3362A6_E721_44CB_AC5A_1FD5305D7081__INCLUDED_)
