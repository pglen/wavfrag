
/* =====[ 3DDlg.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the 3DDlg.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  5/14/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "3DDlg.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DDlg dialog

C3DDlg::C3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	ygap = xgap = 8;
}

void C3DDlg::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DDlg)
	DDX_Control(pDX, IDC_VIS, m_3d);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(C3DDlg, CDialog)
	//{{AFX_MSG_MAP(C3DDlg)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DDlg message handlers

void C3DDlg::OnClose() 

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
	
	//P2N("C3DDlg::SavePos  IDD=%d Pos= '%s'\r\n", xidd, tmp);
	
	AfxGetApp()->WriteProfileString(section, entity, tmp);	
	CDialog::OnClose();
}

BOOL C3DDlg::OnInitDialog() 
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
		//P2N("C3DDlg::LoadPos IDD=%d pos='%s' name='%s'\r\n", xidd, str2, windowname);

		sscanf(str2, "%d %d %d %d",
			&wp2.rcNormalPosition.top, &wp2.rcNormalPosition.left,
				&wp2.rcNormalPosition.bottom,  &wp2.rcNormalPosition.right);

		// Save old positions as pre_wants
		int want_x = wp2.rcNormalPosition.left;
		int want_y = wp2.rcNormalPosition.top;
		int want_w = wp2.rcNormalPosition.right  - wp2.rcNormalPosition.left;
		int want_h = wp2.rcNormalPosition.bottom - wp2.rcNormalPosition.top;
		
		int flag =  SWP_NOZORDER; // | SWP_NOSIZE;

		SetWindowPos(NULL, want_x, want_y, want_w, want_h,  flag);
		}		

	
	RECT rc3; GetClientRect(&rc3);
	int hh3  = rc3.bottom - rc3.top;	
	int ww3  = rc3.right - rc3.left;

	WINDOWPLACEMENT wp4; m_3d.GetWindowPlacement(&wp4);
	int hh4  = wp4.rcNormalPosition.bottom - wp4.rcNormalPosition.top;	
	int ww4  = wp4.rcNormalPosition.right - wp4.rcNormalPosition.left;

	xgap = ww3 - ww4;
	ygap = hh3 - hh4;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void C3DDlg::OnSize(UINT nType, int cx, int cy) 

{
	CDialog::OnSize(nType, cx, cy);
	
	if(IsWindow(m_hWnd) && IsWindow(m_3d.m_hWnd))
		{
		m_3d.SetWindowPos(NULL, 0, 0, cx - xgap, cy - ygap, SWP_NOMOVE | SWP_NOZORDER);
		Invalidate();
		}

	//AP2N("	 C3DDlg::OnSize %d %d\r\n", cx, cy);
}
