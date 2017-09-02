
/* =====[ VisDlg.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the VisDlg.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/4/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// VisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wavfrag.h"
#include "mxpad.h"
#include "VisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisDlg dialog


CVisDlg::CVisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_VIS,  m_vis);
	DDX_Control(pDX, IDC_PLOT, m_plot);

	//DDX_Control(pDX, IDC_VIS2, m_3d);
}

BEGIN_MESSAGE_MAP(CVisDlg, CDialog)
	//{{AFX_MSG_MAP(CVisDlg)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisDlg message handlers

BOOL CVisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), true);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), false);

	// Restore old placement, if any
	WINDOWPLACEMENT wp2;

	CString section = "windowpos";
	CString entity; entity.Format("DlgPos%d", 3);

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
		
		int flag =  SWP_NOZORDER ;

		SetWindowPos(NULL, want_x, want_y, want_w, want_h,  flag);
		}	

	//CRect rc; GetWindowRect(&rc);	
	//OnSize(SIZE_RESTORED, rc.Width(), rc.Height());

	SizeControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CVisDlg::OnClose() 

{
	//P2N("PlotDlg::OnClose\r\n");	

	CString section = "windowpos";

	WINDOWPLACEMENT wp2;
	GetWindowPlacement(&wp2);

	int hh2  = wp2.rcNormalPosition.bottom - wp2.rcNormalPosition.top;	
	int ww2  = wp2.rcNormalPosition.right - wp2.rcNormalPosition.left;

	CString tmp; tmp.Format("%d %d %d %d",
		wp2.rcNormalPosition.top, wp2.rcNormalPosition.left,
				wp2.rcNormalPosition.bottom,  wp2.rcNormalPosition.right);	

	CString entity; entity.Format("DlgPos%d", 3);
	
	//P2N("PersistDlg::SavePos  IDD=%d Pos= '%s'\r\n", xidd, tmp);
	
	AfxGetApp()->WriteProfileString(section, entity, tmp);

	
	CDialog::OnClose();
}

//DEL void CVisDlg::PreSubclassWindow() 
//DEL 
//DEL {	
//DEL 	CDialog::PreSubclassWindow();
//DEL }

//////////////////////////////////////////////////////////////////////////

void CVisDlg::OnSize(UINT nType, int cx, int cy) 

{
	CDialog::OnSize(nType, cx, cy);	
	SizeControls();
}

//////////////////////////////////////////////////////////////////////////

void CVisDlg::OnMove(int x, int y) 

{
	CDialog::OnMove(x, y);
	
	if(IsWindow(m_vis.m_hWnd))
		{
		//m_vis.Invalidate();
		m_vis.SoftInval();
		}
}

//////////////////////////////////////////////////////////////////////////

void CVisDlg::SizeControls()

{
	if(IsWindow(m_vis.m_hWnd))
		{
		RECT rc;	GetClientRect(&rc);
		m_vis.SetWindowPos(NULL, 0, 0, rc.right - 4, rc.bottom - 4, 
							SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
			
		if(IsWindow(m_plot.m_hWnd))
			{
			//m_plot.GetWindowPos(
			m_plot.SetWindowPos(NULL, 0, 0, rc.right - 4, 100, 
							SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);

			}
		}
}

//////////////////////////////////////////////////////////////////////////

void CVisDlg::OnLButtonDown(UINT nFlags, CPoint point) 

{
	//AP2N("CVisDlg::OnLButtonDown\r\n");
	//SetFocus();
	CDialog::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////

BOOL CVisDlg::PreTranslateMessage(MSG* pMsg) 

{
	if(pMsg->message == WM_USER)
		{
		//AP2N("CVisDlg::PreTranslateMessage click=%d ptr=%p\r\n", 
		//	pMsg->wParam, pMsg->lParam);

		double mag = m_plot.GetMag();

		//AP2N("mag=%f\r\n", mag);
		m_plot.ClearAll();

		CPtrArray *parr = (CPtrArray*)pMsg->lParam;
		if((int)pMsg->wParam < parr->GetSize())
			{
			CIntArr *tmp = (CIntArr*)parr->GetAt(pMsg->wParam);
			m_plot.AddIntArr(tmp);
			m_plot.SetMag(mag);
			}		
		}

	return CDialog::PreTranslateMessage(pMsg);
}
