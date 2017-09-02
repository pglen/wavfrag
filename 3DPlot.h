#if !defined(AFX_3DPLOT_H__106F0161_6A13_496A_8BEA_61F94584BA07__INCLUDED_)
#define AFX_3DPLOT_H__106F0161_6A13_496A_8BEA_61F94584BA07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DPlot.h : header file
//

#include "IntArr.h"

/////////////////////////////////////////////////////////////////////////////
// C3DPlot window

class C3DPlot : public CStatic
{
// Construction
public:
	C3DPlot();

// Attributes
public:

	void AddMarker();
	void AddIntArr(CIntArr *iarr);
	void AddIntArr(int *ptr, int len);
	void Clear();
	void TrimLong();

	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DPlot)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3DPlot();

	// Generated message map functions
protected:
	CPtrArray xarr;

	//{{AFX_MSG(C3DPlot)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPLOT_H__106F0161_6A13_496A_8BEA_61F94584BA07__INCLUDED_)
