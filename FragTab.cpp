
/* =====[ FragTab.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the FragTab.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/22/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "wavfragDlg.h"

#include "FragTab.h"
#include "GetText.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Simplify cast to parent window
#define PARENT ((CWavfragDlg*)GetParent())

/////////////////////////////////////////////////////////////////////////////
// CFragTab dialog


CFragTab::CFragTab(CWnd* pParent /*=NULL*/)
	: CDialog(CFragTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFragTab)
	//}}AFX_DATA_INIT

	b6_reenter = false;
}


void CFragTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFragTab)
	DDX_Control(pDX, IDC_BUTTON4, m_play);
	DDX_Control(pDX, IDC_BUTTON2, m_loadall);
	DDX_Control(pDX, IDC_BUTTON19, m_delwav);
	DDX_Control(pDX, IDC_BUTTON18, m_del);
	DDX_Control(pDX, IDC_BUTTON6, m_reload);
	DDX_Control(pDX, IDC_BUTTON8, m_new);
	DDX_Control(pDX, IDC_CURRSP, m_currsp);
	DDX_Control(pDX, IDC_COMBO4, m_users);
	DDX_Control(pDX, IDC_BUTTON12, m_tb);
	DDX_Control(pDX, IDC_COMBO5, m_currw);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFragTab, CDialog)
	//{{AFX_MSG_MAP(CFragTab)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_CBN_SELCHANGE(IDC_COMBO5, OnSelchangeCombo5)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFragTab message handlers

BOOL CFragTab::OnInitDialog() 

