// SendKeys.h: interface for the CSendKeys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENDKEYS_H__42E119CE_16D2_4C7D_946A_A4A43FB3E5F5__INCLUDED_)
#define AFX_SENDKEYS_H__42E119CE_16D2_4C7D_946A_A4A43FB3E5F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSendKeys  
{

public:

	typedef struct

{
	int		scan;
	int		slen;
	char	*vkstr;
} skkeydef;


	CSendKeys();
	virtual ~CSendKeys();


	int		SendKeys(const char *keys);


private:

	int		CSendKeys::xTrans(const char *keys, int *skip, int *scan);


};

#endif // !defined(AFX_SENDKEYS_H__42E119CE_16D2_4C7D_946A_A4A43FB3E5F5__INCLUDED_)
