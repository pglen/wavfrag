
/* =====[ LightBoxDlg.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the LightBoxDlg.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/30/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "LightBoxDlg.h"
#include "xraym.h"
#include "xrect.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightBoxDlg dialog

CLightBoxDlg::CLightBoxDlg(CWnd* pParent /*=NULL*/)
	: CGrayDlg(CLightBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//ini_message	= false;
	ini_message	= true;					// no need
	
	bgcolor = GetSysColor(COLOR_3DFACE);
}

void CLightBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CGrayDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightBoxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLightBoxDlg, CGrayDlg)
	//{{AFX_MSG_MAP(CLightBoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()

	ON_COMMAND(ID_RCLICK_WHITE, WhiteScreen)
	ON_COMMAND(ID_RCLICK_GRAY, GrayScreen)
	ON_COMMAND(ID_RCLICK_DARKGRAY, DarkGrayScreen)
	ON_COMMAND(ID_RCLICK_WINDOWSDEFAULT, DefaultScreen)
	ON_COMMAND(ID_RCLICK_CUSTOM, CustomScreen)
	ON_COMMAND(ID_RCLICK_BLACK, BlackScreen)
	ON_COMMAND(ID_RCLICK_EXIT, ExitHere)

	
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void	CLightBoxDlg::ExitHere()

{
	EndDialog(IDOK);
}


void	CLightBoxDlg::BlackScreen()

{
	bgcolor = RGB(0, 0, 0);
	Invalidate();
}


void	CLightBoxDlg::CustomScreen()

{
	CColorDialog cd;

	cd.m_cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR | CC_ENABLEHOOK;
	cd.m_cc.rgbResult = bgcolor;

	//cd.m_cc.lpCustColors = custom;

	if(cd.DoModal() == IDOK)
		{
		bgcolor  = cd.m_cc.rgbResult;
		Invalidate();
		}		
}

void	CLightBoxDlg::DefaultScreen()

{
	bgcolor = GetSysColor(COLOR_3DFACE);
	Invalidate();
}

void	CLightBoxDlg::DarkGrayScreen()

{
	bgcolor = RGB(64, 64, 64);
	Invalidate();
}

void	CLightBoxDlg::GrayScreen()

{
	bgcolor = RGB(128, 128, 128);
	Invalidate();
}

void	CLightBoxDlg::WhiteScreen()

{
	//P2N("White Screen\r\n");
	bgcolor = RGB(255, 255, 255);
	Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CLightBoxDlg message handlers

BOOL CLightBoxDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	HDC     hdc = ::GetDC(HWND_DESKTOP);
    int     xsize =  GetDeviceCaps(hdc, HORZRES);
    int     ysize =  GetDeviceCaps(hdc, VERTRES);
	SetWindowPos( NULL, 0, 0, xsize, ysize, SWP_NOZORDER);

	LOGFONT m_lf;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf), &m_lf);
	m_lf.lfHeight = 36;

	m_font.CreateFontIndirect(&m_lf);

	SetTimer(0, 3000, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLightBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CGrayDlg::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLightBoxDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting
		
		if(!ini_message)
			{
			CRect rc; GetClientRect(rc);
			CFont* oldFont = dc.SelectObject(&m_font);

			CxRect rct, rcd;

			CString str = "Press escape to exit LightBox, right click for Color options";
			
			dc.SetBkColor(GetSysColor(COLOR_3DFACE));

			dc.DrawText(str, rct, DT_CALCRECT);

			rcd.left   = (rc.left + rc.Width() / 2) - rct.Width() / 2;
			rcd.top    = (rc.top + rc.Height() / 2) - rct.Height() / 2;
			rcd.right  = rcd.left + rct.Width();
			rcd.bottom = rcd.top + rct.Height();

			dc.DrawText(str, rcd, 0);

			dc.SelectObject(oldFont);
			}

		CGrayDlg::OnPaint();
		}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLightBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLightBoxDlg::OnRButtonDown(UINT nFlags, CPoint point) 

{
	CXrayM   *mm = new CXrayM(IDD_DIALOG1, this);
	mm->LoadAndShow(IDR_MENU1, 1);	

	CGrayDlg::OnRButtonDown(nFlags, point);
}

void CLightBoxDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 

{
	EndDialog(IDOK);		
	CGrayDlg::OnLButtonDblClk(nFlags, point);
}

BOOL CLightBoxDlg::OnEraseBkgnd(CDC* pDC) 

{
	RECT rect; GetClientRect(&rect);

	CBrush NewBrush;
	//NewBrush.CreateSolidBrush(RGB(0xff, 0xff, 0x80)) ;
	NewBrush.CreateSolidBrush(bgcolor) ;

	pDC->SetBrushOrg(0,0) ;
	CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&NewBrush);
	pDC->PatBlt(rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, PATCOPY);
	pDC->SelectObject(pOldBrush);
	
	return(false);

	//return CGrayDlg::OnEraseBkgnd(pDC);
}

void CLightBoxDlg::OnTimer(UINT nIDEvent) 
{
	ini_message	= true;
	Invalidate();
	CGrayDlg::OnTimer(nIDEvent);
}
