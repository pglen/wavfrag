// CPlotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wavfrag.h"
#include "PlotDlg.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlotDlg dialog


CPlotDlg::CPlotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlotDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlotDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_arr[0] = &m_plot1;
	m_arr[1] = &m_plot2;
	m_arr[2] = &m_plot3;
	m_arr[3] = &m_plot4;
	m_arr[4] = &m_plot5;
	m_arr[5] = &m_plot6;
}


void CPlotDlg::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PLOT6, m_plot6);
	DDX_Control(pDX, IDC_PLOT5, m_plot5);
	DDX_Control(pDX, IDC_PLOT4, m_plot4);
	DDX_Control(pDX, IDC_PLOT3, m_plot3);
	DDX_Control(pDX, IDC_PLOT2, m_plot2);
	DDX_Control(pDX, IDC_PLOT1, m_plot1);

	//DDX_Control(pDX, IDC_PLOT7, m_vis);

	//{{AFX_DATA_MAP(CPlotDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlotDlg, CDialog)
	//{{AFX_MSG_MAP(CPlotDlg)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotDlg message handlers

void CPlotDlg::OnDestroy() 
{
	P2N("CPlotDlg::OnDestroy\r\n");
	CDialog::OnDestroy();
}

void CPlotDlg::PostNcDestroy() 

{
	P2N("CPlotDlg::PostNcDestroy\r\n");
	CDialog::PostNcDestroy();
}

BOOL CPlotDlg::DestroyWindow() 

{
	//AfxMessageBox("CPlotDlg::DestroyWindow");

	P2N("CPlotDlg::DestroyWindow\r\n");	
	return CDialog::DestroyWindow();
}

void CPlotDlg::OnClose() 

{
	P2N("CPlotDlg::OnClose\r\n");	

	CString section = "windowpos";

	WINDOWPLACEMENT wp2;
	GetWindowPlacement(&wp2);

	int hh2  = wp2.rcNormalPosition.bottom - wp2.rcNormalPosition.top;	
	int ww2  = wp2.rcNormalPosition.right - wp2.rcNormalPosition.left;

	CString tmp; tmp.Format("%d %d %d %d",
		wp2.rcNormalPosition.top, wp2.rcNormalPosition.left,
				wp2.rcNormalPosition.bottom,  wp2.rcNormalPosition.right);	


	CString entity; entity.Format("DlgPos%d", 2);
	
	//P2N("PersistDlg::SavePos  IDD=%d Pos= '%s'\r\n", xidd, tmp);
	
	AfxGetApp()->WriteProfileString(section, entity, tmp);

	CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////

BOOL CPlotDlg::OnInitDialog() 

{
	CDialog::OnInitDialog();

	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1)), true);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1)), false);

	// Restore old placement, if any
	WINDOWPLACEMENT wp2;

	CString section = "windowpos";
	CString entity; entity.Format("DlgPos%d", 2);

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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CPlotDlg::PreSubclassWindow() 

{
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);

	CDialog::PreSubclassWindow();
}
