
/* =====[ Command.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Command.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/24/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_COMMAND_H__E7C7CB2E_2E9A_4667_A413_7946E55F7045__INCLUDED_)
#define AFX_COMMAND_H__E7C7CB2E_2E9A_4667_A413_7946E55F7045__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CCommand_Magic 0xffee4543

//////////////////////////////////////////////////////////////////////////
// Command Kinds

#define DO_EXE			1
#define DO_KEYS			2
#define DO_IMAGE		3
#define DO_IMAGECLOSE	4
#define DO_SLEEP		5
#define DO_WAKE			6
#define DO_EXITME		7
#define DO_MINME		8
#define DO_MAXME		9
#define DO_YESMODAL		10
#define DO_NOMODAL		11
#define DO_IMAGENEXT	12
#define DO_IMAGEPREV	14
#define DO_SHUTDOWN		15
#define DO_TERMINATE	16
#define DO_ACTNEXT		17
#define DO_ACTPREV		18
#define DO_ENABACT		19
#define DO_DISABACT		20
#define DO_DOC			21

//////////////////////////////////////////////////////////////////////////

class CCommand  

{
public:

	friend class CComColl;


	int			Dump();

	//////////////////////////////////////////////////////////////////////

	CCommand();
	virtual ~CCommand();

	CString *name, *comm, *para;
	CString *comstr, *comstr2, *comstr3;

	int		kind, prompt, magic;

private:

};

#endif // !defined(AFX_COMMAND_H__E7C7CB2E_2E9A_4667_A413_7946E55F7045__INCLUDED_)