{
	//CRect rc; GetClientRect(rc);
	//m_tl.Create(WS_CHILD, rc, this, IDC_LIST2);
	//tl.Create(IDC_LIST2);
	
	m_tl.SubclassDlgItem(IDC_LIST2, this);
	
	CDialog::OnInitDialog();

	//AP2N("CFragTab::OnInitDialog\r\n");

	m_new.SetTooltip(	"Create a new frag, (or uttering / phoneme) by giving it a name.\r\n"
						"It is practical (but not nessessary) to give it a name that is the actual frag\r\n"
						"Please only use characters that are file name clean. (no '\\' no ':')\r\n"
						"The newly created entry is blank. With the recording on,\r\n"
						"pronouce the desired word to train, select frag portion. When satisfied with\r\n"
						"the current uttering, click on the 'Train' button.\r\n"
						"There is no limit to the number of frags that can be trained.\r\n"
						"Shortcut key Alt-N");

	m_reload.SetTooltip("Reload ALL Wave Files and generate new Frags.\r\n"
				"Will re-create the wavfrag list from the wave files found in the \r\n"
				"'Stock' directory. Dependent of the amount of trained items,\r\n"
				"this operation will take some time. If the regeneration process\r\n"
				"is interrupted, it needs to be re done at a future time.\r\n"
				"This button will ask for Yes/No confirmation.");

	m_del.tip.bgcolor = RGB(0xff, 0xee, 0xee);
	m_del.SetTooltip(	"Delete selected frag and ALL its waves from the recognition engine.\r\n" 
						"Deleted entries cannot be recovered, but can be easily\r\n"
						"re-created and re-trained.\r\n"
						"This button will ask for Yes/No confirmation.");


	m_tb.SetTooltip("Will train the currently selected frag with the recording\r\n"
				"selection that is displayed in the wave editor. If nothing\r\n"
				"is selected, the whole wave is trained.");

	m_delwav.tip.bgcolor = RGB(0xff, 0xee, 0xee);
	m_delwav.SetTooltip("Delete selected wave from the list of active frags.\r\n"
						"The selected wave from the currently selected frag will be deleted.\r\n"
						"This is particularitly useful for deleting errorneous training items\r\n"
						"Deleted entries cannot be recovered, but can be easily\r\n"
						"re-created and re-trained.\r\n"
						"This button will ask for Yes/No confirmation.");

	m_play.SetTooltip("Play currently displayed wave.\r\n"
						"If no sound is loaded, the wave editor will\r\n"
						"flash for a brief moment with an approriate message.\r\n"
						"Shortcut key Alt-A");

	//SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////
// Add loaded frags to listbox

void CFragTab::xLoadData()

{
	//AP2N("CFragTab::xLoadData()\r\n");
	xFillUserCombo(); xFillFragCombo(); xFillCurrUser();
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnSelchangeList2() 

{
	int idx = m_tl.GetCurSel();
	if(idx < 0)
		{
		return;
		}

	CString str; m_tl.GetText(idx, str);

	CString str2; str2.Format("&Train wav selection as '%s'", str);
	m_tb.SetWindowText(str2);

	CString str3; str3.Format(
		"Will train the currently selected word with the recording\r\n"
			"that is displayed in the wave editor.\r\n\r\n"
			"Word that will be trained: '%s'\r\n\r\n"
			"Shortcut key to train this word: Alt-T", str);

	m_tb.SetTooltip(str3);

	m_currw.ResetContent();

	CString tmps; char *chstr = tmps.GetBuffer(_MAX_PATH + 1); 
	int xidx = 0;
	while(true)
		{
		int	ret = WFL_GetFragEntry(str, xidx++, chstr, _MAX_PATH);

		if(ret < 0)
			break;

		m_currw.AddString(chstr);
		}
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnButton1() 

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
		OnSelchangeCombo4();
		}
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnButton8() 

{
	CGetText gt; gt.m_title = "Enter new frag to add to current speaker's frag collection";

	if(gt.DoModal() == IDCANCEL)
		return;

	if(gt.m_edit == "")
		return;

	// Is it a duplicate?

	for(int loop = 0; loop < m_tl.GetCount(); loop++)
		{
		CString str; m_tl.GetText(loop, str);
		//AP2N("%s\r\n", str);

		if(str.CompareNoCase(gt.m_edit) == 0)
			{
			AfxMessageBox("Frag already exist, cannot add.");
			return;
			}
		}

	int idx = m_tl.AddString(gt.m_edit);

	//m_tl.SetCheck(idx, 1);
	m_tl.SetCurSel(idx);

	OnSelchangeList2();	
}

void CFragTab::OnButton18() 
{
	//reso.DumpSine(&plotdlg.m_plot1);	

	int idx = m_tl.GetCurSel();

	if(idx < 0)
		{
		AfxMessageBox("Please select a frag to delete");
		return;
		}

	CString str; m_tl.GetText(idx, str);
	CString tmp; tmp.Format("Are you sure you want to delete the frag: '%s'", str);

	if(AfxMessageBox(tmp, MB_YESNO) != IDYES)
		return;

	WFL_DelFragWord(str);
	m_tl.DeleteString(idx);	
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnButton6() 

{
	if(b6_reenter)
		{
		//AP2N("CFragTab::OnButton6 reentry\r\n");
		
		WFL_StopCompile();
		PARENT->ChangeTab(0);
		PARENT->Busy(false);
	
		PARENT->GetLogWin()->printf("Load aborted, frag collextion may be incomplete.\r\n");
		PARENT->GetLogWin()->printf("Reload frags at a later time.\r\n");
		return;
		}

	int ret = AfxMessageBox(
			"Reloading frags might take a minute or two. Are you sure?",
			MB_YESNO);

	if(ret != IDYES)
		return;

	int oldrec = WFL_WaveIsRec();

	PARENT->StopRec();

	b6_reenter = true;
	
	PARENT->Busy(true);
	PARENT->ChangeTab(4);
	
	PARENT->GetPick()->SetText("Parsing Frags ..."); support.YieldToWinEx();

	CString oldtext; m_reload.GetWindowText(oldtext);
	m_reload.SetWindowText("Stop Reload");
	
	//WFL_SetReload(true);

	//int ret2 = WFL_ParseAllFragWaves();
	//AP2N("Parsed %d frags\r\n", ret2);
				
	// Disable callback for now
	//WFL_SetSpectCallback(NULL);

	PARENT->GetPick()->SetText("Loading Frags ..."); support.YieldToWinEx();

	//int ret3 = WFL_LoadAllFrags();

	int ret3 =  WFL_CompileFrags();

	//AP2N("Loaded %d frags\r\n", ret3);
	
	// Restore it
	WFL_SetSpectCallback(PARENT->_staticSpectFromRec);

	m_reload.SetWindowText(oldtext);
	
	xLoadData();

	PARENT->Busy(false);
	PARENT->ChangeTab(0);

	// Re-scan dialog
	support.YieldToWinEx();
	xFillFragCombo();


	if(oldrec)
		PARENT->StartRec();

	b6_reenter = false;	
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnButton20() 

{
	int idx = m_users.GetCurSel();

	if(idx < 0)
		return;

	CString str; m_users.GetLBText(idx, str);

	if(str == "default")
		{
		AfxMessageBox("Cannot delete default user");
		return;
		}

	CString tmp; tmp.Format("Are you sure you want to delete '%s' and all the speaker's frags?", str);

	if(AfxMessageBox(tmp, MB_YESNO) != IDYES)
		return;

	WFL_DelFragSpeaker(str);
	
	xFillUserCombo() ;
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::xFillUserCombo() 

{
#if 0
	m_users.ResetContent();

	CString tmps; char *str = tmps.GetBuffer(_MAX_PATH); 
	int cnt = 0;
	while(true)
		{
		int  ret =   WFL_GetFragSpeaker(cnt++, str, _MAX_PATH + 1);

		if(ret < 0)
			break;

		m_users.AddString(str);
		}	
#endif
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::xFillFragCombo() 

{
	int idxs = 0; 

	AP2N("void CFragTab::xFillFragCombo() \r\n");

	m_tl.ResetContent();

	CString tmps; char *strx = tmps.GetBuffer(_MAX_PATH + 1); 

	while(true)
		{
		int ret = WFL_GetFragStr(idxs++, strx, _MAX_PATH );
		
		if(ret < 0)
			break;

		AP2N("CFragTab::xFillFragCombo %s\r\n", strx);

		m_tl.AddString(strx);
		}
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnSelchangeCombo4() 

{
	int idx = m_users.GetCurSel();
	
	if(idx < 0)
		return;

	CString str; m_users.GetLBText(idx, str);
	WFL_SetCurrSpeaker(str);
	
	xLoadData();
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::UserChanged(const char *str) 

{		
	xLoadData();
}


//////////////////////////////////////////////////////////////////////////

void CFragTab::OnButton12() 
{
	int idx = m_tl.GetCurSel();

	if(idx < 0)
		{
		AfxMessageBox("Please select a word to train.");
		return;
		}

	CString str; m_tl.GetText(idx, str);
	
	PARENT->GetWavEdit()->ZeroCross();

	char *buff; int len;
	PARENT->GetWavEdit()->GetSelBuff(&buff, &len);

	if(!buff || !len)
		{
		AfxMessageBox("No recording in wav edit window.");
		return;
		}
		
	PARENT->Busy(true);
	int ret = WFL_SaveWavAndFrag(str, buff, len);
	PARENT->Busy(false);
		
	if(ret < 0)
		{
		CString tmp2; tmp2.Format("Cannot save: %s", str);
		PARENT->GetPick()->SetText(tmp2);
		}
	else
		{
		//AP2N("Learning added under %s\r\n", str);
	
		CString tmp2; tmp2.Format("Learned: %s", str);
		PARENT->GetPick()->SetText(tmp2);
		}

	OnSelchangeList2();	
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnButton19() 

{
	int idx = m_tl.GetCurSel();
	if(idx < 0)
		{
		AfxMessageBox("Please select a wav to delete");
		return;
		}

	CString str; m_tl.GetText(idx, str);

	int idx2 = m_currw.GetCurSel();

	if(idx2 < 0)
		{
		return;
		}

	CString str2; m_currw.GetLBText(idx2, str2);

	CString tmp; tmp.Format("Are you sure you want to delete the entry:\r\n"
			"'%s / %s'", str, str2);

	if(AfxMessageBox(tmp, MB_YESNO) != IDYES)
		return;

	//AP2N("w=%s f-%s\r\n", str, str2);

	int ret = WFL_DelFragEntry(str, str2);

	if(ret >= 1)
		{
		m_currw.DeleteString(idx2);
		}

	if(ret == 2)
		{
		m_tl.DeleteString(idx);
		}

	// Select prev item
	idx2 = max(idx2 - 1, 0);
	m_currw.SetCurSel(idx2);
	m_currw.SetFocus();

	//OnSelchangeCombo5();	
}

//////////////////////////////////////////////////////////////////////////

	

void CFragTab::OnButton2() 

{	
#if 0
	int ret = AfxMessageBox(
			"This will clear frag directory, operation cannot be undone. Are you sure?",
			MB_YESNO);

	if(ret != IDYES)
		return;
#endif


	static CStringArray sarr;
	static CPtrArray parr;

	//AP2N("Size =  %d size2= %d\r\n", sarr.GetSize(), parr.GetSize());

	sarr.Add("hello");
	CString str = sarr.GetAt(0);
	//AP2N("sarr[0] %s\r\n", str);
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::xFillCurrUser() 

{
	CString tmps; char *curr = tmps.GetBuffer(_MAX_PATH + 1); 
	int	ret2 = WFL_GetCurrSpeaker(curr, _MAX_PATH);
	m_currsp.SetWindowText(curr);

	m_users.SelectString(0, curr);
}

void CFragTab::OnButton4() 

{
	PARENT->GetWavEdit()->PlayBuff();
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnSelchangeCombo5() 

{
	int idx = m_currw.GetCurSel();

	if(idx < 0)
		{
		return;
		}
	
	CString stdir;  
	
	CString tmpd; char *wavdir = tmpd.GetBuffer(_MAX_PATH + 1); 
	WFL_GetWavDir(wavdir, _MAX_PATH); 
	tmpd.ReleaseBuffer();	
	
	stdir += wavdir;	
	
	CString strusr; char *currsp = strusr.GetBuffer(_MAX_PATH + 1); 
	int	ret2 = WFL_GetCurrSpeaker(currsp, _MAX_PATH); 
	strusr.ReleaseBuffer();
	
	if(strusr != "default") 
		{
		stdir += strusr; stdir += "\\";
		}
	
	CString str; m_currw.GetLBText(idx, str);
	stdir += str;  stdir += ".wav";
		
	//AP2N("CFragTab::OnSelchangeCombo5 %s\r\n", stdir);

	PARENT->GetWavEdit()->OpenWave(stdir, false);	
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::OnTimer(UINT nIDEvent) 

{
	KillTimer(nIDEvent);

	switch(nIDEvent)
		{
		case 1:
			//AP2N("CFragTab::OnTimer(UINT nIDEvent) \r\n");		
			break;
		}
	
	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////

void CFragTab::InitCombos() 

{
	//xFillUserCombo();
	//m_users.SelectString(0, "default");
	//OnSelchangeCombo4();
}
