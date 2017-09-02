#if !defined(AFX_PHONAMES_H__B50E8110_60B4_4E18_96DB_7EFA4B891170__INCLUDED_)
#define AFX_PHONAMES_H__B50E8110_60B4_4E18_96DB_7EFA4B891170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Phonames.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhonames dialog

class CPhonames : public CDialog
{
// Construction
public:
	CPhonames(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPhonames)
	enum { IDD = IDD_DIALOG5 };
	//CStatic	m_4d;
	CEdit	m_edit;
	//}}AFX_DATA

	LOGFONT		m_lf;
	CFont		m_font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhonames)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhonames)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONAMES_H__B50E8110_60B4_4E18_96DB_7EFA4B891170__INCLUDED_)
