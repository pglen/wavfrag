
/* =====[ RecItem.cpp ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the RecItem.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/25/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
//#include "daco.h"
#include "mxpad.h"
#include "RecItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecItem::CRecItem()

{
	//pstr  = new CString;	pstr2 = new CString;
	//pstr3 = new CString;	pstr4 = new CString;

	pstrx = new CString;
	pstrx2 = new CString;

	rat = midx = mval = midx2 = mval2 = 0;
	midx3 = mval3 =  midx4 = mval4 = 0;

	magic = CRecItem_Magic;
}

//////////////////////////////////////////////////////////////////////////

CRecItem::~CRecItem()

{
	ASSERT(magic == CRecItem_Magic);

	//delete pstr; delete pstr2;
	//delete pstr3; delete pstr4;
	
	delete pstrx; delete pstrx2;
}

//////////////////////////////////////////////////////////////////////////

void CRecItem::Dump(int flag)

{
	ASSERT(magic == CRecItem_Magic);

	if(flag)
		{
		AP2N("%s\t%s\t(%d%%)\t%d/%d\r\n", *pstrx, *pstrx2, rat, mval, mval2);	
		}
	else
		{
		AP2N("%s\t%s\t(%d%%)\t%d\t\r\n", *pstrx, *pstrx2, rat, mval);

		//AP2N("%s\t%d\t", *pstr2, mval2);
		//AP2N("%s\t%d\t", *pstr3, mval3);
		//AP2N("%s\t%d\t\r\n", *pstr4, mval4);
		}
}

//

void CRecItem::Sanity()

{
	ASSERT(magic == CRecItem_Magic);
}
