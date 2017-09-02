
/* =====[ IntArrRec.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the IntArrRec.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/10/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "IntArrRec.h"

#include "math.h"
#include "mxpad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntArrRec::CIntArrRec()
{
	//magic = CIntArrRec_Magic;
}

//////////////////////////////////////////////////////////////////////////

CIntArrRec::CIntArrRec(CIntArrRec *org)

{
	//magic = CIntArrRec_Magic;
	Copy((CIntArrRec*)org);
}

CIntArrRec::CIntArrRec(int size)

{
	//magic = CIntArrRec_Magic;
	SetSize(size);
}


CIntArrRec::~CIntArrRec()

{
	ASSERT(magic == CIntArr_Magic);
}

//////////////////////////////////////////////////////////////////////////

int		CIntArrRec::Mean()

{
	int	alen = GetSize();

	if(!alen)
		return 0;

	double sum = 0;
	for(int loop3 = 0; loop3 < alen; loop3++)
		{
		int val = GetAt(loop3);
		sum += val * val;
		//avg /= 2;
		}
	return (int)sqrt(sum);
}

//////////////////////////////////////////////////////////////////////////
//

int CIntArrRec::ToFile(CFile *fp)

{
	int ret = true;

	struct_ms ms; ms.magic = CIntArr_Magic; ms.len = GetSize();

	//AP2N("		CIntArrRec::ToFile %d\r\n", ms.len);
	
	// Write out length and data
	fp->Write(&ms, sizeof(ms));			

	if(ms.len)
		fp->Write(GetData(), ms.len * sizeof(int));				

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Read it from file. Return -1 if error

int CIntArrRec::FromFile(CFile *fp)

{
	int ret = 0;

	struct_ms ms; ms.magic = 0; ms.len = 0;

	// Read in length and magic
	fp->Read(&ms, sizeof(ms));	
	
	//AP2N("		CIntArrRec::FromFile %d\r\n", ms.len);

	if(ms.magic != CIntArr_Magic)
		{
	 	AP2N("CIntArrRec::FromFile - Invalid Magic\r\n");
		return -1;
		}

	 // Check for reasonable length
	 if(ms.len >  5000 || (ms.len < 0) )
		{
	 	AP2N("CIntArrRec::FromFile - unreasonable length (%d) \r\n", ms.len);
		return -1;
		}

	// Make an exception if empty
	if(ms.len == 0)
		{
		SetSize(0);
		return ret;
		}

	// Get rid of any old stuff
	delete[] (int*)m_pData;

	int* pNewData = (int*) new BYTE[ms.len * sizeof(int)];
	ASSERT(pNewData);

	ret = fp->Read(pNewData, ms.len * sizeof(int));				

	// Assign new buffer and set length, with no slack
	m_pData = pNewData;		
	m_nSize = ms.len; m_nMaxSize = ms.len; 

	return ret;
}

// -----------------------------------------------------------------------
//
/// \brief  CIntArr::NormArrLen  normalize array to length
/// 
/// \details CIntArr::NormArrLen Descibe Here 
/// \n  
/// Return type:      
/// \n  
/// \param normto Arg Type: int 
//
// -----------------------------------------------------------------------

void	CIntArrRec::NormArrLen(int normto)

{
	//ASSERT(normto > 0);

	//AP2N("CIntArr::NormArray len=%d to=%d\r\n", GetSize(), normto);

	if(normto <= 0)
		{
		//AP2N("CIntArr::NormArray norm to nothing\r\n");
		return;
		}

	int asize = GetSize();
	if(asize == 0)
		{
		//AP2N("CIntArr::NormArray empty array\r\n");
		return;
		}

	// Create temporary (normalized) copy 
	CIntArr normarr;

	// Create temporary (normalized) copy 
	double factor = double(asize) / normto;

	//AP2N("CIntArr::NormArrLen factor=%.f\r\n", factor);
	//if(factor < 1)
	//{
	//}

#if 1
	if(factor > 1)
		{
		for(int zloop2 = 0; zloop2 < normto; zloop2++)
			{
			double avg = 0;	int base = (int)(zloop2 * factor);
			// Avarage run
			for(int zloop3 = 0; zloop3 < (int)factor; zloop3++)
				{
				avg += GetAt(base +  zloop3);				
				//avg /= 2;			// running avarage is lesser
				}
			avg /= factor;			// proper avarage works better
			normarr.Add((int)avg);
			}
		}
	else
#endif

		{
		for(int zloop2 = 0; zloop2 < normto; zloop2++)
			{
			int xloop = int(factor * zloop2);
			xloop = min(xloop, asize - 1);
			normarr.Add(GetAt(xloop));
			}
		}
		
	// Blank it, and Copy it back
	RemoveAll(); Copy(normarr);
}



// -----------------------------------------------------------------------
//
/// \brief  CIntArr::Smooth  Avarage array by summing with its neighbours
/// 
/// \details CIntArr::Smooth Special arrangement made to correctly 
///						calculate first/last neighbours
/// \n  
/// Return type:      
/// \n  
/// \param passes Arg Type: int 
//
// -----------------------------------------------------------------------

void	CIntArrRec::Smooth(const int passes)

{
	int nlen = GetSize();

	if(nlen <= 2)
		{
		//AP2N("CIntArr::SmoothArr empty array\r\n");
		return;
		}

	for(int loop3 = 0; loop3 < passes; loop3++)
		{
		for(int loop = 1; loop < nlen - 1; loop++)
			{
			double val = 0;
			
			// Catch low boundary
			val += (double)GetAt(loop - 1);
			val += (double)GetAt(loop);
			val += (double)GetAt(loop + 1);
						
			SetAt(loop, (int)(val / 3));
			}
		}

	return;
}

// -----------------------------------------------------------------------
//
/// \brief  CIntArr::Smooth2  Avarage array by summing with its neighbours
/// 
/// \details CIntArr::Smooth Special arrangement made to correctly 
///						calculate first/last neighbours
/// \n  
/// Return type:      
/// \n  
/// \param passes Arg Type: int 
//
// -----------------------------------------------------------------------

void	CIntArrRec::Smooth2(const int passes)

{
	int nlen = GetSize();

	if(nlen <= 2)
		{
		//AP2N("CIntArr::SmoothArr empty array\r\n");
		return;
		}

	for(int loop3 = 0; loop3 < passes; loop3++)
		{
		// Forward pass
		for(int loop = 1; loop < nlen; loop++)
			{
			double val = 0;
			
			val += (double)GetAt(loop - 1);
			val += (double)GetAt(loop);
						
			SetAt(loop, (int)(val / 2));
			}

		// Reverse pass
		for(int loop2 = nlen - 1; loop2 > 1; loop2--)
			{
			double val = 0;
			
			// Catch low boundary
			val += (double)GetAt(loop2);
			val += (double)GetAt(loop2 - 1);
						
			SetAt(loop2 - 1, (int)(val / 2));
			}
		}

	return;
}

//////////////////////////////////////////////////////////////////////////
//  Smooth a range of the array. Smoothing may overflow any three 
//  consecutive values sum up to more than INT_MAX 

void	CIntArrRec::RangeSmooth(const int passes, int start, int endd)

{
	int nlen = GetSize();

	if(endd == -1)
		endd = nlen;

	// Contain it to reasonable defaults
	start = MIN(start, nlen - 1); endd = MIN(endd, nlen - 1);
	start = MAX(start, 1);  endd = MAX(start, endd);

	for(int loop3 = 0; loop3 < passes; loop3++)
		{
		for(int loop = start; loop < endd; loop++)
			{
			int val = 0;
			
			// Catch low boundary in the loop specs
			val += GetAt(loop - 1);
			val += GetAt(loop);
			val += GetAt(loop + 1);
						
			SetAt(loop, (val / 3));
			}
		}
}


// -----------------------------------------------------------------------
//
/// \brief  CIntArrRec::Avg  Calculate avarage value for array
/// 
/// \details CIntArrRec::Avg Arithmetic avarage, uses double for sum
/// \n  
/// Return type:      
/// \n  int
//
// -----------------------------------------------------------------------

int		CIntArrRec::Avg()

{
	int	alen = GetSize();

	if(!alen)
		return 0;

	double sum = 0;
	for(int loop3 = 0; loop3 < alen; loop3++)
		{
		int val = GetAt(loop3);
		sum += val;
		//avg /= 2;
		}
	return (int)(sum / alen);
}

//////////////////////////////////////////////////////////////////////////

int		CIntArrRec::Sum()

{
	int	alen = GetSize();
	double sum = 0;

	for(int loop3 = 0; loop3 < alen; loop3++)
		{
		int val = GetAt(loop3);
		sum += val;
		}
	return (int)(sum);
}

//////////////////////////////////////////////////////////////////////////
// Remove DC

void	CIntArrRec::SinkDown()

{
	//ASSERT(normto > 0);

	if(GetSize() == 0)
		{
		//AP2N("CIntArr::Liftup empty array\r\n");
		return ;
		}

	int loop, asize = GetSize();
	if(!asize)
		return ;

	// Calc avg  value
	double sum = 0;
	for(loop = 0; loop < asize; loop++)
		{
		sum += GetAt(loop);
		}

	sum /= asize;

	for(loop = 0; loop < asize; loop++)
		{
		int val = GetAt(loop) - (int)sum;

		if(val > 0)
			SetAt(loop, val);		
		else
			SetAt(loop, 0);		

		}
}


// -----------------------------------------------------------------------
//
/// \brief  CIntArr::ScaleArrLen  Scale array to size ratio
/// 
/// \details CIntArr::ScaleArrLen Descibe Here 
/// \n  
/// Return type:      
/// \n  
/// \param scaleto Arg Type: int 
//
// -----------------------------------------------------------------------

void	CIntArrRec::ScaleArrLen(double scale)

{
	//ASSERT(normto > 0);

	//AP2N("CIntArr::ScaleArrLen len=%d\r\n", GetSize());

	if(scale <= 0)
		{
		AP2N("CIntArr::ScaleArrLen scale to negaive or nothing\r\n");
		return;
		}

	int asize = GetSize();
	if(asize == 0)
		{
		//AP2N("CIntArr::ScaleArrLen empty array\r\n");
		return;
		}

	// Create temporary (scaled) copy 
	CIntArr normarr;

	//if(!asize)
	//	return;

	int normto = (int)(asize * scale);
	// Create temporary (normalized) copy 
	//double factor = double(asize) / normto;
	for(int zloop2 = 0; zloop2 < normto; zloop2++)
		{
		int xloop = int(zloop2 / scale);
		xloop = min(xloop, asize - 1);
		normarr.Add(GetAt(xloop));
		}
	
	// Blank it, and Copy it back
	RemoveAll(); Copy(normarr);
}

//////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------
//
/// \brief  CIntArr::NormArrHeight  notmalize array to normto value
/// 
/// \details CIntArr::NormArrHeight Descibe Here 
/// \n  
/// Return type:  double. Return scaling factor used    
/// \n  
/// \param normto Arg Type: int 
//
// -----------------------------------------------------------------------

double	CIntArrRec::NormArrHeight(int normto, int uplim)

{
	//ASSERT(normto > 0);

	if(normto <= 0)
		{
		AP2N("CIntArr::NormArrHeight norm to nothing\r\n");
		return 1;
		}

	if(GetSize() == 0)
		{
		//AP2N("CIntArr::NormArrHeight empty array\r\n");
		return 1;
		}

	int loop, asize = GetSize();
	if(!asize)
		return 1;

	// Calc maximum value
	int maxx = 0;
	for(loop = 0; loop < asize; loop++)
		{
		int val = GetAt(loop);
		if(val > maxx)
			maxx = val;
		}

	// Calc scaling factor
	double factor = (double)normto / maxx;
	//int factor = normto / maxx;
	
	if(factor > uplim)
		return 1;

	//AP2N("CIntArr::NormArrHeight factor=%f\r\n", factor);
	
	for(loop = 0; loop < asize; loop++)
		{
		int val = GetAt(loop);
		SetAt(loop, (int) (factor * val));		
		}

	return factor;
}

// -----------------------------------------------------------------------
//
/// \brief  CIntArr::Multiply  array with a factor
/// 
/// \details CIntArr::Multiply Descibe Here 
/// \n  
/// Return type:      
/// \n  
/// \param factor Arg Type: double 
//
// -----------------------------------------------------------------------

void	CIntArrRec::Multiply(double factor)

{
	//ASSERT(normto > 0);

	if(GetSize() == 0)
		{
		//AP2N("CIntArr::Multiply empty array\r\n");
		return;
		}

	int loop, asize = GetSize();
	if(!asize)
		return;

	for(loop = 0; loop < asize; loop++)
		{
		int val = GetAt(loop);
		SetAt(loop, (int) (factor * val));		
		}

	return;
}

//////////////////////////////////////////////////////////////////////////

void	CIntArrRec::SetLast(int val)

{
	SetAt(GetUpperBound(), val);
}


//////////////////////////////////////////////////////////////////////////
// Avarage only entries with power more than ...

int		CIntArrRec::PowAvg(int tresh)

{
	double sum = 0;
	int cnt = 0, loop, asize = GetSize();
	
	for(loop = 0; loop < asize; loop++)
		{
		int val = GetAt(loop);

		if(val > tresh)
			{
			sum += val; cnt++;
			}
		}

	if(cnt)
		sum /= cnt;

	return (int)sum;
}

//////////////////////////////////////////////////////////////////////////

int		CIntArrRec::GetLast()

{
	int ret = 0, len = GetSize() - 1;
	if(len >= 0)
		{
		ret = GetAt(len);
		}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Log array in place

void	CIntArrRec::Log()

{
	int alenc = GetSize();

	// Make sure the multiplication is in double

	for(int loopc = 0; loopc < alenc; loopc++)
		{
		int val = GetAt(loopc);							

		// Conversion. Tried different log functions

		//int val2 = (int) (log10((double)val) * 40);
		//int val2 = (int) (log((double)val) * 40);
		//int val2 = (int) (pow((double)val, 0.65) * 5);
		int val2 = (int) (sqrt(val) * 12);
				
		//AP2N("%d (%d) -  ", val, val2);
		
		SetAt(loopc, val2);
		}
}
