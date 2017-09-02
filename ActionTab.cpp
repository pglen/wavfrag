
/* =====[ ActionTab.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the ActionTab.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  5/26/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "ActionTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Simplify cast to parent window
#define PARENT ((CWavfragDlg*)GetParent())

/////////////////////////////////////////////////////////////////////////////
// CActionTab dialog


CActionTab::CActionTab(CWnd* pParent /*=NULL*/)
	: CDialog(CActionTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActionTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CActionTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActionTab)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CActionTab, CDialog)
	//{{AFX_MSG_MAP(CActionTab)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON31, OnButton31)
	ON_BN_CLICKED(IDC_BUTTON33, OnButton33)
	ON_BN_CLICKED(IDC_BUTTON34, OnButton34)
	ON_BN_CLICKED(IDC_BUTTON36, OnButton36)
	ON_BN_CLICKED(IDC_BUTTON37, OnButton37)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActionTab message handlers

void CActionTab::OnButton14() 
{
	AfxMessageBox("yipeee");	
}

void CActionTab::OnButton31() 

{
	WINDOWPLACEMENT wp; PARENT->plotdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->plotdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->plotdlg.ShowWindow(SW_RESTORE);		
}

void CActionTab::OnButton33() 

{
	WINDOWPLACEMENT wp; PARENT->visdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->visdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->visdlg.ShowWindow(SW_RESTORE);		
}

void CActionTab::OnButton34() 
{
	WINDOWPLACEMENT wp; PARENT->wavdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->wavdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->wavdlg.ShowWindow(SW_RESTORE);		
}

void CActionTab::OnButton36() 

{
	WINDOWPLACEMENT wp; PARENT->fourdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->fourdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->fourdlg.ShowWindow(SW_RESTORE);		
}

void CActionTab::OnButton37() 

{
	WINDOWPLACEMENT wp; PARENT->threedlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->threedlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->threedlg.ShowWindow(SW_RESTORE);	
}
