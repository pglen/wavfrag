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

class CFftBuff  

{
public:
	
	int		Transform(short *buff, int len, CPtrArray *arr);
	void	GetPeaks(CPtrArray *parr, CPtrArray *oarr);
	void	GetDominant(CPtrArray *parr, CIntArr *ouarr, CIntArr *volarr);

	// These are obsolete
	void	ScaleUp(CPtrArray *parr, CPtrArray *outarr);
	void	ScaleDown(CPtrArray *parr);
	void	Flatten(CPtrArray *parr, int vol = 255);
	void	Unroll(CPtrArray *parr, CIntArr *out);

	CFftBuff();
	virtual ~CFftBuff();

protected:

	CFft	*fft;
	int		Transform2(short *buff, int len, CPtrArray *arr);

};

#endif // !defined(AFX_FFTBUFF_H__8194F80B_EA6C_4DA1_A208_994BD9D646AE__INCLUDED_)
