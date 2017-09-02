
/* =====[ WavDlg.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the WavDlg.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  12/18/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "WavDlg.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWavDlg dialog


CWavDlg::CWavDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWavDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWavDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavDlg)
	DDX_Control(pDX, IDC_WAV3, m_wav2);
	DDX_Control(pDX, IDC_WAV, m_wav);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWavDlg, CDialog)
	//{{AFX_MSG_MAP(CWavDlg)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavDlg message handlers

void CWavDlg::PreSubclassWindow() 

{
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);	
	CDialog::PreSubclassWindow();
}

void CWavDlg::OnClose() 
{
	CString section = "windowpos";

	WINDOWPLACEMENT wp2;
	GetWindowPlacement(&wp2);

	int hh2  = wp2.rcNormalPosition.bottom - wp2.rcNormalPosition.top;	
	int ww2  = wp2.rcNormalPosition.right - wp2.rcNormalPosition.left;

	CString tmp; tmp.Format("%d %d %d %d",
		wp2.rcNormalPosition.top, wp2.rcNormalPosition.left,
				wp2.rcNormalPosition.bottom,  wp2.rcNormalPosition.right);	


	CString entity; entity.Format("DlgPos%d", 4);
	
	//P2N("PersistDlg::SavePos  IDD=%d Pos= '%s'\r\n", xidd, tmp);
	
	AfxGetApp()->WriteProfileString(section, entity, tmp);
	
	CDialog::OnClose();
}

BOOL CWavDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), true);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), false);

	// Restore old placement, if any
	WINDOWPLACEMENT wp2;

	CString section = "windowpos";
	CString entity; entity.Format("DlgPos%d", 4);

	CString str2 = AfxGetApp()->GetProfileString(section, entity, "");
	
	if(str2 != "")
		{		
		//P2N("PersistDlg::LoadPos IDD=%d pos='%s' name='%s'\r\n", xidd, str2, windowname);

		sscanf(str2, "%d %d %d %d",
			&wp2.rcNormalPosition.top, &wp2.rcNormalPosition.left,
				&wp2.rcNormalPosition.bottom,  &wp2.rcNormalPosition.right);

		// Save old positions as pre_wants
		int want_x = wp2.rcNormalPosition.left;
		int want_y = wp2.rcNormalPosition.top;
		int want_w = wp2.rcNormalPosition.right  - wp2.rcNormalPosition.left;
		int want_h = wp2.rcNormalPosition.bottom - wp2.rcNormalPosition.top;
		
		int flag =  SWP_NOZORDER | SWP_NOSIZE;

		SetWindowPos(NULL, want_x, want_y, want_w, want_h,  flag);
		}		

	Sizeit();

	//RECT rc;	GetClientRect(&rc);
	//OnSize(SIZE_RESTORED, rc.right - rc.left, rc.top - rc.bottom);

	m_wav.pplaysnd = &playsound;
	m_wav2.pplaysnd = &playsound;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWavDlg::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->message == WM_USER + 2)
		{
		if(pMsg->wParam == (unsigned int)m_wav.m_hWnd)
			{
			AP2N("CWavDlg::PreTranslateMessage WM_USER 2 %d %d\r\n",
									pMsg->wParam, pMsg->lParam);

			//int  ssel = LOWORD(pMsg->lParam);
			//int  esel = HIWORD(pMsg->lParam);

			//AP2N("m_wav3 m_hwnd=%p %p ssel=%d esel=%d\r\n", 
			//				pMsg->wParam, m_wav.m_hWnd, ssel, esel);
		
			char *buff; int len;

			m_wav.GetSelBuff(&buff, &len);
			m_wav2.SetBuff(buff, len); 
			m_wav2.Norm(30);
			}	
		}

	return CDialog::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////

void CWavDlg::OnSize(UINT nType, int cx, int cy) 

{
	CDialog::OnSize(nType, cx, cy);
	//AP2N("CWavDlg::OnSize %d %d\r\n", cx, cy);
	Sizeit();
}


void CWavDlg::Sizeit()
{

	if(IsWindow(m_wav.m_hWnd))
		{
		RECT rc;	GetClientRect(&rc);

		int mid = rc.bottom / 2;

		m_wav.SetWindowPos(NULL, 8, 8, rc.right - 16, mid - 8, 
							SWP_NOOWNERZORDER | SWP_NOCOPYBITS);

		
		m_wav2.SetWindowPos(NULL, 8, mid + 8, rc.right - 16, mid - 8, 
							SWP_NOOWNERZORDER | SWP_NOCOPYBITS);

		}
}
