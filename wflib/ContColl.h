
/* =====[ ContColl.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the ContColl.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/20/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_CONTCOLL_H__3D525B52_97A9_42E0_8F05_26A47B8554AC__INCLUDED_)
#define AFX_CONTCOLL_H__3D525B52_97A9_42E0_8F05_26A47B8554AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xrecog.h"
//#include "frag.h"
#include "contain.h"
#include "LevenStein.h"
#include "StrDiff.h"

#define CStrColl_Magic 0x221122

//////////////////////////////////////////////////////////////////////////

class CStrColl  

{

public:

	void	ClearItem(const char *str, const char *item);
	void	Clear(const char *str);
	
	void	AddCont(CString &name, CString &str);
	void	AddCont(CContain *pcont);
	
	int		CmpCont(CContain *pcont, int *match1 = NULL, int *match2 = NULL);

	void	Dump();

	int		Load(const char *fname);
	int		Save(const char *fname);

	//////////////////////////////////////////////////////////////////////
	// Getters

	int		GetCollName(int idx, CString &str);
	int		GetCollStr(int idx, int idx2, CString &str);

	CStrColl();
	virtual ~CStrColl();

	// Getters
	CString		GetAt(int idx);

	int		magic;
	
	//CString filename;

protected:

	int		minlen, maxlen, maxidx;
	
private:

	LevDistance		xld;
	CStrDiff		xsd;

	int xchanged;

	CStringArray	xnamearr;
	CPtrArray		xarr;

};

#endif // !defined(AFX_CONTCOLL_H__3D525B52_97A9_42E0_8F05_26A47B8554AC__INCLUDED_)
