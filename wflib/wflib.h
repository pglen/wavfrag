
/* =====[ wflib.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the wflib voice 
					recognition DLL
                                                                             
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           C callable, created for the least common denominator
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/24/2010  Peter Glen   Initial version.                         
      0.00  4/16/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_WFLIB_H__DFF3218F_3326_4B41_93F3_2F8EF955C050__INCLUDED_)
#define AFX_WFLIB_H__DFF3218F_3326_4B41_93F3_2F8EF955C050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*! \mainpage

  This DLL represents a breakthru in voice recognition. After two years of 
  research, we finally cracjed the code on how a biological entity recognizes 
  speech so eazily, and why the computer has such difficuty with it.

  The naming convention of the DLLs exported 

 */

//////////////////////////////////////////////////////////////////////////
// Shorthand for standard types

#define WFL_DLL  __declspec(dllexport) ///< Shorthand for export define
#define CCHAR const char			   ///< Shorthand for constant character


/// \addtogroup aaa Typedefs for the callback functions
/// 

//@{

/// PFUNCSI Pointer to a function expecting a pointer to constant char (string)
/// and a length.

typedef void (*PFUNCSI)(CCHAR *str, int len); 
typedef void (*PFUNCV)(void *ptr);
typedef void (*PFUNCPII)(int *ptr, int len);
typedef void (*PFUNCPIII)(int *ptr, int len, int idx);

//@}


//////////////////////////////////////////////////////////////////////////
// Created for the least common denominator

extern "C"

