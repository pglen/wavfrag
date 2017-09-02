
/* =====[ Mixer.cpp ]========================================== 
                                                                             
   Description:     The dogtalk project, implementation of the Mixer.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  12/16/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "Mixer.h"
#include "Mxpad.h"

#undef AP2N

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#undef FAILED
#define FAILED(err) (MMSYSERR_NOERROR != err)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CxMixer::CxMixer()

{
	xdevice = xscanfor = xdest = xsrc = 0;
	
	m_hMixer = 0;
	m_dwControlID = -1;	m_dwChannels = 0;
	m_bOK = m_opened = false;
}

//////////////////////////////////////////////////////////////////////////
// Device this mixer controls. Enum of waveOutGetNumDevs or
//  waveInGetNumDevs
// Pass window handle for callback function

int		CxMixer::SetDevice(int kind, int devi, HWND callback)

{
	//P2N("CxMixer::SetDevice kind=%d devi=%d, callback=%x\r\n", 
	//				kind, devi, callback); 

	m_bOK = false;
	m_kind = kind;
	
	int numdev = 0;
	
	switch(m_kind)
		{
		case MIX_MIC_RECORD:		
			xdest		= MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
			xsrc		= MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
			xscanfor	= MIXER_OBJECTF_WAVEIN;
			numdev = waveInGetNumDevs();	
		break;

		case MIX_MIC_MONITOR:
			xdest		= MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
			xsrc		= MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
			xscanfor	= MIXER_OBJECTF_WAVEOUT;
			numdev = waveOutGetNumDevs();	
		break;

		case MIX_SPEAKER:	
			xdest		= MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
			xsrc		= MIXERLINE_COMPONENTTYPE_SRC_FIRST;
			xscanfor	= MIXER_OBJECTF_WAVEOUT;
			numdev = waveInGetNumDevs();	
		break;

		default:
			P2N("Invalid mixer kind\r\n");
		}
	
	// Just checking
	if(devi >= numdev)
		{
		P2N("Requested device exceeds the number of input/output mixer devices\r\n");
		}

	ASSERT(callback && IsWindow(callback));

	//P2N("Number of input/output mixer devices: %d want: %d\r\n", numdev, devi);
	
	xdevice = devi;
	
	if(m_opened)
		{
		mixerClose(m_hMixer); m_opened = false; m_hMixer = NULL;
		}

	HRESULT hr;
	
	//if(callback)
		{
		hr = mixerOpen(&m_hMixer, xdevice, (int)callback, 0, CALLBACK_WINDOW | xscanfor);

		if (FAILED(hr)) 
			{
			P2N("CxMixer::CxMixer Failed to open mixer\r\n");
			return 0;
			}
		m_opened = true;
		}
	
#if 0
	// Just to see them ...
	MIXERCAPS cap;
	for(int loop = 0; loop < numdev; loop++)
		{
		MMRESULT res = mixerGetDevCaps(loop, &cap, sizeof(cap));

		P2N("wMid=%d  wPid=%d  vDriverVersion=%d szPname=%s  fdwSupport=%d  cDestinations=%d\r\n",	
			cap.wMid, cap.wPid, cap.vDriverVersion, cap.szPname, cap.fdwSupport, cap.cDestinations); 
		}
#endif

	MIXERCAPS cap;
	MMRESULT res = mixerGetDevCaps((DWORD)m_hMixer, &cap, sizeof(cap));

	//P2N("wMid=%d  wPid=%d  vDriverVersion=%d szPname=%s  "
	//		"fdwSupport=%d  cDestinations=%d\r\n",	
	//				cap.wMid, cap.wPid, cap.vDriverVersion, cap.szPname, 
	//					cap.fdwSupport, cap.cDestinations); 

	for(int loopd = 0; loopd < (int)cap.cDestinations; loopd++)
		{
		MIXERLINE mxl;	memset(&mxl, 0, sizeof(mxl));
		mxl.cbStruct = sizeof(mxl);

		mxl.dwDestination = loopd;
		hr = mixerGetLineInfo((HMIXEROBJ)m_hMixer, &mxl, MIXER_GETLINEINFOF_DESTINATION);
		
		if (FAILED(hr)) 
			{
			P2N("CxMixer::CxMixer Failed to get mixerGetLineInfor\r\n");
			xShowErr(hr);
			continue;
			}

		if(mxl.dwComponentType != (DWORD)xdest)
			continue;

		//xShowStruct(&mxl, "");
	
		UINT count = mxl.cConnections;

		for(UINT ii = 0; ii < count; ii++)
			{
			MIXERLINE  mxxl; memset(&mxxl, 0, sizeof(mxxl));
			mxxl.cbStruct = sizeof(mxxl);

			mxxl.dwLineID = mxl.dwLineID;				
			mxxl.dwSource = ii;
			mxxl.dwDestination = mxl.dwDestination;

			hr = mixerGetLineInfo((HMIXEROBJ)m_hMixer, &mxxl, 
								MIXER_GETLINEINFOF_SOURCE  );

			if (FAILED(hr))
				{
				P2N("CxMixer::CxMixer mixerGetLineInfo failed\r\n");
				xShowErr(hr);
				continue;
				}

			if(mxxl.dwComponentType != (DWORD)xsrc)
				continue;

			//xShowStruct(&mxxl, "   ");

			MIXERCONTROL mc;	memset(&mc, 0, sizeof(mc));
			mc.cbStruct = sizeof(mc);	
			
			MIXERLINECONTROLS mxlc;	memset(&mxlc, 0, sizeof(mxlc));
			mxlc.cbStruct = sizeof(mxlc);

			mxlc.dwLineID = mxxl.dwLineID;
			mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
			mxlc.cControls = 1;
			mxlc.cbmxctrl = sizeof(MIXERCONTROL);
			mxlc.pamxctrl = &mc;

			hr = mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, 
									MIXER_GETLINECONTROLSF_ONEBYTYPE);
			
			if (FAILED(hr))
				{
				P2N("CxMixer::CxMixer mixerGetLineControls failed\r\n");
				xShowErr(hr);
				}
			else
				{
				//P2N("    Mixer control found on device=%d type-%x id=%d\r\n\r\n",  
				//				xdevice, mc.dwControlType, mc.dwControlID );
				
				// Only assign the first found (safety measure)
				if(!m_bOK)
					{
					m_dwChannels = mxxl.cChannels;
					m_dwControlID = mc.dwControlID;
					m_bOK = true;
					}
				}
			}
		}
	return true;
}

//////////////////////////////////////////////////////////////////////////

CxMixer::~CxMixer()

{
	if(m_opened)
		{
		mixerClose(m_hMixer); m_opened = false; m_hMixer = NULL;
		}
}

//////////////////////////////////////////////////////////////////////////
// Currently open device

DWORD		CxMixer::GetDevice()

{
	return (DWORD) m_hMixer;
}

//////////////////////////////////////////////////////////////////////////

int		CxMixer::SetVolume(DWORD dwVol)

{
	int ret = 0;
	
	if (!m_bOK) 
		{
		P2N("Please initialize CxMixer first by calling SetDevice\r\n");
		return ret;
		}

	HRESULT hr;
	
	MIXERCONTROLDETAILS_UNSIGNED mxdu; memset(&mxdu, 0, sizeof(mxdu));
	MIXERCONTROLDETAILS mxcd; memset(&mxcd, 0, sizeof(mxcd));

	mxdu.dwValue = dwVol;

	mxcd.cMultipleItems = 0;
	mxcd.cChannels = m_dwChannels;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.dwControlID = m_dwControlID;
	mxcd.cbDetails = sizeof(mxdu);
	mxcd.paDetails = &mxdu;

	hr = mixerSetControlDetails((HMIXEROBJ)xdevice, &mxcd, 
								MIXER_SETCONTROLDETAILSF_VALUE | xscanfor);	
	
	if (FAILED(hr))
		{
		P2N("CxMixer::SetVolume() Failed to set volume\r\n");
		xShowErr(hr);		
		}
	else
		{
		ret = true;
		}
	
	return ret;
}

//////////////////////////////////////////////////////////////////////////

DWORD CxMixer::GetVolume()

{
	MIXERCONTROLDETAILS_UNSIGNED mxdu; mxdu.dwValue = 0;
	MIXERCONTROLDETAILS mxcd; memset(&mxcd, 0, sizeof(mxcd));

	if (!m_bOK) 
		{
		P2N("Please initialize CxMixer first by calling SetDevice\r\n");
		return mxdu.dwValue;
		}

	HRESULT hr;
	
	mxcd.cMultipleItems = 0;
	mxcd.cChannels = m_dwChannels;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.dwControlID = m_dwControlID;
	mxcd.cbDetails = sizeof(mxdu);
	mxcd.paDetails = &mxdu;
	hr = mixerGetControlDetails((HMIXEROBJ)xdevice, &mxcd, 
						MIXER_GETCONTROLDETAILSF_VALUE | xscanfor);	

	if (FAILED(hr))
		{
		P2N("CxMixer::GetVolume Failed to get volume\r\n");	
		xShowErr(hr);		
		}
	
	return mxdu.dwValue;
}

//////////////////////////////////////////////////////////////////////////

void	CxMixer::GetMinMax(int *minval, int *maxval)
	
{
	HRESULT hr;

	if (!m_bOK) 
		{
		P2N("Please initialize CxMixer first by calling SetDevice\r\n");
		return;
		}

	MIXERCONTROL mc;	memset(&mc, 0, sizeof(mc));
	mc.cbStruct = sizeof(mc);	

	MIXERLINECONTROLS mxlc;	memset(&mxlc, 0, sizeof(mxlc));
	mxlc.cbStruct = sizeof(mxlc);

	mxlc.dwControlID = m_dwControlID;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = &mc;

	hr = mixerGetLineControls((HMIXEROBJ)xdevice, &mxlc, 
							MIXER_GETLINECONTROLSF_ONEBYID  | xscanfor);
						
	if (FAILED(hr))
		{
		P2N("CxMixer::CxMixer mixerGetLineControls failed\r\n");
		xShowErr(hr);
		}
	
	*minval = mc.Bounds.dwMinimum;
	*maxval = mc.Bounds.dwMaximum;
}

//////////////////////////////////////////////////////////////////////////
// The functions below help debugging

void CxMixer::xShowErr(int hr)

{
	if(MIXERR_INVALLINE == hr)
		P2N("MIXERR_INVALLINE\r\n");

	if(MMSYSERR_BADDEVICEID == hr)
		P2N("MMSYSERR_BADDEVICEID\r\n");

	if(MMSYSERR_INVALFLAG == hr)
		P2N("MMSYSERR_INVALFLAG\r\n");

	if(MMSYSERR_INVALHANDLE == hr)
		P2N("MMSYSERR_INVALHANDLE\r\n");
	
	if(MMSYSERR_INVALPARAM == hr)
		P2N("MMSYSERR_INVALPARAM\r\n");

	if(MMSYSERR_NODRIVER == hr)
		P2N("MMSYSERR_NODRIVER\r\n");

	if(MIXERR_INVALCONTROL == hr)
		P2N("MIXERR_INVALCONTROL\r\n");

	

}

//////////////////////////////////////////////////////////////////////////

void CxMixer::xShowStruct(MIXERLINE *ptr, const char *str)

{	
	P2N("%scbStruct=%d "       ,str ,ptr->cbStruct);
	P2N("%sdwDestination=%d "   ,str    ,ptr->dwDestination); 
	P2N("%sdwSource=%d "      ,str ,ptr->dwSource); 
	P2N("%sdwLineID=%d\r\n"     ,str  ,ptr->dwLineID); 
	P2N("%sfdwLine=%d "      ,str ,ptr->fdwLine); 
	P2N("%sdwUser=%d "       ,str,ptr->dwUser); 
	P2N("%sdwComponentType=%x\r\n"    ,str   ,ptr->dwComponentType); 
	P2N("%scChannels=%d  "      ,str ,ptr->cChannels); 
	P2N("%scConnections=%d "     ,str  ,ptr->cConnections); 
	P2N("%scControls=%d\r\n"     ,str  ,ptr->cControls); 
	P2N("%sszShortName='%s'\r\n"  ,str     ,ptr->szShortName); 
	P2N("%sszName='%s' \r\n"     ,str  ,ptr->szName); 
	P2N("%sTarget.dwType=%d "     ,str 	,ptr->Target.dwType);  
	P2N("%sTarget.dwDeviceID=%d "  ,str    	,ptr->Target.dwDeviceID);  
	P2N("%sTarget.wMid=%d "      ,str	,ptr->Target.wMid);  
	P2N("%sTarget.wPid=%d "      ,str	,ptr->Target.wPid);  
	P2N("%sTarget.vDriverVersion=%d; \r\n"    ,str  	,ptr->Target.vDriverVersion);  
	P2N("%sTarget.szPname='%s';\r\n\r\n"    ,str  	,ptr->Target.szPname);  
}

