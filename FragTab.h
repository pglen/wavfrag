
/* =====[ FragTab.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the FragTab.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/24/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_FRAGTAB_H__B4B74170_F654_4543_B788_DA9DA6F26C29__INCLUDED_)
#define AFX_FRAGTAB_H__B4B74170_F654_4543_B788_DA9DA6F26C29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FragTab.h : header file
//

#include "xButton.h"
#include "SelList.h"

/////////////////////////////////////////////////////////////////////////////
// CFragTab dialog

class CFragTab : public CDialog
{
// Construction
public:
	CFragTab(CWnd* pParent = NULL);   // standard constructor
	void InitCombos();

// Dialog Data
	//{{AFX_DATA(CFragTab)
	enum { IDD = IDD_DIALOG8 };
	CxButton	m_play;
	CxButton	m_loadall;
	CxButton	m_delwav;
	CxButton	m_del;
	CxButton	m_reload;
	CxButton	m_new;
	CLabel		m_currsp;
	CComboBox	m_users;
	CxButton	m_tb;
	CComboBox	m_currw;
	//}}AFX_DATA

	int			b6_reenter;

	CSelList	m_tl;

	void CFragTab::UserChanged(const char *str);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFragTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	//CSelList	m_tl;
	//CListBox	m_tl;

	void xFillUserCombo();
	void xFillFragCombo();
	void xFillCurrUser();

	void xLoadData();

	// Generated message map functions
	//{{AFX_MSG(CFragTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList2();
	afx_msg void OnButton1();
	afx_msg void OnButton8();
	afx_msg void OnButton18();
	afx_msg void OnButton6();
	afx_msg void OnButton20();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnButton12();
	afx_msg void OnButton19();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnSelchangeCombo5();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAGTAB_H__B4B74170_F654_4543_B788_DA9DA6F26C29__INCLUDED_)
