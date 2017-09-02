// RecLib.h: interface for the CRecLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECLIB_H__7C1DDAE0_F5DE_4526_9EC3_003E2B8E592B__INCLUDED_)
#define AFX_RECLIB_H__7C1DDAE0_F5DE_4526_9EC3_003E2B8E592B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRecLib  
{
public:
	__declspec(dllexport) static int _FeedSound(char *buff, int len);

public:
	__declspec(dllexport) int Init();

	CRecLib();
	virtual ~CRecLib();

};

#endif // !defined(AFX_RECLIB_H__7C1DDAE0_F5DE_4526_9EC3_003E2B8E592B__INCLUDED_)
