// 4DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "mxpad.h"

#include "4DDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C4DDlg dialog


C4DDlg::C4DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C4DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C4DDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void C4DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C4DDlg)
	DDX_Control(pDX, IDC_4D, m_4d);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C4DDlg, CDialog)
	//{{AFX_MSG_MAP(C4DDlg)
	ON_WM_CLOSE()
	ON_WM_MOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C4DDlg message handlers

void C4DDlg::OnClose() 
{
	CString section = "windowpos";

	WINDOWPLACEMENT wp2;
	GetWindowPlacement(&wp2);

	int hh2  = wp2.rcNormalPosition.bottom - wp2.rcNormalPosition.top;	
	int ww2  = wp2.rcNormalPosition.right - wp2.rcNormalPosition.left;

	CString tmp; tmp.Format("%d %d %d %d",
		wp2.rcNormalPosition.top, wp2.rcNormalPosition.left,
				wp2.rcNormalPosition.bottom,  wp2.rcNormalPosition.right);	

	CString entity; entity.Format("DlgPos%d", 5);
	
	//P2N("C4DDlg::SavePos  IDD=%d Pos= '%s'\r\n", xidd, tmp);
	
	AfxGetApp()->WriteProfileString(section, entity, tmp);		
	CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////

BOOL C4DDlg::OnInitDialog() 

{
	CDialog::OnInitDialog();
	
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), true);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), false);

	// Restore old placement, if any
	WINDOWPLACEMENT wp2;

	CString section = "windowpos";
	CString entity; entity.Format("DlgPos%d", 5);

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
	
	SizeControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void C4DDlg::SizeControls()

{
	if(IsWindow(m_4d.m_hWnd))
		{
		RECT rc;	GetClientRect(&rc);
		m_4d.SetWindowPos(NULL, 0, 0, rc.right - 6, rc.bottom - 6, 
							SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
					
		}
}

//////////////////////////////////////////////////////////////////////////

void C4DDlg::OnMove(int x, int y) 

{
	CDialog::OnMove(x, y);
}

void C4DDlg::OnSize(UINT nType, int cx, int cy) 

{
	CDialog::OnSize(nType, cx, cy);
	
	SizeControls();
}
