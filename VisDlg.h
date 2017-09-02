#if !defined(AFX_VISDLG_H__F4A98494_E30F_4C50_9B6A_BEAE81FF1FB7__INCLUDED_)
#define AFX_VISDLG_H__F4A98494_E30F_4C50_9B6A_BEAE81FF1FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisDlg.h : header file
//

#include "Vis.h"
#include "plot.h"

//#include "MemVis.h"
//#include "3DPlot.h"

/////////////////////////////////////////////////////////////////////////////
// CVisDlg dialog

class CVisDlg : public CDialog
{
// Construction
public:
	CVisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisDlg)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CVis		m_vis;
	CPlot		m_plot;

	//C3DPlot		m_3d;
	//CMemVis		m_vis;

	void CVisDlg::SizeControls();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISDLG_H__F4A98494_E30F_4C50_9B6A_BEAE81FF1FB7__INCLUDED_)
