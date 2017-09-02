
/* =====[ Command.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Command.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/28/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "Command.h"

#include "mxpad.h"
#include "support.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()

{
	magic	=	CCommand_Magic;
	prompt	=	false;
	kind	=	0;

	name	= new CString;
	comstr	= new CString;	comstr2 = new CString;	comstr3 = new CString;
	comm = new CString;	para = new CString;
}

//////////////////////////////////////////////////////////////////////////

CCommand::~CCommand()

{
	delete name; delete comm; delete para; 
	delete comstr; delete comstr2; delete comstr3;
}

//////////////////////////////////////////////////////////////////////////

int CCommand::Dump()

{
	AP2N("Action: '%s' - '%s' '%s' '%s'\r\n", 
								*name, *comstr, *comstr2, *comstr3);
	AP2N("'%s' '%s' - %d %d\r\n",
								*comm, *para, prompt, kind);

	return 0;
}

