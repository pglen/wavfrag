
/* =====[ wavfragDlg.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the wavfragDlg.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/19/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"

#include <io.h>
#include <math.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <process.h>
#include <direct.h>
#include <winuser.h>

#include "wavfrag.h"
#include "wavfragDlg.h"
#include "mxpad.h"
#include "GetText.h"
#include "FileDialogST.h"
#include "ComConf.h"
#include "support.h"
#include "SendKeys.h"
#include "Status.h"
#include "PickDlg.h"
#include "Focus.h"
#include "Phonames.h"

//const UINT WM_WF_NOTIFYICON = ::RegisterWindowMessage(_T("NotifyIcon"));
const UINT WM_WF_NOTIFYICON = WM_USER + 5;

CStatus   *statusdlg;
CFocus	  focus;

#undef P2N

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern	CReso		reso;

char wavfilter[] =
		"Wave Files (*.wav)\0*.wav\0All Files\0*.*\0\0" ;

char textfilter[] =
		"Text Files (*.txt)\0*.txt\0All Files\0*.*\0\0" ;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)

{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavfragDlg dialog

CWavfragDlg::CWavfragDlg(CWnd* pParent /*=NULL*/)
	: CGrayDlg(CWavfragDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavfragDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//bAlpha = 220;

	recdone = in_train = stop_train = rec = false;

	noheader = true;
	busy = stablized = sleepcontext = modalcontext = false;

	b6_reenter = false;

	// Disable window size retention
	want_w = -1;
}

void CWavfragDlg::DoDataExchange(CDataExchange* pDX)

{
	CGrayDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavfragDlg)
	DDX_Control(pDX, IDC_TAB2, m_tab2);
	DDX_Control(pDX, IDC_BUTTON30, m_phoneme);
	DDX_Control(pDX, IDC_BUTTON28, m_onemon);
	DDX_Control(pDX, IDC_COMBO7, m_words);
	DDX_Control(pDX, IDC_CHECK8, m_balloon);
	DDX_Control(pDX, IDC_LOG6, m_log6);
	DDX_Control(pDX, IDC_WAV2, m_wav2);
	DDX_Control(pDX, IDC_DELAY, m_delay);
	DDX_Control(pDX, IDC_OUT, m_out);
	DDX_Control(pDX, IDC_IN, m_in);
	DDX_Control(pDX, IDC_VOL, m_vol);
	DDX_Control(pDX, IDC_CHECK1, m_hist);
	DDX_Control(pDX, IDC_BUTTON7, m_cplot);
	DDX_Control(pDX, IDC_BUTTON2, m_stop);
	DDX_Control(pDX, IDC_BUTTON1, m_rec);
	DDX_Control(pDX, IDC_BUTTON3, m_recog);
	DDX_Control(pDX, IDC_BUTTON4, m_play);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_CHECK3, m_strict);
	DDX_Control(pDX, IDC_CHECK2, m_do);
	DDX_Control(pDX, IDC_LOG5, m_vis);
	DDX_Control(pDX, IDC_PROGRESS1, m_prog);
	DDX_Control(pDX, IDC_CHECK4, m_arm);
	DDX_Control(pDX, IDC_PICK, m_pick);
	DDX_Control(pDX, IDC_LED, m_led);
	DDX_Control(pDX, IDC_LOG, m_log);
	DDX_Control(pDX, IDC_LOG2, m_log2);
	DDX_Control(pDX, IDC_LOG3, m_log3);
	DDX_Control(pDX, IDC_LOG4, m_log4);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_WAV, m_wav);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWavfragDlg, CGrayDlg)
	//{{AFX_MSG_MAP(CWavfragDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, OnSelchangingTab1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_WM_SETCURSOR()
	ON_CBN_SELCHANGE(IDC_COMBO5, OnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_WM_SETFOCUS()
	ON_CBN_DROPDOWN(IDC_COMBO1, OnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON24, OnButton24)
	ON_BN_CLICKED(IDC_BUTTON23, OnButton23)
	ON_BN_CLICKED(IDC_BUTTON26, OnButton26)
	ON_BN_CLICKED(IDC_BUTTON27, OnButton27)
	ON_BN_CLICKED(IDC_BUTTON25, OnButton25)
	ON_CBN_SELCHANGE(IDC_COMBO7, OnSelchangeCombo7)
	ON_BN_CLICKED(IDC_BUTTON28, OnButton28)
	ON_WM_SHOWWINDOW()
	ON_WM_ACTIVATEAPP()
	ON_BN_CLICKED(IDC_BUTTON29, OnButton29)
	ON_BN_CLICKED(IDC_BUTTON30, OnButton30)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB2, OnSelchangingTab2)
	ON_MESSAGE(WM_WF_NOTIFYICON, OnNotifyIcon)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, OnSelchangeTab2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavfragDlg message handlers

BOOL CWavfragDlg::OnInitDialog()

{	
	CGrayDlg::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	statusdlg = new CStatus(this);
	statusdlg->parent = this;
	statusdlg->CenterStatus(GetDesktopWindow());
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		
	GetWindowText(orgtitle);

	// Create plot dialogs for testing
	plotdlg.Create(IDD_DIALOG2, GetDesktopWindow());
	plotdlg.ShowWindow(SW_SHOW);
	//plotdlg.ShowWindow(SW_HIDE);

	visdlg.Create(IDD_DIALOG3, GetDesktopWindow());
	//visdlg.ShowWindow(SW_HIDE);
	visdlg.ShowWindow(SW_SHOW);

	wavdlg.Create(IDD_DIALOG4, GetDesktopWindow());
	//wavdlg.ShowWindow(SW_HIDE);
	wavdlg.ShowWindow(SW_SHOW);

	threedlg.Create(IDD_DIALOG12, GetDesktopWindow());
	threedlg.ShowWindow(SW_SHOW);

	fourdlg.Create(IDD_DIALOG11, GetDesktopWindow());
	fourdlg.ShowWindow(SW_HIDE);
	//fourdlg.ShowWindow(SW_SHOW);

	// Align sub windows to tab
	xInitTabCtrl();

	xInitTabCtrl2();

	CTime ct = CTime::GetCurrentTime();
	CString datestr2 = ct.Format("%A, %B %d, %Y - %I:%M %p");

	m_log.AddString("Started "); m_log.AddString(datestr2); 
	m_log.AddString("\r\n");	m_log.AddString("\r\n");

	// Fill in wave device list
	xFillWaveIn();
	int ssource = AfxGetApp()->GetProfileInt("", "ssource", 0);	
	//AP2N(" CPlay::OnInitDialog sndsrc %d\r\n", ssource);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(ssource);
	
	xFillWaveOut();
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	int hist = AfxGetApp()->GetProfileInt("", "history", 0);	
	m_hist.SetCheck(hist);
	
	int ball = AfxGetApp()->GetProfileInt("", "balloon", 0);	
	m_balloon.SetCheck(ball);

	int arm = AfxGetApp()->GetProfileInt("", "arm", 1);	
	m_arm.SetCheck(arm);
	
	xSetToolTips();

	m_hPlay = playsound.WaveOpen();
	m_wav.pplaysnd = &playsound;
	m_wav2.pplaysnd = &playsound;
	
	int	licstat = WFL_GetLicStatus(1);

	//AP2N("Got Lic days: %d\r\n", licstat);

	// Re-read treshold from old instance
	CSliderCtrl *noise_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int	 initpos = AfxGetApp()->GetProfileInt("", "tresh", 3000);	
	noise_slider->SetRange(0, 10000);
	noise_slider->SetPos(noise_slider->GetRangeMax() - initpos);
	WFL_SetNoisetresh(initpos);

	// Do volume slider
	CSliderCtrl *vol_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	mixer.SetDevice(MIX_MIC_RECORD, ssource, m_hWnd);

	int mm, xx;	mixer.GetMinMax(&mm, &xx);
	//AP2N("min=%d max=%d\r\n", mm, xx);

	vol_slider->SetRange(mm, xx);
	DWORD vol = mixer.GetVolume();
	vol_slider->SetPos(vol_slider->GetRangeMax() - vol);
	
	CSliderCtrl *delay_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);
	delay_slider->SetRange(0, 8);
	int	 speedpos = AfxGetApp()->GetProfileInt("", "delay", 3);	
	delay_slider->SetPos(delay_slider->GetRangeMax() - speedpos);
	WFL_SetSilSpeed(speedpos + 2);
	//AP2N("speedpos=%d\r\n", speedpos);
	
	// Initialize callbacks 
	WFL_SetWavCallback(_staticWavFromRec);
	WFL_SetWavCallback2(_staticWavFromRec2);

	WFL_SetFragCallback(_staticFragFromRec);
	WFL_SetFragCallback2(_staticFrag2FromRec);

	WFL_SetSpectCallback(_staticSpectFromRec);
	WFL_SetSpectCallback2(_staticSpectFromRec2);
	
	WFL_SetStrCallback(_staticStrFromRec);
	WFL_SetLedCallback(_staticLedFromRec);
	WFL_SetPerfCallback(_staticPerfFromRec);
	WFL_SetPlotCallback(_staticPlotFromRec);

	// Feed to the voice recognition DLL
	//recsnd.callthis =	WFL_FeedSound; 
	WFL_WaveConnect(WFL_FeedSound);

	//recsnd.pprog = &m_prog;
	
	// Load wavfrag data
	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWavfragDlg::OnSysCommand(UINT nID, LPARAM lParam)

