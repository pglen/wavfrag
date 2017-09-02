 
/* =====[ Frag.h ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the Frag.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/25/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_FRAG_H__7EB01796_BB28_4390_BADF_FE629A509047__INCLUDED_)
#define AFX_FRAG_H__7EB01796_BB28_4390_BADF_FE629A509047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "analres.h"
#include "fragutil.h"
#include "CmpRes.h"

#ifndef CCHAR
#define CCHAR const char
#endif 

//////////////////////////////////////////////////////////////////////////

#define CFrag_Magic  0xe3e4e5

#define ASSERT_VALID_CFRAG(fr)  ASSERT(fr->magic == CFrag_Magic);

//////////////////////////////////////////////////////////////////////////

class CFrag  

{	
	// Give access to the higher level class
	friend class CFragColl;

public:
	
	static	int	onefraglen;
	static	CString wavext, fragext;

	// Called to convert a wav to frag
	static int CFrag::ParseFragWav(const char *pname, const char *wdir, const char *fdir, int force);

	//////////////////////////////////////////////////////////////////////
	// Getters:

	CAnalRes	*GetData() { return &xres; };
	int			GetUnitSize() {	return xres.raw.GetSize(); }

	//////////////////////////////////////////////////////////////////////
	// Functions:

	// Load a frag from parsed file
	int		LoadFrag(const char *str, int force);

	int		Save(CFile *pfp);
	int		Load(CFile *pfp);

	// Main entry point for compare
	int		CmpFrags(CAnalRes *parr, int offs, CCmpRes *pres);
	
	CFrag(); virtual ~CFrag();

	//////////////////////////////////////////////////////////////////////
	// Data:

	int			idx, magic;
	
	CString		*name, *shortname, *fname;
	
#ifdef _DEBUG
	int	verbose;
#endif

protected:
	
	//////////////////////////////////////////////////////////////////////
	// Compare functions

	int xHitFrags(CAnalRes *parr, int offs, int loopr, int nlim);
	int xHitPow(CAnalRes *parr, int offs, int loopr, int nlim);

private:

	CAnalRes	xres;
};

#endif // !defined(AFX_FRAG_H__7EB01796_BB28_4390_BADF_FE629A509047__INCLUDED_)
