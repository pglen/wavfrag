
/* =====[ FragCollTab.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the FragCollTab.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/24/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"

#include <process.h>
#include <direct.h>
#include <io.h>


#include "wavfrag.h"
#include "wavfragDlg.h"
#include "FragCollTab.h"

#include "FileDialogST.h"

#include "GetText.h"
#include "mxpad.h"

// Simplify cast to parent window
#define PARENT ((CWavfragDlg*)GetParent())

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char wavfilter[] =
		"Wave Files (*.wav)\0*.wav\0All Files\0*.*\0\0" ;

/////////////////////////////////////////////////////////////////////////////
// CFragCollTab dialog


CFragCollTab::CFragCollTab(CWnd* pParent /*=NULL*/)
	: CDialog(CFragCollTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFragCollTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	stop_train = in_train = 0;
}


void CFragCollTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFragCollTab)
	DDX_Control(pDX, IDC_COMBO1, m_words);
	DDX_Control(pDX, IDC_LIST3, m_coll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFragCollTab, CDialog)
	//{{AFX_MSG_MAP(CFragCollTab)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON35, OnButton35)
	ON_BN_CLICKED(IDC_BUTTON25, OnButton25)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON29, OnButton29)
	ON_BN_CLICKED(IDC_BUTTON26, OnButton26)
	ON_BN_CLICKED(IDC_BUTTON31, OnButton31)
	ON_BN_CLICKED(IDC_BUTTON33, OnButton33)
	ON_BN_CLICKED(IDC_BUTTON34, OnButton34)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON27, OnButton27)
	//ON_BN_CLICKED(IDC_BUTTON32, OnButton32)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFragCollTab message handlers

void CFragCollTab::OnButton21() 

{
	CGetText gt; gt.m_title = "Enter a word / phrase to train";
	
	int oldrec = WFL_WaveIsRec();

	PARENT->StopRec();

	// Pre fill 
	int idx = m_coll.GetCurSel();
	if(idx >= 0)
		{
		m_coll.GetText(idx, gt.m_edit);
		}

	if(gt.DoModal() == IDCANCEL)
		{
		if(oldrec)
			PARENT->StartRec();
		return;
		}

	WFL_SetTrainStr(gt.m_edit);	

	CString tmp; 
	if(gt.m_edit == "")
		{
		tmp.Format("Switched to recognition");
		}
	else
		{
		tmp.Format("Training '%s'", gt.m_edit);

		if(m_coll.FindString(0, gt.m_edit) == LB_ERR)
			{
			m_coll.AddString(gt.m_edit);
			}
		}

	PARENT->GetPick()->SetText(tmp);
	
	if(oldrec)
		PARENT->StartRec();

}

//////////////////////////////////////////////////////////////////////////
// Fill in listbox

void CFragCollTab::LoadData() 

{
	CString tmp; char *collstr = tmp.GetBuffer(_MAX_PATH + 1); 
	
	int idx3 = 0, ret3 = 0;
	while(true)
		{
		ret3 = WFL_GetCollName(idx3++, collstr, _MAX_PATH);

		if(ret3 < 0)
			break;

//		if(ret3 > sizeof(collstr))
//			{
//			AP2N("WFL_GetCollName needs bigger buffer %s\r\n", collstr);
//			}

		m_coll.AddString(collstr);
		}
}

void CFragCollTab::OnButton35() 

{
	WFL_SetTrainStr("");

	CString tmp; tmp.Format("Switched to recognition");
	PARENT->GetPick()->SetText(tmp);	
}

void CFragCollTab::OnButton25() 
{
	//AP2N("CWavfragDlg::OnButton25\r\n");

	if(in_train)
		{
		//m_b25.SetWindowText("Stopping");
		stop_train = true;
		return;
		}

	CFileDialogST  cdf(true);

	CString droot, dresult, lresult;
	CString wavdir(appdata); wavdir += "wavdic";
	
	cdf.m_ofn.lpstrInitialDir = wavdir;
	cdf.m_ofn.lpstrFilter	= wavfilter;
	cdf.m_ofn.nFilterIndex	= 1;
	cdf.m_ofn.Flags |=  OFN_EXPLORER;

	int ret = cdf.DoModal();

	if(ret != IDOK)
		return;

	CString oldface; //m_b25.GetWindowText(oldface);
	in_train = true;
	//m_b25.SetWindowText("Stop");
	
	CString strdir = cdf.GetFileDir();

	char	olddir[_MAX_PATH]; getcwd(olddir, sizeof(olddir));

	if(chdir(strdir) < 0)
		{
		CString tmp; tmp.Format("CWavfragDlg: Cannot load waves from '%s'", strdir);
		AP2N("%s\r\n", tmp);
		AfxMessageBox(tmp);
		return;
		}

	WFL_SetWavCallback(NULL);	

	struct _finddata_t c_file;
    long hFile;

	if( (hFile = _findfirst("*.wav", &c_file )) >= 0)
		{
		int cnt = 0;
		while(true)
			{
			//AP2N( " %-12s %.24s  %9ld\r\n",
			//	c_file.name, ctime( &( c_file.time_write ) ), c_file.size );

			//xTrainString(c_file.name);

			if( _findnext( hFile, &c_file ) != 0 )
				break;

			if(stop_train)
				break;

			cnt++;
			}
		_findclose( hFile );
		}
	
	chdir(olddir);

	//WFL_SetWavCallback(_staticWavFromRec);	

	in_train = false;
	//m_b25.SetWindowText(oldface);	

	PARENT->GetPick()->SetWindowText("Done training");
	support.YieldToWinEx();	
}

