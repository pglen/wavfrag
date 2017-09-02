
/* =====[ CSelList.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the CSelList.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  7/9/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// CSelList.cpp : implementation file
//

#include "stdafx.h"
#include "SelList.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelList

CSelList::CSelList()
{


}

CSelList::~CSelList()
{
}


BEGIN_MESSAGE_MAP(CSelList, CCheckListBox)
	//{{AFX_MSG_MAP(CSelList)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelList message handlers

BOOL CSelList::OnInitDialog()

{
	//AP2N("CSelList::OnInitDialog\r\n");

	OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CSelList::OnCreate(LPCREATESTRUCT lpCreateStruct)

{
	AP2N("CSelList::OnCreate\r\n");

	if (CCheckListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
