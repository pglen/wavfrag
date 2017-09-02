
/* =====[ Focus.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Focus.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/16/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */


#include "stdafx.h"
#include "wavfrag.h"
#include "Focus.h"
#include "mxpad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
// Filter out top level, non blank, visible non tool windows
//

BOOL CALLBACK CFocus::EnumWindowsProc( HWND hwnd, LPARAM lParam)

{
	_finproc *pfp = (_finproc *)lParam;

	char str[255]; ::GetWindowText(hwnd, str, sizeof(str));

	if(str[0] != 0)
		{
		if(GetParent(hwnd) == 0)
			{
			if(GetWindowLong(hwnd, GWL_STYLE) & WS_VISIBLE)
				{
				 LONG exstyle = GetWindowLong(hwnd, GWL_EXSTYLE);
				 if(exstyle & ~WS_EX_TOOLWINDOW)
					{
					//AP2N("%9d %s\r\n", hwnd, str);
					
					if(pfp->found == 1)
						pfp->hwnd_first = hwnd;

					pfp->hwnd_next  = hwnd;					
					pfp->found++;
					}
				}
			}
		}
	return  true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFocus::CFocus()
{

}

CFocus::~CFocus()
{

}

//////////////////////////////////////////////////////////////////////////

HWND	CFocus::GrabFocus(HWND wto)

{
	//AP2N("CWavfragDlg::GrabFocus\r\n");
  
	HWND fg_hwnd = NULL;

	::BringWindowToTop(wto);
	//::SetWindowPos(HWND_TOP, wto, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	// If could not set it
	if(!::SetForegroundWindow(wto))
		{
		AP2N("CWavfragDlg::GrabFocus - Grabbing by force\r\n");
	
		fg_hwnd = ::GetForegroundWindow();

		// Just in case
		if(!fg_hwnd)
			{
			AP2N("CWavfragDlg::GrabFocus - Fall Back on systray\r\n");
			fg_hwnd = ::FindWindow("Shell_TrayWnd", NULL);
			}

		DWORD pid_fg_win = GetWindowThreadProcessId(fg_hwnd, NULL);
		DWORD pid_win = GetWindowThreadProcessId(wto, NULL);				
		
		::AttachThreadInput(pid_fg_win, pid_win, TRUE);
		::BringWindowToTop(wto);
		::AttachThreadInput(pid_fg_win, pid_win, FALSE);

		//::SetForegroundWindow(wto);	
		//::SetActiveWindow(wto);
		//::SetFocus(wto);
		//::SetWindowPos(HWND_BOTTOM, fg_hwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//::SetWindowPos(HWND_TOP, wto, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);		
		
		// Tried too hard ....
		//::SendMessage(fg_hwnd, WM_ACTIVATE, WA_INACTIVE, NULL);
		//::SendMessage(fg_hwnd, WM_KILLFOCUS, (long)wto, NULL);
		//::SetActiveWindow(wto);
		//::SetFocus(wto);
		//::BringWindowToTop(wto);
		//::SetWindowPos(HWND_BOTTOM, fg_hwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//::SendMessage(wto, WM_SETFOCUS, (long)fg_hwnd, NULL);
		//::SendMessage(wto, WM_ACTIVATE, WA_ACTIVE, NULL);		
		}

	if(::IsIconic(wto))
		::SendMessage(wto, WM_SYSCOMMAND, SC_RESTORE, 0);
 
	return fg_hwnd;
}

//////////////////////////////////////////////////////////////////////////
// Switch to Next Process

HWND	CFocus::FindNextProc()

{
	_finproc fpr; fpr.found = 0; fpr.hwnd_next = 0; fpr.hwnd_first = 0;	

	EnumWindows(EnumWindowsProc, (long)&fpr);

	//char str[255]; ::GetWindowText(hwnd_next, str, sizeof(str));
	//AP2N("Activating: %9d %s\r\n", hwnd_next, str);
					
	return fpr.hwnd_next;
}

//////////////////////////////////////////////////////////////////////////
// Switch to Prev Process

HWND	CFocus::FindPrevProc()

{
	_finproc fpr; fpr.found = 0; fpr.hwnd_next = 0; fpr.hwnd_first = 0;	

	EnumWindows(EnumWindowsProc, (long)&fpr);

	//char str[255]; ::GetWindowText(hwnd_first, str, sizeof(str));
	//AP2N("Activating: %9d %s\r\n", hwnd_first, str);
					
	return fpr.hwnd_first;
}
