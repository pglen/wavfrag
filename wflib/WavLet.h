// WavLet.h: interface for the CWavLet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVLET_H__BD739E7B_49EB_4176_A916_24A2D86C596F__INCLUDED_)
#define AFX_WAVLET_H__BD739E7B_49EB_4176_A916_24A2D86C596F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "intarr.h"


class CWavLet  
{

public:

	CWavLet();
	virtual ~CWavLet();

	int		Transform(short *buff, int len, CPtrArray *parr);
	int		step;

protected:

	int		xAnalize(CIntArr *inp, CIntArr *outp);

};

#endif // !defined(AFX_WAVLET_H__BD739E7B_49EB_4176_A916_24A2D86C596F__INCLUDED_)
