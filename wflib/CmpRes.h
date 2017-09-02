// CmpRes.h: interface for the CCmpRes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMPRES_H__639D5F74_2EF4_403A_AEBE_B62D10B5593C__INCLUDED_)
#define AFX_CMPRES_H__639D5F74_2EF4_403A_AEBE_B62D10B5593C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CCmpRes_Magic 0x22101019

class CCmpRes  
{
public:
	CCmpRes();
	virtual ~CCmpRes();

	int magic, nfund, nharm, nhiss;
};

#endif // !defined(AFX_CMPRES_H__639D5F74_2EF4_403A_AEBE_B62D10B5593C__INCLUDED_)
