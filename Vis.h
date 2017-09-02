#if !defined(AFX_VIS_H__6DEA0FEB_4370_47B6_AED1_97FBBEA37DA0__INCLUDED_)
#define AFX_VIS_H__6DEA0FEB_4370_47B6_AED1_97FBBEA37DA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Vis.h : header file
//

#include "afxmt.h"

#include "IntArr.h"

/////////////////////////////////////////////////////////////////////////////
// CVis window

class CVis : public CWnd
{
// Construction
public:

	static LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam);    // second message parameter
	
	CVis();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVis)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	
	void	AddBuff(short *buff, int len);
	void	AddBuff(int	 *buff, int len);
	void	AddIntArr(CIntArr *iarr);
	
	void	AddMarker();
	void	Clear();

	void SoftInval();

	virtual ~CVis();

protected:


	void	xAdd(CIntArr *iarr);
	int		lasttime, in_paint, in_add;

	int		Num2Col(int num);
	BOOL	xMyKeyDown(MSG* pMsg);

	int		xdrag, xstart, xmarker, xchanged; 

	LARGE_INTEGER freq, last;

	CPoint	xdragstart;
	CPtrArray xarr;

	CCriticalSection lock;

	//{{AFX_MSG(CVis)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIS_H__6DEA0FEB_4370_47B6_AED1_97FBBEA37DA0__INCLUDED_)
