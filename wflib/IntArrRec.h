
/* =====[ IntArrRec.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the IntArrRec.h                
                                                                             
                    Defines the behavior for the application.          
					Extend basic integer array for recognition. Mostly 
					serialization and some math functions.
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/10/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_INTARRREC_H__36BA0391_394F_4125_8783_F54BDA46EB91__INCLUDED_)
#define AFX_INTARRREC_H__36BA0391_394F_4125_8783_F54BDA46EB91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IntArr.h"

#define CIntArrRec_Magic = 0x21234543

class CIntArrRec : public CIntArr   

{
	struct struct_ms {int magic; int len; };

	//////////////////////////////////////////////////////////////////////
	
	public:

	CIntArrRec();
	CIntArrRec(CIntArrRec *org);
	CIntArrRec(int size);

	virtual ~CIntArrRec();

	int		GetLast();

	// File ops
	int		ToFile(CFile *fp); int FromFile(CFile *fp);

	// Math related
	int		Mean(); int	Avg();	int	Sum();
	int		PowAvg(int tresh = 10);

	//////////////////////////////////////////////////////////////////////
	// Functions moved from CIntArr because they need double

	// Low Pass Filters
	void	Smooth(const int passes = 1);
	void	Smooth2(const int passes = 1);
	void	RangeSmooth(const int passes = 1, int start = 0, int endd = -1);

	// Remove DC
	void	SinkDown();
	
	// Normalizers
	void	NormArrLen(int normto);
	void	ScaleArrLen(double scale);
	double	NormArrHeight(int normto, int uplim);
	void	Multiply(double factor);

	void	Log();

	// Convenience
	void	SetLast(int val);
};

#endif // !defined(AFX_INTARRREC_H__36BA0391_394F_4125_8783_F54BDA46EB91__INCLUDED_)
