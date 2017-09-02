
/* =====[ NormArr.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the NormArr.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/20/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// NormArr.cpp: implementation of the CNormArr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wflib.h"
#include "NormArr.h"

#include "support.h"
#include "mxpad.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNormArr::CNormArr()
{

}

CNormArr::~CNormArr()
{

}


//////////////////////////////////////////////////////////////////////////
// Normalize every spectra

void	CNormArr::NormEvery(CPtrArray *parr, int maxrat)

{
	int alen = parr->GetSize();

	for(int loopno = 0; loopno < alen; loopno++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopno);
		tmp->NormArrHeight(255, maxrat);
		}
}

//////////////////////////////////////////////////////////////////////////
// Normalize entire scan

void	CNormArr::NormAll(CPtrArray *parr, int limfact)

{
	int alen = parr->GetSize();

	int mxx = 0;
	for(int loop = 0; loop < alen; loop++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loop);
		
		int midx, mval; tmp->FindMax(&midx, &mval);
		mxx = MAX(mxx, mval);	
		}

	double fact = 255L / (double)mxx;

	AP2N("CNormArr::NormAll mxx=%d fact=%f\r\n", mxx, fact);
	
	if(fact < limfact)
		{
		// Apply
		for(int loopa = 0; loopa < alen; loopa++)
			{
			CIntArr *tmp = (CIntArr *)parr->GetAt(loopa);
			tmp->Multiply(fact);		
			}
		}
}

//////////////////////////////////////////////////////////////////////////

void	CNormArr::NormAvg(CPtrArray *parr, int limfact)

{
	int alen = parr->GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loop);

		int avg = tmp->Avg();

		if(avg)
			{
			double fact = 255L / (double)avg;

			AP2N("CNormArr::NormAvg avg=%d fact=%f\r\n", avg, fact);
			
			if(fact < limfact)
				{
				tmp->Multiply(fact);
				}
			}
		}
}

//////////////////////////////////////////////////////////////////////////
// Normalize bands

void	CNormArr::NormBands(CPtrArray *parr, int bands, int maxrat)

{
	int alen = parr->GetSize();	

	ASSERT(bands > 0);

	for(int looph3 = 0; looph3 < alen; looph3++)
		{	
		CIntArr *tmp = (CIntArr *)parr->GetAt(looph3);
		int clen = tmp->GetSize();

		int sivi = clen / bands;
		for(int looph4 = 0; looph4 < clen; looph4 += sivi)
			{
			//AP2N("sivi %d %d\r\n", looph4, looph4 + clen / sivi);

			// Make sum
			int mxx = 0, ssum = 0;
			for(int looph5 = looph4; looph5 < min(clen-1, looph4 + sivi); looph5++)
				{
				int val = tmp->GetAt(looph5);
				ssum += val;
				if(mxx < val) mxx = val;
				}			

			ssum /= sivi;

			// Normalize if valid signal
			//if(ssum > ANAL_TRESH)
				{
				double rat = 255. / mxx;

				if(rat < maxrat)
					{
					//AP2N("mxx =%d rat = %f\r\n", mxx, rat);

					for(looph5 = looph4; looph5 < min(clen-1, looph4 + sivi); looph5++)
						{
						int val = tmp->GetAt(looph5);
						tmp->SetAt(looph5, int(rat * val));
						}						
					}
				}
			}
		}
}