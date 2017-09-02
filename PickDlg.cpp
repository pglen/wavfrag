
/* =====[ PickDlg.cpp ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the PickDlg.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/9/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include <direct.h>

#include "wavfrag.h"
#include "wavfragdlg.h"
#include "mxpad.h"

#include "support.h"
#include "PickDlg.h"
#include "FreqScan.h"
#include "bend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPickDlg dialog


CPickDlg::CPickDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPickDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPickDlg)
	//}}AFX_DATA_INIT
}

void CPickDlg::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPickDlg)
	DDX_Control(pDX, IDC_PICK5, m_vis5);
	DDX_Control(pDX, IDC_PICK4, m_vis4);
	DDX_Control(pDX, IDC_PICK3, m_vis3);
	DDX_Control(pDX, IDC_PICK2, m_vis2);
	DDX_Control(pDX, IDC_WAV4, m_wav4);
	DDX_Control(pDX, IDC_SINGLE2, m_sin2);
	DDX_Control(pDX, IDC_SINGLE, m_sin);
	DDX_Control(pDX, IDC_SEL, m_sel);
	DDX_Control(pDX, IDC_PLOT, m_plot);
	DDX_Control(pDX, IDC_WAV, m_wav);
	DDX_Control(pDX, IDC_WAV5, m_wav2);
	DDX_Control(pDX, IDC_WAV3, m_wav3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPickDlg, CDialog)
	//{{AFX_MSG_MAP(CPickDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON38, OnButton38)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON40, OnButton40)
	ON_BN_CLICKED(IDC_BUTTON41, OnButton41)
	ON_BN_CLICKED(IDC_BUTTON42, OnButton42)
	ON_BN_CLICKED(IDC_BUTTON43, OnButton43)
	ON_BN_CLICKED(IDC_BUTTON45, OnButton45)
	ON_BN_CLICKED(IDC_BUTTON47, OnButton47)
	ON_BN_CLICKED(IDC_BUTTON48, OnButton48)
	//ON_BN_CLICKED(IDC_BUTTON51, OnButton51)
	//ON_BN_CLICKED(IDC_BUTTON52, OnButton52)
	//ON_BN_CLICKED(IDC_BUTTON53, OnButton53)
	ON_BN_CLICKED(IDC_BUTTON54, OnButton54)
	ON_BN_CLICKED(IDC_BUTTON55, OnButton55)
	ON_BN_CLICKED(IDC_BUTTON56, OnButton56)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPickDlg message handlers

void CPickDlg::OnDestroy() 

{
	CleanBig(); CleanSmall();
	CDialog::OnDestroy();	
}


BOOL CPickDlg::PreTranslateMessage(MSG* pMsg) 

{
	if(pMsg->message == WM_USER)
		{

#if 0
		CRect rc;	m_wav.GetClientRect(rc);
		int len	= m_picker.GetArrLen();
			
		if(len)
			{
			int  ssel = LOWORD(pMsg->lParam);
			int  esel = HIWORD(pMsg->lParam);

			// Note the image scaling factor of 2
			double fact = (double)rc.Width() / (len * 2);
			
			//AP2N("CPickDlg::PreTranslateMessage WM_USER %d %d len=%d\r\n",
			//					pMsg->wParam, pMsg->lParam, len);

			m_wav.SetSel((int)(fact * ssel), int(fact * esel));

			int start = ssel / 2;
			int end = esel / 2;

			start = max(start, 0);
			end = min(end, m_picker.arr.GetSize());

			//m_3d.arr.RemoveAll();
			//for(int loop = start; loop < end; loop++)
			//	{
			//	m_3d.AddIntArr((CIntArr*)m_picker.arr.GetAt(loop));
			//	}
			}
#endif

		}

	if(pMsg->message == WM_USER + 1)
		{
		m_wav.PlayBuff();
		}

	if(pMsg->message == WM_USER + 2)
		{
		char *buff; int len;

		//AP2N("CPickDlg::PreTranslateMessage WM_USER 2 %d %d\r\n",
		//						pMsg->wParam, pMsg->lParam);
#if 0
		CRect rc;	m_wav.GetClientRect(rc);
		int len	= m_picker.GetArrLen();
		
		//if(len)
			{
			int  ssel = LOWORD(pMsg->lParam);
			int  esel = HIWORD(pMsg->lParam);

			if(pMsg->wParam == (unsigned int)m_wav.m_hWnd)
				{
				//AP2N("m_wav m_hwnd=%p %p ssel=%d esel=%d\r\n", 
				//				pMsg->wParam, m_wav.m_hWnd, ssel, esel);
			
				// Note the image scaling factor of 2
				double fact = (double)len / rc.Width();
				//fact *= 2;
			
				//m_picker.SetSel( (int)(fact * ssel), 
				//					(int)(fact * esel), TRUE );
				//OnButton45();
				}
			}
#endif
			if(pMsg->wParam == (unsigned int)m_wav2.m_hWnd)
				{
				//AP2N("m_wav2 m_hwnd=%p %p ssel=%d esel=%d\r\n", 
				//				pMsg->wParam, m_wav.m_hWnd, ssel, esel);			

				m_wav3.GetSelBuff(&buff, &len);
				m_wav4.SetBuff(buff, len); 
				}

			if(pMsg->wParam == (unsigned int)m_wav3.m_hWnd)
				{
				//AP2N("m_wav3 m_hwnd=%p %p ssel=%d esel=%d\r\n", 
				//				pMsg->wParam, m_wav.m_hWnd, ssel, esel);
					
				m_wav3.GetSelBuff(&buff, &len);
				m_wav4.SetBuff(buff, len); 
				}

			if(pMsg->wParam == (unsigned int)m_wav.m_hWnd)
				{
				//AP2N("m_wav m_hwnd=%p %p ssel=%d esel=%d\r\n", 
				//				pMsg->wParam, m_wav.m_hWnd, ssel, esel);			

				m_wav.GetSelBuff(&buff, &len);				
				m_wav4.SetBuff(buff, len); 

				ScanBigPart();
				}
		}

	if(pMsg->message == WM_USER + 3)
		{
		//P2N("Loaded new file into wave editor %s\r\n", (char*)pMsg->lParam);

		if(pMsg->wParam == (unsigned int)m_wav.m_hWnd)
			{
			OnButton52();
			}		

		if(pMsg->wParam == (unsigned int)m_wav3.m_hWnd)
			{
			ScanSmall();
			}
		}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CPickDlg::OnInitDialog() 

{
	CDialog::OnInitDialog();
	
	AP2N("CPickDlg::OnInitDialog\r\n");
	
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	//m_wav.sendmsg = true;
	m_wav.pplaysnd = &pwnd->playsound;
	m_wav2.pplaysnd = &pwnd->playsound;
	m_wav3.pplaysnd = &pwnd->playsound;
	
	CString strdir = appdir;
	strdir += "\\num";

	AP2N("strdir=%s\r\n", strdir);

	_chdir(strdir);
		
	// Pre -scan wave
	//OnButton52();
	//ScanSmall();

	//OnButton55(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton38() 

{
	m_wav.SaveWave("");
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton2() 

{
	//AP2N("Bend Compare\r\n");

	m_plot.ClearAll();
	m_sin2.ClearAll();

	AP2N("darrbig %d darrsmall %d\r\n", darrbig.GetSize(), darrsmall.GetSize());

		int alen = darrbig.GetSize();
		int slen = darrsmall.GetSize();

	int  maxval = 0;
	for(int loops = 0; loops < slen; loops++)
		{
		int val = abs(darrsmall.GetAt(loops));
		maxval = max(maxval, val);
		}
		
	//double factor = (double)SHRT_MAX / maxval;
	//for(int loops2 = 0; loops2 < slen; loops2++)
	//	{
	//	int val = factor * darrsmall.GetAt(loops2);
	//	darrsmall.SetAt(loops2, val);
	//	}
	//maxval = SHRT_MAX;
	//darrsmall.Plot(&m_sin2);

	//////////////////////////////////////////////////////////////////////

	for(int loop = 0; loop < alen - slen; loop++)
		{
		int sum = 0;

		int  maxval2 = 0;
		for(int loops2 = 0; loops2 < slen; loops2++)
			{
			int val = abs(darrbig.GetAt(loop + loops2));
			maxval2 = max(maxval2, val);
			}
		
		for(int loop2 = 0; loop2 < slen; loop2++)
			{
			int val = (darrbig.GetAt(loop + loop2));
			int val2 = (darrsmall.GetAt(loop2));

			// Adjust for norm
			val2 *= maxval; val2 /= maxval2;
			sum += abs(val - val2);
			}

		//sum *= 100; 
		sum /= slen;

		//m_plot.AddLine(sum);
 		}
}

//////////////////////////////////////////////////////////////////////////
//

double CPickDlg::CmpArray(int *skip, CPtrArray *parr, CPtrArray *big)

{
	double diff = 0;

	int myskip = *skip;
	
	int alen = big->GetSize(), blen = parr->GetSize();
	int clen = min(alen, blen);

	if(myskip + parr->GetSize() >= big->GetSize())
		clen =  big->GetSize() - myskip;
	
	//Fuzzy fuzzy;

	////////////////////////////////////////////////////////////////
	for(int loopx = 0; loopx < clen; loopx++)	
		{
		CIntArr *curr1 = (CIntArr*)parr->GetAt(loopx);
		CIntArr *curr2 = (CIntArr*)big->GetAt(loopx + myskip);

		//int		diffone = fuzzy.FuzzyCmpBuff(curr1, curr2);	
		//diff += diffone;
		}

	diff /= clen;
	return diff;
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton40() 

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	int ret = m_wav.OpenWave("");

	if(!ret)
		return;

	SetWindowText(m_wav.wavename);

	char *buff = m_wav.GetBuff(); int len = m_wav.GetBuffLen();

	CPtrArray arr; CPtrArray *parr = &arr;

	//recog.BendScan((short*)buff, len / sizeof(short), parr); 
	//recog.Scan((short*)buff, len / sizeof(short), parr); 

	//m_picker.AddArr(&arr);

	//recog.FreeArr(parr);

	//int olen = arr.GetSize();
	//for(int loop = 0; loop < olen; loop++)
	//	{
	//	CIntArr *org = (CIntArr*)arr.GetAt(loop);
	//	delete org;
	//	}
	//m_picker.SetFocus();
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton41() 

{
	AP2N("AutoPick\r\n");

	//CPtrArray arr2;

#if 0
	CProg prog;	CIntArr arr, arr2; 
	
	//prog.DiffProg(&m_picker.arr, &arr);

	arr.DumpAll();

	//m_picker.smark.RemoveAll();
	//m_picker.emark.RemoveAll();

#if 0
	int olen = m_picker.arr.GetSize();
	for(int loop = 0; loop < olen; loop += 3)
		{
		CRect rc;	m_wav.GetClientRect(rc);
		int len	= m_picker.GetArrLen();
			
		if(len)
			{
			// Note the image scaling factor of 2
			double fact = (double)rc.Width() / (len);
			
			m_wav.SetSel((int)(fact * loop), int(fact * (loop+3)));
			}

		support.YieldToWinEx();

		P2N("loop=%d\r\n", loop);
		m_picker.smark.Add(loop * 2);
		Sleep(100);
		}
#endif

	int alen = arr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		int val = arr.GetAt(loop);
		//m_picker.smark.Add(val * 2);
 		}

	m_wav.SetSel(0, 0);
	//m_picker.Invalidate();

#endif

}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton42() 

{
	//CPtrArray arr2;

	//CProg prog;	CIntArr arr, arr2; 
	//prog.DiffProg(&m_picker.arr, &arr2, 1);
	//arr2.DumpAll();

	//m_picker.smark.RemoveAll();
	//m_picker.emark.RemoveAll();

	//int alen2 = arr2.GetSize();
	//for(int loop2 = 0; loop2 < alen2; loop2++)
	//	{
	//	int val = arr2.GetAt(loop2);
	//	//m_picker.emark.Add(val * 2);
 	//	}
	//m_wav.SetSel(0, 0);
	//m_picker.Invalidate();


	m_plot.ClearAll();
	m_sin2.ClearAll();
	m_sin.ClearAll();

	m_sel.SetWindowText("");
	
	m_vis2.Clear();
	m_vis3.Clear();
	m_vis4.Clear();
	m_vis5.Clear();
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton43() 

{
#if 0
	CWavCmp wc;	CIntArr arr, varr, darr;
	char *buff; int len, ss, ee;
	
	m_plot.ClearAll();
	m_sin.ClearAll();
	m_sin2.ClearAll();

	m_wav.GetSel(&ss, &ee);	m_wav.GetSelBuff(&buff, &len);	

	short *buff2 = (short*)buff;
	
	wc.SplitZcross(buff2, len / sizeof(short), &arr);
	
#endif

#if 0
	// Dump distances
	int alen2 = arr.GetSize();
	for(int loop2 = 0; loop2 < alen2 - 1; loop2++)		
		{
		int val = arr.GetAt(loop2), val2 = arr.GetAt(loop2+1);
		
		for(int loop3 = val; loop3 < val2; loop3++)		
			{
			m_plot.AddLine(buff2[loop3] );
			}
		m_plot.AddMarker();
		}		
#endif

	//arr.DumpAll();
	
#if 0

	// Find self similar, walk side by side, blind ten, break at trailing edge
		
	int alen = arr.GetSize();
	for(int loop = 1; loop < alen - 1; loop++)
		{
		int val = arr.GetAt(loop);

		darr.RemoveAll();

		short *inaddr = buff2 + val;
		int prev  = 0;
		
		// Start from anchor, step till 10, break at descending edge
		for(int loop2 = loop + 1; loop2 < min(loop + 10, alen - 1); loop2++)
			{
			int val2 = arr.GetAt(loop2);
 			short *inaddr2 = buff2 + val2;
			int cmp = wc.HitCmp(inaddr, val2 - val, inaddr2);
			darr.Add(cmp);
			}		

		int xx, vv;
		darr.FindMax(&xx, &vv);

		if(xx > 0)
			{		
			AP2N("max=%d val=%d ---\r\n", xx, vv);

			// Put it to the second plot
			int val5 = arr.GetAt(loop);
			int val6 = arr.GetAt(loop + xx + 1);

			for(int loop3 = val5; loop3 < val6; loop3++)
				{
				m_sin.AddLine( *(buff2 + loop3) );
				}
			m_sin.AddMarker();
			
			loop += xx ;
			}
 		}
#endif

}

//////////////////////////////////////////////////////////////////////////
// Similarity of waves

void CPickDlg::OnButton45() 

{
	cwc.pplot = &m_plot; cwc.pplot2 = &m_sin;

	int	 flen	= m_wav. GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *elim = fbuff + flen;
	short *fdata = (short*)fbuff;
	
	//char *data = fbuff, *flim = fbuff + flen;
	
	if(!fbuff)
		{
		AfxMessageBox("No main wave");
		return;
		}

	// Get compare buffer
	char *buff3; int len3; m_wav3.GetSelBuff(&buff3, &len3);
	if(!buff3)
		{
		AfxMessageBox("No selection on cmp wav");
		return;
		}

	if(len3 == m_wav3.GetBuffLen())
		{
		AfxMessageBox("Full selection on cmp wav");
		return;
		}

	m_plot.ClearAll();	m_sin.ClearAll(); m_sin2.ClearAll();
	
	int lenx = len3 / (int)sizeof(short);
	int prog = 0, skip = 0;

	CIntArr arr; 
	cwc.CmpBuff(fbuff, flen, buff3, len3, &arr);

	m_plot.AddIntArr(&arr);
}

//////////////////////////////////////////////////////////////////////////

#if 0

void CPickDlg::OnButton45() 

{
	//AP2N("CPickDlg::OnButton45 WaveSimilar\r\n");	

	char *buff; int len, ss, ee;

	m_wav.GetSel(&ss, &ee);	m_wav.GetSelBuff(&buff, &len);

	char *dlim = buff + len;

	CString str; str.Format("%d/%d (%d)", ss, ee, len);
	m_sel.SetWindowText(str);

	m_wav2.SetBuff(buff, len);

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff();
	
	short *fdata = (short*)fbuff;
		
	// Beginning zero cross
	short *xdata = (short*)buff;
	while(true)
		{
		if((char*)xdata >= dlim - 2)
			break;

		if(*xdata < 0 && *(xdata+1) >= 0)
			{
			if(*xdata != 0) 
				xdata++;
			break;
			}	
		xdata++;
		}

	// End Zero Cross
	short *ydata = (short*)(buff + len);
	ydata = max(ydata, xdata);
	while(true)
		{
		if((char*)ydata <= (char*)xdata)
			break;

		if(*ydata <= 0 && *(ydata+1) > 0)
			break;

		ydata--;
		}

	if(ydata <= xdata)
		{
		AP2N("Zero Crossing overflow %p %p\r\n", xdata, ydata);
		//xdata = (short*)buff;
		//ydata = (short*)(buff + len);
		return;
		}

	int		lenx = ydata - xdata;

	// Get Max factor
	int maxval2 = 0, maxval = 0;
	short *tmpptr2 = xdata;
	for(int loop2 = 0; loop2 < lenx; loop2++)
		{
		int val = *tmpptr2;
		val = abs(val);
		maxval2 = max(maxval2, val);
		tmpptr2++;
		}

	//AP2N("maxval2 = %d\r\n", maxval2);

	m_plot.ClearAll();

	//AP2N("xdata= %d %d %d  ydata= %d %d %d\r\n", 
	//			*(xdata-1), *(xdata), *(xdata+1),
	//				*(ydata-1), *(ydata), *(ydata+1));

	// Dump data
	//short *zdata = (short*)xdata;
	//while(true)
	//	{
	//	if(zdata >= ydata)
	//		break;
	//	AP2N("%5d  ", *zdata);
	//	zdata++;
	//	}
	//AP2N("\r\n\r\n");
	//return;

	m_sin.ClearAll();

	for(int loop2b = 0; loop2b < ydata - xdata; loop2b++)
		{
		m_sin.AddLine(xdata[loop2b]);
		}

	char *elim = fbuff + flen;
	
	while(true)
		{
		if((char*)fdata >= elim - len)
			break;

		short	*data = (short*)xdata;		
		double	diff = 0;

		// Normalize to curr
		short *tmpptr = fdata;
		int	 maxval = 0, maxval3 = 0;
		for(int loop2 = 0; loop2 < lenx; loop2++)
			{
			int val = *tmpptr;
			val = abs(val);
			maxval = max(maxval, val);
			tmpptr++;
			}

		tmpptr = fdata;
		for(int loop2a = 0; loop2a < lenx; loop2a++)
			{
			int val = *tmpptr;
			
			// Normalize
			val *= maxval2;	val /= maxval;

			maxval3 = max(val, maxval3);

			//diff += *data - val;
			diff += abs(*data - val);
			//diff += abs(*data * val);
			
			data++; tmpptr++; 
			//fdata++;
			}

		//AP2N("maxval=%d maxval2=%d maxval3=%d\r\n", 
		//				maxval, maxval2, maxval3);
		
		//m_plot.AddLine(diff / maxval2);

		// printf
		//AP2N("diff=%+-16.f  ", diff);
		
		fdata += 1;

		// Walk till next zero cross
		while(true)
			{
			if((char*)fdata >= elim - len)
				break;
			if(*fdata < 0 && *(fdata+1) >= 0)
				break;
			fdata++;
			}

		//AP2N("fdata= %d %d %d  fdata= %d %d %d\r\n", 
		//		*(fdata-1), *(fdata), *(fdata+1),
		//			*(fdata-1), *(fdata), *(fdata+1));
 		}

	AP2N("\r\n\r\n");
}

#endif

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton46() 

{		
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	
#if 0
	CString stry = pwnd->appname;

	int idx2 = stry.ReverseFind('\\'); stry = stry.Left(idx2 + 1);

	// Hack for the build environment
	if(stry.Find("Debug") >= 0 || stry.Find("Release") >= 0)
		{
		//AP2N("Applied build hack\r\n");
		stry += "..\\";
		}
	stry += "slices\\";

	AP2N("Extract to: %s\r\n", stry);

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *elim = fbuff + flen;

	//AP2N("m_wav.wavename '%s'\r\n",  m_wav.wavename);

	int slicelen = RECLEN ;
	for(int loop = 0; loop < flen; loop += slicelen)
		{
		CString newname; 
		newname.Format("%s%s+%d.wav",  stry, m_wav.wavename, loop / slicelen);
	
		// Save the middle
		char *buff = fbuff + loop;
		AP2N("Creating: %s %p\r\n",  newname, buff);
		m_wav.pplaysnd->SaveWave(newname, buff, slicelen);
		}
#endif

}

//////////////////////////////////////////////////////////////////////////
// WaveProg

void CPickDlg::OnButton47() 

{
	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *flim = fbuff + flen;

	if(fbuff == NULL)
		{
		AfxMessageBox("No main wav loaded");
		return;
		}
		
	m_plot.ClearAll();	m_sin.ClearAll(); m_sin2.ClearAll();

	CIntArr arr;
	cwc.SplitZcross((short*)fbuff, flen / sizeof(short), &arr);

	int falen = arr.GetSize();
	for(int floop2 = 0; floop2 < falen - 13; floop2++)		
		{	
		int rval = arr.GetAt(floop2);
		int rval2 = arr.GetAt(floop2+1);
			
		for(int floop3 = 1; floop3 < 12; floop3++)		
			{		
			int floop4 = floop2 + floop3;
			
			int fval = arr.GetAt(floop4);
			int fval2 = arr.GetAt(floop4 + 1);
			
			int diff = cwc.HitCmp(
							(short*)(fbuff + rval * sizeof(short)),	rval2 - rval,
								(short*)(fbuff + fval  * sizeof(short)), fval2 - fval);

			m_plot.AddLine(diff);
			}				

		m_plot.AddMarker();
		}

}

//////////////////////////////////////////////////////////////////////////
// WaveCmp

void CPickDlg::OnButton48() 

{	

#if 1

	//CWavCmp wc; 
	CIntArr arr;

	m_sin.ClearAll(); m_plot.ClearAll();

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *flim = fbuff + flen;

	if(fbuff == NULL)
		{
		AfxMessageBox("No main wav loaded");
		return;
		}
		
	cwc.SplitZcross((short*)fbuff, flen / sizeof(short), &zeroarr);

	//////////////////////////////////////////////////////////////////////////
	char *buff; int len, ss, ee;

	m_wav3.GetSel(&ss, &ee); m_wav3.GetSelBuff(&buff, &len);
	char *dlim = buff + len;

	if(buff == NULL)
		{
		AfxMessageBox("No cmp wav loaded");
		return;
		}
	
	//m_wav2.SetBuff(buff, len);

	CString str; str.Format("%d/%d (%d)", ss, ee, len);
	m_sel.SetWindowText(str);
	
	cwc.SplitZcross((short*)buff, len / sizeof(short), &arr);

	int step = 4;
	int alen2 = arr.GetSize();
	for(int loop2 = 0; loop2 < alen2 - (step + 1); loop2 += step)		
		{
		int val = arr.GetAt(loop2), val2 = arr.GetAt(loop2 + step);
		
		for(int loop3 = val; loop3 < val2; loop3++)		
			{
			m_sin.AddLine(((short*)buff)[loop3]);
			}

		int falen = zeroarr.GetSize();
		for(int floop2 = 0; floop2 < falen - 1; floop2++)		
			{		
			int fval = zeroarr.GetAt(floop2), fval2 = zeroarr.GetAt(floop2+1);

			short *inaddr = (short*)buff + val;
			short *inaddr2 = (short*)fbuff + fval;
			}

		m_sin.AddMarker();
		m_plot.AddMarker();
		}		

	//for(int loop2b = 0; loop2b < len / 2; loop2b++)
	//	{
	//	m_sin.AddLine(((short*)buff)[loop2b]);
	//	}

#endif

}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton49() 

{
#if 0

	char *buff; int len, ss, ee;

	if(m_wav3.GetBuff() == NULL)
		{
		AfxMessageBox("No wav loaded");
		return;
		}

	m_wav3.GetSel(&ss, &ee);	m_wav3.GetSelBuff(&buff, &len);

	char *dlim = buff + len;

	CString str; str.Format("%d/%d (%d)", ss, ee, len);
	m_sel.SetWindowText(str);

	m_wav2.SetBuff(buff, len); 

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *elim = fbuff + flen;

	short *fdata = (short*)fbuff;

	CIntArr varr, darr, varr2, darr2;

	int		ret = bend.ProcBuff((short*)fbuff, flen/2, &varr, &darr);
	int		ret2 = bend.ConvDist(&darr, &darr2, &varr, &varr2);

	//darr2.Plot(&m_plot);
	//varr2.Plot(&m_sin2);

	//AP2N("Darr2 full\r\n");
	//darr2.DumpAll();

	//m_plot.AddMarker();
	//m_sin2.AddMarker();

	//darrbig.Copy(darr2);
	darrbig.Copy(varr2);

#endif

}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton50() 

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	//AP2N("Bend \r\n");
	
	char *buff; int len, ss, ee;

	if(m_wav3.GetBuff() == NULL)
		{
		AfxMessageBox("No wav loaded");
		return;
		}

	m_wav3.GetSel(&ss, &ee);	m_wav3.GetSelBuff(&buff, &len);

	char *dlim = buff + len;

	CString str; str.Format("%d/%d (%d)", ss, ee, len);
	m_sel.SetWindowText(str);

	m_wav2.SetBuff(buff, len); 

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *elim = fbuff + flen;

	short *fdata = (short*)fbuff;

	pwnd->plotdlg.m_plot1.ClearAll();
	pwnd->plotdlg.m_plot2.ClearAll();
	pwnd->plotdlg.m_plot3.ClearAll();

	//pwnd->plotdlg.m_plot4.ClearAll();
	//pwnd->plotdlg.m_plot5.ClearAll();
	//pwnd->plotdlg.m_plot6.ClearAll();

	CIntArr		spec;
	//bend.BendSpectra(buff, len, &spec);

	//spec2.Plot(pwnd->plotarr[4]);
	//spec3.Plot(pwnd->plotarr[5]);

	//AP2N("Darr2 small\r\n");
	//darr2.DumpAll();

	//darrsmall.Copy(darr2);
	//darrsmall.Copy(varr2);
	darrsmall.Copy(spec);
}

#if 0

//P2N("Self Similar button\r\n");

	CPtrArray arr2;

	int start, endd;

	m_picker.GetSel(&start, &endd);

	endd = min(endd, m_picker.arr.GetSize());

	for(int loop = start; loop < endd; loop++)
		{
		arr2.Add(m_picker.arr.GetAt(loop));
 		}
	
	// Walk the array
	int alen = m_picker.arr.GetSize();
	for(int loopw = 0; loopw < alen; loopw++)
		{
		double diff = CmpArray(&loopw, &arr2, &m_picker.arr);

		P2N("%3d  diff %.f\r\n", loopw, diff);
 		}
#endif	

//////////////////////////////////////////////////////////////////////////
// Build small aray 

void CPickDlg::OnButton51() 

{
	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	//P2N("CPickDlg::OnButton51\r\n");

	char *buff; int len, ss, ee;

	if(m_wav3.GetBuff() == NULL)
		{
		//AfxMessageBox("No wav loaded");
		return;
		}

	CleanSmall();

	m_wav3.GetSel(&ss, &ee);	
	m_wav3.GetSelBuff(&buff, &len);
	
	CString str; str.Format("%d/%d (%d)", ss, ee, len);
	m_sel.SetWindowText(str);

	CPtrArray arr, *parr = &arr;
					
	//fscan.ScanBuff(buff, len, parr);
	//fftbuff.Transform((short*)buff, len, parr);
	
	//recog.BendScan((short*)buff, len / sizeof(short), parr);
	//recog.Scan((short*)buff, len / sizeof(short), parr);
	
#if 0

	// Fresh copy
	m_vis2.Clear();

	for(int loopd = 0; loopd < arr.GetSize(); loopd += 1)
		{
		CIntArr *val = (CIntArr*)arr.GetAt(loopd);		
		//pwnd->visdlg.m_vis.AddIntArr(val);	
		m_vis2.AddIntArr(val);
		}
	//pwnd->visdlg.m_vis.AddMarker();	
#endif

	arrsmall.Copy(arr);
}

//////////////////////////////////////////////////////////////////////////
// Scan big array

void CPickDlg::OnButton52() 

{
#if 0
	CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *elim = fbuff + flen;

	if(!fbuff)
		return;

	CleanBig();

	CPtrArray arr, *parr = &arr;
	
	//fftbuff.Transform((short*)fbuff, flen, parr);
	//recog.BendScan((short*)fbuff, flen / sizeof(short), parr);
	recog.Scan((short*)fbuff, flen / sizeof(short), parr);
	
	//CPtrArray res;
	//fftbuff.GetPeaks(parr, &res);
	
#endif

#if 0
	m_vis3.Clear();
	for(int loopd = 0; loopd < arr.GetSize(); loopd += 1)
		{
		CIntArr *val = (CIntArr*)arr.GetAt(loopd);		
		pwnd->visdlg.m_vis.AddIntArr(val);	
		m_vis3.AddIntArr(val);
		}
	//pwnd->visdlg.m_vis.AddMarker();
	
#endif
	
	//arrbig.Copy(arr);
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::OnButton53() 

{
	//AP2N("Array Cmp big=%d small=%d\r\n", arrbig.GetSize(), arrsmall.GetSize());

	m_plot.ClearAll();	m_sin2.ClearAll();

	OnButton51(); OnButton52();

	int alen = arrbig.GetSize(); int slen = arrsmall.GetSize();

	if(!slen)
		return;

	int sides = 2;

	for(int loop = 0; loop < alen - slen; loop++)
		{
		int sum = 0;

		for(int loop2 = 0; loop2 < slen; loop2++)
			{
			int cmp = 0;

			CIntArr *val2 = (CIntArr *)arrsmall.GetAt(loop2);

			int ss = max(0, loop - sides), ee = min(alen - slen, loop + sides + 1);

			for(int loop3 = ss; loop3 < ee; loop3++)
				{
				CIntArr *val = (CIntArr *)arrbig.GetAt(loop3);
			
				//int		sub = fuzzy.FuzzyCmpBuff(val, val2);
				//cmp = max(sub, cmp);
				}
			sum += cmp;
			}
		sum /= slen;
 		
		m_plot.AddLine(sum);	
		}
}

//////////////////////////////////////////////////////////////////////////
// WavZcomp

void CPickDlg::OnButton54() 

{	
	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *flim = fbuff + flen;

	if(fbuff == NULL)
		{
		AfxMessageBox("No main wav loaded");
		return;
		}
		
	m_plot.ClearAll();	m_sin.ClearAll(); m_sin2.ClearAll();

	CIntArr arr, arr3;
	cwc.SplitZcross((short*)fbuff, flen / sizeof(short), &arr);

	// Get compare buffer
	int	 flen3	= m_wav3.GetBuffLen();
	char *fbuff3 = m_wav3.GetBuff(), *flim3 = fbuff3 + flen3;

	char *buff3; int len3; m_wav3.GetSelBuff(&buff3, &len3);
	
	int offs ;
	if(!buff3)
		{
		offs = m_wav3.GetStartLen();
		}
	else
		{
		offs = buff3 - m_wav3.GetBuff();
		}
 
	offs /= sizeof(short);

	m_plot.ClearAll();	m_sin.ClearAll(); m_sin2.ClearAll();
	
	cwc.SplitZcross((short*)fbuff3, flen3 / sizeof(short), &arr3);

	//m_plot.AddIntArr(&arr3);
	
	//AP2N("Looking for selection %d\r\n", offs);

	int found = 0, found2 = 0, alen3 = arr3.GetSize();
	for(int floop3 = 0; floop3 < alen3 - 4; floop3++)		
		{
		int fval = arr3.GetAt(floop3);
		int fval2 = arr3.GetAt(floop3 + 1);
		int fval3 = arr3.GetAt(floop3 + 2);
		int fval4 = arr3.GetAt(floop3 + 4);
		
		if(fval <= offs && fval2 > offs)
			{
			//AP2N("Found selection %d\r\n", offs);
			found = fval;
			found2 = fval4;
			break;
			}
		}

	if(!found)
		{
		AfxMessageBox("Offset not found");
		return;
		}

	short *tmp = (short*)(fbuff3 + found * sizeof(short));
	for(int loop = 0; loop < found2 - found; loop++)
		{
		m_sin.AddLine(*tmp++);
 		}

	int falen = arr.GetSize();
	for(int floop2 = 0; floop2 < falen - 4; floop2++)		
		{
		int fval = arr.GetAt(floop2);
		int fval2 = arr.GetAt(floop2 + 1);
		int fval3 = arr.GetAt(floop2 + 2);
		int fval4 = arr.GetAt(floop2 + 4);
		
		// Animate second buffer
		m_sin2.ClearAll();
		short *tmp2 = (short*)(fbuff + fval * sizeof(short));
		for(int loop = 0; loop < fval4 - fval; loop++)
			{
			m_sin2.AddLine(*tmp2++);
 			}		
		support.YieldToWinEx();
		Sleep(500);
	
		int diff = cwc.HitCmp(
						(short*)(fbuff + fval * sizeof(short)), fval4 - fval,
						(short*)(fbuff3 + found  * sizeof(short)), found2 - found);

		m_plot.AddLine(diff);	
		}
}

//////////////////////////////////////////////////////////////////////////
// Compare wave to wave

void CPickDlg::OnButton55() 

{
	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *flim = fbuff + flen;

	if(fbuff == NULL)
		{
		AfxMessageBox("No main wav loaded");
		return;
		}
		
	m_plot.ClearAll();	m_sin.ClearAll(); m_sin2.ClearAll();
	m_sel.SetWindowText("");

	CIntArr arr, arr3;
	cwc.SplitZcross((short*)fbuff, flen / sizeof(short), &arr);

	// Get compare buffer
	int	 flen3	= m_wav3.GetBuffLen();
	char *fbuff3 = m_wav3.GetBuff(), *flim3 = fbuff3 + flen3;
	
	if(fbuff3 == NULL)
		{
		AfxMessageBox("No cmp wav loaded");
		return;
		}

	//AP2N("fbuff=%p fbuff3=%p\r\n", fbuff, fbuff3);

	m_plot.ClearAll();	m_sin.ClearAll(); m_sin2.ClearAll();
	
	cwc.SplitZcross((short*)fbuff3, flen3 / sizeof(short), &arr3);

	//m_sin.AddIntArr(&arr);	m_sin2.AddIntArr(&arr3);
	
	int sum = 0, falen = arr.GetSize(), falen3 = arr3.GetSize();
	falen = min(falen, falen3);

	for(int floop2 = 0; floop2 < falen - 8 ; floop2++)		
		{
		int rval = arr.GetAt(floop2);
		int rval2 = arr.GetAt(floop2 + 8);
		
				
//		// Animate for checking
//		m_sin.ClearAll();
//		short *tmp2 = (short*)(fbuff + rval * sizeof(short));
//		for(int loop = 0; loop < rval2 - rval; loop++)
//			{
//			m_sin.AddLine(*tmp2++);
// 			}		
//
//		m_sin2.ClearAll();
//		short *tmp3 = (short*)(fbuff3 + fval * sizeof(short));
//		for(int loopa = 0; loopa < fval2 - fval; loopa++)
//			{
//			m_sin2.AddLine(*tmp3++);
// 			}		
//
//		support.YieldToWinEx();
//		Sleep(100);

		// Wobble
		int wobble = 1000, xdiff = 0;
		for(int wloop = -wobble; wloop < wobble + 1; wloop += 1)		
			{
			int wloop2 = floop2 + wloop;

			// If wobble in range
			if(wloop2 >= 0 && wloop2 < falen - 8)
				{
				int fval = arr3.GetAt(wloop2);
				int fval2 = arr3.GetAt(wloop2 + 8);

				int diff = cwc.HitCmp(
							(short*)(fbuff + rval * sizeof(short)), rval2 - rval,
						(short*)(fbuff3 + fval  * sizeof(short)), fval2 - fval);

				//int diff = cwc.SubCmp(
				//			(short*)(fbuff + rval * sizeof(short)), rval2 - rval,
				//		(short*)(fbuff3 + fval  * sizeof(short)), fval2 - fval);

				xdiff = max(diff, xdiff);
				}
			}
		m_plot.AddLine(xdiff);	
		sum += xdiff;
		}

	sum /= falen;

	CString str; str.Format("Sum of %s / %s -> %d", 
					m_wav.GetFileName(), m_wav3.GetFileName(),  sum);

	//CString str; str.Format("Wac2Wav sum=%d", sum);
	m_sel.SetWindowText(str);

}

//////////////////////////////////////////////////////////////////////////
//

void CPickDlg::OnButton56() 

{
	//CIntArr arr;

	m_sin.ClearAll(); m_plot.ClearAll();
	zeroarr.RemoveAll();

	int	 flen	= m_wav.GetBuffLen();
	char *fbuff = m_wav.GetBuff(), *elim = fbuff + flen;

	if(fbuff == NULL)
		{
		AfxMessageBox("No main wav loaded");
		return;
		}
		
	cwc.SplitZcross((short*)fbuff, flen / sizeof(short), &zeroarr);

	int alen = zeroarr.GetSize();
	for(int loop = 0; loop < alen - 1; loop++)
		{
		int val = zeroarr.GetAt(loop);
		int val2 = zeroarr.GetAt(loop + 1);

		for(int loop2 = val; loop2 < val2; loop2++)
			{
			short val3 = ((short*)fbuff)[loop2];
			m_plot.AddLine(val3);

			m_sin.AddLine(min(1000, val2 - val));
			}
		m_plot.AddMarker();
		}


}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::CleanSmall()

{
	// Empty it for the next walk
	for(int loopd3 = 0; loopd3 < arrsmall.GetSize(); loopd3 += 1)
		{
		delete (CIntArr*)arrsmall.GetAt(loopd3);
		}
}

void CPickDlg::CleanBig()

{
	// Empty it for the next walk
	for(int loopd3 = 0; loopd3 < arrbig.GetSize(); loopd3 += 1)
		{
		delete (CIntArr*)arrbig.GetAt(loopd3);
		}
}

void CPickDlg::OnOK() 

{		
	CDialog::OnOK();
}


void CPickDlg::ScanSmall()

{

	int	 len	= m_wav3.GetBuffLen();
	char *buff = m_wav3.GetBuff();

	CPtrArray arr, *parr = &arr;
					
	//recog.BendScan((short*)buff, len / sizeof(short), parr);
	//recog.Scan((short*)buff, len / sizeof(short), parr);
	
#if 1

	// Fresh copy
	m_vis4.Clear();

	for(int loopd = 0; loopd < arr.GetSize(); loopd += 1)
		{
		CIntArr *val = (CIntArr*)arr.GetAt(loopd);		
		//pwnd->visdlg.m_vis.AddIntArr(val);	
		m_vis4.AddIntArr(val);
		}
	//pwnd->visdlg.m_vis.AddMarker();	
#endif

	//recog.FreeArr(parr);
}

//////////////////////////////////////////////////////////////////////////

void CPickDlg::ScanBigPart()

{
	int	 len; char *buff;

	m_wav.GetSelBuff(&buff, &len);
	
	CPtrArray arr, *parr = &arr;
					
	//recog.BendScan((short*)buff, len / sizeof(short), parr);
	//recog.Scan((short*)buff, len / sizeof(short), parr);
	
#if 1

	// Fresh copy
	m_vis5.Clear();

	for(int loopd = 0; loopd < arr.GetSize(); loopd += 1)
		{
		CIntArr *val = (CIntArr*)arr.GetAt(loopd);		
		//pwnd->visdlg.m_vis.AddIntArr(val);	
		m_vis5.AddIntArr(val);
		}
	//pwnd->visdlg.m_vis.AddMarker();	
#endif

	//recog.FreeArr(parr);
}