{

/// \addtogroup bbb Convenience functions
/// 
/// These functions estabilish the running parameters of the machine
///

//@{

//////////////////////////////////////////////////////////////////////////
/// \brief Return the running version of the Lib
///
/// Return:
///
///		Format: major * 100 + minor * 10 + subminor * 1
///
/// Examples: 
///
///		Version 1.00 -> 100;  Version 1.02 -> 102;  Version 1.10 -> 110
///

WFL_DLL int WFL_Version();					///< Version of the DLL
WFL_DLL int	WFL_GetLicStatus(int flag);		///< Return number of days used
WFL_DLL void WFL_Abort();					///< Abort current operation (noop)

//@}

//////////////////////////////////////////////////////////////////////////

/// \addtogroup ccc Wave and frag dirs
/// 
/// These functions manage the wave and frag directories.
///

//@{

WFL_DLL void WFL_SetWavDir(CCHAR *dir);			///< Waves go here
WFL_DLL void WFL_GetWavDir(char *dir, int len);	///< Query wavdir

WFL_DLL void WFL_SetFragDir(CCHAR *dir);		///< Frags go here
WFL_DLL void WFL_GetFragDir(char *dir, int len);///< Query fragdir

//@}

//////////////////////////////////////////////////////////////////////////
// 

/// \addtogroup ddd String Collection Management
/// 
/// These functions manage string collection and training.
///

//@{

/// Set current str to train
WFL_DLL void WFL_SetTrainStr(CCHAR *pname);		

/// Clear string. Pass NULL for clearing all training
WFL_DLL void WFL_ClearTraining(CCHAR *pname);	

/// Clear ONE traing item from pname
WFL_DLL void WFL_ClearTrainItem(CCHAR *pname, CCHAR *pitem);

/// Get name of entry by index
WFL_DLL int  WFL_GetCollName(int idx, char *str, int maxlen); 

/// List sub entries by two indexes
WFL_DLL int  WFL_GetCollStr(int idx, int idx2, char *str, int maxlen);

/// Load str coll from file
WFL_DLL void WFL_LoadStrColl(CCHAR *fname);		///< Call On start

/// Save str coll to file
WFL_DLL void WFL_SaveStrColl(CCHAR *fname);		///< Call On end

//@}

//////////////////////////////////////////////////////////////////////////
// 

/// \addtogroup eee Wave Device Encapsulation
///
/// These functions represent the wave device.
///

//@{

WFL_DLL int		WFL_WaveInOpen(int dev);		///< Dev=0 for default
WFL_DLL void	WFL_WaveInClose();				///< Close device

WFL_DLL void	WFL_WaveStart();				///< Start recording
WFL_DLL void	WFL_WaveStop();					///< Stop recording
WFL_DLL int		WFL_WaveIsRec();				///< Is it recording?

// Callback -> VR
WFL_DLL void	WFL_WaveConnect(PFUNCSI	ptrfunc);	

//@}

//////////////////////////////////////////////////////////////////////////
//
// Entry point to feed the sound data to the DLL
// Pass a buffer allocated with malloc, the recognition engine 
// will free() the buffer when it is done with it. 
// There is an overflow mechanism to free it when too many buffers 
// are queued, so one can freely pass any amount.
//
// Advanced function, use WFL_WaveConnect for most cases.
//
//////////////////////////////////////////////////////////////////////////

WFL_DLL void WFL_FeedSound(const char *buff, int len);	// Sound goes in

//////////////////////////////////////////////////////////////////////////
// Emit results. This will force recognition, ignoring the silence 
// mechansm.

WFL_DLL void WFL_Emit();								

//////////////////////////////////////////////////////////////////////////
// Shutdown recognition. Will stop accumulation of data, frees all 
// buffers and prepares for exit; May need to wait for all that to 
// happen, standard windows mechanisms apply. (yield)

WFL_DLL void WFL_ShutDown();

//////////////////////////////////////////////////////////////////////////
// Used mostly in testing. Caller responsible on freeing buffers.

WFL_DLL void WFL_ScanBuffer(const char *buff, int len, CPtrArray *parr);

//////////////////////////////////////////////////////////////////////////
// Get last recognized wav entry. Treat the buffer read only; 
// Valid until next uttering (async buffer, overriden by the next recog)
// Will wait until actual buffer is available, so it is thread safe.
//

WFL_DLL void WFL_GetLastWav(char **ptr, int *plen);

//////////////////////////////////////////////////////////////////////////
// Manage frags
//
// Set the wave dir and frag dir before using these functions with:
//
//     WFL_SetWavDir() WFL_SetFragDir()
//

//////////////////////////////////////////////////////////////////////////
// Manage frag speakers. The 'default' speaker always exists.

WFL_DLL	int WFL_AddFragSpeaker(const char *name);
WFL_DLL	int WFL_DelFragSpeaker(const char *name);
WFL_DLL	int WFL_GetFragSpeaker(int idx, char *str, int maxlen);

WFL_DLL	int WFL_SetCurrSpeaker(const char *str);
WFL_DLL	int WFL_GetCurrSpeaker(char *str, int maxlen);

//////////////////////////////////////////////////////////////////////////

WFL_DLL int	WFL_LoadAllFrags(CCHAR *fname);	// Load all
WFL_DLL int	WFL_SaveAllFrags(CCHAR *fname);	// Save all

WFL_DLL int	WFL_CompileFrags();				// Reload All
WFL_DLL void WFL_StopCompile();				// Abort compile

WFL_DLL int WFL_ParseAllFragWaves();		// Rescan all waves
WFL_DLL int WFL_ParseFragWav(CCHAR *pname); // Resan one wav
WFL_DLL int WFL_ClearFrags();				// Clear old frags

WFL_DLL int	WFL_SaveWavAndFrag(CCHAR *name, char *pwavdat, int len);
WFL_DLL int WFL_LoadFrag(CCHAR *fname);	

//////////////////////////////////////////////////////////////////////////
// Remove frag entries. Operates on current speaker.

WFL_DLL int WFL_DelFragWord(CCHAR *pword);
WFL_DLL int	WFL_DelFragEntry(CCHAR *pword, CCHAR *pentry);

//////////////////////////////////////////////////////////////////////////
// Manage frag entries. Operates on current speaker.

WFL_DLL int WFL_GetFragName(int idx, char *ptr, int strlim);
WFL_DLL int WFL_GetFragSize(int idx);
WFL_DLL int WFL_GetFragContext(int idx);
WFL_DLL int WFL_GetFragStr(int idx, char *ptr, int strlim);
WFL_DLL int WFL_GetFragEntry(CCHAR *pword, int idx, char *ptr, int strlim);

//////////////////////////////////////////////////////////////////////////
// Manage recognition parameters

WFL_DLL int	WFL_SetStrict(int flag);		// Two maching entries needed
WFL_DLL int	WFL_SetNoisetresh(int tresh);	// Trshold for sig recog
WFL_DLL int	WFL_SetNoPrompt(int flag);		// No MessageBoxes (default=off)
WFL_DLL int WFL_SetSilSpeed(int val);		// Sil/Sig lenght to transition

//////////////////////////////////////////////////////////////////////////
// CALLBACKs

WFL_DLL int WFL_SetStrCallback(PFUNCSI func);		// Recognized string
WFL_DLL int WFL_SetFragCallback(PFUNCSI func);		// Recognized frag
WFL_DLL int WFL_SetFragCallback2(PFUNCSI func);		// Recognized frag list

WFL_DLL int WFL_SetWavCallback(PFUNCSI func);		// Wave isolated
WFL_DLL int WFL_SetWavCallback2(PFUNCSI func);		// Wave isolated, stage 2

WFL_DLL int WFL_SetSpectCallback(PFUNCPII func);	// Spectral data
WFL_DLL int WFL_SetSpectCallback2(PFUNCPII func);	// Spectral data stage2

WFL_DLL int WFL_SetLedCallback(PFUNCSI func);		// Led activity
WFL_DLL int WFL_SetPerfCallback(PFUNCSI func);		// Performance data
WFL_DLL	int	WFL_SetPlotCallback(PFUNCPIII func);	// Plot callback 

}

#endif // !defined(AFX_WFLIB_H__DFF3218F_3326_4B41_93F3_2F8EF955C050__INCLUDED_)

// EOF
