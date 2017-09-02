// ShowPic.cpp : implementation file
//

#include "stdafx.h"
#include "wavfrag.h"
#include "ShowPic.h"

#include "mxpad.h"

#include "misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowPic dialog


CShowPic::CShowPic(CWnd* pParent /*=NULL*/)
	: CGrayDlg(CShowPic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowPic)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	gotpic = false;
	bgcolor = RGB(64, 64, 64);
	want_x = want_y = want_w = want_h = 0;
}

void CShowPic::DoDataExchange(CDataExchange* pDX)

{
	CGrayDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowPic)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowPic, CGrayDlg)
	//{{AFX_MSG_MAP(CShowPic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowPic message handlers

BOOL CShowPic::OnInitDialog() 

{
	CGrayDlg::OnInitDialog();
		
	HDC     hdc = ::GetDC(HWND_DESKTOP);
    int     xsize =  GetDeviceCaps(hdc, HORZRES);
    int     ysize =  GetDeviceCaps(hdc, VERTRES);
	SetWindowPos( NULL, 0, 0, xsize, ysize, SWP_NOZORDER);

	//LoadPic();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowPic::OnPaint() 

{
	CPaintDC dc(this); // device context for painting

	AP2N("want_x=%d, want_y=%d want_w=%d want_h=%d\r\n", 
							want_x, want_y, want_w, want_h);		

	if(gotpic)		
		pic.Draw(&dc, want_x, want_y, want_w, want_h);		
	else
		dc.TextOut(10, 10,"No picture, press ESC or say 'Close Image'");

	// Do not call CGrayDlg::OnPaint() for painting messages
}

//////////////////////////////////////////////////////////////////////////

void CShowPic::OnLButtonDown(UINT nFlags, CPoint point) 

{	
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));	
	CGrayDlg::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////

void CShowPic::OnLButtonDblClk(UINT nFlags, CPoint point) 

{
	EndDialog(IDOK);		
	CGrayDlg::OnLButtonDblClk(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////

void CShowPic::LoadPic()

{
	gotpic  = pic.Load(fname);

	if(gotpic)
		{
		//CWnd
		WINDOWPLACEMENT wp;	GetWindowPlacement(&wp);
		WINDOWPLACEMENT pwp; AfxGetMainWnd()->GetWindowPlacement(&pwp);

		POINT here; 
		here.x = pwp.rcNormalPosition.top; here.y = pwp.rcNormalPosition.left;

		P2N("here %d %d\r\n", here.x, here.y);

		CRect	rc3; misc.CurrentMonRect(here, &rc3);

		//P2N_RECT(rc3);

		CPaintDC dc(this);
		
		CSize ss = pic.GetSize(&dc);

		if(ss.cx > rc3.Width())
			{	
			ss.cy = ss.cy *  rc3.Width() / ss.cx;
			ss.cx = rc3.Width();
			}

		// Position it into the middle
		wp.rcNormalPosition.left = rc3.left + rc3.Width() / 2 - ss.cx / 2 ;
		wp.rcNormalPosition.top = rc3.top + rc3.Height() / 2 - ss.cy / 2 ;

		// Resize the Dialog to the image
		wp.rcNormalPosition.right = wp.rcNormalPosition.left + ss.cx;
		wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + ss.cy;

		want_x = wp.rcNormalPosition.left;
		want_y = wp.rcNormalPosition.top;
					
		want_w = wp.rcNormalPosition.right  - wp.rcNormalPosition.left;
		want_h = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top;
			
		//::MoveWindow(m_hWnd, want_x, want_y, want_w, want_h,  true); 
		// This did not work on multi screens
		//SetWindowPlacement(&wp);

		Invalidate();
		}
}

//////////////////////////////////////////////////////////////////////////

BOOL CShowPic::OnEraseBkgnd(CDC* pDC) 

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
