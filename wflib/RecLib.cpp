// RecLib.cpp: implementation of the CRecLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wflib.h"
#include "RecLib.h"
#include "mxpad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

__declspec(dllexport) CRecLib reclib;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecLib::CRecLib()

{

}

CRecLib::~CRecLib()

{

}

//////////////////////////////////////////////////////////////////////////

int CRecLib::Init()

{
	//P2N("CRecLib::Init()\r\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CRecLib::_FeedSound(char *buff, int len)

{
	//P2N("CRecLib::_FeedSound(buff = %p len=%d)\r\n", buff, len);

	return 0;
}