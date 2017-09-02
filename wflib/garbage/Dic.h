// Dic.h: interface for the CDic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIC_H__AC11A4AD_2D90_48BE_847D_4FEE36683DF1__INCLUDED_)
#define AFX_DIC_H__AC11A4AD_2D90_48BE_847D_4FEE36683DF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDic_Magic  0xe4e5213

class CDic  
{
public:
		
	void	Add(CString *pstr);
	void	Dump();
	int			magic;

public:

	CDic();
	virtual ~CDic();

	CStringArray	*strarr;	
	CString			*name, *str;

};

#endif // !defined(AFX_DIC_H__AC11A4AD_2D90_48BE_847D_4FEE36683DF1__INCLUDED_)
