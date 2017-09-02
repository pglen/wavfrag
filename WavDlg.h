#if !defined(AFX_WAVDLG_H__0EDCB2F3_9257_4602_BD41_B51942CBC887__INCLUDED_)
#define AFX_WAVDLG_H__0EDCB2F3_9257_4602_BD41_B51942CBC887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WavDlg.h : header file
//

#include "WaveEdit.h"
#include "RecordSound.h"
#include "PlaySound.h"

/////////////////////////////////////////////////////////////////////////////
// CWavDlg dialog

class CWavDlg : public CDialog
{
// Construction
public:
	void Sizeit();
	CWavDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWavDlg)
	enum { IDD = IDD_DIALOG4 };
	CwaveEdit	m_wav2;
	CwaveEdit	m_wav;
	//}}AFX_DATA

	CPlaySound		playsound;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWavDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVDLG_H__0EDCB2F3_9257_4602_BD41_B51942CBC887__INCLUDED_)
