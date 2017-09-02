
/* =====[ UserTab.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the UserTab.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  7/13/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"

#include "UserTab.h"
#include "GetText.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserTab dialog


CUserTab::CUserTab(CWnd* pParent /*=NULL*/)
	: CDialog(CUserTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserTab)
	//}}AFX_DATA_INIT
}


void CUserTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserTab)
	DDX_Control(pDX, IDC_CURRSP, m_currsp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserTab, CDialog)
	//{{AFX_MSG_MAP(CUserTab)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON32, OnButton32)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserTab message handlers

void CUserTab::xFillUserCombo() 

{
	m_users.ResetContent();

	CString tmps; char *str = tmps.GetBuffer(_MAX_PATH); 
	int cnt = 0;
	while(true)
		{
		int  ret =   WFL_GetFragSpeaker(cnt++, str, _MAX_PATH + 1);

		if(ret < 0)
			break;

		int idx = m_users.AddString(str);
		m_users.SetCheck(idx, true);
		}	
}

//////////////////////////////////////////////////////////////////////////

void CUserTab::InitCombos() 

{
	xFillUserCombo();
	m_users.SelectString(0, "default");
	OnSelchangeList1();
}

//////////////////////////////////////////////////////////////////////////

BOOL CUserTab::OnInitDialog() 

{
	m_users.SubclassDlgItem(IDC_LIST1, this);
	
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CUserTab::OnButton1() 

{
	CGetText gt; gt.m_title = "Enter new speaker name to add to recognition frags";

	if(gt.DoModal() == IDCANCEL)
		return;

	if(gt.m_edit == "")
		return;

	//AP2N("Adding speaker '%s'\r\n", gt.m_edit);

	int  ret =  WFL_AddFragSpeaker(gt.m_edit);

	if(ret >= 0)
		{
		xFillUserCombo();
		m_users.SelectString(0, gt.m_edit);		
		OnSelchangeList1();
		}	
}

//////////////////////////////////////////////////////////////////////////

void CUserTab::OnButton32() 

{
	int idx = m_users.GetCurSel();

	if(idx < 0)
		return;

	CString str; m_users.GetText(idx, str);

	if(str == "default")
		{
		AfxMessageBox("Cannot delete default user");
		return;
		}

	CString tmp; tmp.Format("Are you sure you want to delete '%s' and all the speaker's frags?", str);

	if(AfxMessageBox(tmp, MB_YESNO) != IDYES)
		return;

	WFL_DelFragSpeaker(str);
	
	xFillUserCombo();

	// Select previous one
	m_users.SetCurSel(idx - 1);

	OnSelchangeList1();

}

//////////////////////////////////////////////////////////////////////////

void CUserTab::OnSelchangeList1() 

{
	int idx = m_users.GetCurSel();
	
	if(idx < 0)
		return;

	CString str; m_users.GetText(idx, str);
	WFL_SetCurrSpeaker(str);		

	AP2N("CUserTab::OnSelchangeList1 %s\r\n", str);

	xFillCurrUser();
}

//////////////////////////////////////////////////////////////////////////

void CUserTab::xFillCurrUser() 

{
	CString tmps; char *curr = tmps.GetBuffer(_MAX_PATH + 1); 
	int	ret2 = WFL_GetCurrSpeaker(curr, _MAX_PATH);
	m_currsp.SetWindowText(curr);
}
