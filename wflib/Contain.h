
/* =====[ Contain.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the Contain.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/28/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_CONTAIN_H__6A6B27C5_60D4_4518_9C14_0C57C8113B7B__INCLUDED_)
#define AFX_CONTAIN_H__6A6B27C5_60D4_4518_9C14_0C57C8113B7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "xrecog.h"

#include "intarr.h"
#include "frag.h"

#define CContain_Magic	0x323245
#define CContData_Magic 0x324567
#define CContFilt_Magic 0x324578

// Shorthand for the nested class names
#define ContData	CContain::CContData
#define ConFilt		CContain::CContFilt
	
//////////////////////////////////////////////////////////////////////////

class CContain  

{

public:
	void Copy(CContain *ptr);

	// Processing data helper class
	class CContData
		{
		public:
		
		int magic, outlim;			// Number of outputs to store
		CIntArr		idxs;			// Array of items to scan
		CIntArr		vals;			// Array of hit values
		CPtrArray	frags;			// Frags found (do not free them)
		
		CContData(); ~CContData();
		};
	
	// Names and weight of filtered entries
	class CContFilt
		{
		public:

			CContFilt() { magic = CContFilt_Magic; };

			int magic;
			CStringArray snames;		
			CIntArr	vals;				// Array of hit values
		};
		

	// Pre processors
	void	Weed();
	void	WeedNX();
	void	WeedNul();
	void	WeedWeak();
	void	WeedEnds(int tresh = 0);
	
	// Debug helpers
	CString	Dump2Str();
	void	Dump();
	void	DumpFilter();

	// Operations
	void	Add(CContain::CContData *predat);
	
	// Analisys
	
	CString Filter();
	CString Scan(int start);

	// Calculations
	
	// Getters
	CString	GetConcatStrx();
	CString	GetConcatStrf();

	CContData*	GetAt(int pos);

	inline CContData*	GetItem(int item) 
				{ return (CContData*)xcontarr.GetAt(item); }

	inline CPtrArray*	GetData() { return &xcontarr; }
	inline CPtrArray*	GetFiltData() { return &xfiltarr; }
	inline int	GetSize() { return xcontarr.GetSize(); }
			
	CIntArrRec	sig, sig2;

	int			magic;	
	CString		*name;

	//////////////////////////////////////////////////////////////////////

	CContain();
	virtual ~CContain();

protected:

	
	void	xDelAll();
	void	xConvStr(CString &xname);

	CString xFilter(int start, int endd, CContain::CContFilt *pdata);
	
	int		xUniqueIdx(CString *str, CStringArray *pstrarr);
	int		xIsUnique(CString *str, CStringArray *pstrarr);

private:

	CStringArray sim; 
	
	CString		laststr;
	CPtrArray	xcontarr, xfiltarr;

};

//////////////////////////////////////////////////////////////////////////
// Single container

#if 0

class CCont  
{		
	public:
	
	CContData predat;

	// Data:
	CString *str, *shstr;	

	CFrag *pfr;
	int sum, val, cnt, rat, magic;

	CCont();
	~CCont();
};

#endif

#endif // !defined(AFX_CONTAIN_H__6A6B27C5_60D4_4518_9C14_0C57C8113B7B__INCLUDED_)

