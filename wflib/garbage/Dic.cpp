// Dic.cpp: implementation of the CDic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "daco.h"
#include "mxpad.h"
#include "Dic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDic::CDic()

{
	magic = CDic_Magic;

	name = new CString;	str = new CString;
	strarr = new CStringArray;
}

CDic::~CDic()

{
	ASSERT(magic == CDic_Magic);
	
	delete name; delete str; 
	delete strarr;
}

//////////////////////////////////////////////////////////////////////////
// Dump it

void CDic::Dump()

{
	//P2N("CDic::Dump()\r\n");

	P2N("name='%s' str='%s'\r\n", *name, *str);	

	int alen = strarr->GetSize();
	for(int loopd = 0; loopd < alen; loopd++)
		{
		AP2N("strarr[%d] = '%s'\r\n",  loopd, strarr->GetAt(loopd));
 		}

}

//////////////////////////////////////////////////////////////////////////

void CDic::Add(CString *pstr)

{
	int idx = pstr->FindOneOf(" \t");  // will also do empty string correctly
	if(idx >= 0)
		{
		*name = pstr->Left(idx);

		// Skip over space
		for(int loop = idx; loop < pstr->GetLength(); loop++)
			{
			if(pstr->GetAt(loop) != ' ' && pstr->GetAt(loop) != '\t')
				break;
			}
		*str = pstr->Mid(loop);	
		//str->MakeLower();
		}

	int create = true;
	int len = str->GetLength();
	for(int loop = 0; loop < len; loop++)
		{
		if(str->GetAt(loop) == ' ')
			{
			create = true;
			}
		else
			{
			if(create)
				{
				strarr->Add(""); create = false;
				}
			strarr->SetAt(strarr->GetUpperBound(),
				strarr->GetAt(strarr->GetUpperBound()) + str->GetAt(loop));
			}
		}

}
