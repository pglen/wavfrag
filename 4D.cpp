
/* =====[ 4D.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the 4D.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/7/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "mxpad.h"

#include "4D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C4DPlot

C4DPlot::C4DPlot()
{
}

C4DPlot::~C4DPlot()
{
	Clear();
}


BEGIN_MESSAGE_MAP(C4DPlot, CStatic)
	//{{AFX_MSG_MAP(C4DPlot)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C4DPlot message handlers

void C4DPlot::OnPaint() 

{
	CPaintDC dc(this); // device context for painting
	
	int ss = dc.SaveDC();

	RECT rc; GetClientRect(&rc);

	int ww = rc.right - rc.left - 2;
	int hh = rc.bottom - rc.top - 2;

	dc.SetBkColor(RGB(220, 220, 220));
	dc.SetTextColor(RGB(120, 120, 120));

	int start = 0, alen = arr.GetSize();

	if(alen == 0)
		{
		CString str; str.Format("4DPlot");
		dc.TextOut(2, 2, str);
		}
	
	int cnt = 0, skip = 4, steep = 2;
	for(int loop = start; loop < alen; loop += 1)
		{
		CIntArr	*tmp = (CIntArr*) arr[loop];
		int blen = tmp->GetSize();

		for(int loop2 = 0; loop2 < blen; loop2 += 1)
			{
			int val = tmp->GetAt(loop2);

			val /= 2;			

			//val -= val / 2;
			//val += loop2 * steep;
			//val = min(val, 255); val = max(val, 0);
			//val = hh - val;						
			//dc.SetPixel(cnt, hh - loop2 * val / 100, RGB(100, 100, 100) );		

			int xx = cnt + loop2;
			int yy = loop2 / 2 + val;

			dc.SetPixel(xx, hh - yy , RGB(100, 100, 100) );			
			}
		cnt++;
		}

	// Do not call CStatic::OnPaint() for painting messages
}

//////////////////////////////////////////////////////////////////////////

void C4DPlot::AddIntArr(CIntArr *iarr)

{
	CIntArr	*tmp = new CIntArr; ASSERT(tmp);
	tmp->Copy(*iarr);
	arr.Add(tmp);

	//SetTimer(1, 200, NULL);

	Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void C4DPlot::AddIntArr(int *ptr, int len)

{
	CIntArr	*tmp = new CIntArr; ASSERT(tmp);

	tmp->SetSize(len);
	
	memcpy(tmp->GetData(), ptr, len * sizeof(int));
	
	arr.Add(tmp);

	//SetTimer(1, 200, NULL);

	Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void C4DPlot::Clear()

{
	int alen = arr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		delete (CIntArr*) arr[loop];
		}
	arr.RemoveAll();

	if(IsWindow(m_hWnd))
		Invalidate();
}

//////////////////////////////////////////////////////////////////////////

void C4DPlot::AddMarker()

{
	for(int loop2 = 0; loop2 < 100; loop2++)
		{
		CIntArr	*tmp = new CIntArr; ASSERT(tmp);
		
		for(int loop = 0; loop < 5; loop++)
			tmp->Add(0);

		arr.Add(tmp);
		}

}

//////////////////////////////////////////////////////////////////////////

BOOL C4DPlot::OnEraseBkgnd(CDC* pDC) 

{
	RECT rc; GetClientRect(&rc);

	pDC->FillSolidRect(&rc, RGB(220,220,220));
	pDC->Draw3dRect(&rc, RGB(200,200,200), RGB(100,100,100));
	
	return CStatic::OnEraseBkgnd(pDC);
}

//////////////////////////////////////////////////////////////////////////

void C4DPlot::PreSubclassWindow() 
{
	ModifyStyle(0, WS_CLIPCHILDREN);
	
	CStatic::PreSubclassWindow();
}
