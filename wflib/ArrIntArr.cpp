
/* =====[ ArrIntArr.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the ArrIntArr.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/12/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "ArrIntArr.h"
#include "mxpad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArrIntArr::CArrIntArr()

{
	magic = CArrIntArr_Magic;
}

CArrIntArr::~CArrIntArr()

{
	ASSERT(magic == CArrIntArr_Magic);
	
	int alen = arrdata.GetSize();
	for(int loopf = 0; loopf < alen; loopf++)
		{
		CIntArrRec *ddd = GetAt(loopf);
		ASSERT(ddd->magic == CIntArr_Magic);
		delete ddd;
		}
	arrdata.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////
// Get lastly added member (for current op)

CIntArrRec *CArrIntArr::GetLast()

{
	CIntArrRec *ret = NULL;

	int len = GetSize() - 1;

	if(len >= 0)
		{
		ret = GetAt(len);
		}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Add a new candidate array. Create if needed.

int CArrIntArr::Add(CIntArrRec *piarr)

{
	if(piarr == NULL)
		piarr = new CIntArrRec;

	ASSERT(piarr);

	arrdata.Add(piarr);
	
	return arrdata.GetSize();
}

//////////////////////////////////////////////////////////////////////////

CIntArrRec *CArrIntArr::GetAt(int idx)

{
	ASSERT(idx >= 0);  ASSERT(idx < arrdata.GetSize());

	return((CIntArrRec*)arrdata.GetAt(idx));
}


//////////////////////////////////////////////////////////////////////////
// Write it out. Return number of INT records written

int		CArrIntArr::ToFile(CFile *fp)

{
	int wcnt = 0;
	struct_ms ms; ms.magic = CArrIntArr_Magic; ms.len = GetSize();

	//AP2N("	CArrIntArr::ToFile %d\r\n", ms.len);

	// Write out descriptor
	fp->Write(&ms, sizeof(ms));
	
	// Write out vol array
	for(int loopc = 0; loopc < ms.len; loopc++)
		{
		CIntArrRec *tmp = GetAt(loopc);			
		tmp->ToFile(fp);
		//AP2N("	CArrIntArr::ToFile wrote %d\r\n", tmp->GetSize());
 		wcnt += tmp->GetSize();
		}	
	return wcnt;
}

//////////////////////////////////////////////////////////////////////////
// Read it back in ..

int		CArrIntArr::FromFile(CFile *fp)

{
	int rcnt = 0; struct_ms ms; ms.magic = 0; ms.len = 0;

	fp->Read(&ms, sizeof(ms));

	//AP2N("	CArrIntArr::FromFile %d\r\n", ms.len);

	if(ms.magic != CArrIntArr_Magic)
		{
		AP2N("CArrIntArr::FromFile BAD magic\r\n");
		return 0;
		}

	// Sensible values ...
	if(ms.len > 1000 || ms.len < 0) 
		{
		AP2N("CArrIntArr::FromFile unreasonable data length %d\r\n");
		return 0;
		}

	//AP2N("CArrIntArr::FromFile %s count=%d\r\n", *name, sss);

	// Load frags
	for(int loop = 0; loop < ms.len; loop++)
		{
		CIntArrRec *tmp = new CIntArrRec; ASSERT(tmp);

		if(tmp->FromFile(fp) >= 0)
			{
			Add(tmp);
			rcnt += tmp->GetSize();	
			}
		else
			{
			delete tmp;			// Free dangling one
			break;
			}
		//AP2N("	CArrIntArr::FromFile got %d bytes\r\n", ret);	
		}
	return rcnt;
}

// EOF
