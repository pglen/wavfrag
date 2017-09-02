
/* =====[ Phonames.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Phonames.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/21/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// Phonames.cpp : implementation file
//

#include "stdafx.h"
#include "wavfrag.h"
#include "Phonames.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhonames dialog

static char help[] = "\
\r\n\
Phoneme      Example      Translation             Samples                 Category\r\n\
\r\n\
AA            CAT         CC AA TT                flat, mat               Monophthong\r\n\
AH            SAW         SS AH WW                caught, tall            Monophthong\r\n\
AI            HAIR        HH AI RR                air, where\r\n\
AR            ARGUE       AR RR GG UW             aunt, car               Monophthong\r\n\
AY            TABLE       TT AY BB LL             bake, train, say        Diphthongs\r\n\
\r\n\
BB            BABY        BB AY BB II             ball, bow, buy, bay     Stop\r\n\
\r\n\
CC            CAKE        CC AY KK                key, carot              Stop\r\n\
CH            CHEESE      CH EE ZZ                child, chair, chest     Affricate\r\n\
CK            BACK        BB AA CK                racket\r\n\
\r\n\
DD            DISC        DD II SS KK             door, day\r\n\
DH            FATHER      FF AH DH ER             gather, father          Fricative\r\n\
\r\n\
EA            HEAD        H EA DD                 pet, red                Monophthong\r\n\
EE            FEET        FF EE TT                meet, creep             Monophthong\r\n\
EH            EVIL        EH VV AH LL             enough, erase\r\n\
ER            HURT        HH ER T                 her, bird, nurse        Monophthong\r\n\
\r\n\
FF            FOOL        FF UU LL                free, fry               Fricative\r\n\
GG            GREEN       GG RR EE NN             girl, go, gas           Stop\r\n\
HH            HOT         HH OH TT                hill, house             Fricative\r\n\
\r\n\
II            HILL        HH II LL                ill, pin                Monophthong\r\n\
IY            HIDE        HH IY DD                bite, pride             Monophthong\r\n\
\r\n\
JJ            BRIDGE      BB RR II DD JJ          jeep, just, gym         Affricate\r\n\
\r\n\
"
"\
KN            KNOCK       KN OO CK                knot, knife\r\n\
KW            QUICK       KW II CK                quiet\r\n\
KS            SIX         SS II KS                rocks,\r\n\
\r\n\
LL            LAMP        LL AA MM PP             lazy, loose             Liquid\r\n\
\r\n\
MM            MEDIA       MM EH DD II AH          my, kistery             Nasal\r\n\
NG            PING        PP II NG                lung, sing\r\n\
NN            NEED        NN EE DD                nothing                 Nasal\r\n\
\r\n\
"
"\
OH            BOX         BB OH XX                pot, dot, box           Monophthong\r\n\
OO            OKAY        OO KK AY                oven, bone\r\n\
OW            COW         KK OW                   flower,                 Monophthong\r\n\
OY            TOY         TT OY                   soil, boil, low         Monophthong\r\n\
PP            PIE         PP IY                   pee, pay                Stop\r\n\
QQ            QUIT        QQ UU II TT             queue,\r\n\
RR            READ        RR EE DD                roar                    Liquid\r\n\
\r\n\
SH            SHE         SH II                   ship, nation, special   Fricative\r\n\
SS            SEA         SS EE                   soup,                   Fricative\r\n\
\r\n\
TT            TEA         TT EE                   take, tow               Stop\r\n\
TH            THICK       TH II CK                three, thrue            Fricative\r\n\
\r\n\
UH            HUT         HH UH TT                utter, undo\r\n\
UR            FUR         FF UR                   bird, urgent\r\n\
UU            HOOD        HH UU DD                cure, boot, chew\r\n\
UW            FEW         FF UW\r\n\
\r\n\
VV            VERIFY      VV EH RR II FF YY       vehicle, vase\r\n\
\r\n\
WH            WHITE       WH IY TT                wheat, which\r\n\
WW            WEB         WW EH BB                want, will, wash        Semivowel\r\n\
\r\n\
XX            EXAM        SS II XX                external, exist\r\n\
\r\n\
YY            YIELD       YY IY LL DD             yellow, yes             Semivowel\r\n\
\r\n\
ZH            SEIZURE     SS IY ZH ER             measure\r\n\
ZZ            ZOO         ZZ UU                   zorro, zero, nose\r\n\
\r\n\
";




CPhonames::CPhonames(CWnd* pParent /*=NULL*/)
	: CDialog(CPhonames::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhonames)
	//}}AFX_DATA_INIT

	::GetObject((HFONT)GetStockObject(ANSI_FIXED_FONT),sizeof(m_lf),&m_lf);
	m_font.CreateFontIndirect(&m_lf);
}


void CPhonames::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhonames)
	//DDX_Control(pDX, IDC_4D, m_4d);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPhonames, CDialog)
	//{{AFX_MSG_MAP(CPhonames)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhonames message handlers

BOOL CPhonames::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_edit.SetFont(&m_font);
	m_edit.SetWindowText(help);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPhonames::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	m_edit.SetSel(-1, 0);
		
}
