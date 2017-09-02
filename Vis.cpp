
/* =====[ Vis.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the Vis.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "Vis.h"
#include "support.h"
#include "misc.h"

#include "mxpad.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LRESULT CALLBACK CVis::MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{ 
	//AP2N("MainWndProc %s\r\n", mxpad.num2msg(uMsg));

	return ::DefWindowProc(
		hwnd,      // handle to window
		uMsg,       // message identifier
		wParam,  // first message parameter
		lParam   // second message parameter
		);
}

/////////////////////////////////////////////////////////////////////////////
// CVis

CVis::CVis()

{
	in_add = in_paint = 0;	
	
	xstart = xdrag = xchanged = xmarker = 0;

	lasttime = time(NULL);

	QueryPerformanceFrequency(&freq); freq.LowPart /= 1000;

	//AP2N("CVis::CVis() %d %d\r\n", freq.HighPart, freq.LowPart);
}

//////////////////////////////////////////////////////////////////////////

CVis::~CVis()

{
	Clear();
}

BEGIN_MESSAGE_MAP(CVis, CWnd)
	//{{AFX_MSG_MAP(CVis)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVis message handlers

BOOL CVis::OnEraseBkgnd(CDC* pDC) 

{
	return(true);	
	//return CWnd::OnEraseBkgnd(pDC);
}

//////////////////////////////////////////////////////////////////////////

//#define OLDPAINT 1   // define this for old DC paint 

void CVis::OnPaint() 

{
	QueryPerformanceCounter(&last);

	// Jump to end, if new data
	if(xchanged)
		{				
		RECT rc; GetClientRect(&rc);

		int ww = rc.right - rc.left - 2;
		int hh = rc.bottom - rc.top - 2;

		xstart = xarr.GetSize() - ww / 2;
		xchanged = false;
		}

	//AP2N("CVis::OnPaint start=%d\r\n", start);

	if(in_paint)
		{
		//AP2N("CVis::OnPaint reentry\r\n");	
		CPaintDC dc(this);		
		return;
		}

	in_paint = true;
	int prog = 0; 
	void *ptr = NULL;
	
	// Device contexts for painting	
	CClientDC dcX(this);
	
	int magfact = 2, vmagfact = 1;
	PAINTSTRUCT  ps;
	RECT rc; GetClientRect(&rc);
 
#ifndef OLDPAINT

	// Will flush to display on destruction
	CMemDC mdc(&dcX); 

	// New mem DC method
	CMemDC *pDC = &mdc; 

	BeginPaint(&ps);
	
	// Get bitmap on this mem DC
	CBitmap *bmp = pDC->GetBitmap(); ASSERT(bmp);
	BITMAP bbb; bmp->GetBitmap(&bbb);

	//AP2N("GetBitmap www=%d hhh=%d bpx=%d\r\n", 
	//			bbb.bmWidth, bbb.bmHeight, bbb.bmBitsPixel);

	int  bmpsize = bbb.bmWidth * bbb.bmHeight * bbb.bmBitsPixel / 8;

	//AP2N("ww=%d hh=%d\r\n", rc.right - rc.left, rc.bottom - rc.top);
	
#else
	// Test old DC method
	CClientDC *pDC = &dcX;
	BeginPaint(&ps);

#endif
	
	int ww = rc.right - rc.left - 2;
	int hh = rc.bottom - rc.top - 2;

	pDC->FillSolidRect(&rc, RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(128, 128, 128));
	
	int endd = 0, alen = 0;
	
	lock.Lock();

	alen = xarr.GetSize();
	
	if(!alen)
		{
		CString str; str.Format("Visualizer");
		pDC->TextOut(8, 4, str);
		}

	// Limit start position if over the limits
	if(xstart > alen)
		xstart = alen - ww / magfact;

	//start = min(start, alen - 1);
	xstart = max(xstart, 0);	

	endd  = xstart + ww / magfact;
	endd = max(endd, 0); endd  = min(endd, alen);
	

	//AP2N("bmp size=%d drawing=%d\r\n", bmpsize, 
	//			(endd - start) * bbb.bmHeight);

#ifndef OLDPAINT		// Paint via memory bitmap

	// ASSERT if buffer and bitmap differ
	if(bmpsize == 0)
		{
		in_paint = false;
		return;
		}
#endif

	try
	{

#ifndef OLDPAINT		// Paint via memory bitmap

	ptr = malloc(bmpsize);  ASSERT(ptr);
	bmp->GetBitmapBits(bmpsize, ptr);
	int *buff = (int*)ptr;

	//////////////////////////////////////////////////////////////////////
	//	Paint:		
	//				loop
	//  ****************************  
	//  **************************** loop2 * Width
	//  ****************************
	//

	int cnt = 0;
	for(int loop = xstart; loop < endd; loop++)
		{
		prog = loop;
	
		CIntArr	*tmp = (CIntArr*) xarr[loop];
		int blen = tmp->GetSize();

		for(int loop2 = 0; loop2 < blen; loop2++)
			{
			int offs = (bbb.bmHeight - 4) - loop2 * vmagfact;
			offs = max(offs, 0);
			
			int val = Num2Col(tmp->GetAt(loop2));
			
			ASSERT(magfact * cnt + offs * bbb.bmWidth < bmpsize);
			ASSERT(magfact * cnt + offs * bbb.bmWidth >= 0);

			// Fill in all four 
			buff[magfact * cnt + offs * bbb.bmWidth] = val;
			buff[magfact * cnt + (offs + 1) * bbb.bmWidth] = val;
			
			buff[magfact * cnt + 1 + offs * bbb.bmWidth] = val;
			buff[magfact * cnt + 1 + (offs + 1) * bbb.bmWidth] = val;
			}

		cnt++;
		cnt = min(cnt, bbb.bmWidth - 2);
		}
		
	// Commit bits we painted
	bmp->SetBitmapBits(bmpsize, ptr);

	if(ptr)
		free(ptr);
	
#else   // Paint via pDC

	int horoffs = 10, cnt = 0;
	for(int loop = start; loop < alen; loop++)
		{
		CIntArr	*tmp = (CIntArr*) arr[loop];
		int blen = tmp->GetSize();
		
		for(int loop2 = 0; loop2 < blen; loop2++)
			{
			int val = Num2Col(tmp->GetAt(loop2));
			int pp = hh - magfact * loop2;
			pp = max(pp, 0);
			
			pDC->SetPixel(horoffs + cnt, pp, val);
			pDC->SetPixel(horoffs + cnt+1, pp, val);

			pDC->SetPixel(horoffs + cnt, pp+1, val);
			pDC->SetPixel(horoffs + cnt+1, pp+1, val);
			}		
		cnt += 2;
 		}
#endif
	}
	catch(...)
		{		
		AP2N("Exception in CVis::OnPaint arr len=%d prog=%d\r\n", xarr.GetSize(), prog);
		}

	//support.HeapCheck("in paint");

	lock.Unlock();

	// Paint markers on top
	CPen pen(PS_SOLID, 1, RGB(200,200,200));
	pDC->SelectObject(pen);

	for(int hloop = 0; hloop < hh; hloop +=10)
		{
		int pp = hh - 2 * hloop;
		pDC->MoveTo(1 , pp); pDC->LineTo(5 , pp);
		}

	if(xmarker)
		{
		CPen penr(PS_SOLID, 1, RGB(100,200,200));
		pDC->SelectObject(penr);

		// Paint drag start
		pDC->MoveTo(xdragstart.x, 0); pDC->LineTo(xdragstart.x, rc.bottom);
		}
		 
	// Do not call CStatic::OnPaint() for painting messages
	EndPaint(&ps);

	in_paint = false;
}

//////////////////////////////////////////////////////////////////////////

void CVis::AddBuff(int *buff, int len)

{
	//while(in_paint)
	//	support.YieldToWinEx();

	in_add = true;

	CIntArr	*tmp = new CIntArr; ASSERT(tmp);

	for(int loop = 0; loop < len; loop++)
		{
		tmp->Add(*buff++);
 		}

	//lock.Lock();	
	xAdd(tmp);
	//lock.Unlock();
	
	xchanged = true;
	SoftInval();

	in_add = false;
}

//////////////////////////////////////////////////////////////////////////

void CVis::AddBuff(short *buff, int len)

{
	//while(in_paint)
	//	support.YieldToWinEx();

	in_add = true;

	CIntArr	*tmp = new CIntArr; ASSERT(tmp);

	int len2 = len / sizeof(short);
	for(int loop = 0; loop < len2; loop++)
		{
		tmp->Add(*buff++);
 		}

	//lock.Lock();
	xAdd(tmp);
	//lock.Unlock();
	
	xchanged = true;
	SoftInval();

	in_add = false;
}

//////////////////////////////////////////////////////////////////////////

void CVis::AddIntArr(CIntArr *iarr)

{
	//while(in_paint)
	//	support.YieldToWinEx();

	in_add = true;

	CIntArr	*tmp = new CIntArr; ASSERT(tmp);
	tmp->Copy(*iarr);

	//lock.Lock();
	xAdd(tmp);
	//lock.Unlock();
	
	
	xchanged = true;
	SoftInval();


	in_add = false;
}

//////////////////////////////////////////////////////////////////////////

void CVis::AddMarker()

{
	// Calculate marker height
	RECT rc; GetClientRect(&rc);

	int hh = rc.bottom - rc.top;

	for(int loop2 = 0; loop2 < 3; loop2++)
		{
		CIntArr	*tmp = new CIntArr; ASSERT(tmp);
	
		for(int loop = 0; loop < hh; loop++)
			tmp->Add(20);
		
		xAdd(tmp);
		}

	// Soft inval ..
	xchanged = true;
	SoftInval();
}

//////////////////////////////////////////////////////////////////////////

int CVis::Num2Col(int num)

{
	//int ccc = (num + 10 ) % 255;
	//int ccc = 255 - min(num, 255);

	int col, ccc;
	
	ccc = min(num, 255);
	col = RGB(255 - ccc, 255 - ccc, 255 - ccc);
		
#if 0
	if(num < 355)
		{
		ccc = min(num / 2 + 50, 255);
		col = RGB(ccc, 0, 0);
		}
	else if(num < 1024)
		{
		ccc = min(num / 10 + 50, 255);
		col = RGB(0, ccc, 0);
		}
	else
		{
		ccc = min(num / 20 + 50, 255);
		col = RGB(0, 0, ccc);
		}
#endif

	//AP2N("%d->%d \r\n", num, col);

	return col;
}

//////////////////////////////////////////////////////////////////////////

void CVis::Clear()

{
	lock.Lock();

	int alen = xarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		delete (CIntArr*) xarr[loop];
		}

	xarr.RemoveAll();

	lock.Unlock();

	if(IsWindow(m_hWnd))
		Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void CVis::OnTimer(UINT nIDEvent) 

{	
	KillTimer(nIDEvent);

	switch(nIDEvent)
		{
		case 1:
			{
			if(!in_paint)
				{
				Invalidate();
				}
			else
				{
				SetTimer(1, 200, NULL);
				}
			}
			break;
		}

	CWnd::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////

void CVis::PreSubclassWindow() 

{
	//AP2N("CVis::PreSubclassWindow\r\n");

	//ModifyStyleEx(WS_EX_APPWINDOW | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 0);
	ModifyStyle(0, WS_CLIPSIBLINGS);
	
	SetWindowLong(m_hWnd, GWL_WNDPROC, (DWORD)MainWndProc);

	CWnd::PreSubclassWindow();	
}

//////////////////////////////////////////////////////////////////////////

void CVis::OnLButtonDown(UINT nFlags, CPoint point) 

{
	int show = xstart + point.x / 2;

	SetFocus();

	//AP2N("CVis::OnLButtonDown start=%d, show=%d, xx=%d yy=%d\r\n", 
	//					start, show, point.x, point.y);

	GetParent()->PostMessage(WM_USER, show, (long) &xarr);
	
	xdragstart = point;	xdrag = true; xmarker = false;

#if 0
    TRACKMOUSEEVENT t = {
                sizeof(TRACKMOUSEEVENT),
                TME_LEAVE,
                m_hWnd,
                0
            };
     ::_TrackMouseEvent(&t);
#endif

	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////

void CVis::OnLButtonUp(UINT nFlags, CPoint point) 

{
	ReleaseCapture();
	// TODO: Add your message handler code here and/or call default
	xdrag = false;
	CWnd::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////

void CVis::OnMouseMove(UINT nFlags, CPoint point) 

{
	//if(in_paint)
	//	return;
	//xmarker = false;
	//AP2N("CVis::OnMouseMove(UINT nFlags, CPoint point) \r\n");

	if(xdrag)
		{		
		int diff = (xdragstart.x - point.x) ;

		//AP2N("CVis::OnMouseMove diff=%d start=%d\r\n", diff, start);
		
		xdragstart = point;		
		xstart += diff;
		xstart = max(xstart, 0); xstart = min(xstart, xarr.GetSize());

		//if(!in_paint)
		Invalidate();
		//support.YieldToWinEx();
		}

	CWnd::OnMouseMove(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////

LRESULT CVis::OnMouseLeave(WPARAM, LPARAM)

{
	//AP2N("CVis::OnMouseLeave\r\n");
	xdrag = false;

	return 0;
}

void CVis::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 

{
	//AP2N("CVis::OnKeyDown %d\r\n", nChar);
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////////

BOOL CVis::xMyKeyDown(MSG* pMsg) 

{
	xmarker = false;

	if(pMsg->wParam == VK_HOME)
		{
		xstart = 0;	Invalidate();
		}

	if(pMsg->wParam == VK_END)
		{
		xstart = INT_MAX; Invalidate();
		}

	if(pMsg->wParam == VK_PRIOR)
		{
		xstart += 3000;
		xstart = max(xstart, 0);	xstart = min(xstart, xarr.GetSize());

		Invalidate();
		}

	if(pMsg->wParam == VK_NEXT)
		{
		xstart -= 3000;
		xstart = max(xstart, 0);	xstart = min(xstart, xarr.GetSize());

		Invalidate();
		}

	if(pMsg->wParam == VK_UP)
		{
		xstart += 300;
		xstart = max(xstart, 0);	xstart = min(xstart, xarr.GetSize());

		Invalidate();
		}

	if(pMsg->wParam == VK_DOWN)
		{
		xstart -= 300;
		xstart = max(xstart, 0);	xstart = min(xstart, xarr.GetSize());

		Invalidate();
		}

	if(pMsg->wParam == VK_LEFT)
		{
		if(misc.IsCtrlDown())
			{
			}
		else if(misc.IsShiftDown())
			{
			//AP2N("CVis::xMyKeyDown Shift left\r\n");
			
			int show = xstart + xdragstart.x / 2;
			GetParent()->PostMessage(WM_USER, show, (long) &xarr);
			xdragstart.x -= 2;
			xmarker = true;
			Invalidate();
			}
		else
			{
			xstart += 30;
			xstart = max(xstart, 0);	xstart = min(xstart, xarr.GetSize());

			Invalidate();
			}		
		}

	if(pMsg->wParam == VK_RIGHT)
		{
		if(misc.IsCtrlDown())
			{
			}
		else if(misc.IsShiftDown())
			{
			//AP2N("CVis::xMyKeyDown Shift right\r\n");

			int show = xstart + xdragstart.x / 2;
			GetParent()->PostMessage(WM_USER, show, (long) &xarr);
			xdragstart.x += 2; 	xmarker = true;
			Invalidate();
			}
		else
			{
			xstart -= 30;
			xstart = max(xstart, 0); xstart = min(xstart, xarr.GetSize());

			Invalidate();
			}
		}

	return true;
}

//////////////////////////////////////////////////////////////////////////

BOOL CVis::PreTranslateMessage(MSG* pMsg) 

{
	if(pMsg->message == WM_KEYDOWN)
		{
		//AP2N("CVis::PreTranslateMessage OnKeyDown %d\r\n", pMsg->wParam);

		xMyKeyDown(pMsg);

		return true;
		}

	if(pMsg->message == WM_KEYUP)
		{
		return true;
		}
	
	return CWnd::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////////
// Scedule timer or force it if too long

void CVis::SoftInval()

{
	LARGE_INTEGER perf;	QueryPerformanceCounter(&perf);
	int diff = perf.LowPart / freq.LowPart - last.LowPart / freq.LowPart;

	//AP2N("CVis::SoftInval() %d\r\n", diff);

	if(diff > 300)
		{
		//AP2N("CVis::SoftInval() force\r\n");
		KillTimer(1);
		Invalidate();
		}
	else
		{
		SetTimer(1, 200, NULL);
		}
}

//////////////////////////////////////////////////////////////////////////

void CVis::xAdd(CIntArr *iarr)

{	
	xarr.Add(iarr);

#if 1

	lock.Lock();

	if(xarr.GetSize() > 2000)
		{
		for(int loop = 0; loop < 100; loop++)
			{
			delete (CIntArr*) xarr[loop];
			}
		xarr.RemoveAt(0, 100);
		}

	lock.Unlock();
#endif

}