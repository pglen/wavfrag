#if !defined(AFX_CPlotDlg_H__D3E71372_2D49_4D24_A9CB_ABBE4D1C9269__INCLUDED_)
#define AFX_CPlotDlg_H__D3E71372_2D49_4D24_A9CB_ABBE4D1C9269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CPlotDlg.h : header file
//

#include "plot.h"
//#include "Vis.h"

 
/////////////////////////////////////////////////////////////////////////////
// CPlotDlg dialog

class CPlotDlg : public CDialog
{
// Construction
public:
	CPlotDlg(CWnd* pParent = NULL);   // standard constructor

	CPlot		*m_arr[6];

	CPlot		m_plot6;
	CPlot		m_plot5;
	CPlot		m_plot4;
	CPlot		m_plot3;
	CPlot		m_plot2;
	CPlot		m_plot1;
	
	//CVis		m_vis;

// Dialog Data
	//{{AFX_DATA(CPlotDlg)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlotDlg)
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPlotDlg_H__D3E71372_2D49_4D24_A9CB_ABBE4D1C9269__INCLUDED_)
