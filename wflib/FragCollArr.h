
/* =====[ FragCollArr.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the FragCollArr.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/21/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_FRAGCOLLARR_H__678CA53E_7C7F_4337_AAB7_5CA039AA3326__INCLUDED_)
#define AFX_FRAGCOLLARR_H__678CA53E_7C7F_4337_AAB7_5CA039AA3326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFragCollArr  

{
public:

	friend class CFragColl;

	static char defname[];

	CFragCollArr();	virtual ~CFragCollArr();

	int	 LoadAll(const char *fname); int	 SaveAll(const char *fname);

	CFragColl*	 GetCollPtr(const char *name);
	CFragColl*	 GetAt(int idx);

	int	 AddSpeaker(const char *name);
	int	 RemoveSpeaker(const char *name);
	
	int	 GetSize() { return xarr.GetSize(); };
	int	 GetSpeakerName(int idx, CString &str);
	int	 SetCurrSpeaker(const char *name);

	void SetFragDir(CCHAR *dir);
	void SetWaveDir(CCHAR *dir);

	int	 GetCurrSpeaker(CString &str);
	int	 GetCurrSpeaker();

	//////////////////////////////////////////////////////////////////////
	
	int	 Dump();
	void Clear();
	
	//////////////////////////////////////////////////////////////////////////
	// Compile all wav data

	int	 CompileAll();	
	int	 CompileSpeaker(const char *speaker);
	int	 StopCompile();
	
	void SetChangeFlag(int flag = true);

	void BuildIdx();

	CString		rootfragdir, rootwavdir;

	int stop;

protected:

	int xcurridx, xchanged;

private:

	CStringArray xnames;
	CPtrArray	 xarr;
	CPtrArray	 xidx;

};

#endif // !defined(AFX_FRAGCOLLARR_H__678CA53E_7C7F_4337_AAB7_5CA039AA3326__INCLUDED_)
