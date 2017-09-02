
/* =====[ ContainArr.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the ContainArr.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  5/24/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "ContainArr.h"

#include "mxpad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContainArr::CContainArr()

{

	magic = CContainArr_Magic;
}

//////////////////////////////////////////////////////////////////////////

CContainArr::~CContainArr()

{
	ASSERT(CContainArr_Magic == magic);
	Clear();
}

//////////////////////////////////////////////////////////////////////////

void	CContainArr::Add(CContain *ptr)

{
	xarr.Add(ptr);
}

//////////////////////////////////////////////////////////////////////////

void	CContainArr::Dump()

{
	int size = xarr.GetSize();
		
	for(int loop = 0; loop < size; loop++)
		{
		CContain *val = (CContain*)xarr.GetAt(loop);

		ASSERT(val->magic == CContain_Magic);

		AP2N("CContainArr name='%s'\r\n", *val->name);

		val->Dump();
 		}
}

//////////////////////////////////////////////////////////////////////////

void	CContainArr::Clear()

{
	int size = xarr.GetSize();
		
	for(int loop = 0; loop < size; loop++)
		{
		CContain *val = (CContain*)xarr.GetAt(loop);

		ASSERT(val->magic == CContain_Magic);

		delete val;
 		}

	xarr.RemoveAll();
}
