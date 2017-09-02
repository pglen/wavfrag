#if !defined(AFX_4D_H__2EFD6306_14BD_4D5D_8F06_E29AF0B56AC3__INCLUDED_)
#define AFX_4D_H__2EFD6306_14BD_4D5D_8F06_E29AF0B56AC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 4D.h : header file
//

#include "IntArr.h"


/////////////////////////////////////////////////////////////////////////////
// C4D window

class C4DPlot : public CStatic
{
// Construction
public:

	C4DPlot();

	void AddIntArr(int *ptr, int len);
	void AddIntArr(CIntArr *iarr);
	void Clear();
	void AddMarker();

	CPtrArray arr;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C4D)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C4DPlot();

	// Generated message map functions
protected:
	//{{AFX_MSG(C4D)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_4D_H__2EFD6306_14BD_4D5D_8F06_E29AF0B56AC3__INCLUDED_)
