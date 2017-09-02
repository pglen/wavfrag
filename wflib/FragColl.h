
/* =====[ FragColl.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the FragColl.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  12/15/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "xrecog.h"

#if !defined(AFX_FRAGCOLL_H__0F9BF18B_518D_47C8_91F4_3233C75A327E__INCLUDED_)
#define AFX_FRAGCOLL_H__0F9BF18B_518D_47C8_91F4_3233C75A327E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFragColl_Magic	0x4354546

class CFragColl

{
	friend class CFrag;			//< Estabilish access to frag details 
	friend class CFragCollArr;	//< Access to higher level class

public:

	int	 ClearOldFrags(CCHAR *dir);
	int  ClearOldWaves(CCHAR *dir);

	CString GetFragDir();	CString GetWavDir();

	/// Add / remove frags
	void	AddFrag(CFrag *pfrag);
	int		ParseAllWaves(CCHAR *dir, CCHAR *fdir, int reload);
	int		SaveAllFrags(const char *dir); 
	int		LoadAllFrags(const char *dir, int reload);
	
	/// API entry points to remove items
	int		DelWord(CCHAR *pword);
	int		DelFragEntry(CCHAR *pword, CCHAR *pentry);

	//// Getters
	CString	Idx2Str(int idx, int real = false);
	int		Idx2Len(int idx);

	// Data access
	CFrag	  *GetAt(int idx) { return (CFrag*)xfragarr.GetAt(idx); }
	CPtrArray *GetData() { return &xfragarr; }
	CPtrArray *GetIdxData() { return &xidxarr; }
	CStringArray *GetStrData() { return xfragstrarr; }

	// Debug
	void	DumpFrags();
	void	DumpIdx();

	CFragColl();
	virtual ~CFragColl();

	// Operational
	int				magic, stop;

	// Statistics
	int		maxlen, minlen, maxidx; //, noprompt;
	
	CString user;

protected:

	void xSave(CFile *pfp); 
	int  xLoad(CFile *pfp);
	void xRemoveIdx(CFrag *pfr);

private:

	void	xDelFrags();

	// Collections
	CStringArray	*xfragstrarr;
	CPtrArray		xfragarr;
	CPtrArray		xidxarr;
};


#endif // !defined(AFX_FRAGCOLL_H__0F9BF18B_518D_47C8_91F4_3233C75A327E__INCLUDED_)