{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CGrayDlg::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWavfragDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CGrayDlg::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWavfragDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWavfragDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 

{
	int sel = m_tab.GetCurSel();

	TC_ITEM tc;

	tc.mask = TCIF_PARAM;
	m_tab.GetItem(sel, &tc);
			
	//AP2N("Change tab %x %d\r\n", tc.lParam, sel);

	CWnd *m_edit = (CWnd	*) tc.lParam;

	m_edit->SetWindowPos(&wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
	m_edit->ShowWindow(SW_SHOW);
	m_edit->SetFocus();	
	m_edit->Invalidate();

	*pResult = 0;
}

void CWavfragDlg::OnSelchangingTab1(NMHDR* pNMHDR, LRESULT* pResult) 

{
	int sel = m_tab.GetCurSel();

	TC_ITEM tc;

	tc.mask = TCIF_PARAM;
	m_tab.GetItem(sel, &tc);
			
	//AP2N("Change tab leave %x %d\r\n", tc.lParam, sel);

	CWnd *m_edit = (CWnd	*) tc.lParam;

	m_edit->ShowWindow(SW_HIDE);		
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnDestroy() 

{	
	CGrayDlg::OnDestroy();
	
	//ASSERT(IsWindow(m_hWnd));

	//desAP2N("CWavfragDlg::OnDestroy\r\n");

	// Close devices
	playsound.WaveClose();
	//recsnd.WaveInClose();
	WFL_WaveInClose();

	support.YieldToWinEx();

	CString fragfile(appdata);  fragfile += "fragfile.frg";
	WFL_SaveAllFrags(fragfile);

	CString collfile(appdata); collfile += "coll.txt";
	WFL_SaveStrColl(collfile);

	// Clean up recognition
	CString comfile(appdata);  comfile += "wavfrag.wfc";
	comcoll.Save(comfile);

	// Save Sound source
	int ssource = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	AfxGetApp()->WriteProfileInt("", "ssource", ssource);	

	int tresh = WFL_SetNoisetresh(3000);
	AfxGetApp()->WriteProfileInt("", "tresh", tresh);	

	int hist = m_hist.GetCheck();
	AfxGetApp()->WriteProfileInt("", "history", hist);	

	int ball = m_balloon.GetCheck();
	AfxGetApp()->WriteProfileInt("", "balloon", ball);	
			
	int arm = m_arm.GetCheck();
	AfxGetApp()->WriteProfileInt("", "arm", arm);	

	// Account for the artifical down floor
	int delay = WFL_SetSilSpeed(3) - 2;   
	AfxGetApp()->WriteProfileInt("", "delay", delay);	

#if 1
	// Clear balloon
	nid2.uFlags = NIF_INFO;
	nid2.dwInfoFlags = NIIF_INFO;
	strcpy(nid2.szInfo, "");
	
	Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA*)&nid2);
	Shell_NotifyIcon(NIM_DELETE,  &nid);	 

#endif

	delete	statusdlg;
}

//////////////////////////////////////////////////////////////////////////
// Start recording audio

void CWavfragDlg::StartRec() 

{
	int idx = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	if(idx < 0)
		idx = 0;

	int ret = WFL_WaveInOpen(idx);
	//AP2N("opened wave device %d\r\n", ret);

	if(ret < 0)
		{
		AfxMessageBox("Cannot open Wave Device");
		m_pick.SetText("Needs Wave Input Device");	
		}
	else
		{
		WFL_WaveStart();
		rec = true;
		m_pick.SetText("Listening ... ");	

		WFL_SetWavCallback(_staticWavFromRec);
		}
} 

//////////////////////////////////////////////////////////////////////////
// Start recording audio

void CWavfragDlg::OnButton1() 

{
	StartRec();
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton2() 

{
	StopRec();
}


//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::StopRec() 

{
	//recsnd.StopRecord();	
	WFL_WaveStop();
	rec = false;
	m_led.SetState(false);
	m_pick.SetText("Stopped.");
}

//////////////////////////////////////////////////////////////////////////

#if 0

void CPlay::OnButton39() 

{
	P2N("Load Frag\r\n");
	
	CFileDialogST  cdf(TRUE);

	CString droot, dresult, lresult;

	cdf.m_ofn.lpstrInitialDir = ".\\frags";
	cdf.m_ofn.lpstrFilter	= wavfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_ALLOWMULTISELECT | OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;

	POSITION pos = cdf.GetStartPosition( );

	// Delete accumulated frags
	int lenfr = fragarr.GetSize();
	for(int loopfr = 0; loopfr < lenfr; loopfr++)
		{
		ASSERT(((CFrag*)fragarr[loopfr])->magic == CFrag_Magic);
		delete( (CFrag*) fragarr[loopfr]);
		}
	fragarr.RemoveAll();
	
	int cnt = 0;
	while(true)
		{
		if(!pos) 
			break;

		CString str = cdf.GetNextPathName(pos);
		
		//P2N("Loading frag: '%s'\t fname='%s'\r\n",  str, fname); 

		CFrag  *pfrag = new CFrag;

		pfrag->LoadFrag(str);		
		//pfrag->Dump();		

		fragarr.Add(pfrag);
		
		cnt++;
		
		//support.YieldToWinEx();
		}
}

#endif

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnTimer(UINT nIDEvent) 

{
	// Called at application initialization
	if(nIDEvent == 1)
		{
		KillTimer(nIDEvent);
		LoadTray();	LoadData();		
		}
	
	if(nIDEvent == 2)
		{
		KillTimer(nIDEvent);
		
		int ssource = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		if(ssource < 0)
			ssource = 0;

		CString str2;
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(ssource, str2);

		m_pick.SetText(str2); support.YieldToWinEx();

		//recsnd.StopRecord();	
		WFL_WaveStop();
		rec = false;

		Sleep(300);

		// Do volume slider
		CSliderCtrl *vol_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		mixer.SetDevice(MIX_MIC_RECORD, ssource, m_hWnd);

		DWORD vol = mixer.GetVolume();
		vol_slider->SetPos(vol_slider->GetRangeMax() - vol);

		if(m_arm.GetCheck())
			OnButton1();
		}

	if(nIDEvent == 5)
		{
		KillTimer(nIDEvent);

		if(m_balloon.GetCheck())
			{
			CString tmp; tmp.Format("WavFrag: '%s' ", laststr);
			nid2.dwInfoFlags = NIIF_INFO;
			strcpy(nid2.szInfo, tmp);
			strcpy(nid2.szInfoTitle, "");
			
			Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA*)&nid2);
			}	

		Command(laststr);
		}
	
	CGrayDlg::OnTimer(nIDEvent);
}

void CWavfragDlg::OnButton3() 

{
	char *buff; int len;
	m_wav.GetSelBuff(&buff, &len);

	//char *buff = wedit.GetBuff();
	//int len = wedit.GetBuffLen();

	if(!buff || !len)
		return;

	WFL_SetWavCallback(NULL);
	
	int part = RECLEN / 2;

	// Feed it all at once
	//char *buff2 = (char*)malloc(len); ASSERT(buff2);
	//memcpy(buff2, buff, len);
	//recog.Recognize(buff2, len);

	CPtrArray arr;
	WFL_ScanBuffer(buff, len, &arr);

	// Free array
	int alen2 = arr.GetSize();
	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		CIntArr *tmp = (CIntArr *)arr.GetAt(loop2);
		ASSERT(tmp->magic == CIntArr_Magic);
		delete tmp;
		}
	
	WFL_SetWavCallback(_staticWavFromRec);	
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::LoadStock(const char *dir)

{
	CString strx(dir), strdir(dir);

	// Load stock from stock dir
	int idx = strx.ReverseFind('\\'); 
	strx = strx.Mid(idx + 1);	strdir = strdir.Left(idx + 1);

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	AP2N("CWavfragDlg::LoadStock olddir=%s\r\n", olddir);

	if(chdir(strdir) < 0)
		{
		CString tmp; tmp.Format("CWavfragDlg::LoadStock::Cannot load frags from '%s'", strdir);
		AP2N("%s\r\n", tmp);
		AfxMessageBox(tmp);
		return;
		}

	struct _finddata_t c_file;
    long hFile;

	if( (hFile = _findfirst("*.wav", &c_file )) >= 0)
		{
		int cnt = 0;
		while(true)
			{
			//AP2N( " %-12s %.24s  %9ld\r\n",
			//	c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

			//m_stock2.AddString(c_file.name);

			if( _findnext( hFile, &c_file ) != 0 )
				break;

			cnt++;
			}
		_findclose( hFile );
		}
		
	chdir(olddir);

	// Load stock from frag list
#if 0
	CPtrArray *tmparr = &CFrag::fragarr;
	int len2f = tmparr->GetSize();

	for(int loopw = 0; loopw < len2f; loopw++)
		{
		CFrag *fr = ((CFrag *)tmparr->GetAt(loopw));	
		ASSERT(fr->magic == CFrag_Magic);

		CString str = *fr->fname;
		support.PathToFname(str);

		m_stock2.AddString(str);
		}
#endif

}


