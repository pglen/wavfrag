// Donut.h: interface for the CDonut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DONUT_H__A1274FC2_65BB_4B51_BB87_384A9981B4C0__INCLUDED_)
#define AFX_DONUT_H__A1274FC2_65BB_4B51_BB87_384A9981B4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "intarr.h"

class CDonut  
{

public:

	int		Donut(CString *str1, CString *str2, CIntArr *pval);
	int		NewDonut(CPtrArray *recarr, int s2, int e2, CStringArray *darr);
	
public:
	CDonut();
	virtual ~CDonut();

protected:

	void	xParse(CString *pstr, CStringArray *strarr);
	int		xAlike(CString *s1, CString *s2);
	int		xDonut2(CStringArray *sarr, CStringArray *darr, CIntArr *pval);
	int		xDonut3(CStringArray *sarr, CStringArray *darr, CIntArr *pval);
	int		xDonut4(CStringArray *sarr, CStringArray *darr);
	
};

#endif // !defined(AFX_DONUT_H__A1274FC2_65BB_4B51_BB87_384A9981B4C0__INCLUDED_)
