
/* =====[ wavfragDlg.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the wavfragDlg.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/28/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_WAVFRAGDLG_H__380C999E_02E2_4DEA_8EA3_06713B98D102__INCLUDED_)
#define AFX_WAVFRAGDLG_H__380C999E_02E2_4DEA_8EA3_06713B98D102__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GrayDlg.h"
#include "waveEdit.h"
#include "label.h"
#include "LogWin.h"
#include "led.h"

#include "PlotDlg.h"
#include "VisDlg.h"
#include "WavDlg.h"
#include "4DDlg.h"
#include "3DDlg.h"

#include "xProgCtrl.h"

#include "RecordSound.h"
#include "PlaySound.h"
#include "ShowPic.h"
#include "LightBoxDlg.h"
#include "xButton.h"
#include "mixer.h"

#include "ActionTab.h"
#include "FragTab.h"
#include "FragCollTab.h"
#include "UserTab.h"

//////////////////////////////////////////////////////////////////////////
// Patch for the new notify icon function

#if 1

#define     NOTIFYICON_VERSION 3

#define NIM_SETVERSION  0x00000004
#define NIF_INFO        0x00000010

#define NIIF_NONE       0x00000000
#define NIIF_INFO       0x00000001
#define NIIF_WARNING    0x00000002
#define NIIF_ERROR      0x00000003


typedef struct _NOTIFYICONDATA2 {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    TCHAR szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    TCHAR szInfo[256];
    union {
        UINT uTimeout;
        UINT uVersion;
    };
    TCHAR szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
} NOTIFYICONDATA2, *PNOTIFYICONDATA2;

#endif

/////////////////////////////////////////////////////////////////////////////
// CWavfragDlg dialog

//class CWavfragDlg : public CDialog
class CWavfragDlg : public CGrayDlg

{
public:

	//static	void	_staticExeThread(void *ptr);

	static	void	_staticStrFromRec(const char *ptr, int len);
	static	void	_staticWavFromRec(const char *ptr, int len);
	static	void	_staticWavFromRec2(const char *ptr, int len);
	static	void	_staticFragFromRec(const char *ptr, int len);
	static	void	_staticFrag2FromRec(const char *ptr, int len);
	static	void	_staticLedFromRec(const char *ptr, int len);
	static	void	_staticPerfFromRec(const char *ptr, int len);

	static	void	_staticSpectFromRec(int *ptr, int len); 
	static	void	_staticSpectFromRec2(int *ptr, int len); 
	
	static	void	CWavfragDlg::_staticPlotFromRec(int *ptr, int len, int idx);

public:
	void LoadData();
	void LoadTray();
	void StopVR();

	void StartRec();
	void StopRec(); 

	void OnNotifyIcon(WPARAM wParam, LPARAM lParam);

	CWavfragDlg(CWnd* pParent = NULL);	// standard constructor

	void	DoSleep(int flag);
	void	Busy(int flag);
	void	Command(const char *comstr);
	void	LoadStock(const char *dir);
	
	void	OnOK();
	void	OnCancel();

	void	ChangeTab(int newtab);

//////////////////////////////////////////////////////////////////////////
// Data:

	NOTIFYICONDATA		nid;
	NOTIFYICONDATA2		nid2;

	int		stablized, busy, rec, recdone;	
	int		modalcontext, sleepcontext;

	int		in_train, stop_train;

	CPlotDlg			plotdlg;

	HWAVEIN			m_hRecord;
	HWAVEOUT		m_hPlay;

	//CRecordSound	recsnd;
	CPlaySound		playsound;
	
	CShowPic		showpic; 
	CVisDlg			visdlg;
	CxMixer			mixer;
	CWavDlg			wavdlg;
	C4DDlg			fourdlg;
	C3DDlg			threedlg;

	CString			laststr, orgtitle;

	CActionTab		actab;
	CFragTab		fragtab;
	CFragCollTab	fragcolltab;
	CUserTab		usertab;
	
	//////////////////////////////////////////////////////////////////////
	// Getters

	CLogWin *GetLogWin() { return &m_log; };
	CLabel	*GetPick() { return	&m_pick; };
	CTabCtrl *GetTab() { return &m_tab2; };
	CxButton  *GetArm() { return &m_arm; };
	CwaveEdit	*GetWavEdit() { return 	&m_wav; };
	CComboBox	*GetWordsCombo() { return 	&m_words; };

protected:

	void	xSetToolTips();
	void	xFillWaveIn();
	void	xFillWaveOut();
	void	xInitTabCtrl();
	void	xInitTabCtrl2();

	void	xTrainString(const char *str);

// Data:

	int		b6_reenter;

// Dialog Data
	//{{AFX_DATA(CWavfragDlg)
	enum { IDD = IDD_WAVFRAG_DIALOG };
	CTabCtrl	m_tab2;
	CxButton	m_phoneme;
	CxButton	m_onemon;
	CComboBox	m_words;
	CxButton	m_balloon;
	CLogWin		m_log6;
	CwaveEdit	m_wav2;
	CLabel		m_delay;
	CLabel		m_out;
	CLabel		m_in;
	CLabel		m_vol;
	CxButton	m_hist;
	CxButton	m_cplot;
	CxButton	m_stop;
	CxButton	m_rec;
	CxButton	m_recog;
	CxButton	m_play;
	CxButton	m_ok;
	CxButton	m_strict;
	CxButton	m_do;
	CVis		m_vis;
	CComboBox	m_com;
	CProgressCtrl	m_prog;
	CxButton	m_arm;
	CLabel		m_pick;
	CLed		m_led;
	CLogWin		m_log;
	CLogWin		m_log2;
	CLogWin		m_log3;
	CLogWin		m_log4;
	CTabCtrl	m_tab;
	CwaveEdit	m_wav;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavfragDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWavfragDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton3();
	afx_msg void OnButton12();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton11();
	afx_msg void OnButton13();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnButton15();
	afx_msg void OnButton14();
	afx_msg void OnButton16();
	afx_msg void OnButton17();
	afx_msg void OnButton9();
	afx_msg void OnButton18();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSelchangeCombo5();
	afx_msg void OnButton19();
	afx_msg void OnCheck3();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDropdownCombo1();
	afx_msg void OnButton21();
	afx_msg void OnButton22();
	afx_msg void OnButton24();
	afx_msg void OnButton23();
	afx_msg void OnButton26();
	afx_msg void OnButton27();
	afx_msg void OnButton25();
	afx_msg void OnSelchangeCombo7();
	afx_msg void OnButton28();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnButton29();
	afx_msg void OnButton30();
	afx_msg void OnSelchangeList3();
	afx_msg void OnSelchangingTab2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVFRAGDLG_H__380C999E_02E2_4DEA_8EA3_06713B98D102__INCLUDED_)