//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton12() 

{


}

void CWavfragDlg::OnButton4() 

{
	m_wav.PlayBuff();	
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton5() 

{
	CFileDialogST  cdf(TRUE);

	CString droot, dresult, lresult;

	CString frdir(appdata);  frdir += "frags\\";
		
	cdf.m_ofn.lpstrInitialDir = frdir;
	cdf.m_ofn.lpstrFilter	= wavfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_ALLOWMULTISELECT | OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;

	POSITION pos = cdf.GetStartPosition( );

#if 0
	// Delete accumulated frags
	CFrag::DelFrags();

	int cnt = 0;
	while(true)
		{
		if(!pos) 
			break;

		CString str = cdf.GetNextPathName(pos);
		
		//P2N("Loading frag: '%s'\t fname='%s'\r\n",  str, fname); 

		CFrag  *pfrag = new CFrag;
		pfrag->LoadFrag(str);		
		//pfrag->Dump();		
		CFrag::fragarr.Add(pfrag);
		
		cnt++;
		
		//support.YieldToWinEx();
		}	

#endif
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton6() 

{
	if(b6_reenter)
		{
		//WFL_StopLoadAllFrags();
		AP2N("CWavfragDlg::OnButton6 reentry\r\n");
		m_log.printf("Load aborted, frag dictionary may be incomplete.\r\n");
		m_log.printf("Reload Frags at a later time.\r\n");
		return;
		}

	int ret = AfxMessageBox(
			"Reloading frags might take a minute or two. Are you sure?",
			MB_YESNO);

	if(ret != IDYES)
		return;

	OnButton2();

	b6_reenter = true;
	
	Busy(true);

	NMHDR dummy;LRESULT dummy2;
	
	OnSelchangingTab1(&dummy, &dummy2);
	m_tab.SetCurSel(3);
	OnSelchangeTab1(&dummy, &dummy2);

	m_pick.SetText("Parsing Frags ..."); support.YieldToWinEx();

	CString oldtext;
	//m_reload.GetWindowText(oldtext);
	//m_reload.SetWindowText("Stop Reload");
	
	//WFL_SetReload(true);
	//int ret2 = WFL_ParseAllFragWaves();
	//AP2N("Parsed %d frags\r\n", ret2);
				
	// Disable callback for now
	//WFL_SetSpectCallback(NULL);
	m_pick.SetText("Loading Frags ..."); support.YieldToWinEx();

	CString fragfile(appdata);  fragfile += "fragfile.frg";
	int ret3 = WFL_LoadAllFrags(fragfile);
	//AP2N("Loaded %d frags\r\n", ret3);
	
	// Restore it
	WFL_SetSpectCallback(_staticSpectFromRec);

	Busy(false);

	OnSelchangingTab1(&dummy, &dummy2);
	m_tab.SetCurSel(0);
	OnSelchangeTab1(&dummy, &dummy2);

	if(m_arm.GetCheck())
		OnButton1();

	//m_reload.SetWindowText(oldtext);
	b6_reenter = false;
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton7() 
 
{
	//m_plot.ClearAll();
	//m_plot2.ClearAll();
	//m_plot3.ClearAll();

	m_log.Clear();
	m_log2.Clear();
	m_log3.Clear();
	m_log4.Clear();
	m_log6.Clear();
	m_vis.Clear();


#if 1
	plotdlg.m_plot1.ClearAll();
	plotdlg.m_plot2.ClearAll();
	plotdlg.m_plot3.ClearAll();
	plotdlg.m_plot4.ClearAll();
	plotdlg.m_plot5.ClearAll();
	plotdlg.m_plot6.ClearAll();
#endif

	visdlg.m_vis.Clear();
	//d3ddlg.m_3d.Clear();
	//d4ddlg.m_4d.Clear();

	C2N;	
}

void CWavfragDlg::OnButton8() 

{	

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton11() 

{
#if 0
	int idx = m_coll.GetCurSel();
	if(idx < 0)
		{
		AfxMessageBox("Please select a word first");
		return;
		}

	int idx2 = m_words.GetCurSel();
	if(idx2 < 0)
		{
		AfxMessageBox("Please select an item first");
		return;
		}

	CString str; m_coll.GetText(idx, str);
	CString str2; m_words.GetLBText(idx, str2);

	char collstr[512]; 
		
	WFL_GetCollStr(idx, idx2, collstr, sizeof(collstr));

	AfxMessageBox(collstr);
#endif
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton13() 

{


}

void CWavfragDlg::OnSelchangeCombo1() 

{
	SetTimer(2, 100, NULL);
}

void CWavfragDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 

{
	CSliderCtrl  *noise_slider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER1);
	
	if(pScrollBar == (CScrollBar*)noise_slider)
		{
		if(nSBCode == SB_ENDSCROLL || nSBCode == SB_THUMBTRACK )
			{
			int top = noise_slider->GetRangeMax();
			int pos = top - noise_slider->GetPos();

			WFL_SetNoisetresh(pos);

			AP2N("Setting Noise treshold %d\r\n", pos);
			}
		}

	CSliderCtrl  *vol_slider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER2);

	if(pScrollBar == (CScrollBar*)vol_slider)
		{
		if(nSBCode == SB_ENDSCROLL || nSBCode == SB_THUMBTRACK )
			{
			int top = vol_slider->GetRangeMax();
			int pos = top - vol_slider->GetPos();

			mixer.SetVolume(pos);
			//AP2N("Got Volume %d\r\n", mixer.GetVolume());
			}
		}

	CSliderCtrl  *delay_slider = (CSliderCtrl *)GetDlgItem(IDC_SLIDER3);

	if(pScrollBar == (CScrollBar*)delay_slider)
		{
		if(nSBCode == SB_ENDSCROLL || nSBCode == SB_THUMBTRACK )
			{
			int top = delay_slider->GetRangeMax();
			int pos = top - delay_slider->GetPos();

			WFL_SetSilSpeed(pos + 2);
			AP2N("Setting silence / sig speed %d\r\n", pos);
			}
		}

	CGrayDlg::OnVScroll(nSBCode, nPos, pScrollBar);
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnSelchangeCombo3() 

{
#if 0
	int idx = m_stock2.GetCurSel();

	if(idx < 0)
		{
		return;
		}

	CString str; m_stock2.GetLBText(idx, str);

	CString stdir(appdata);  stdir += "stock\\";
	stdir += str;
		
	//AP2N("Selection changed %s\r\n", stdir);

	m_wav.OpenWave(stdir);

	OnButton3();
#endif
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton15() 

{
	UpdateData();

	int idx = m_com.GetCurSel();

	if(idx < 0)
		{
		AfxMessageBox("Please select an action first");
		return;
		}

	CString name; m_com.GetLBText(idx, name);
	CString tmp; tmp.Format(
		"Are you sure you want to delete the action: '%s'", name);

	if(AfxMessageBox(tmp, MB_YESNO) != IDYES)
		return;

	comcoll.DelComm(name);

	m_com.DeleteString(idx);
	m_com.SetCurSel(idx );
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton14() 

{

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton16() 

{
	CComConf conf;

	UpdateData();

	int idx = m_com.GetCurSel();

	if(idx < 0)
		{
		AfxMessageBox("Please select an action first");
		return;
		}

	CString name; m_com.GetLBText(idx, name);

	conf.name = name;
	
	conf.DoModal();
}

static char imgfilter[] =
		"Image Files (*.jpg *.gif *.bmp)\0*.jpg;*.gif;*.bmp\0All Files\0*.*\0\0" ;

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton17() 

{
	//HWND hwnd = focus.FindNextProc();
	//focus.GrabFocus(hwnd);	
		
	AfxGetApp()->WinHelp(0);
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticStrFromRec(const char *ptr, int len)

{
	//AP2N("String from recognizer '%s'\r\n", ptr);
	
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	pwnd->laststr = ptr;
	pwnd->recdone = true;
	pwnd->SetTimer(5, 20, NULL);

	if(pwnd->m_hist.GetCheck())	
		{
		CString strhist(appdata);  strhist += "history\\";

		char *buff; int wlen;
		WFL_GetLastWav(&buff, &wlen);

		if(buff != NULL && len != 0)
			{
			// Save it to wave history
			CString tmp; int cnt = 0;
			// Find first available filename	
			while(true)
				{
				tmp.Format("%s%s-%02d.wav", strhist, ptr, cnt);

				if(access(tmp, 0) < 0)
					{
					break;
					}
				cnt++;
				}
			//AP2N("Saving history to %s\r\n", tmp);
			int ret = pwnd->playsound.SaveWave(tmp, (void*)buff, wlen);
			}
	}
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticWavFromRec(const char *ptr, int len)

{
	//AP2N("Wav from recognizer %p %d\r\n", ptr, len);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	if(!pwnd->sleepcontext)
		{	
		//if(pwnd->rec)
			pwnd->m_wav.SetBuff((void*)ptr, len);
			//pwnd->wavdlg.m_wav.SetBuff((void*)ptr, len);
		}
}

void	CWavfragDlg::_staticWavFromRec2(const char *ptr, int len)

{
	//AP2N("Wav from recognizer %p %d\r\n", ptr, len);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	if(!pwnd->sleepcontext)
		{	
		//if(pwnd->rec)
			pwnd->m_wav2.SetBuff((void*)ptr, len);
		}
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticLedFromRec(const char *ptr, int len)

{	
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	if(!pwnd->sleepcontext)
		pwnd->m_led.SetState(len);

	int peak = (int)ptr;

	pwnd->m_prog.SetPos(100 * peak / SHRT_MAX);
}
		
//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticFragFromRec(const char *ptr, int len)

{
	//AP2N("Frag from recognizer %s\r\n", ptr);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	if(!pwnd->sleepcontext)
		pwnd->m_log3.printf("%s\r\n", ptr);
}

void	CWavfragDlg::_staticFrag2FromRec(const char *ptr, int len)

{
	//AP2N("Frag from recognizer %s\r\n", ptr);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	if(!pwnd->sleepcontext)
		pwnd->m_log6.printf("%s\r\n", ptr);
}


void	CWavfragDlg::_staticPerfFromRec(const char *ptr, int len)

{
	//AP2N("Perf data from recognizer %s\r\n", ptr);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	pwnd->m_log2.printf("%s\r\n", ptr);
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticSpectFromRec(int *ptr, int len)

{
	//AP2N("Spectral data from recognizer %p, %d\r\n", ptr, len);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	if(pwnd->sleepcontext)
		return;

	if(!ptr)
		{
		pwnd->m_vis.AddMarker();
		//pwnd->m_vis.Invalidate();
		}
	else
		{
		pwnd->m_vis.AddBuff(ptr, len);
		}

}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticSpectFromRec2(int *ptr, int len)

{
	//AP2N("Spectral data from recognizer %p, %d\r\n", ptr, len);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	if(!ptr)
		{
		pwnd->visdlg.m_vis.AddMarker();
		//pwnd->visdlg.m_vis.Invalidate();
		}
	else
		{
		pwnd->visdlg.m_vis.AddBuff(ptr, len);
		//pwnd->fourdlg.m_4d.AddIntArr(ptr, len);
		pwnd->threedlg.m_3d.AddIntArr(ptr, len);
		
		}
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::_staticPlotFromRec(int *ptr, int len, int idx)

{
	//AP2N("Plot data from recognizer %p, len=%d idx=%d\r\n", ptr, len, idx);

	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
	if(idx > 5 || idx < 0)
		{
		AP2N("_staticPlotFromRec invalid idx\r\n");
		return;	
		}

	if(!ptr)
		{
		pwnd->plotdlg.m_arr[idx]->AddMarker();
		pwnd->plotdlg.m_arr[idx]->Invalidate();
		}
	else
		{
		for(int loop = 0; loop < len; loop++)
			{
 			pwnd->plotdlg.m_arr[idx]->AddLine(ptr[loop]);
 			}
		}
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton9() 

{

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton18() 

{

}

//////////////////////////////////////////////////////////////////////////

BOOL CWavfragDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 

{
	if(busy)
		{	
		::SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_WAIT)));
		return true;
		}
	return CGrayDlg::OnSetCursor(pWnd, nHitTest, message);
}

//////////////////////////////////////////////////////////////////////////
// Refresh cursor to show busy status

void CWavfragDlg::Busy(int flag)

{
	busy = flag;
	POINT pt; GetCursorPos(&pt); SetCursorPos(pt.x, pt.y);
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnSelchangeCombo5() 

{
#if 0
	int idx = m_currw.GetCurSel();

	if(idx < 0)
		{
		return;
		}

	CString str; m_currw.GetLBText(idx, str);

	char dir[_MAX_PATH];	WFL_GetWavDir(dir, sizeof(dir));

	CString stdir;  stdir += dir;	stdir += str;  stdir += ".wav";
		
	//AP2N("Selection changed %s\r\n", stdir);

	m_wav.OpenWave(stdir, false);
#endif

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton19() 

{

}

//////////////////////////////////////////////////////////////////////////
// See if it is a command, execute it
	
void CWavfragDlg::Command(const char *comstr) 

{
	// Display cursor accompanyment
	if(GetForegroundWindow()!= this)
		statusdlg->Show(comstr, 1000);

	if(!sleepcontext || stricmp(comstr, "Wake Up") == 0)
		{
		m_pick.SetText(comstr);
		m_log.printf("%s\r\n", comstr);

		CString tmptitle = orgtitle; tmptitle += "  --  '"; 
		tmptitle += comstr; tmptitle += "'";
		SetWindowText(tmptitle);

		}

	CCommand *comx = comcoll.GetComStr(comstr);

	if(sleepcontext && comx && comx->kind != DO_WAKE)
		{
		return;
		}

	// These are cheats for an empty command dictionary
	if(strcmpi(comstr, "enable actions") == 0)
		{
		m_do.SetCheck(true);
		}
	if(strcmpi(comstr, "disable actions") == 0)
		{
		m_do.SetCheck(false);
		}

	
	// No command, defleat
	if(!comx)
		return;

	m_com.SelectString(0, *comx->name);

	if(modalcontext)
		{
		AP2N("In modal context\r\n");
			
		if(comx->kind == DO_NOMODAL || 	comx->kind == DO_YESMODAL)
			{
			CSendKeys sk;

			int endid = 0;

			if(comx->kind == DO_YESMODAL)
				endid = IDYES;
				
			if(comx->kind == DO_NOMODAL)
				endid = IDNO;			
				
			AP2N("Sending yes/no comm to modal window\r\n");
			
			#if 1
			if(comx->kind == DO_YESMODAL)
				sk.SendKeys("y");

			if(comx->kind == DO_NOMODAL)
				sk.SendKeys("n");
		
			#endif
			
#if 0
			// Send terninating command
			HWND fg_hwnd = ::GetForegroundWindow();
			
			//AP2N("Forground %d me %d\r\n", fg_hwnd, m_hWnd);

			DWORD pid_fg_win = GetWindowThreadProcessId(fg_hwnd, NULL);
			DWORD pid_win = GetWindowThreadProcessId(m_hWnd, NULL);				

			::AttachThreadInput(pid_fg_win, pid_win, TRUE);

			//((CDialog*)FromHandle(fg_hwnd))->EndDialog(endid);
			
			::AttachThreadInput(pid_fg_win, pid_win, FALSE);	
			
#endif

			}
		return;
		}

	// Pre-getcheck state
	if(comx->kind == DO_ENABACT)
		{
		AP2N("Enabling actions.\r\n");
		m_do.SetCheck(true);
		return;
		}

	// Pre-getcheck state
	if(comx->kind == DO_DISABACT)
		{
		AP2N("Disable actions.\r\n");
		m_do.SetCheck(false);
		return;
		}

#if 0
	// Pre-getcheck state
	if(comx->kind == DO_SLEEP)
		{
		AP2N("Goto sleep\r\n");
		DoSleep(true);			
		return;
		}

	if(comx->kind == DO_WAKE)
		{
		AP2N("Waking up\r\n");
		DoSleep(false);			
		return;
		}
#endif

	if(!m_do.GetCheck())
		{
		m_log.printf("'%s' action skipped.\r\n", *comx->name);
		m_log.printf("To enable actions check the 'Enable Actions' checkbox.\r\n");
		m_log.printf("Or say 'enable actions' to enable\r\n");
		return;
		}
	
	//////////////////////////////////////////////////////////////////////
	// Do Commands

	switch(comx->kind)
		{	
		case DO_EXE:
			{
			CString comstr = *comx->comstr;
			CString comm = *comx->comm;
			CString para = *comx->para;

			SHELLEXECUTEINFO sei; memset(&sei, 0, sizeof(SHELLEXECUTEINFO));
			sei.cbSize = sizeof(SHELLEXECUTEINFO);

			sei.fMask		  = SEE_MASK_DOENVSUBST | SEE_MASK_FLAG_NO_UI;
			sei.lpFile		  = comm;
			sei.lpParameters  = para;
			sei.nShow		  = SW_SHOWNORMAL;

			//AP2N("Shell command %s -> '%s' '%s'\r\n", comstr, comm, para);
					
			if(comx->prompt)
				{							
				CString tmp; tmp.Format(
					"Are you sure you want to execute action\r\n\r\n"
										"'%s'",	*comx->name);

				int ret = AfxMessageBox(tmp, MB_YESNO);
				
				if(ret != IDYES)
					return;
				}

			int ret = ShellExecuteEx(&sei);
			if(ret == 0)
				{
				CString tmp; tmp.Format(
					"Could not execute: '%s'", *comx->comm);

				AfxMessageBox(tmp);
				}
			}
			break;


		case DO_IMAGE:				

			focus.GrabFocus(m_hWnd);	

			SetActiveWindow();
			ShowWindow(SW_SHOWNORMAL);

			support.lastimg = *comx->para;
showimage:
			if(support.lastimg != "")
				{
				//lb.Show();	lb.DarkGrayScreen();
				showpic.fname = support.lastimg;
				showpic.Show();
				showpic.LoadPic();
				}
			break;

		case DO_IMAGECLOSE:				
			//SetTimer(4, 100, NULL);
			//lb.Hide();			
			showpic.Hide();
			break;

		case DO_IMAGENEXT:				
			if(support.NextImgFileName(support.lastimg))
				goto showimage;
			break;

		case DO_IMAGEPREV:				
			if(support.PrevImgFileName(support.lastimg))
				goto showimage;
			break;

		case DO_EXITME:	
			{
			CString tmp; tmp.Format(
					"Are you sure you want to exit WavFrag?\r\n");

			int ret = AfxMessageBox(tmp, MB_YESNO);
			
			if(ret != IDYES)
				return;

			EndDialog(IDOK);
			break;
			}

		case DO_SHUTDOWN:
			{
			CString tmp; tmp.Format(
					"Are you sure you want to shut down the computer\r\n\r\n");										
			int ret = AfxMessageBox(tmp, MB_YESNO);				
			if(ret != IDYES)
				return;
			support.ShutDownComputer();
			EndDialog(IDOK);			
			}
			break;

		case DO_MINME:
			// CWnd
			ShowWindow(SW_MINIMIZE);
			break;

		case DO_MAXME:

			focus.GrabFocus(m_hWnd);	

			SetActiveWindow();
			ShowWindow(SW_SHOWNORMAL);
			break;

		case DO_TERMINATE:
			{
			CWnd *wnd = GetForegroundWindow();
			CString title; wnd->GetWindowText(title);

			CString tmp; tmp.Format(
					"Are you sure you want to close program\r\n\r\n"
					"'%s'", 
					title);										
			int ret = AfxMessageBox(tmp, MB_YESNO);				
			if(ret != IDYES)
				return;
			
			wnd->PostMessage(WM_QUIT);
			}
			break;

		case DO_ACTNEXT:			
			{
			HWND hwnd = focus.FindNextProc();
			focus.GrabFocus(hwnd);	
			}
			break;

		case DO_ACTPREV:			
			{
			HWND hwnd = focus.FindPrevProc();
			focus.GrabFocus(hwnd);	
			}
			break;

		case DO_KEYS:			
			{
			CSendKeys sk;

			AP2N("Sending keys '%s'\r\n", *comx->para);

			// Do not send to ourselves

			if(GetForegroundWindow() != this)		
				sk.SendKeys(*comx->para);
			}
			break;

		case DO_DOC:			
			{
			CString para = *comx->para;
			ShellExecute(NULL, "open", para, NULL, NULL, SW_SHOWNORMAL);	
			}
			break;
		}
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnCheck3() 

{
	WFL_SetStrict(m_strict.GetCheck());		
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::DoSleep(int flag)

{
	// CWnd
	sleepcontext = flag;

	if(sleepcontext)
		{
		m_pick.SetText("Sleeping ...");
		//m_prog.EnableWindow(false);
		m_log.printf("Entered Sleeping state, not listening ...\r\n");
		m_log.printf("Say 'Wake Up' for activating reconition.\r\n");
		
		m_wav.SetBuff(NULL, 0);
		}
	else
		{
		//m_pick.SetText("Awakened, listening ...");
		m_log.printf("Awakened, listening ...");
		//m_prog.EnableWindow(true);
		}
}

//////////////////////////////////////////////////////////////////////////

BOOL CWavfragDlg::PreTranslateMessage(MSG* pMsg) 

{
	//AP2N("CWavfragDlg::PreTranslateMessage(MSG* pMsg %s)\r\n", mxpad.num2msg(pMsg->message));

	if(pMsg->message == nid.uCallbackMessage)
		{
		AP2N("Message from tray %d %d\r\n", pMsg->wParam, pMsg->lParam);
		}

	if(pMsg->message == MM_MIXM_CONTROL_CHANGE)
		{
		//AP2N("MM_MIXM_CONTROL_CHANGE %x %x\r\n", pMsg->wParam, pMsg->lParam);
		//AP2N("Mixer volume %d device %x\r\n", mixer.GetVolume(), mixer.GetDevice());

		// See which device sent it
		if(mixer.GetDevice() == pMsg->wParam)
			{
			CSliderCtrl *vol_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
			DWORD vol = mixer.GetVolume();
			vol_slider->SetPos(vol_slider->GetRangeMax() - vol);
			}
		}

	return CGrayDlg::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnSetFocus(CWnd* pOldWnd) 

{
	//AP2N("CWavfragDlg::OnSetFocus\r\n");

	CGrayDlg::OnSetFocus(pOldWnd);
	
	statusdlg->Hide();	
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnDropdownCombo1() 

{
	//AP2N("Re-read devices\r\n");
	xFillWaveIn();
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::xFillWaveIn()

{	
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();

	int dev = waveInGetNumDevs();
	for(int loop = 0; loop < dev; loop++)
		{
		WAVEINCAPS wc;

		waveInGetDevCaps(loop, &wc, sizeof(WAVEINCAPS));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(wc.szPname);
			
		//AP2N("Input device %s\r\n", wc.szPname);
		}
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::xFillWaveOut()

{
	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();

	int dev2 = waveOutGetNumDevs();
	for(int loop2 = 0; loop2 < dev2; loop2++)
		{
		WAVEOUTCAPS wc;

		waveOutGetDevCaps(loop2, &wc, sizeof(WAVEOUTCAPS));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(wc.szPname);
			
		//AP2N("Output device %s\r\n", wc.szPname);
		}
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::xSetToolTips()

{
//	m_train.SetTooltip("List of trained frags.\r\n"
//		"Click on any word to select it. The currently selected frag is operated on\r\n"
//		"with the training facility and the wave management facility.\r\n"
//		"Click on the 'New Word' button to add a new string, then train it \r\n"
//		"by pronouncing it, and clicking on the 'Train Word' button");

//	m_lab_wav.SetTooltip("List of trained wave files.\r\n"
//		"Click on the 'Delete Entry' button to remove the selected wave, \r\n"
//		"When selected, click on the file name to show/edit it in the wave editor window.\r\n"
//		"Do remember to save the edited wave file.");

//	m_lab_tresh.SetTooltip("Silence treshold.\r\n"
//		"Adjust the slider to a boundary where your speech triggers recognition,\r\n"		
//		"and Wavfrag is idle when you are not speaking.");

//	m_lab_actions.SetTooltip("Action / Uttering assignment.\r\n"
//		"Assign actions to trained words. One action can be assigned to three different words,\r\n"		
//		"creating aliases like 'Close Window' or 'Close Application' or 'Exit program'.\r\n"
//		"The created aliases will execute the same action. (Ex: Closing the Current Application)");

	m_strict.SetTooltip("Use strict recognition.\r\n"
						"Recognition normally is dependent on the top match.\r\n"
						"with 'Strict Recognition' recognition needs two top matches.\r\n"
						"Shortcut key Alt-G");
		
	m_hist.SetTooltip("Save recognition history.\r\n"
						"When checked, wave files are saved to the history directory,r\n"
						"under their (proposed) match name. It is safe to leave this unchecked.\r\n"
						"Uses significant disk space to save all the wave files.");
	
	m_do.SetTooltip("Enable actions."
					"One can arm this function by clicking on the checkbox or saying\r\n"
					"'Enable Actions' or 'Enable Commands'. Additionally, the command\r\n"
					"configuration dialog will allow you to assign newly "
					"trained words to this action.\r\n"
					"Shortcut key Alt-B");

	m_balloon.SetTooltip("Enable ballon tooltip on the taskbar");

	m_ok.SetTooltip("Exit WavFrag Application.\r\n"
					"Recognition will stop, all sound and command data is saved.\r\n"
					"Shortcut key Alt-X");

	//m_play.SetTooltip("Play currently displayed wave.\r\n"
	//					"If no sound is loaded, the wave editor will\r\n"
	//					"flash for a brief moment with an approriate message.\r\n"
	//					"Shortcut key Alt-A");

	m_recog.SetTooltip("Recognize the currently active wave, that is displayed in\r\n"
					"the wave editor. After recognition the waveform will be \r\n"
					"displayed again, processed, normalized, and cut to boundaries\r\n"
					"as the recognition engine understood it and parsed it.\r\n"
					"Mostly useful for testing.");

	
	//m_delwav.SetTooltip(IDS_TEST);

	m_rec.SetTooltip(	"Start Recording (listening)\r\n"
						"On startup WavFrag will start in listening mode\r\n"
						"Shortcut key Alt-R");

	m_stop.SetTooltip(	"Stop Recording (listening)\r\n"
						"WavFrag will stop listening to commands.\r\n"
						"To restart listening press the 'Record' button.\r\n"
						"If you want WavFrag to be restartable by voice, \r\n"
						"use the 'Sleep' commands\r\n"
						"Shortcut key Alt-S");

	m_vol.SetTooltip(	"Volume Control.\r\n"
						"Will control the Windows Mixer volume for the currently\r\n"
						"selected input. One can use this volum,e control and the\r\n"
						"mixer volume control interchangably");

//	m_cplot.SetTooltip(	"Clear plots.\r\n"
//						"WavFrag will clear all utility windows, and the log and spectral plots.\r\n"
//						"Shortcut key Alt-C");

//	m_help.SetTooltip(	"Show help.\r\n"
//						"Help file is shown in a standard web browser.\r\n"
//						"Shortcut key F1");
	
//	m_conf.SetTooltip(	"Configure currently selected action.\r\n"
//						"A confiure dialog is shown, where one can assign\r\n"
//						"words / utterings to commands. Every command can have\r\n"
//						"three aliases. There is no limit to the number of commands.");

//	m_rem.tip.bgcolor = RGB(0xff, 0xee, 0xee);
//	m_rem.SetTooltip(	"Remove currently selected action.\r\n"
//						"The command will be deactivated and removed from the list\r\n"
//						"of commands. Will not remove the training data.\r\n"
//						"A Yes/No confirmation dialog is shown before deleteing");

//	m_add.SetTooltip(	"Add a new action.\r\n"
//						"A new action / command will added to the action list.\r\n"
//						"This is the name of the action, it does not have any bearing\r\n"
//						"on the recognized word or the executed command.\r\n"
//						"Aliases and identical names are permitted, but may be confusing.");

	m_in.SetTooltip(	"The input sound source.");

	m_out.SetTooltip(	"The output sound device.");

	m_arm.SetTooltip(	"Start WavFrag in listening (recognition) mode.\r\n"
						"When checked, as soon as WavFrag initilised itself,\r\n"
						"it will start listening. Commands are not enabled by default,\r\n"
						"one can say 'Enable Commands' or 'Enable Actions' to fully\r\n"
						"activate command functionality.");

	m_delay.SetTooltip(	"Delay / Speed of silence detection.\r\n"
						"Select a delay where the recognition recognizes short words, but does not\r\n"
						"break long phrases into fragments. The best way to set this is trying\r\n"
						"to say the word 'Yes' and a longer phrase like 'Activate Next'\r\n"
						"Setting is optimal where one can say both naturally, and it is not"
						"broken into fragments and it is recognized.");


	//m_sleepb.SetTooltip("Toggle sleep state.\r\n"
	//					"If asleep, WavFrag will wake up, and vice versa. The sleep state\r\n"
	//					"can also be controlled by voice by saying 'Go to Sleep' or\r\n"
	//					"'Wake up'. Additional words can be trained to put wavefrag to\r\n"
	//					"sleep or wake it up in the command configration dialog");

	m_onemon.SetTooltip("Gather all utility windows to this monitor\r\n"
						"Useful if system monitor settigs change.");

	m_phoneme.SetTooltip("Show a consise listing of phonems.\r\n"
						"Useful in case a new phoneme is needed, and no other references are available.");
}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::xInitTabCtrl()

{
	WINDOWPLACEMENT wp; m_tab.GetWindowPlacement(&wp);

	m_log.ShowWindow(true);
	m_log.SetWindowPos(NULL, wp.rcNormalPosition.left + 4,  wp.rcNormalPosition.top + 25, 
				wp.rcNormalPosition.right - wp.rcNormalPosition.left - 6, 
					wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - 27, SWP_NOZORDER );

	m_log2.ShowWindow(false);
	m_log2.SetWindowPos(NULL, wp.rcNormalPosition.left + 4,  wp.rcNormalPosition.top + 25, 
				wp.rcNormalPosition.right - wp.rcNormalPosition.left - 6, 
					wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - 27, SWP_NOZORDER );

	m_log3.ShowWindow(false);
	m_log3.SetWindowPos(NULL, wp.rcNormalPosition.left + 4,  wp.rcNormalPosition.top + 25, 
				wp.rcNormalPosition.right - wp.rcNormalPosition.left - 6, 
					wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - 27, SWP_NOZORDER );

	m_log4.ShowWindow(false);
	m_log4.SetWindowPos(NULL, wp.rcNormalPosition.left + 4,  wp.rcNormalPosition.top + 25, 
				wp.rcNormalPosition.right - wp.rcNormalPosition.left - 6, 
					wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - 27, SWP_NOZORDER );

	m_vis.ShowWindow(false);
	m_vis.SetWindowPos(NULL, wp.rcNormalPosition.left + 4,  wp.rcNormalPosition.top + 25, 
				wp.rcNormalPosition.right - wp.rcNormalPosition.left - 6, 
					wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - 27, SWP_NOZORDER );
	
	m_log6.ShowWindow(false);
	m_log6.SetWindowPos(NULL, wp.rcNormalPosition.left + 4,  wp.rcNormalPosition.top + 25, 
				wp.rcNormalPosition.right - wp.rcNormalPosition.left - 6, 
					wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - 27, SWP_NOZORDER );

//////////////////////////////////////////////////////////////////////////


	m_pick.ModifyStyleEx(0, WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_EX_DLGMODALFRAME,  SWP_DRAWFRAME);

	m_pick.SetTrans(false);	
	m_pick.SetFontSize(36); 	m_pick.SetFontBold(true);
	m_pick.CenterText(true);	m_pick.CenterTextV(true);

	m_pick.SetText("Idle");

	//CTabCtrl
	TCITEM TabCtrlItem; int cnt = 0;
	
	TabCtrlItem.pszText = "&Recog";
	TabCtrlItem.lParam = (long) &m_log;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab.InsertItem(cnt++, &TabCtrlItem );

	TabCtrlItem.pszText = "Progress";
	TabCtrlItem.lParam = (long) &m_log2;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab.InsertItem(cnt++, &TabCtrlItem );

	TabCtrlItem.pszText = "Frags";
	TabCtrlItem.lParam = (long) &m_log3;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab.InsertItem(cnt++, &TabCtrlItem );

	TabCtrlItem.pszText = "Frag2";
	TabCtrlItem.lParam = (long) &m_log6;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab.InsertItem(cnt++, &TabCtrlItem );
	
	TabCtrlItem.pszText = "Spectra";
	TabCtrlItem.lParam = (long) &m_vis;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab.InsertItem(cnt++, &TabCtrlItem );

}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::xInitTabCtrl2()

{
	WINDOWPLACEMENT wp; m_tab2.GetWindowPlacement(&wp);

	int padd = 4;	// Universal padding 
	int cnt = 0;

	usertab.Create(usertab.IDD, this);
	fragtab.Create(fragtab.IDD, this);
	fragcolltab.Create(fragcolltab.IDD, this);
	actab.Create(actab.IDD, this);
		
	//CTabCtrl	
	TCITEM TabCtrlItem; 
	
	//ClientToScreen(&wp.rcNormalPosition); // Used on popup dlg property

	TabCtrlItem.pszText = "&Users";
	TabCtrlItem.lParam = (long) &usertab;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab2.InsertItem(cnt++, &TabCtrlItem );

	CRect rc; m_tab2.GetItemRect( cnt - 1, &rc);

	//////////////////////////////////////////////////////////////////////
	int www = wp.rcNormalPosition.right - wp.rcNormalPosition.left;
	int hhh = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top;

	usertab.SetWindowPos(NULL, wp.rcNormalPosition.left + padd,  
				wp.rcNormalPosition.top + rc.Height() + 2 * padd, 
					www - 2 * padd, hhh - rc.Height() -  4 * padd, 
							SWP_NOZORDER );

	TabCtrlItem.pszText = "&Frags";
	TabCtrlItem.lParam = (long) &fragtab;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab2.InsertItem(cnt++, &TabCtrlItem );
	
	//AP2N("CWavfragDlg::xInitTabCtrl2 item rect ww=%d hh=%d\r\n", 
			//rc.Width(), rc.Height()); 

	fragtab.SetWindowPos(NULL, wp.rcNormalPosition.left + padd,  
				wp.rcNormalPosition.top + rc.Height() + 2 * padd, 
					www - 2 * padd, hhh - rc.Height() -  4 * padd, 
							SWP_NOZORDER );

	TabCtrlItem.pszText = "&Str Coll";
	TabCtrlItem.lParam = (long) &fragcolltab;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab2.InsertItem(cnt++, &TabCtrlItem );

	fragcolltab.SetWindowPos(NULL, wp.rcNormalPosition.left + padd,  
				wp.rcNormalPosition.top + rc.Height() + 2 * padd, 
					www - 2 * padd, hhh - rc.Height() -  4 * padd, 
							SWP_NOZORDER );

	TabCtrlItem.pszText = "&Action";
	TabCtrlItem.lParam = (long) &actab;
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT ;
	m_tab2.InsertItem(cnt++, &TabCtrlItem );

	actab.SetWindowPos(NULL, wp.rcNormalPosition.left + padd,  
				wp.rcNormalPosition.top + rc.Height() + 2 * padd, 
					www - 2 * padd, hhh - rc.Height() -  4 * padd, 
							SWP_NOZORDER );

	// Init default visible
	usertab.ShowWindow(SW_SHOW);

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton21() 

{
#if 0
	CGetText gt; gt.m_title = "Enter a string to train";
	
	int oldrec = WFL_WaveIsRec();
	OnButton2();

	if(gt.DoModal() == IDCANCEL)
		{
		OnButton1();
		return;
		}

	WFL_SetTrainStr(gt.m_edit);	

	CString tmp; 
	if(gt.m_edit == "")
		{
		tmp.Format("Switched to recognition");
		}
	else
		{
		tmp.Format("Training '%s'", gt.m_edit);

		if(m_coll.FindString(0, gt.m_edit) == LB_ERR)
			{
			m_coll.AddString(gt.m_edit);
			}
		}

	m_pick.SetText(tmp);
	
	if(oldrec)
		OnButton1();
#endif
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton22() 

{
	WFL_SetTrainStr("");

	CString tmp; tmp.Format("Switched to recognition");
	m_pick.SetText(tmp);
}

void CWavfragDlg::OnButton24() 

{
	CPickDlg dlg;
	dlg.DoModal();
}

BOOL CWavfragDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//AP2N("CWavfragDlg::OnCommand wParam=%d lParam=%d\r\n", wParam, lParam);
		
	switch(wParam)
		{
		case ID_Q_EXITWAVFRAG:
			OnOK();
			break;

		case ID_Q_STARTLISTENING:
			OnButton1();
			break;

		case ID_Q_STOPLISTENING:
			OnButton2();
			break;
		}

	return CGrayDlg::OnCommand(wParam, lParam);
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)

{
	//AP2N("CWavfragDlg::OnNotifyIcon wParam=%d (%x) lParam=%d (%x)\r\n", 
	//			wParam, wParam, lParam, lParam);

	switch(lParam)
		{
		case WM_LBUTTONDOWN:
			//AP2N("WM_LBUTTONDOWN\r\n");
			//ShowWindow(SW_SHOW);
			//SetActiveWindow();
			focus.GrabFocus(m_hWnd);	
			break;

		case WM_RBUTTONDOWN:
			//AP2N("WM_RBUTTONDOWN\r\n");
			{
			CMenu aMenu;
			aMenu.LoadMenu(IDR_TASKBAR_MENU);

			CPoint mouse; GetCursorPos(&mouse);
			aMenu.GetSubMenu(0)->TrackPopupMenu(
				TPM_RIGHTALIGN | TPM_RIGHTBUTTON, mouse.x, mouse.y, 
						AfxGetMainWnd(), 0);				
			}
			break;

		}
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton23() 

{
	char *buff; int len;
	m_wav.GetSelBuff(&buff, &len);

	//char *buff = wedit.GetBuff();
	//int len = wedit.GetBuffLen();

	if(!buff || !len)
		return;

	OnButton2();

	WFL_SetWavCallback(NULL);
	
	int part = RECLEN / 2;

	recdone = false;

#if 1
	// Feed blank ones to trigger emit
	for(int loopb = 0; loopb < 30 * part; loopb += part)
		{
		char *buff3 = (char*)malloc(part); ASSERT(buff3);
		
		// Empty buffer, zero it
		memset(buff3, 0, part);

		WFL_FeedSound(buff3, part);
		}
#endif

	// Feed it like it comes from a sound source
	for(int loop = 0; loop < len; loop += part)
		{
		char *buff3 = (char*)malloc(part); ASSERT(buff3);
		int len2 = min(len - loop, part);

		// Partial buffer, zero it
		if(len2 < part)
			memset(buff3, 0, part);

		memcpy(buff3, buff + loop, len2);
		WFL_FeedSound(buff3, len2);
		}

	//WFL_Emit();

#if 1
	// Feed blank ones to trigger emit
	for(loop = 0; loop < 30 * part; loop += part)
		{
		char *buff3 = (char*)malloc(part); ASSERT(buff3);
		
		// Empty buffer, zero it
		memset(buff3, 0, part);

		WFL_FeedSound(buff3, part);
		}
#endif

	unsigned int lastclock = clock() + 15 * CLOCKS_PER_SEC;
	
	// Wait for recognition to finish
	while (true)
		{
		unsigned int newclock = clock();
		if(newclock > lastclock)
			{
			//AP2N("Timeout waiting voice recognition to finish\r\n");
			break;
			}
			
		if(recdone)
			break;

		if(stop_train)
			break;

		Sleep(5);
		support.YieldToWinEx();
		}

	WFL_SetWavCallback(_staticWavFromRec);	
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton26() 

{	
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton27() 

{
#if 0
	AP2N("CWavfragDlg::OnButton27\r\n");

	int idx = m_coll.GetCurSel();
	if(idx < 0)
		{
		AfxMessageBox("Must select a word to train first");
		return;
		}

	int oldrec = WFL_WaveIsRec();
	OnButton2();

	CString str; m_coll.GetText(idx, str);

	WFL_SetTrainStr(str);	

	OnButton23();

	WFL_SetTrainStr("");

	if(oldrec)
		OnButton1();

#endif
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton25() 

{
	//AP2N("CWavfragDlg::OnButton25\r\n");

	if(in_train)
		{
		//m_b25.SetWindowText("Stopping");
		stop_train = true;
		return;
		}

	CFileDialogST  cdf(true);

	CString droot, dresult, lresult;
	CString wavdir(appdata); wavdir += "wavdic";
	
	cdf.m_ofn.lpstrInitialDir = wavdir;
	cdf.m_ofn.lpstrFilter	= wavfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;

	CString oldface; //m_b25.GetWindowText(oldface);
	in_train = true;
	//m_b25.SetWindowText("Stop");
	
	CString strdir = cdf.GetFileDir();

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	if(chdir(strdir) < 0)
		{
		CString tmp; tmp.Format("CWavfragDlg: Cannot load waves from '%s'", strdir);
		AP2N("%s\r\n", tmp);
		AfxMessageBox(tmp);
		return;
		}

	WFL_SetWavCallback(NULL);	

	struct _finddata_t c_file;
    long hFile;

	if( (hFile = _findfirst("*.wav", &c_file )) >= 0)
		{
		int cnt = 0;
		while(true)
			{
			//AP2N( " %-12s %.24s  %9ld\r\n",
			//	c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

			xTrainString(c_file.name);

			if( _findnext( hFile, &c_file ) != 0 )
				break;

			if(stop_train)
				break;

			cnt++;
			}
		_findclose( hFile );
		}
	
	chdir(olddir);

	WFL_SetWavCallback(_staticWavFromRec);	

	in_train = false;
	//m_b25.SetWindowText(oldface);	

	m_pick.SetWindowText("Done training");
	support.YieldToWinEx();

}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::xTrainString(const char *str)

{
	CString fname = support.GetFilename(str);

	int idxx = fname.FindOneOf("1234567890-");

	if(idxx >= 0)
		fname = fname.Left(idxx);
	
	fname.MakeLower();

	WFL_SetTrainStr(fname);	

	AP2N("CWavfragDlg::xTrainString fname='%s'\r\n", fname);	

	if(!m_wav.OpenWave(str))
		{
		AfxMessageBox("Cannot load wave");
		return;
		}
	
	OnButton23();

	WFL_SetTrainStr("");

	support.YieldToWinEx();
	
	//m_wav.PlayBuff();
	//support.YieldToWinEx();
	//m_wav.WaitForEnd();

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnSelchangeCombo7() 
{

}

//////////////////////////////////////////////////////////////////////////

void	CWavfragDlg::OnOK()

{
	//AP2N("CWavfragDlg:OnOK\r\n");
	StopVR();
	CGrayDlg::OnOK();
}

void	CWavfragDlg::OnCancel()

{
	//AP2N("CWavfragDlg:OnCancel\r\n");
	StopVR();
	CGrayDlg::OnCancel();
}

//////////////////////////////////////////////////////////////////////////

//DEL BOOL CWavfragDlg::DestroyWindow() 
//DEL 
//DEL {
//DEL 	AP2N("CWavfragDlg::DestroyWindow\r\n");	
//DEL 	return CGrayDlg::DestroyWindow();
//DEL }

void CWavfragDlg::StopVR()

{
	//AP2N("CWavfragDlg::StopVR\r\n");	
	
	// Stop rec/playing 
	playsound.StopPlay();
	
	//recsnd.StopRecord();
	WFL_WaveStop();
	rec = false;

	//support.YieldToWinEx();
	WFL_ShutDown();
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton28() 

{	
	if(!IsWindow(visdlg) || !IsWindow(plotdlg) || !IsWindow(wavdlg))
		return;
	
	visdlg.CenterWindow();
	visdlg.ShowWindow(SW_SHOW);
	visdlg.BringWindowToTop();
	
	plotdlg.CenterWindow();
	plotdlg.ShowWindow(SW_SHOW);
	plotdlg.BringWindowToTop();

	wavdlg.CenterWindow();
	wavdlg.ShowWindow(SW_SHOW);
	wavdlg.BringWindowToTop();

	BringWindowToTop();
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnShowWindow(BOOL bShow, UINT nStatus) 

{
	CGrayDlg::OnShowWindow(bShow, nStatus);
	
	//AP2N("CWavfragDlg::OnShowWindow\r\n");	
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnActivateApp(BOOL bActive, HTASK hTask) 

{
	CGrayDlg::OnActivateApp(bActive, hTask);
	
	//AP2N("CWavfragDlg::OnActivateApp %d\r\n", bActive);

	//if(bActive)
	//	OnButton28();
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton29() 

{
#if 0
	int idx = m_coll.GetCurSel();

	if(idx < 0)
		{
		AfxMessageBox("Please select a word to clear");
		return;
		}
	
	CString str; m_coll.GetText(idx, str);

	//AP2N("Deleteing collection under %s\r\n", str);

	CString tmp; 
	tmp.Format("This will clear all items for '%s'. Are you sure?",
			str);
		
	int ret = AfxMessageBox(tmp, MB_YESNO);

	if(ret != IDYES)
		return;

	WFL_ClearTraining(str);	
	
	// Fill in collections box
	m_coll.ResetContent();
	char collstr[64]; int idx3 = 0, ret3 = 0;
	while(true)
		{
		ret3 = WFL_GetCollName(idx3++, collstr, sizeof(collstr));

		if(ret3 < 0)
			break;

		m_coll.AddString(collstr);
		}
#endif
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnButton30() 

{
	CPhonames dlg; dlg.DoModal();
}

//////////////////////////////////////////////////////////////////////////
// Set up system tray icon

void CWavfragDlg::LoadTray()

{

#if 1
	memset(&nid, 0, sizeof(nid));
	nid.cbSize	= sizeof(NOTIFYICONDATA);
	nid.hWnd	= m_hWnd;
	nid.uID		= 0x1111; 
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//nid.uCallbackMessage = RegisterWindowMessage("NotifyIcon");
	nid.uCallbackMessage = WM_WF_NOTIFYICON;
	strcpy(nid.szTip, "WavFrag Voice Recognition");	
	Shell_NotifyIcon(NIM_ADD,  &nid);
#endif
	
	memset(&nid2, 0, sizeof(nid2));
	nid2.cbSize	= sizeof(NOTIFYICONDATA2);
	nid2.hWnd	= m_hWnd;
	nid2.uID	= 0x1111; 

	//nid2.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	//nid2.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//nid2.uCallbackMessage = WM_WF_NOTIFYICON;
	//strcpy(nid2.szTip, "WavFrag Voice Recognition");
	//Shell_NotifyIcon(NIM_ADD, (NOTIFYICONDATA*)&nid2);

	nid2.uVersion = NOTIFYICON_VERSION;
	int retsh = Shell_NotifyIcon(NIM_SETVERSION, (NOTIFYICONDATA*)&nid2);
	ASSERT(retsh);

	// Set up balloon
	nid2.uFlags = NIF_INFO;
	nid2.cbSize	= sizeof(NOTIFYICONDATA2);
	nid2.uTimeout = 2000;
	nid2.dwInfoFlags = NIIF_INFO;
	strcpy(nid2.szInfo, "Welcome to wavefrag.");
	strcpy(nid2.szInfoTitle, "WavFrag Recognition");
	
	//if(m_balloon.GetCheck())
	//	Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA*)&nid2);

}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::LoadData()

{
	Busy(true);

	//WFL_SetNoPrompt(true);

	m_pick.SetText("Parsing Frags ..."); support.YieldToWinEx();
	
	CString wavdir(appdata); wavdir += "waves\\";  
	support.SoftMkdir(wavdir);
	WFL_SetWavDir(wavdir);

	CString fragdir(appdata);  fragdir += "frags\\";
	support.SoftMkdir(fragdir);
	WFL_SetFragDir(fragdir);

	int ret = WFL_ParseAllFragWaves();
	char str[128]; WFL_GetWavDir(str, sizeof(str));
	//AP2N("Parsed %d waves in %s\r\n", ret, str);

	m_log2.printf("Parsed %d waves in %s\r\n", ret, str);

	m_pick.SetText("Loading Frags ..."); support.YieldToWinEx();

	// Disable callback for now
	//WFL_SetSpectCallback(NULL);

	CString fragfile(appdata);  fragfile += "fragfile.frg";
	int ret2 = WFL_LoadAllFrags(fragfile);

	char str2[128]; WFL_GetFragDir(str2, sizeof(str2));

	//AP2N("Loaded %d frags in %s\r\n", ret2, str2);

	m_log2.printf("Loaded %d frags in %s\r\n", ret2, str2);

#if 0
		// Dump frags
		int idxf = 0; char str3[128];
		while(true)
			{
			int ret = WFL_GetFragName(idxf, str3, sizeof(str3));
			
			if(ret < 0)
				break;

			int sss = WFL_GetFragSize(idxf);
			AP2N("Frag %s %d units\r\n", str3, sss);

			idxf++;	// Scan next
			}
#endif

	usertab.InitCombos();
	fragtab.InitCombos();
	
	// Restore callbacks
	WFL_SetSpectCallback(_staticSpectFromRec);

	//Busy(false);
					
	//////////////////////////////////////////////////////////////////////
	// Load collections
		
	m_pick.SetText("Loading Frag collections ..."); support.YieldToWinEx();

	CString collfile(appdata); collfile += "coll.txt";
	//WFL_SetCollFile(collfile);

	//AP2N("Collection file %s\r\n", collfile);

	//Busy(true);
	WFL_LoadStrColl(collfile);
	fragcolltab.LoadData();	
	Busy(false);
	
	//////////////////////////////////////////////////////////////////
	// Load commands

#if 0
	m_pick.SetText("Loading Commands ..."); support.YieldToWinEx();

	CString comfile(appdata);  comfile += "wavfrag.wfc";
	comcoll.LoadComms(comfile);

	// Fill up command listbox
	int idx = 0;
	while(true)
		{
		CCommand *com = (CCommand*)comcoll.GetComm(idx++);
		
		if(!com)
			break;

		//AP2N("adding %s\r\n", *com->name);

		m_com.AddString(*com->name);
		}
#endif


#if 0

	//////////////////////////////////////////////////////////////////
	// Fill up words strings

	int idx2 = 0;
	CString str11, str22;
	char *strx3  = str11.GetBufferSetLength(1000);
	char *strx2 = str22.GetBufferSetLength(5000);

	while(true)
		{	
		int	retn = WFL_GetDicName(idx2, strx3, str11.GetLength());
		if(retn < 0) 
			break;
		int	retn2 = WFL_GetDicStrx(idx2, strx2, str22.GetLength());
		if(retn2 < 0) 
			break;

		idx2++;

		//AP2N("WFL_GetDicName: '%s' (%d) %s\r\n", strx3, strlen(strx2), strx2);

		if(m_words.FindString(0, strx3) == CB_ERR)
			m_words.AddString(strx3);
		}	

	str11.ReleaseBuffer(); str22.ReleaseBuffer();

#endif

	m_pick.SetText("Idle");

	stablized = true;

	CString strhist(appdata);  strhist += "history\\";

	if(!support.IsDir(strhist))
		mkdir(strhist);

	// Start recording
	if(m_arm.GetCheck())
		OnButton1();

	//int *ptr = NULL; *ptr = 0;


	// Change to num dir
	CString strdir2 = appdir;
	strdir2 += "\\num";
	
	//AP2N("strdir2=%s\r\n", strdir2);

	_chdir(strdir2);	
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::OnSelchangeList3() 

{
#if 0
	int idx = m_coll.GetCurSel();
	if(idx < 0)
		{
		return;
		}

	Busy(true);

	CString str; m_coll.GetText(idx, str);

	CString str2; str2.Format("Train as '%s'", str);
	//m_tb2.SetWindowText(str2);

	CString str3; str3.Format(
		"Will train the currently selected word with the recording\r\n"
			"that is displayed in the wave editor.\r\n\r\n"
			"Word that will be trained: '%s'", str);

	//m_tb2.SetTooltip(str3);
	
	m_words.ResetContent();

	//m_words.ShowScrollBar(SB_BOTH);

	// Fill in combo
	char collstr[512]; int idx3 = 0, ret3 = 0;
	while(true)
		{
		int ret3 = WFL_GetCollStr(idx, idx3++, collstr, sizeof(collstr));

		if(ret3 < 0)
			break;
				
		if(ret3 > sizeof(collstr))
			{
			AP2N("WFL_GetCollName needs bigger buffer %d\r\n", ret3);
			}

		//AP2N("collstr='%s'\r\n", collstr);

		m_words.AddString(collstr);
		}

	Busy(false);

	AP2N("CWavfragDlg::OnSelchangeList3 %s\r\n", str);	
#endif

}

void CWavfragDlg::OnSelchangingTab2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = m_tab2.GetCurSel();

	TC_ITEM tc;

	tc.mask = TCIF_PARAM;
	m_tab2.GetItem(sel, &tc);
			
	//AP2N("Change tab2 leave %x %d\r\n", tc.lParam, sel);

	CDialog *m_dia = (CDialog	*) tc.lParam;

	m_dia->ShowWindow(SW_HIDE);		
	*pResult = 0;	
	*pResult = 0;
}

void CWavfragDlg::OnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult) 

{
	int sel = m_tab2.GetCurSel();

	TC_ITEM tc;

	tc.mask = TCIF_PARAM;
	m_tab2.GetItem(sel, &tc);
			
	//AP2N("Change tab2 enter %x %d\r\n", tc.lParam, sel);

	CDialog *m_dia = (CDialog	*) tc.lParam;

	//m_dia->DoModal();
	//m_dia->SetWindowPos(&wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
	m_dia->ShowWindow(SW_SHOW);
	//m_dia->SetFocus();	
	//m_edit->Invalidate();
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////

void CWavfragDlg::ChangeTab(int newtab)

{
	NMHDR dummy; LRESULT dummyres;
	
	OnSelchangingTab1(&dummy, &dummyres);
	m_tab.SetCurSel(newtab);
	OnSelchangeTab1(&dummy, &dummyres);

	m_tab.Invalidate();
}
