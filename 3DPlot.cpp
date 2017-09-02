// 3DPlot.cpp : implementation file
//

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "mxpad.h"
#include "3DPlot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DPlot

C3DPlot::C3DPlot()
{
}

C3DPlot::~C3DPlot()
{
	int alen = xarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		delete (CIntArr*) xarr[loop];
		}	
}


BEGIN_MESSAGE_MAP(C3DPlot, CStatic)
	//{{AFX_MSG_MAP(C3DPlot)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DPlot message handlers

void C3DPlot::OnPaint() 

{
	CPaintDC dc(this); // device context for painting
	
	int ss = dc.SaveDC();

	RECT rc; GetClientRect(&rc);
	int ww = rc.right - rc.left - 2; int hh = rc.bottom - rc.top - 2;

	//dc.SetBkColor(RGB(220, 220, 220));	dc.SetTextColor(RGB(120, 120, 120));

	int start = 0, alen = xarr.GetSize();

	if(alen == 0)
		{
		CString str; str.Format("3DPlot");
		dc.TextOut(2, 2, str);
		}

	if(alen > ww / 6)
		{
		start = alen - ww / 6;
		//AP2N("C3DPlot::OnPaint start=%d\r\n", start);
		}

	CPen pen; pen.CreatePen(PS_SOLID, 1, RGB(100,100,100));

	dc.SelectStockObject(BLACK_PEN); dc.SelectStockObject(GRAY_BRUSH);

	//dc.SelectStockObject(BLACK_BRUSH);
	//dc.SelectStockObject(DKGRAY_BRUSH);
	//dc.SelectStockObject(WHITE_BRUSH);

	//CPen *old = (CPen*)dc.SelectObject(pen);

	int cnt = 0, skip = 4, steep = 1;
	for(int loop = start; loop < alen; loop += 1)
		{
		CIntArr	*tmp = (CIntArr*) xarr[loop];
		int blen = tmp->GetSize();

		//pen.DeleteObject();
		//pen.CreatePen(PS_SOLID, 1, RGB(loop,0,0));
		//dc.SelectObject(pen);
	
		int xxx = cnt * skip;	// Starting point

		// Draw base line
		//CPen *old = (CPen*)dc.SelectObject(pen);
		
		dc.BeginPath();

		//dc.SelectStockObject(BLACK_PEN);
		//dc.SelectObject(pen);

		dc.MoveTo(xxx, hh);
		dc.LineTo(xxx + blen, hh - blen * steep);
		dc.MoveTo(xxx, hh);

		for(int loop2 = 0; loop2 < blen; loop2 += 1)
			{
			int val = tmp->GetAt(loop2);
			int val2 = val / 10 + loop2 * steep;

			int val3 = hh - val2;			// Adjust for reversed Y
		
			//if(val)
				dc.LineTo(xxx + loop2, val3);
			//else
			//	dc.MoveTo(xxx + loop2, val3);
			}

		//dc.SelectStockObject(WHITE_PEN );
		dc.LineTo(cnt * skip + loop2, hh - loop2 * steep);
		dc.EndPath();
		
		//dc.FloodFill(cnt * skip + 1, hh - 6, RGB(0,0,0));
		//dc.StrokePath();
		//dc.FillPath();

		//COLORREF col = (3 * cnt  % 100) + 120;
		//CBrush br;	br.CreateSolidBrush(RGB(col,col, col));
		//dc.SelectObject(br);

		dc.StrokeAndFillPath();
		
		//Sleep(200);

		cnt++;
 		}

	dc.RestoreDC(ss);

	// Do not call CStatic::OnPaint() for painting messages
}

void C3DPlot::PreSubclassWindow() 

{
	ModifyStyle(0, WS_CLIPCHILDREN);
	ModifyStyleEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 0);
	CStatic::PreSubclassWindow();
}

//////////////////////////////////////////////////////////////////////////

BOOL C3DPlot::OnEraseBkgnd(CDC* pDC) 

{
	//AP2N("C3DPlot::OnEraseBkgnd\r\n");

	// TODO: Add your message handler code here and/or call default
	RECT rc; GetClientRect(&rc);

	pDC->FillSolidRect(&rc, RGB(255,255,255));

	//pDC->FillSolidRect(&rc, RGB(220,220,220));
	//pDC->Draw3dRect(&rc, RGB(200,200,200), RGB(100,100,100));

	//return CStatic::OnEraseBkgnd(pDC);

	return 1;
}

//////////////////////////////////////////////////////////////////////////

void C3DPlot::AddIntArr(CIntArr *iarr)

{
	CIntArr	*tmp = new CIntArr; ASSERT(tmp);
	tmp->Copy(*iarr);
	xarr.Add(tmp);

	//SetTimer(1, 200, NULL);
	Invalidate();
}

void C3DPlot::AddIntArr(int *ptr, int len)

{
	CIntArr	*tmp = new CIntArr; ASSERT(tmp);

	tmp->SetSize(len);
	memcpy(tmp->GetData(), ptr, len * sizeof(int));

	xarr.Add(tmp);

	//SetTimer(1, 200, NULL);
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void C3DPlot::Clear()

{
	int alen = xarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		delete (CIntArr*) xarr[loop];
		}

	xarr.RemoveAll();
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void C3DPlot::AddMarker()

{
	for(int loop2 = 0; loop2 < 3; loop2++)
		{
		CIntArr	*tmp = new CIntArr; ASSERT(tmp);
		for(int loop = 0; loop < 200; loop++)
			tmp->Add(0);
		xarr.Add(tmp);
		}

}

void C3DPlot::TrimLong()

{
	int alen = xarr.GetSize();

	if(alen > 1000)
		{		
		for(int loop = 1; loop < 100;  loop++)
			{
			delete (CIntArr*) xarr[alen - loop];
			}		
		xarr.RemoveAt(alen - 100, 99);			
		}
}
