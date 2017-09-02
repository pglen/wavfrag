
/* =====[ SendKeys.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the SendKeys.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  10/1/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "SendKeys.h"
#include "mxpad.h"

#undef P2N

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static	CSendKeys::skkeydef kd[] =

{
	// These are obsolete
	//VK_ALT,			6	, "VK_ALT",
	//VK_BACK_QUOTE,	13	, "VK_BACK_QUOTE",
	//VK_BACK_SLASH,	13	, "VK_BACK_SLASH",
	//VK_BACK_SPACE,	13	, "VK_BACK_SPACE",
	//VK_CAPS_LOCK,	13	, "VK_CAPS_LOCK",
	//VK_CLOSE_BRACKET,17	, "VK_CLOSE_BRACKET",
	//VK_COMMA,		8	, "VK_COMMA",
	//VK_ENTER,		8	, "VK_ENTER",
	//VK_EQUALS,		9	, "VK_EQUALS",
	//VK_META,		7	, "VK_META",
	//VK_NUM_LOCK,	11	, "VK_NUM_LOCK",
	//VK_OPEN_BRACKET,15	, "VK_OPEN_BRACKET",
	//VK_PAGE_DOWN,	12	, "VK_PAGE_DOWN",
	//VK_PAGE_UP,		10	, "VK_PAGE_UP",
	//VK_PERIOD,		9	, "VK_PERIOD",
	//VK_PRINTSCREEN,	14	, "VK_PRINTSCREEN",
	//VK_QUOTE,		8	, "VK_QUOTE",
	//VK_SCROLL_LOCK,	15	, "VK_SCROLL_LOCK",
	//VK_SEMICOLON,	13	, "VK_SEMICOLON",
	//VK_SLASH,		8	, "VK_SLASH",
	//VK_UNDEFINED,	12	, "VK_UNDEFINED",

	VK_LBUTTON,		10	,"VK_LBUTTON",
	VK_RBUTTON,		10	,"VK_RBUTTON",
	VK_CANCEL ,		9	,"VK_CANCEL",
	VK_MBUTTON,		10	,"VK_MBUTTON",
	VK_BACK,		7	,"VK_BACK",
	VK_CLEAR ,		8	,"VK_CLEAR",
	VK_RETURN ,		9	,"VK_RETURN",
	VK_SHIFT,		8	,"VK_SHIFT",
	VK_CONTROL,		10	,"VK_CONTROL",
	VK_MENU ,		7	,"VK_MENU",
	VK_PAUSE,		8	,"VK_PAUSE",
	VK_CAPITAL ,	10	,"VK_CAPITAL",
	VK_PRIOR,		8	,"VK_PRIOR",
	VK_NEXT ,		7	,"VK_NEXT",
	VK_END ,		6	,"VK_END",
	VK_HOME,		7	,"VK_HOME",
	VK_LEFT,		7	,"VK_LEFT",
	VK_SELECT,		9	,"VK_SELECT",
	VK_EXECUTE,		10	,"VK_EXECUTE",
	VK_SNAPSHOT,	11	,"VK_SNAPSHOT",
	VK_PLAY,		7	,"VK_PLAY",
	VK_ACCEPT,		9	, "VK_ACCEPT",
	VK_ADD,			6	, "VK_ADD",
	VK_CANCEL,		9	, "VK_CANCEL",
	VK_CLEAR,		8	, "VK_CLEAR",
	VK_CONTROL,		10	, "VK_CONTROL",
	VK_CONVERT,		10	, "VK_CONVERT",
	VK_DECIMAL,		10	, "VK_DECIMAL",
	VK_DELETE,		9	, "VK_DELETE",
	VK_DIVIDE,		9	, "VK_DIVIDE",
	VK_DOWN,		7	, "VK_DOWN",
	VK_END,			6	, "VK_END",
	VK_ESCAPE,		9	, "VK_ESCAPE",
	VK_F1,			5	, "VK_F1",
	VK_F10,			6	, "VK_F10",
	VK_F11,			6	, "VK_F11",
	VK_F12,			6	, "VK_F12",
	VK_F2,			5	, "VK_F2",
	VK_F3,			5	, "VK_F3",
	VK_F4,			5	, "VK_F4",
	VK_F5,			5	, "VK_F5",
	VK_F6,			5	, "VK_F6",
	VK_F7,			5	, "VK_F7",
	VK_F8,			5	, "VK_F8",
	VK_F9,			5	, "VK_F9",
	VK_FINAL,		8	, "VK_FINAL",
	VK_HELP,		7	, "VK_HELP",
	VK_HOME,		7	, "VK_HOME",
	VK_INSERT,		9	, "VK_INSERT",
	VK_KANA,		7	, "VK_KANA",
	VK_KANJI,		8	, "VK_KANJI",
	VK_LEFT,		7	, "VK_LEFT",
	VK_MODECHANGE,	13	, "VK_MODECHANGE",
	VK_MULTIPLY,	11	, "VK_MULTIPLY",
	VK_NONCONVERT,	13	, "VK_NONCONVERT",
	VK_NUMPAD0,		10	, "VK_NUMPAD0",
	VK_NUMPAD1,		10	, "VK_NUMPAD1",
	VK_NUMPAD2,		10	, "VK_NUMPAD2",
	VK_NUMPAD3,		10	, "VK_NUMPAD3",
	VK_NUMPAD4,		10	, "VK_NUMPAD4",
	VK_NUMPAD5,		10	, "VK_NUMPAD5",
	VK_NUMPAD6,		10	, "VK_NUMPAD6",
	VK_NUMPAD7,		10	, "VK_NUMPAD7",
	VK_NUMPAD8,		10	, "VK_NUMPAD8",
	VK_NUMPAD9,		10	, "VK_NUMPAD9",
	VK_PAUSE,		8	, "VK_PAUSE",
	VK_RIGHT,		8	, "VK_RIGHT",
	VK_SEPARATOR,	12 	, "VK_SEPARATOR",
	VK_SHIFT,		8	, "VK_SHIFT",
	VK_SPACE,		8	, "VK_SPACE",
	VK_SUBTRACT,	11	, "VK_SUBTRACT",
	VK_TAB,			6	, "VK_TAB",
	VK_UP,			5	, "VK_UP",
	VK_LWIN			,7, "VK_LWIN",
	VK_RWIN			,7, "VK_RWIN",
	VK_APPS			,7, "VK_APPS",

	0,			0, NULL
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSendKeys::CSendKeys()
{

}

CSendKeys::~CSendKeys()
{

}

//////////////////////////////////////////////////////////////////////////

int		CSendKeys::xTrans(const char *keys, int *skip, int *scan)

{
	int vk = 0, loop = 0;

	*scan = 0, *skip = 0;
	while(true)
		{
		if(kd[loop].vkstr == NULL)
			break;

		//AP2N("Scanning %s %d %d\r\n", 
		//			kd[loop].vkstr, kd[loop].slen, kd[loop].scan);
		// Just to confirm lenght correctness
	
		//ASSERT(strlen(kd[loop].vkstr) == kd[loop].slen);

		if(strncmp(keys, kd[loop].vkstr, kd[loop].slen) == 0)
			{
			//AP2N("Found %s %d %d\r\n", 
			//		kd[loop].vkstr, kd[loop].slen, kd[loop].scan);

			*skip = kd[loop].slen; 	*scan = kd[loop].scan;	
			
			vk = kd[loop].scan;
			}
		loop++;
		}

	return vk;
}

//////////////////////////////////////////////////////////////////////////

int		CSendKeys::SendKeys(const char *keys)

{
	int len = strlen(keys);
	
	for(int loop2 = 0; loop2 < len; loop2++)
		{
		// Is it a virtual scan code?
		if(strncmp(&keys[loop2], "VK_", 3) == 0)
			{
			int skip = 0, scan = 0;
			
			xTrans(&keys[loop2], &skip, &scan);

			if(scan)
				{
				//AP2N("Virtual key '%s' scan=%d, skip=%d\r\n", &keys[loop2], scan, skip);
				
				// These keys are used to toggle it
				if(scan == VK_CONTROL)
					{
					short kstate = GetKeyState(VK_CONTROL);
					if(kstate & 0x80)
						{	
						keybd_event(scan, 0, KEYEVENTF_KEYUP, 0);
						}
					else
						{
						keybd_event(scan, 0, 0, 0);
						}
					}
				// These keys are used to toggle it
				else if(scan == VK_MENU)
					{
					short kstate = GetKeyState(VK_MENU);
					if(kstate & 0x80)
						{	
						keybd_event(scan, 0, KEYEVENTF_KEYUP, 0);
						}
					else
						{
						keybd_event(scan, 0, 0, 0);
						}
					}
				else
					{
					keybd_event(scan, 0, 0, 0);
					}		
				}
			
			//AP2N("Sending scan: %d skip=%d\r\n", scan, skip);		

			if(skip)
				loop2 += skip - 1;
			}
		else
			{
			char chh = keys[loop2];
			short ks = VkKeyScan(chh);

			BYTE  key = ks & 0xff, state = ks >> 8;

			//AP2N("chh=%d (%c) ks=%d key=%d state=%d \r\n", 
			//							chh, chh, ks, key, state);

			//AP2N("CSendKeys::Sending key %d: chh=%d (%c)\r\n", loop2, chh, chh);
		
			if(state & 1)
				keybd_event(VK_SHIFT, 0, 0, 0);

			keybd_event(BYTE(ks & 0xff), 0, 0, 0);
			
			Sleep(10);

			keybd_event(BYTE(ks & 0xff), 0, KEYEVENTF_KEYUP, 0);

			if(state & 1)
				keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
			}
		}

	return 0;
}