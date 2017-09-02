
/* =====[ wflib.cpp ]==========================================================

   Description:     The wflib project, implementation of the wflib.cpp

                    Defines the behavior for the application.

   Compiled:        MS-VC 6.00

   Notes:           <Empty Notes>

   Revisions:

      REV     DATE        BY            DESCRIPTION
      ----  --------  -----------  ----------------------------
      0.00  9/24/2010  Peter Glen   Initial version.
	  0.00  6/13/2012  Peter Glen   More

   ======================================================================= */

#include "stdafx.h"
#include <io.h>
#include <direct.h>

#include "wflib.h"
#include "mxpad.h"
#include "frag.h"
#include "fragcoll.h"
#include "FragCollArr.h"
#include "xrecog.h"
#include "fftbuff.h"
#include "RecordSound.h"
#include "support.h"
#include "ContColl.h"

extern  CStrColl   dicstrcoll;

// Remove mxpad sync calls
#undef P2N

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWflibApp

class CWflibApp : public CWinApp

{
public:

    //int TestEntry(int val);
    CWflibApp();

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWflibApp)
    //}}AFX_VIRTUAL

    //{{AFX_MSG(CWflibApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//
//  Note from the MFC documentation:
//
//      If this DLL is dynamically linked against the MFC
//      DLLs, any functions exported from this DLL which
//      call into MFC must have the AFX_MANAGE_STATE macro
//      added at the very beginning of the function.
//
//      For example:
//
//      extern "C" BOOL PASCAL EXPORT ExportedFunction()
//      {
//          AFX_MANAGE_STATE(AfxGetStaticModuleState());
//          // normal function body here
//      }
//
//      It is very important that this macro appear in each
//      function, prior to any calls into MFC.  This means that
//      it must appear as the first statement within the
//      function, even before any object variable declarations
//      as their constructors may generate calls into the MFC
//      DLL.
//
//      Please see MFC Technical Notes 33 and 58 for additional
//      details.
//

//////////////////////////////////////////////////////////////////////////
// On the note 'AFX_MANAGE_STATE'; (above) pls do not insert it in 
// this file, despite what MS says. It breaks things badly. WTF
//

/////////////////////////////////////////////////////////////////////////////
// CWflibApp

BEGIN_MESSAGE_MAP(CWflibApp, CWinApp)
    //{{AFX_MSG_MAP(CWflibApp)      .
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWflibApp construction

CWflibApp::CWflibApp()

