#if !defined(AFX_FRAGCOLLTAB_H__9D9CE894_315B_406F_A5F7_FEAAABED37CA__INCLUDED_)
#define AFX_FRAGCOLLTAB_H__9D9CE894_315B_406F_A5F7_FEAAABED37CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FragCollTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFragCollTab dialog

class CFragCollTab : public CDialog
{
// Construction
public:
	CFragCollTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFragCollTab)
	enum { IDD = IDD_DIALOG10 };
	CComboBox	m_words;
	CListBox	m_coll;
	//}}AFX_DATA

	void CFragCollTab::LoadData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFragCollTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	int in_train;
	int stop_train;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFragCollTab)
	afx_msg void OnButton21();
	afx_msg void OnButton35();
	afx_msg void OnButton25();
	afx_msg void OnButton11();
	afx_msg void OnButton29();
	afx_msg void OnButton26();
	afx_msg void OnButton31();
	afx_msg void OnButton33();
	afx_msg void OnButton34();
	afx_msg void OnButton22();
	afx_msg void OnButton27();
	afx_msg void OnButton32();
	afx_msg void OnSelchangeList3();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAGCOLLTAB_H__9D9CE894_315B_406F_A5F7_FEAAABED37CA__INCLUDED_)
