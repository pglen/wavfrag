
/* =====[ MsgBox.h ]========================================== 
                                                                             
   Description:     The xraynotes project, implementation of the MsgBox.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  11/24/2008  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_MSGBOX_H__97DB95B2_93EC_41F6_AB21_F4C3C3D336AA__INCLUDED_)
#define AFX_MSGBOX_H__97DB95B2_93EC_41F6_AB21_F4C3C3D336AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBox.h : header file
//

#include "GrayDlg.h"
#include "xButton.h"

#define MBTYPE_YESOK		MB_OK
#define MBTYPE_YESNO		MB_YESNO
#define MBTYPE_YESNOSTOP	2

#define MBOXYES		IDYES
#define MBOXNO		IDNO
#define MBOXSTOP	-1

#define DEFYES		IDYES
#define DEFNO		IDNO
#define DEFSTOP		3

#define AUTOCLOSE 11	// Number of seconds in close
#define AUTOWARN  3		// Number of seconds before timeout warning

/////////////////////////////////////////////////////////////////////////////
// CMsgBox dialog

class CMsgBox : public CGrayDlg

{
	// Construction
public:

	void OnCancel();
	void OnOK();

	
	int		timeout;
	int		yesno;
	int		idret;

	CString m_text;
	CString m_header;

	CMsgBox(CWnd* pParent = NULL);   // standard constructor

	//CRect closerect;

protected:

	CSize titlesss, textsss;

	CString m_timer;

	int		tocount, ttextoffs;
	int		drag, drag_x, drag_y;
	int		m_nWidth, m_nHeight;	// Bitmap's width & height
	
	CSize GetTextSize(const char *str, CFont *font);

	CFont	m_font, m_fontb;
	CBitmap		m_bitmap;				// Bitmap
	
// Dialog Data
	//{{AFX_DATA(CMsgBox)
	enum { IDD = IDD_MBOX };
	CStatic	m_icon;
	CxButton	m_stop;
	CxButton	m_no;
	CxButton	m_yes;
	CxButton	m_ok;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnOk2();
	afx_msg void OnOk3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOk4();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOX_H__97DB95B2_93EC_41F6_AB21_F4C3C3D336AA__INCLUDED_)
