
/* =====[ Mixer.h ]========================================== 
                                                                             
   Description:     The dogtalk project, implementation of the Mixer.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  12/17/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_MIXER_H__6AC26CD7_97BC_4721_8248_423000A8B0E7__INCLUDED_)
#define AFX_MIXER_H__6AC26CD7_97BC_4721_8248_423000A8B0E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		MIX_MIC_RECORD		0
#define		MIX_MIC_MONITOR		1
#define		MIX_SPEAKER			2

#include <mmsystem.h>

class CxMixer  
{

public:
	
	CxMixer();
	~CxMixer();

	DWORD	GetVolume();
	int		SetVolume(DWORD dwVol);
	void	GetMinMax(int *minval, int *maxval);
	int		SetDevice(int kind, int devi, HWND  callback = NULL);
	DWORD	GetDevice();

private:

	// Data
	int		xdevice, xscanfor, xdest, xsrc;
	int		m_bOK, m_kind, m_opened;

	DWORD	m_dwChannels, m_dwControlID;

	HMIXER	m_hMixer;	

	
	// Functions
	void	xShowStruct(MIXERLINE *ptr, const char *str);
	void	xShowErr(int hr);
	
};

#endif // !defined(AFX_MIXER_H__6AC26CD7_97BC_4721_8248_423000A8B0E7__INCLUDED_)
