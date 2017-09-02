// DicRec.h: interface for the CDicRec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICREC_H__A9506743_7D13_450A_98FF_B4C204BADFAB__INCLUDED_)
#define AFX_DICREC_H__A9506743_7D13_450A_98FF_B4C204BADFAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CDicRec_Magic 0x3239393


class CDicRec  

{

public:
	void	RemLast();
	void	Clear();

	static	CPtrArray	dicarr;			// Collective
	static	int		changed;			// Flag

	// Global Management
	static	void	LoadDics(const char *dir);
	static	void	SaveDics(const char *fname);
	static	void	DelDics();

	void	Dump();
	void	Serialize(const char *dir);
	int		Find(CPtrArray *parr);

	int		Add(const char *str);
	void	Parse(CString *pstr, CStringArray *strarr);

	int		magic;	
	CString	*name;

	CDicRec();
	virtual ~CDicRec();

protected:

	void	Parse(const char *str, CStringArray *strarr);
	int		Compare(int skip, CPtrArray *parr, CStringArray *ref);

	CStringArray	arr;
};

#endif // !defined(AFX_DICREC_H__A9506743_7D13_450A_98FF_B4C204BADFAB__INCLUDED_)
