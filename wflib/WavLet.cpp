
/* =====[ WavLet.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the WavLet.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */


#include "stdafx.h"
#include "wflib.h"
#include "WavLet.h"
#include "mxpad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWavLet::CWavLet()

{
	step = 256;
}

CWavLet::~CWavLet()

{

}

//////////////////////////////////////////////////////////////////////////
//
// Wavelet JAVA code
//
//public static int[] invoke(int[] input)
//{
// 
//    //This function assumes input.length=2^n, n>1
//    int[] output = new int[input.length];
// 
//    for (int length = input.length >> 1; ; length >>= 1) {
//        //length=input.length/2^n, WITH n INCREASING to log(input.length)/log(2)
//        for (int i = 0; i < length; i++) {
//            int sum = input[i*2]+input[i*2+1];
//            int difference = input[i*2]-input[i*2+1];
//            output[i] = sum;
//            output[length+i] = difference;
//        }
//        if (length == 1) 
//            return output;
// 
//        //Swap arrays to do next iteration
//        System.arraycopy(output, 0, input, 0, length<<1);
//    }
//}

//////////////////////////////////////////////////////////////////////////
// This function assumes input.length=2^n, n>1

int CWavLet::xAnalize(CIntArr *inp, CIntArr *outp)

{    
	int length = inp->GetSize(); 
	outp->SetSize(length);
 
    for (int loop = length >> 1; loop > 0; loop >>= 1) 
		{		
        for (int ii = 0; ii < loop; ii++) 
			{
			int aa = inp->GetAt(ii * 2), bb = inp->GetAt(ii * 2 + 1);
            outp->SetAt(ii, (aa + bb) );  outp->SetAt(loop + ii, aa - bb);
			}

        // Swap arrays to do next iteration	
		int alen = loop << 1;
		for(int loop2 = 0; loop2 < alen; loop2++)
			{
			inp->SetAt(loop2, outp->GetAt(loop2));
 			}
		}

#if 1
	// Norm array
	int alen = outp->GetSize();
	for(int loop3 = 0; loop3 < alen; loop3++)
		{
		int val = outp->GetAt(loop3);
		//outp->SetAt(loop3, val / 300000 * (255 - loop3));

		val /= 100; 
		val *= loop3;
		val /= 200;
		
		val = max(val, 0);
		//val = abs(val);

 		outp->SetAt(loop3, val);
 		}

	//outp->NormArrHeight(255);
#endif

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int		CWavLet::Transform(short *buff, int len, CPtrArray *parr)

{
	int len2 = len; // / sizeof(short);
		
	//AP2N("CWavLet::Transform %p len=%d step=%d\r\n", buff, len, step);

	short	*data = buff;
	short	*endd = buff + (len2 - step);  // Miss the last one

	CIntArr  inp;	inp.SetSize(step);
		
	while(TRUE)
		{
		if(data > endd)
			break;

		// Set up arrays for processing
		CIntArr *tmp = new CIntArr; ASSERT(tmp);

		for(int loop = 0; loop < step; loop++)
			inp.SetAt(loop, *data++);
 			
		xAnalize(&inp, tmp);
		parr->Add(tmp);	

		data += step;
		}

	return 0;
}
