// FftBuff.h: interface for the CFftBuff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFTBUFF_H__8194F80B_EA6C_4DA1_A208_994BD9D646AE__INCLUDED_)
#define AFX_FFTBUFF_H__8194F80B_EA6C_4DA1_A208_994BD9D646AE__INCLUDED_

#include "Fft.h"
#include "IntArr.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define		DOM_DEPTH	2		// How deep freq stack to create
//#define		QUAD_DEPTH	2		// Optimum, sorted -> dominance -> freq

//#define		MAXFFTVAL	300		// How high it goes

#define		FRAG_STEP	4		// How many dominant components to include


class CFftBuff  

{
public:
	
	int		Transform(short *buff, int len, CPtrArray *parr, CPtrArray *parr2);

	// Mirrored on x / 2 axis, so only half of it is valid info
	int		GetDepth() { return (fft->Points() / 2); }

	//////////////////////////////////////////////////////////////////////

	CFftBuff();
	virtual ~CFftBuff();

	//////////////////////////////////////////////////////////////////////
	
	int		fftpts;
	//int		NoiseLevel;	

protected:

	CFft	*fft;
	int		xTransform(short *buff, int len, CIntArr *tmp, CIntArr *ph);

};

#endif // !defined(AFX_FFTBUFF_H__8194F80B_EA6C_4DA1_A208_994BD9D646AE__INCLUDED_)
