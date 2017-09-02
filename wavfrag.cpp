
/* =====[ wavfrag.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the wavfrag.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/20/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */


#include "stdafx.h"
#include "direct.h"

#include "wavfrag.h"
#include "mxpad.h"
#include "wavfragDlg.h"
#include "FreqScan.h"
#include "Reso.h"
#include "MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global processing objects

CComColl	comcoll;
CString		appname, appdir, appdata;
	
//CBend		bend;
//CFreqScan	fscan;
//CReso		reso;
//CFftBuff	fftbuff;
//CRecog	recog;

/////////////////////////////////////////////////////////////////////////////
// CWavfragApp

BEGIN_MESSAGE_MAP(CWavfragApp, CWinApp)
	//{{AFX_MSG_MAP(CWavfragApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavfragApp construction

CWavfragApp::CWavfragApp()

{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWavfragApp object

CWavfragApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CWavfragApp initialization

BOOL CWavfragApp::InitInstance()
{
	if (!AfxSocketInit())
		{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
		}

	//AfxMessageBox(m_pszRegistryKey);

	SetRegistryKey(_T("RobotMonkeySoftware"));

#ifdef _DEBUG
	mxpad.SetRemote(true);
	mxpad.SetLocal(false);
	C2N;
#endif

	OSVERSIONINFO ver; ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);

	CTime ct = CTime::GetCurrentTime();
	CString datestr2 = ct.Format("%A, %B %d, %Y - %I:%M %p");
	
	P2N("Application '%s' started on Win %d.%d (%s) on %s\r\n\r\n", 
				AfxGetAppName(),
					ver.dwMajorVersion, ver.dwMinorVersion, ver.szCSDVersion, datestr2);

	char *tmp = appname.GetBuffer(MAX_PATH + 1); ASSERT(tmp);	
	GetModuleFileName(AfxGetInstanceHandle(), tmp, MAX_PATH);
	appname.ReleaseBuffer();

	appdir = appname;
	int idx2 = appdir.ReverseFind('\\'); appdir = appdir.Left(idx2 + 1);
	if(appdir.Find("Debug") >= 0 || appdir.Find("Release") >= 0)
		{
		int idx3 = appdir.ReverseFind('\\'); appdir = appdir.Left(idx3 );
		int idx4 = appdir.ReverseFind('\\'); appdir = appdir.Left(idx4 + 1);

		//P2N("Applied build hack %s \r\n", appdir);
		appdata = appdir;
		}
	else
		{
		support.GetProgDataDir(appdata);
		support.RepairPath(appdata);
		appdata += "WavFrag\\";
		}
	
	if(!support.IsDir(appdata))
		{
		AP2N("creating appdata = %s\r\n", appdata);
		mkdir(appdata);
		if(!support.IsDir(appdata))
			{
			::MessageBox(NULL, "Cannot create application data dir", "", MB_OK);
			appdata = appdir;
			}
		}
	
	//::MessageBox(NULL, appdata, "", MB_OK);
	
	P2N("appname    = %s\r\n", appname);
	P2N("appdir     = %s\r\n", appdir);
	P2N("appdata    = %s\r\n", appdata);

//	try
//		{	
//		AP2N("Null Pointer test started\r\n"); 
//		int bb = 0, *ptr = NULL; 		
//		//*ptr = 0;	ptr = 100 / bb;
//		AP2N("Null Pointer test - not executed %d\r\n", ptr); 		
//		}
//	catch(...)
//		{
//		AP2N("Null pointer exception\r\n");
//		}
//	AP2N("Null Pointer test ended.\r\n"); 


	AP2N("Using wavefrag DLL version %d.%d\r\n", WFL_Version() / 100, WFL_Version() % 100);

	//char str[_MAX_PATH];  getcwd(str, sizeof(str));
	//P2N("Started in directory '%s'\r\n", str);

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	int retry = 0;
	while(true)
		{
		CWavfragDlg *dlg = NULL; 
		
		//try
			{	
			retry = 0;
			dlg = new CWavfragDlg;
			m_pMainWnd = dlg;

			int nResponse = dlg->DoModal();
				
			if (nResponse == IDOK)
				{
				// TODO: Place code here to handle when the dialog is
				//  dismissed with OK
				}
			else if (nResponse == IDCANCEL)
				{
				// TODO: Place code here to handle when the dialog is
				//  dismissed with Cancel
				}
			}

		//catch(...)
		//	{
		//	AP2N("Caught exception in dialog\r\n");
		//	//retry = AfxMessageBox("Caught exception, do you want to restart the application?", MB_YESNO);
		//	AfxMessageBox("Caught exception", MB_OK);
		//	}
		
//		if(retry != IDYES)
//			{
//			if(dlg)
//				delete dlg;
//			break;
//			}
		//::MessageBox(NULL, "retry", "hello", MB_OK);

		if(dlg)
			delete dlg;

		break;
		}


	//TRACE("After CWavfragDlg exit\r\n");

	// Stop playing 
	//dlg.playsound.StopPlay();
	//dlg.playsound.WaveClose();
	//support.YieldToWinEx();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

void CWavfragApp::OnHelp( )

{
	//AP2N("CWavfragApp::Onhelp\r\n");

	WinHelp(0);
}

//////////////////////////////////////////////////////////////////////////

int CWavfragApp::ExitInstance() 

{
	//P2N("CWavfragApp::ExitInstance regkey=%s\r\n", m_pszRegistryKey);
	return CWinApp::ExitInstance();
}

//////////////////////////////////////////////////////////////////////////

void CWavfragApp::WinHelp(DWORD dwData, UINT nCmd) 

{
	//AP2N("CWavfragApp::WinHelp %d\r\n", dwData);

	CString helpfile(appdir);
	helpfile += "html\\";	helpfile += "index.html";

	//AP2N("CWavfragApp::WinHelp %s\r\n", helpfile);

	ShellExecute(NULL, "open", helpfile, NULL, NULL, SW_SHOWNORMAL);	

	//CWinApp::WinHelp(dwData, nCmd);
}

//////////////////////////////////////////////////////////////////////////

int CWavfragApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt) 

{	
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

//	if(nType & MB_YESNO)
//		{
//		nType |= MB_ICONQUESTION ;
//		}

	//nType |= MB_ICONINFORMATION;
	//return ::MessageBox(AfxGetMainWnd()->m_hWnd, lpszPrompt, "Wave Frag Voice Recognition", nType);

	//AP2N("CWavfragApp::DoMessageBox\r\n");

	pwnd->modalcontext = true;
	//int ret = CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
	int ret = xMsgBox(lpszPrompt, "Wavefrag MessageBox", nType, IDNO);
	pwnd->modalcontext = false;
	
	//AP2N("xMsgBox ret=%d (idyes=%d)\r\n", ret, IDYES);

	return ret;
}


//////////////////////////////////////////////////////////////////////////
// Pop up a message box pertaining into the last current window

int		xMsgBox(const char *str, const char *title, int yesno, int defa) 

{
	//CWnd *dlg = AfxGetApp()->m_pMainWnd;	
	//CWnd *oldw = dlg->FromHandle(GetForegroundWindow());

	//AP2N("Forground window %p %p\r\n", GetForegroundWindow(), oldw);
	
	//CMsgBox mb(CWnd::GetDesktopWindow());

	CMsgBox mb(AfxGetApp()->m_pMainWnd);

	if(title == NULL || *title == '\0')
		mb.m_header = "Wavefrag MessageBox";
	else
		mb.m_header = title;

	mb.m_text = str;
	mb.yesno = yesno;
	mb.idret = defa;

	return mb.DoModal();
}
