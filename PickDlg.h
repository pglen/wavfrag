
/* =====[ PickDlg.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the PickDlg.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/26/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_PICKDLG_H__1A65D3F2_A703_4FDF_AAA7_9DD443B067AC__INCLUDED_)
#define AFX_PICKDLG_H__1A65D3F2_A703_4FDF_AAA7_9DD443B067AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PickDlg.h : header file
//

#include "intarr.h"
#include "WavCmp.h"
#include "vis.h"
#include "waveedit.h"

/////////////////////////////////////////////////////////////////////////////
// CPickDlg dialog

class CPickDlg : public CDialog
{
// Construction

public:

	void	ScanSmall();
	void	ScanBigPart();
	void	CleanBig();
	void	CleanSmall();

	CWavCmp cwc;
	
	CIntArr		darrbig, darrsmall;
	CPtrArray	arrbig, arrsmall;

	CIntArr		zeroarr;

	CPickDlg(CWnd* pParent = NULL);   // standard constructor

	//void	GetZCross(char *fbuff, int flen, CIntArr *parr);

	double	CmpArray(int *skip, CPtrArray *parr, CPtrArray *big);

// Dialog Data
	//{{AFX_DATA(CPickDlg)
	enum { IDD = IDD_DIALOG6 };
	CVis	m_vis5;
	CVis	m_vis4;
	CVis	m_vis3;
	CVis	m_vis2;
	CwaveEdit	m_wav4;
	CPlot	m_sin2;
	CPlot	m_sin;
	CPlot	m_plot;
	CLabel	m_sel;
	CwaveEdit	m_wav3;
	CwaveEdit	m_wav2;
	CwaveEdit	m_wav;
	CVis		m_vis;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPickDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPickDlg)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton38();
	afx_msg void OnButton2();
	afx_msg void OnButton40();
	afx_msg void OnButton41();
	afx_msg void OnButton42();
	afx_msg void OnButton43();
	afx_msg void OnButton45();
	afx_msg void OnButton46();
	afx_msg void OnButton47();
	afx_msg void OnButton48();
	afx_msg void OnButton49();
	afx_msg void OnButton50();
	afx_msg void OnButton51();
	afx_msg void OnButton52();
	afx_msg void OnButton53();
	afx_msg void OnButton54();
	afx_msg void OnButton55();
	afx_msg void OnButton56();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICKDLG_H__1A65D3F2_A703_4FDF_AAA7_9DD443B067AC__INCLUDED_)
