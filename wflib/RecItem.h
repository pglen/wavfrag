// RecItem.h: interface for the CRecItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECITEM_H__EAD4DD19_21BC_4157_9734_C62893609075__INCLUDED_)
#define AFX_RECITEM_H__EAD4DD19_21BC_4157_9734_C62893609075__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CRecItem_Magic	0x3234567

//////////////////////////////////////////////////////////////////////////
// Recogntion item

class CRecItem  

{
public:
	void Sanity();
	void Dump(int flag = 0);

	CRecItem();
	virtual ~CRecItem();

	//CString *pstr, *pstr2, *pstr3, *pstr4, 
	CString *pstrx, *pstrx2;
	
	int		midx, mval;
	int		midx2, mval2;
	int		midx3, mval3;
	int		midx4, mval4;

	int		rat;

	int		magic;

private:


};

#endif // !defined(AFX_RECITEM_H__EAD4DD19_21BC_4157_9734_C62893609075__INCLUDED_)