//////////////////////////////////////////////////////////////////////////

void CFragCollTab::OnButton11() 
{
	int idx = m_coll.GetCurSel();
	if(idx < 0)
		{
		AfxMessageBox("Please select a word first");
		return;
		}

	int idx2 = m_words.GetCurSel();
	if(idx2 < 0)
		{
		AfxMessageBox("Please select an item first");
		return;
		}

	CString str; m_coll.GetText(idx, str);
	CString str2; m_words.GetLBText(idx, str2);

	CString tmp; char *collstr = tmp.GetBuffer(_MAX_PATH + 1); 
	
	WFL_GetCollStr(idx, idx2, collstr, _MAX_PATH);

	AfxMessageBox(collstr);	
}

void CFragCollTab::OnButton29() 
{
	int idx = m_coll.GetCurSel();

	if(idx < 0)
		{
		AfxMessageBox("Please select a word to clear");
		return;
		}
	
	CString str; m_coll.GetText(idx, str);

	//AP2N("Deleteing collection under %s\r\n", str);

	CString tmp; 
	tmp.Format("This will clear all items for '%s'. Are you sure?",
			str);
		
	int ret = AfxMessageBox(tmp, MB_YESNO);

	if(ret != IDYES)
		return;

	WFL_ClearTraining(str);	
	
	// Fill in collections box
	m_coll.ResetContent();

	CString tmps; char *collstr = tmps.GetBuffer(_MAX_PATH + 1); 
	int idx3 = 0, ret3 = 0;
	while(true)
		{
		ret3 = WFL_GetCollName(idx3++, collstr, _MAX_PATH);

		if(ret3 < 0)
			break;

		m_coll.AddString(collstr);
		}	
}

//////////////////////////////////////////////////////////////////////////

void CFragCollTab::OnButton26() 
{
	int idx = m_coll.GetCurSel();
	if(idx < 0)
		{
		AfxMessageBox("Please select a word first");
		return;
		}

	int idx2 = m_words.GetCurSel();
	if(idx2 < 0)
		{
		AfxMessageBox("Please select an entry first");
		return;
		}

	CString str;  m_coll.GetText(idx, str);
	CString str2; m_words.GetLBText(idx2, str2);

	// Clear the word
	WFL_ClearTrainItem(str, str2);

	m_words.ResetContent();

	// Fill in combo
	CString tmps; char *collstr = tmps.GetBuffer(_MAX_PATH + 1); 
	int idx3 = 0, ret3 = 0;
	while(true)
		{
		int ret3 = WFL_GetCollStr(idx, idx3++, collstr, _MAX_PATH);

		if(ret3 < 0)
			break;
				
		if(ret3 > sizeof(collstr))
			{
			AP2N("WFL_GetCollName needs bigger buffer %d\r\n", ret3);
			}

		//AP2N("collstr='%s'\r\n", collstr);

		m_words.AddString(collstr);
		}	
}

//////////////////////////////////////////////////////////////////////////

void CFragCollTab::OnButton31() 

{
	WINDOWPLACEMENT wp; PARENT->plotdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->plotdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->plotdlg.ShowWindow(SW_RESTORE);		
}

//////////////////////////////////////////////////////////////////////////

void CFragCollTab::OnButton33() 

{
	WINDOWPLACEMENT wp; PARENT->visdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->visdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->visdlg.ShowWindow(SW_RESTORE);	
}

void CFragCollTab::OnButton34() 
{
	WINDOWPLACEMENT wp; PARENT->wavdlg.GetWindowPlacement(&wp);

	if(wp.showCmd == SW_SHOWNORMAL)
		PARENT->wavdlg.ShowWindow(SW_MINIMIZE);
	else
		PARENT->wavdlg.ShowWindow(SW_RESTORE);		
}

void CFragCollTab::OnButton22() 
{
	
}

void CFragCollTab::OnButton27() 
{
	
}

void CFragCollTab::OnButton32() 
{
	// TODO: Add your control notification handler code here
	
}

//////////////////////////////////////////////////////////////////////////

void CFragCollTab::OnSelchangeList3() 

{
	//AP2N("CFragCollTab::OnSelchangeList3 Selchange\r\n");

	int idx = m_coll.GetCurSel();
	if(idx < 0)
		{
		return;
		}

	PARENT->Busy(true);

	CString str; m_coll.GetText(idx, str);

	CString str2; str2.Format("Train as '%s'", str);
	//m_tb2.SetWindowText(str2);

	CString str3; str3.Format(
		"Will train the currently selected word with the recording\r\n"
			"that is displayed in the wave editor.\r\n\r\n"
			"Word that will be trained: '%s'", str);

	//m_tb2.SetTooltip(str3);
	
	m_words.ResetContent();

	//m_words.ShowScrollBar(SB_BOTH);

	// Fill in combo
	char collstr[512]; int idx3 = 0, ret3 = 0;
	while(true)
		{
		int ret3 = WFL_GetCollStr(idx, idx3++, collstr, sizeof(collstr));

		if(ret3 < 0)
			break;
				
		if(ret3 > sizeof(collstr))
			{
			AP2N("WFL_GetCollName needs bigger buffer %d\r\n", ret3);
			}

		AP2N("collstr='%s'\r\n", collstr);

		m_words.AddString(collstr);
		PARENT->GetWordsCombo()->AddString(collstr);
		}

	PARENT->Busy(false);

	AP2N("CWavfragDlg::OnSelchangeList3 %s\r\n", str);	

}

void CFragCollTab::OnSelchangeCombo1() 
{
	AP2N("CFragCollTab::OnSelchangeCombo1\r\n");	
}
