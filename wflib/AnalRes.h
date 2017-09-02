
/* =====[ AnalRes.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the AnalRes.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_ANALRES_H__EE943C0D_018E_43AD_840F_EC27B9DEF300__INCLUDED_)
#define AFX_ANALRES_H__EE943C0D_018E_43AD_840F_EC27B9DEF300__INCLUDED_

#include "intarr.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CAnalRes_Magic 0xab32143

// Assumes 512 array length (1/8 3/8 1/1);

#define		LOW_TRESH	64
#define		MID_TRESH	192
#define		HIGH_TRESH	512

#define		FULL_OP		1
#define		LOW_OP		2
#define		MID_OP		3
#define		HIGH_OP		4

#include "ArrIntArr.h"

//////////////////////////////////////////////////////////////////////////
// Container for spectral scanning data
//
// NOTE! update file and AddNull functions if new data members are added
//
	
class CAnalRes  

{
	// Declare all members as public, so no access functions are needed 

public:		

	int		FromFile(CFile *fp);			// Load whole struct
	int		ToFile(CFile *fp);				// Save whole struct

	void	AddOne();
	void	AddNull(int nlen);				// Dummy entry for no match

	int		Save(CFile *fp);
	int		Load(CFile *fp);

	int		lowtresh, midtresh, hightresh;	// Treshold freq for dyn values

	int		magic;							// Checking	
	int		opcomm;							// Current operation command

	int		low, med, high;

	CAnalRes();
	virtual ~CAnalRes();

	// Make sure you add members to read / write / create

	CArrIntArr	raw;						// Raw data from FFT
	CArrIntArr	phase;						// Phase data from FFT (not used)

	CArrIntArr	all, vall;					// Full spectra values
	CArrIntArr	pow;						// Spectral power distribution

	//CArrIntArr	leftd, rightd;			// Spectral bell width

	CIntArrRec	sig, sig2;					// Signal stregths
};

#endif // !defined(AFX_ANALRES_H__EE943C0D_018E_43AD_840F_EC27B9DEF300__INCLUDED_)

