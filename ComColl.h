// ComColl.h: interface for the CComColl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMCOLL_H__3BADDAFC_BE8D_4448_B15D_DE889D75955A__INCLUDED_)
#define AFX_COMCOLL_H__3BADDAFC_BE8D_4448_B15D_DE889D75955A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"


class CComColl  
{
	friend class CCommand;

public:
	CComColl();
	virtual ~CComColl();

	void		LoadComms(const char *dir);
	void		Save(const char *dir);
	
	int			Dump();

	void		AddComm(const char *name, const char *comm, const char *para);
	void		DelComm(const char *name);

	CCommand	*GetComm(int idx);
	CCommand	*GetComm(const char *name);
	CCommand	*GetComStr(const char *comstr);
	
	int		changed;

private:

	//CStringArray namearr, commarr, paraarr;
	CPtrArray	arr;

};

#endif // !defined(AFX_COMCOLL_H__3BADDAFC_BE8D_4448_B15D_DE889D75955A__INCLUDED_)
