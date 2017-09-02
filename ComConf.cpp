
/* =====[ ComConf.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the ComConf.cpp                
                                                                             
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
#include "ComConf.h"
#include "FileDialogST.h"
#include "support.h"

#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CComColl comcoll;

/////////////////////////////////////////////////////////////////////////////
// CComConf dialog


CComConf::CComConf(CWnd* pParent /*=NULL*/)
	: CDialog(CComConf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComConf)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComConf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComConf)
	DDX_Control(pDX, IDC_ACTION, m_action);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComConf, CDialog)
	//{{AFX_MSG_MAP(CComConf)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComConf message handlers

BOOL CComConf::OnInitDialog() 

{
	CDialog::OnInitDialog();
	
	//((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(name);
	
	m_action.SetFontSize(36); m_action.SetFontBold();
	m_action.CenterText();
	m_action.SetText(name);

	CComboBox *cbox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CComboBox *cbox2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox *cbox3 = (CComboBox*)GetDlgItem(IDC_COMBO6);
	
	// Fill up command list 
	CString tmp; char *strx = tmp.GetBuffer(_MAX_PATH + 1); 

	int idxs = 0;
	while(true)
		{
		int ret = WFL_GetFragStr(idxs++, strx, _MAX_PATH);
		
		if(ret < 0)
			break;

		int idx = 0, found = false;
		while(true)
			{
			CCommand *com = (CCommand*)comcoll.GetComm(idx++);
			
			if(!com)
				break;

			//AP2N("CComConf::OnInitDialog checking '%s'\r\n", *com->comm);

			if(strx == *com->comstr)
				{
				found = true;
				}
			}

		if(!found)
			{
			cbox->AddString(strx);
			cbox2->AddString(strx);
			cbox3->AddString(strx);
			}
		}

	curr = comcoll.GetComm(name);

	if(curr)
		{
		if(*curr->comstr != "")
			{
			cbox->AddString(*curr->comstr);	
			cbox->SelectString(0, *curr->comstr);
			
			cbox2->AddString(*curr->comstr2);	
			cbox2->SelectString(0, *curr->comstr2);

			cbox3->AddString(*curr->comstr3);	
			cbox3->SelectString(0, *curr->comstr3);
			}
		else
			{
			cbox->SelectString(0, name);
			}

		switch(curr->kind)
			{
			case DO_EXE:
				((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(true);
				((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(curr->prompt);

				((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(*curr->comm);
				((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(*curr->para);
			break;
			
			case DO_SLEEP:
				((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(true);
				((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(curr->prompt);
				break;

			case DO_WAKE:
				((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(true);
				((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(curr->prompt);
				break;

			case DO_IMAGE:
				((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(true);
				((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(curr->prompt);

				((CEdit*)GetDlgItem(IDC_EDIT5))->SetWindowText(*curr->para);
				break;
		
			case DO_IMAGEPREV:
				((CButton *)GetDlgItem(IDC_RADIO13))->SetCheck(true);
				break;
			
			case DO_IMAGENEXT:
				((CButton *)GetDlgItem(IDC_RADIO10))->SetCheck(true);
				break;

			case DO_IMAGECLOSE:
				((CButton *)GetDlgItem(IDC_RADIO12))->SetCheck(true);
				break;

			case DO_EXITME:
				((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(true);
				break;

			case DO_SHUTDOWN:
				((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(true);
				break;
				
			case DO_MINME:
				((CButton *)GetDlgItem(IDC_RADIO7))->SetCheck(true);
				break;
				
			case DO_MAXME:
				((CButton *)GetDlgItem(IDC_RADIO8))->SetCheck(true);
				break;	
				
			case DO_TERMINATE:
				((CButton *)GetDlgItem(IDC_RADIO15))->SetCheck(true);
				break;		
				
			case DO_ACTNEXT:
				((CButton *)GetDlgItem(IDC_RADIO16))->SetCheck(true);
				break;						

			case DO_ACTPREV:
				((CButton *)GetDlgItem(IDC_RADIO17))->SetCheck(true);
				break;		
				
			case DO_KEYS:
				((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(true);						
				((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(curr->prompt);
				((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(*curr->para);
				break;	

			case DO_DOC:
				((CButton *)GetDlgItem(IDC_RADIO20))->SetCheck(true);						
				((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(*curr->para);
				break;	

			case DO_ENABACT:
				((CButton *)GetDlgItem(IDC_RADIO18))->SetCheck(true);
				break;	
				
			case DO_YESMODAL:
				((CButton *)GetDlgItem(IDC_RADIO11))->SetCheck(true);
				break;	

			case DO_NOMODAL:
				((CButton *)GetDlgItem(IDC_RADIO9))->SetCheck(true);
				break;	
			}			
		}
	else
		{
		//
		cbox->SelectString(0, name);		
		}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CComConf::OnOK() 

{
	CString str, str2, str3, str4, str5;
		
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(str3);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(str4);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->GetWindowText(str5);
		
	if(str3 == "")
		{
		AfxMessageBox("Must have at least one string to recognize.");
		return;
		}
	
	*curr->comstr  = str3;
	*curr->comstr2 = str4;
	*curr->comstr3 = str5;
	
	comcoll.changed = true;
		
	if( ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  Radio exe\r\n");
	
		((CEdit *)GetDlgItem(IDC_EDIT2))->GetWindowText(str);
		
		if(str == "")
			{
			AfxMessageBox("Must have a command to execute");
			return;
			}

		((CEdit *)GetDlgItem(IDC_EDIT3))->GetWindowText(str2);

		*curr->comm = str;	*curr->para = str2;
		
		curr->kind = DO_EXE;
		curr->prompt = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_KEYS\r\n");
		
		curr->kind = DO_KEYS;
		curr->prompt = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
		((CEdit*)GetDlgItem(IDC_EDIT4))->GetWindowText(*curr->para);
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  image\r\n");

		curr->kind = DO_IMAGE;
		curr->prompt = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();
		((CEdit*)GetDlgItem(IDC_EDIT5))->GetWindowText(*curr->para);
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_SLEEP\r\n");

		curr->kind = DO_SLEEP;
		curr->prompt = ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck();
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO5))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_WAKE\r\n");

		curr->kind = DO_WAKE;
		curr->prompt = ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck();
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO12))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_IMAGECLOSE\r\n");

		curr->kind = DO_IMAGECLOSE;		
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO11))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_YESMODAL\r\n");

		curr->kind = DO_YESMODAL;		
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO9))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_NOMODAL\r\n");

		curr->kind = DO_NOMODAL;		
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO6))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_EXITME\r\n");

		curr->kind = DO_EXITME;		
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO10))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_IMAGENEXT\r\n");

		curr->kind = DO_IMAGENEXT;		
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO13))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_IMAGEPREV\r\n");

		curr->kind = DO_IMAGEPREV;		
		}
	else if( ((CButton *)GetDlgItem(IDC_RADIO14))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_SHUTDOWN\r\n");

		curr->kind = DO_SHUTDOWN;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO7))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_SHUTDOWN\r\n");

		curr->kind = DO_MINME;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO8))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_SHUTDOWN\r\n");

		curr->kind = DO_MAXME;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO15))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_TERMINATE\r\n");

		curr->kind = DO_TERMINATE;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO16))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_ACTNEXT\r\n");

		curr->kind = DO_ACTNEXT;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO17))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_ACTPREV\r\n");

		curr->kind = DO_ACTPREV;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO18))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_ENABACT\r\n");

		curr->kind = DO_ENABACT;		
		}	
	else if( ((CButton *)GetDlgItem(IDC_RADIO20))->GetCheck())
		{
		//AP2N("CComConf::OnOK()  DO_ENABACT\r\n");

		curr->kind = DO_DOC;	
		((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(*curr->para);		
		}	
	else
		{
		AfxMessageBox("At least one action should be selected.\r\n"
			"(Press Cancel in the dialog to abandon changes)");
		return;
		}
		
	// Save it for sure
	// Clean up recognition
	CString comfile(appdata);  comfile += "wavfrag.wfc";
	comcoll.Save(comfile);
	
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////

char imgfilter[] =
		"Image Files (*.jpg *.gif *.bmp)\0*.jpg;*.gif;*.bmp\0All Files\0*.*\0\0" ;


void CComConf::OnButton20() 

{
	CFileDialogST  cdf(true);

	CString droot, dresult, lresult;

	CString homedata; support.GetHomeDir(homedata);

	cdf.m_ofn.lpstrInitialDir = homedata;
	cdf.m_ofn.lpstrFilter	= imgfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;

	((CEdit*)GetDlgItem(IDC_EDIT5))->SetWindowText(cdf.GetPathName());
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(true);
				

}

char exefilter[] =
		"Executable Files (*.exe *.com *.dll)\0*.exe;*.com;*.dll\0All Files\0*.*\0\0" ;

void CComConf::OnButton1() 

{
	CFileDialogST  cdf(true);

	CString droot, dresult, lresult;

	
	CString progdata;
	support.GetSpecialFolder(CSIDL_PROGRAMS, progdata);

	cdf.m_ofn.lpstrInitialDir = progdata;
	cdf.m_ofn.lpstrFilter	= exefilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;
	
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(cdf.GetPathName());
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(true);
}

char allfilter[] =
		"All Files\0*.*\0\0" ;

void CComConf::OnButton2() 
{
	CFileDialogST  cdf(true);

	CString homedata; support.GetHomeDir(homedata);

	cdf.m_ofn.lpstrInitialDir = homedata;
	CString droot, dresult, lresult;
	cdf.m_ofn.lpstrFilter	= allfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;
	
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(cdf.GetPathName());	
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(true);
}

void CComConf::OnButton3() 
{
	CFileDialogST  cdf(true);

	CString homedata; support.GetHomeDir(homedata);

	cdf.m_ofn.lpstrInitialDir = homedata;
	CString droot, dresult, lresult;
	cdf.m_ofn.lpstrFilter	= allfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;
	
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(cdf.GetPathName());	
	((CButton *)GetDlgItem(IDC_RADIO20))->SetCheck(true);	
}

void CComConf::OnCancel2() 

{
	CString helpfile(appdir);
	helpfile += "html\\";	helpfile += "keystrokes.html";

	//AP2N("CWavfragApp::WinHelp %s\r\n", helpfile);

	ShellExecute(NULL, "open", helpfile, NULL, NULL, SW_SHOWNORMAL);	

}