{  

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWflibApp object

CWflibApp theApp;

//////////////////////////////////////////////////////////////////////////
 // Globals for this DLL

int  dllver = 210;					// Increment this if interface chaged
int  noprompt = false, reload = false;

// Frag management
CFragColl       *pfragcoll = NULL;	  // Current frag coll to operate on
CFragCollArr	fragcollarr;	

// Recognition object
CxRecog         xdllrecog;

// Supporting objects
CFftBuff        fftbuff;
CRecordSound    recsnd;

// ***********************************************************************
//
// Helper functions
//
// ***********************************************************************

//////////////////////////////////////////////////////////////////////////
// Is it a valid frag name

static  IsFragName(const char *str)

{
    int ret = 0;

	ASSERT(pfragcoll->magic == CFragColl_Magic);

    int alen = pfragcoll->GetStrData()->GetSize();
    for(int loop = 0; loop < alen; loop++)
        {
        CString cstr = pfragcoll->GetStrData()->GetAt(loop);

        if(cstr.CompareNoCase(str) == 0)
            {
            //AP2N("IsFragName Found %s %s\r\n", cstr);
            ret = true;
            break;
            }
        }

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Return the DLL version  (major / 10 -- minor % 10)

int     WFL_Version()

{
    //AP2N("Returning DLL Version %d\r\n", ver);
    return dllver;
}

//////////////////////////////////////////////////////////////////////////
// Force recognition (if buffer too long like uninterrupted noise)

void WFL_Emit()

{
    xdllrecog.Recognize(0);
}

//////////////////////////////////////////////////////////////////////////
// Stop recognition and disable all callbacks

void WFL_ShutDown()

{
    // Disable callbacks
    WFL_SetWavCallback(NULL);
    WFL_SetWavCallback2(NULL);

    WFL_SetFragCallback(NULL);
    WFL_SetFragCallback2(NULL);

    WFL_SetStrCallback(NULL);
    WFL_SetLedCallback(NULL);

    WFL_SetPerfCallback(NULL);
    WFL_SetSpectCallback(NULL);
    WFL_SetSpectCallback2(NULL);
    WFL_SetPlotCallback(NULL);

    // Break out of loops
    xdllrecog.meshutdown = true;

	// Remember to instruct the interfacee to yield
}

//////////////////////////////////////////////////////////////////////////
// On the note 'AFX_MANAGE_STATE'; pls do not insert it here, as this
// is an async call, the state is not determined while this executes.
//

void    WFL_FeedSound(const char *buff, int len)

{
    //AP2N("FeedSound(buff = %p len=%d)\r\n", buff, len);

    // We ignore the orgclass pointer, using our version of the class
    //xdllrecog._statRec((void*)&xdllrecog, (char*)buff, len);

    xdllrecog.Feed((char*)buff, len);
}

//////////////////////////////////////////////////////////////////////////
// Set calbacks

int     WFL_SetStrCallback(PFUNCSI func)

{
    xdllrecog._strrec = func;

    //WFL_GetLicStatus(1);

    return 0;
}

int     WFL_SetWavCallback(PFUNCSI func)

{
    xdllrecog._wavrec = func;
    return 0;
}

int     WFL_SetWavCallback2(PFUNCSI func)

{
    xdllrecog._wavrec2 = func;
    return 0;
}


int     WFL_SetFragCallback(PFUNCSI func)

{
    xdllrecog._fragrec = func;
    return 0;
}

int     WFL_SetFragCallback2(PFUNCSI func)

{
    xdllrecog._fragrec2 = func;
    return 0;
}

int WFL_SetLedCallback(PFUNCSI func)

{
    xdllrecog._ledrec = func;
    return 0;
}

int     WFL_SetPerfCallback(PFUNCSI func)

{
    xdllrecog._perfrec = func;
    return 0;
}

int     WFL_SetSpectCallback(PFUNCPII func)

{
    xdllrecog._spectrec = func;
    return 0;
}

int     WFL_SetSpectCallback2(PFUNCPII func)

{
    xdllrecog._spectrec2 = func;
    return 0;
}

int     WFL_SetPlotCallback(PFUNCPIII func)

{
    xdllrecog._plotrec = func;
    return 0;
}

//////////////////////////////////////////////////////////////////////////
// Load all frags into memory

int     WFL_LoadAllFrags(CCHAR *fname)

{
    //AP2N("WFL_LoadAllFrags frags from %s\r\n", fname);

    int ret = fragcollarr.LoadAll(fname);
    
    return(ret);
}

//////////////////////////////////////////////////////////////////////////

int     WFL_ParseFragWav(CCHAR *pname, int force)

{
	if(pfragcoll == NULL)
		return -1;

	ASSERT(pfragcoll->magic == CFragColl_Magic);

	CString fdir = pfragcoll->GetFragDir(), wdir = pfragcoll->GetWavDir();

	int ret = CFrag::ParseFragWav(pname, wdir, fdir, force);

	if(ret >= 0)
		fragcollarr.SetChangeFlag();

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Load one frag from file

int     WFL_LoadFrag(CCHAR *fname)

{
	if(pfragcoll == NULL)
		return -1;

	ASSERT(pfragcoll->magic == CFragColl_Magic);

	int ret = 0;
	CString fragname = pfragcoll->GetFragDir(); fragname += fname;
    
    AP2N("WFL_LoadFrag from %s\r\n", fragname);

    CFrag  *pfrag = new CFrag;
    ret = pfrag->LoadFrag(fragname, false);

    //if(ret < 0)
	//	{
    //  AP2N("WFL_LoadFrag load error on fname='%s'\r\n", fname);
	//	}	

    pfragcoll->AddFrag(pfrag);

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// 

int     WFL_SaveAllFrags(CCHAR *fname)

{
    //AP2N("Saving frags to %s\r\n", fragcollarr.rootfragdir);

	int ret = fragcollarr.SaveAll(fname);

    return ret;
}

//////////////////////////////////////////////////////////////////////////

int WFL_GetFragName(int idx, char *ptr, int strlim)

{
	if(pfragcoll == NULL)
		return -1;

    if(idx >= pfragcoll->GetData()->GetSize())
        return -1;

    CFrag *fr = (CFrag *)pfragcoll->GetData()->GetAt(idx);

    strncpy(ptr, *fr->name, strlim);

	int ret = fr->name->GetLength();
	// Terminate if larger
	if(ret > strlim && strlim >= 0)
		ptr[strlim - 1] = '\0';

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Get frag string by index

int WFL_GetFragStr(int idx, char *ptr, int strlim)

{
	if(pfragcoll == NULL)
		return -1;

 	ASSERT(pfragcoll->magic == CFragColl_Magic);
	
    if(idx >= pfragcoll->GetStrData()->GetSize())
        return -1;

    CString cstr = pfragcoll->GetStrData()->GetAt(idx);	
	int ret = cstr.GetLength();

	strncpy(ptr, cstr, strlim);

	// Terminate if larger
	if(ret > strlim && strlim >= 0)
		ptr[strlim - 1] = '\0';
	
    return ret;
}

//////////////////////////////////////////////////////////////////////////

int WFL_SetStrict(int flag)

{
    int ret = xdllrecog.strict;

    xdllrecog.strict = flag;

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Below this is considered noise. Range: 0-32k default: 2000

int WFL_SetNoisetresh(int tresh)

{
    int ret = xdllrecog.NoiseLevel;

    xdllrecog.NoiseLevel = tresh;

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// The DLL will not call out to messagebox

int WFL_SetNoPrompt(int flag)

{
    int ret = noprompt;

    noprompt = flag;
    xdllrecog.noprompt = flag;
    //pfragcoll->noprompt = flag;

    return ret;
}

//////////////////////////////////////////////////////////////////////////

int WFL_GetFragSize(int idx)

{
    if(idx >= pfragcoll->GetData()->GetSize())
        return -1;

    CFrag *fr = (CFrag *)pfragcoll->GetData()->GetAt(idx);

    return(fr->GetUnitSize());
}

//////////////////////////////////////////////////////////////////////////

int WFL_GetFragContext(int idx)

{
    if(idx >= pfragcoll->GetData()->GetSize())
        return -1;

    CFrag *fr = (CFrag *)pfragcoll->GetData()->GetAt(idx);

    //return(fr->context);
    return(FALSE);
}

//////////////////////////////////////////////////////////////////////////
// ret < 0 if error

int     WFL_SaveWavAndFrag(CCHAR *name, char *pwavdat, int len)

{
    CString tmp, tmp2; int ret = 0, ret2 = 0, cnt = 1; 

	AP2N("WFL_SaveWavAndFrag name='%s'\r\n", name);

	CString wavdir = pfragcoll->GetWavDir();
	CString fragdir = pfragcoll->GetFragDir();
    
    // Get file unique name, scan wave and frag dir
    while(true)
        {
        tmp.Format("%s-%02d%s", name, cnt, CFrag::wavext);
		tmp2.Format("%s%s", wavdir, tmp);

        if(access(tmp2, 0) < 0)
            {
            //AP2N("Found empty file slot %s\t\n", tmp);
            if(!IsFragName(tmp2))
                {
                //AP2N("Found empty frag slot %s\t\n", tmp);
                break;
                }
            }
        cnt++;
        }

    AP2N("WFL_SaveWavAndFrag file '%s'\r\n", tmp2);

    // Finally, save it here
    if(!dsp.SaveWave(tmp2, pwavdat, len))
        {
        //AfxMessageBox("WFL_SaveWavAndFrag: Cannot save wave");
		AP2N("WFL_SaveWavAndFrag: Cannot save wave %s", tmp2);
		ret = -1;
		return ret;
        }

    // Convert
    ret = CFrag::ParseFragWav(tmp, wavdir, fragdir, true);

    CString fragname; fragname.Format("%s-%02d%s", name, cnt, CFrag::fragext);

    // Load
	ret2 = WFL_LoadFrag(fragname);

	if(ret >= 0)
		fragcollarr.SetChangeFlag();

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Removes a whole frag from memory

int     WFL_DelFragWord(CCHAR *pword)

{
    //AP2N("WFL_DelWord %s\r\n", pword);

    int ret = pfragcoll->DelWord(pword);
    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Removes one frag entry

int     WFL_DelFragEntry(CCHAR *pword, CCHAR *pentry)

{
    //AP2N("WFL_DelFragEntry %s %s\r\n", pword, pentry);

    int ret = pfragcoll->DelFragEntry(pword, pentry);
    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Gets a frag

int     WFL_GetFragEntry(CCHAR *pword, int idx, char *ptr, int strlim)

{
    int ret = 0;

    int alen = pfragcoll->GetStrData()->GetSize();
    for(int loop = 0; loop < alen; loop++)
        {
        CString cstr = pfragcoll->GetStrData()->GetAt(loop);

        if(cstr.CompareNoCase(pword) == 0)
            {
            //AP2N("WFL_GetFragEntry %s %s\r\n", cstr, pword);
            break;
            }
        }

    // Found
    if(loop >= alen)
        return -1;

    int alen2 = pfragcoll->GetData()->GetSize();
    for(int loop2 = 0; loop2 < alen2; loop2++)
        {
        CFrag *fr = (CFrag *)pfragcoll->GetData()->GetAt(loop2);

        if(fr->shortname->CompareNoCase(pword) == 0)
            {
            //AP2N("WFL_GetFragEntry Found1 %s %s\r\n", *fr->name, pword);

            if(idx == 0)
                {
                //AP2N("WFL_GetFragEntry Found2 %s %s\r\n", *fr->name, pword);               

                strncpy(ptr, *fr->name, strlim);

				ret = fr->name->GetLength();
				
				// Terminate if larger
				if(ret > strlim && strlim >= 0)
					ptr[strlim - 1] = '\0';

				break;
                }
            idx--;
            }
        }

    if(!ret)
        return -2;

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Get last stored wave

void    WFL_GetLastWav(char **ptr, int *plen)

{
    xdllrecog.lock.Lock();

    *ptr  = xdllrecog.lastbuff;
    *plen = xdllrecog.lastbuflen;

    xdllrecog.lock.Unlock();
}

//////////////////////////////////////////////////////////////////////////
// Reload all frags from waves

int WFL_ParseAllFragWaves()

{
    //int ret = pfragcoll->ParseAllFragWaves(pfragcoll->wavdir, pfragcoll->fragdir, reload);

    reload = false;

    return 0;
}

//////////////////////////////////////////////////////////////////////////

int WFL_GetLicStatus(int flag)

{
    int     ret = 0; char   str[32] = "";

    // Estabilish first time usage
    time_t sumtime = time(NULL);
    time_t firsttime = support.GetRegInt(HKEY_CURRENT_USER,  "Software\\RobotMonkeySoftware\\WavFrag", "FirstUse");
    time_t firsttime2 = support.GetRegInt(HKEY_CURRENT_USER,  "Software\\RobotMonkeySoftware\\WavFrag\\License", "FirstUse");

    CString fname; support.GetProgDataDir(fname);

    // Create app data even if we do not have install running
    fname += "WavFrag\\"; if(!support.IsDir(fname))
            mkdir(fname);
    fname += ".WavFrag.txt";

    //AP2N("Licence file name %s\r\n", fname);

    // Estabilish first time usage from data dir
    CFile fpr;
    int retr = fpr.Open(fname, CFile::modeRead);
    if(retr)
        {
        fpr.Read(str, sizeof(str));
        }
    time_t firsttime3 = 0;  sscanf(str, "%d", &firsttime3);

    //AP2N("Got first use %x\r\n", firsttime);
    //AP2N("Got first use2 %x\r\n", firsttime2);
    //AP2N("Got first use3 %x\r\n", firsttime3);

    // Estabilish first
    if(firsttime)  sumtime = min(firsttime, sumtime);
    if(firsttime2) sumtime = min(firsttime2, sumtime);
    if(firsttime3) sumtime = min(firsttime3, sumtime);

    //AP2N("Got sumtime %x\r\n", sumtime);

    if(firsttime == 0 || firsttime2 == 0)
        {
        firsttime = time(NULL);

        //AP2N("Wrote first use %x\r\n", firsttime);

        support.SetRegInt(HKEY_CURRENT_USER,  "Software\\RobotMonkeySoftware\\WavFrag", "FirstUse", sumtime);
        support.SetRegInt(HKEY_CURRENT_USER,  "Software\\RobotMonkeySoftware\\WavFrag\\License", "FirstUse", sumtime);
        }

    if(!support.IsFile(fname))
        {
        //AP2N("Create licence file '%s'\r\n", fname);

        CString tmp; tmp.Format("%d", sumtime);
        CFile fp;
        int ret = fp.Open(fname, CFile::modeCreate | CFile::modeWrite);
        if(ret)
            {
            fp.Write(tmp, tmp.GetLength());
            fp.Close();

            DWORD oldattr = GetFileAttributes(fname);
            SetFileAttributes(fname, oldattr | FILE_ATTRIBUTE_HIDDEN);
            }
        else
            {
            //AP2N("Cannot create file \r\n");
            }
        }

    time_t ttt = time(NULL);
    CTimeSpan ts(ttt -  firsttime);
    ret = ts.GetMinutes() * flag;
    //ret = ts.GetDays() * flag;

    return ret;
}

// ***********************************************************************
//
// String collection (dictionary) related entries
//
// ***********************************************************************

//////////////////////////////////////////////////////////////////////////
// Load/Save  string collection

void WFL_LoadStrColl(CCHAR *fname)

{
    dicstrcoll.Load(fname);
}

void WFL_SaveStrColl(CCHAR *fname)

{
    dicstrcoll.Save(fname);
}

//////////////////////////////////////////////////////////////////////////
// New train string, empty if stop training

void    WFL_SetTrainStr(CCHAR *pname)

{
    xdllrecog.trainstr = pname;
}

//////////////////////////////////////////////////////////////////////////
// Clear all training for str or all data if NULL

void WFL_ClearTraining(CCHAR *pname)

{
	//AP2N("WFL_ClearTraining %s\r\n", pname);

    dicstrcoll.Clear(pname);
}

void WFL_ClearTrainItem(CCHAR *pname, CCHAR *pitem)

{
	//AP2N("WFL_ClearTrainItem %s\r\n", pname);

    dicstrcoll.ClearItem(pname, pitem);
}

//////////////////////////////////////////////////////////////////////////
// Collection getters

int  WFL_GetCollName(int idx, char *str, int maxlen)

{
	int ret; CString cstr;

	ret = dicstrcoll.GetCollName(idx, cstr);

	strncpy(str, cstr, maxlen);

	// terminate if larger
	if(ret > maxlen && maxlen >= 0)
		str[maxlen - 1] = '\0';

	//AP2N("WFL_GetCollName ret=%d %s\r\n", ret, str);

	return ret;
}

int  WFL_GetCollStr(int idx, int idx2, char *str, int maxlen)

{
	int ret; CString cstr;

	ret = dicstrcoll.GetCollStr(idx, idx2, cstr);

	strncpy(str, cstr, maxlen);

	// terminate if larger
	if(ret > maxlen && maxlen >= 0)
		str[maxlen - 1] = '\0';

	//AP2N("WFL_GetCollStr ret=%d %s\r\n", ret, str);

	return ret;
}

//-----------------------------------------------------------------------
// Frag Related functions

//////////////////////////////////////////////////////////////////////////
// Set / Get frag directory

void    WFL_SetFragDir(CCHAR *dir)

{
	fragcollarr.SetFragDir(dir);
}

void WFL_GetFragDir(char *dir, int len)

{
	strncpy(dir, fragcollarr.rootfragdir, len);

	if(len >= 0 && fragcollarr.rootfragdir.GetLength() > len)
		dir[len-1] = '\0';
}

//////////////////////////////////////////////////////////////////////////
// Set / Get wave directory

void    WFL_SetWavDir(CCHAR *dir)

{
    fragcollarr.SetWaveDir(dir);
}

void WFL_GetWavDir(char *dir, int len)

{
    strncpy(dir, fragcollarr.rootwavdir, len);

	if(len >= 0 && fragcollarr.rootwavdir.GetLength() > len)
		dir[len-1] = '\0';
}

////////////////////////////////////////////////////////////////////////////
//// Force reload
//
//int    WFL_SetReload(int flag)
//
//{
//	int old = reload;
//    reload = flag;
//	return old;
//}

void    WFL_Abort()

{
	pfragcoll->stop = true;
}

//////////////////////////////////////////////////////////////////////////

int     WFL_SetSilSpeed(int val)

{
    int ret = xdllrecog.ChangeTresh;

    xdllrecog.ChangeTresh = val;

    return ret;
}

//////////////////////////////////////////////////////////////////////////
// Handle the sound device

int     WFL_WaveInOpen(int dev)

{
    //recsnd.silent = true;
    return (int)recsnd.WaveInOpen(dev);
}

void    WFL_WaveInClose()

{
    recsnd.WaveInClose();
}

void    WFL_WaveStart()

{
    recsnd.StartRecord();
}

void    WFL_WaveStop()

{
    recsnd.StopRecord();
}

int    WFL_WaveIsRec()

{
	return recsnd.recording;
}

void    WFL_WaveConnect(PFUNCSI ptrfunc)

{
    //recsnd.callthis = (CRecordSound::PFPCIRI) ptrfunc;
    recsnd.callthis = ptrfunc;
}

//////////////////////////////////////////////////////////////////////////
// Functions for diagnostics:

void WFL_ScanBuffer(const char *buff, int len, CPtrArray *parr)

{
    CAnalRes res;

    xdllrecog.ScanSpectra((char*)buff, len, &res);
    xdllrecog.analproc.ProcSpectra(&res, xdllrecog.FreqCompCnt);
}

//////////////////////////////////////////////////////////////////////////
// Add Frag Speaker

int     WFL_AddFragSpeaker(const char *name)

{
    //AP2N("WFL_AddFragSpeaker %s\r\n", name);
    
	int ret = fragcollarr.AddSpeaker(name);

    return(ret);
}

//////////////////////////////////////////////////////////////////////////
// Delete frag speaker

int     WFL_DelFragSpeaker(const char *name)

{
    //AP2N("WFL_DelFragSpeaker %s\r\n", name);

	int ret = fragcollarr.RemoveSpeaker(name);

    return(ret);
}

//////////////////////////////////////////////////////////////////////////

int     WFL_GetFragSpeaker(int idx, char *str, int maxlen)

{
	int ret; CString cstr;

	ret = fragcollarr.GetSpeakerName(idx, cstr);

	strncpy(str, cstr, maxlen);

	// terminate if larger
	if(ret > maxlen && maxlen >= 0)
		str[maxlen - 1] = '\0';

	//AP2N("WFL_GetFragSpeaker ret=%d %s\r\n", ret, str);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int		WFL_SetCurrSpeaker(const char *str)

{
	int ret = fragcollarr.SetCurrSpeaker(str);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int		WFL_GetCurrSpeaker(char *str, int maxlen)

{
	CString cstr;

	int ret = fragcollarr.GetCurrSpeaker(cstr);

	strncpy(str, cstr, maxlen);

	// terminate if larger
	if(ret > maxlen && maxlen >= 0)
		str[maxlen - 1] = '\0';

	return ret;
}

//////////////////////////////////////////////////////////////////////////
/// Abort load

int     WFL_CompileFrags()

{	
	//AP2N("WFL_CompileFrags\r\n");
	int ret = fragcollarr.CompileAll();
	return ret;
}

int     WFL_ClearFrags()

{
	CString fdir = pfragcoll->GetFragDir();
	int  ret = pfragcoll->ClearOldFrags(fdir);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Abort load

void    WFL_StopCompile()

{
	fragcollarr.StopCompile();
}
