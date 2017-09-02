
/* =====[ FragUtil.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the FragUtil.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// FragUtil.cpp: implementation of the CFragUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Frag.h"
#include "FragUtil.h"

#include "xrecog.h"
#include "support.h"
#include "mxpad.h"

extern	CxRecog		xdllrecog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFragUtil::CFragUtil()
{

}

CFragUtil::~CFragUtil()
{

}


//////////////////////////////////////////////////////////////////////////

void CFragUtil::_FreeArr(CPtrArray *parr)

{
	// Clean array by freeing attached int arrays

	for(int loopf = 0; loopf < parr->GetSize(); loopf++)
		{
		CIntArr *ddd = (CIntArr*) parr->GetAt(loopf);
		ASSERT(ddd->magic == CIntArr_Magic);

		delete ddd;
		}
	parr->RemoveAll();
}

//////////////////////////////////////////////////////////////////////////
// Clean zero entries from the integer array

void	CFragUtil::_CleanZeros(CPtrArray *parr, CPtrArray *pclean)

{
	int alen = parr->GetSize();

	pclean->RemoveAll();				// Just a safety measure

	for(int loops2 = 0; loops2 < alen; loops2++)
		{
		CIntArr *ttt = (CIntArr *) parr->GetAt(loops2);		
		CIntArr *tmp = new CIntArr; ASSERT(tmp);

		int alen3 = ttt->GetSize();
		for(int loops3 = 0; loops3 < alen3; loops3 += 1)
			{
			int val = ttt->GetAt(loops3); 			
			if(val > 0)
				tmp->Add(val);
 			}	

		// Show how much cleaning
		//AP2N("%3d->%-3d  ", ttt->GetSize(), tmp->GetSize());

		pclean->Add(tmp);
		}

	//AP2N("CFrag::_CleanZeros from %d to %d \r\n",  alen, pclean->GetSize());
}

//////////////////////////////////////////////////////////////////////////
// Duplicate arrarr

void	CFragUtil::_Dup(CPtrArray *parr, CPtrArray *oarr)
		 
{
	int alen = parr->GetSize();
 	for(int loopdy = 0; loopdy < alen; loopdy += 1)
		{
		CIntArr *tmp = (CIntArr*)parr->GetAt(loopdy);
		CIntArr *tmp2 = new CIntArr; ASSERT(tmp2);
		tmp2->Copy(*tmp);
		oarr->Add(tmp2);
		}
}

//////////////////////////////////////////////////////////////////////////
// Clean zero entries from the integer array, in place

void	CFragUtil::_CleanZeros(CPtrArray *parr)

{
	int alen = parr->GetSize();
	
	for(int loops2 = 0; loops2 < alen; loops2++)
		{
		CIntArr hold, *ttt = (CIntArr *) parr->GetAt(loops2);			
		int val = 0, alen3 = ttt->GetSize();

		for(int loops3 = 0; loops3 < alen3; loops3 += 1)
			{
			val = ttt->GetAt(loops3); 			
			if(val > 0)
				hold.Add(val);
 			}	
		ttt->Copy(hold);	// In lace put it back to original
		}
}

//////////////////////////////////////////////////////////////////////////
// Grab fundamental and store ratios compared to it.
//

#if 0

void CFragUtil::_DivisorConvert(CIntArr *piarr, CIntArr *poarr)

{
	int alen = piarr->GetSize();

	if(alen == 0)
		goto endd;

	{
	for(int loops = 0; loops < alen; loops++)
		if(piarr->GetAt(loops) != 0)
			break;

	// Acessing ahead, prevent the unexpected 
	if(loops >= alen)
		goto endd;

	int fund = piarr->GetAt(loops);
	
	//AP2N("Fundamental: %3d Ratios: ", fund);
	poarr->Add(fund);

	for(int loopss2 = loops + 1; loopss2 < alen; loopss2++)
		{
		int curr = piarr->GetAt(loopss2); 
		poarr->Add(10 * curr / fund);

		//AP2N(" %3d (%3d)  -   ", 10 * curr / fund, curr);
		}
	//AP2N("\r\n");	
	}

endd:
	// Padd it with zeros for saving
	int blen = poarr->GetSize();
	for(int loopf = blen; loopf < alen; loopf++)
		{
		poarr->Add(0);
		}
	//poarr->DumpAll("poarr");
}

#endif

//////////////////////////////////////////////////////////////////////////
// Convert edge array back to value array

int CFragUtil::_VisConv(CIntArr *piarr,  CIntArr *pvarr)
	
{	
	int arrsize = CFrag::onefraglen;
	
	int alen = piarr->GetSize(); 

	//AP2N("CFrag::_VisConv(CIntArr *piarr, len=%d\r\n", alen);

	alen = MIN(alen, arrsize);

	pvarr->SetSize(arrsize);

	// Reverse plot
	for(int loopw = 0; loopw < alen; loopw++)
		{
		int idx = piarr->GetAt(loopw);

		if(idx < arrsize && idx >= 0)
			pvarr->SetAtGrow(idx, 255);
		else
			AP2N("CFrag::_VisConv - offs=%d val=%d\r\n", loopw, idx); 
 		}		
		
	return 0;
}

#if 0

//////////////////////////////////////////////////////////////////////////
// Convert edge array back to value array

int CFragUtil::_VisConvDiv(CIntArr *piarr, CIntArr *pvarr)
	
{	
	int alen = piarr->GetSize();

	if(alen < 1)
		return 0;

	int fund = piarr->GetAt(0);

	pvarr->SetAtGrow(fund, 255);

	// Reverse plot the divi 
	for(int loopw = 1; loopw < alen; loopw++)
		{
		pvarr->SetAtGrow(fund * piarr->GetAt(loopw) / 10, 255);
 		}		
	
	// Padd empty for correct display
	if(pvarr->GetSize() == 0)	
		pvarr->Add(0);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Convert edge array back to value array

int CFragUtil::_VisConvRat(CIntArr *piarr, CIntArr *pvarr)
	
{	
	int alen = piarr->GetSize();

	if(alen < 1)
		return 0;

	int fund = piarr->GetAt(0);
	
	pvarr->SetAtGrow(fund, 255);

	// Reverse plot the divi 
	for(int loopw = 1; loopw < alen; loopw++)
		{
		int val = fund * piarr->GetAt(loopw) / 10;
		fund = val;

		//AP2N("%d\r\n", fund);
		pvarr->SetAtGrow(fund, 255);
 		}		
	
	// Padd empty for correct display
	if(pvarr->GetSize() == 0)	
		pvarr->Add(0);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Convert edge array back to value array

int CFragUtil::_VisConvStep(CIntArr *piarr, CIntArr *pvarr)
	
{	
	int alen = piarr->GetSize();

	if(alen < 1)
		return 0;

	int fund = piarr->GetAt(0);
	
	pvarr->SetAtGrow(fund, 255);

	// Reverse plot the steps
	for(int loopw = 1; loopw < alen; loopw++)
		{
		int val = piarr->GetAt(loopw);
		fund += val;
		//AP2N("%d\r\n", fund);
		pvarr->SetAtGrow(fund, 255);
 		}		
	
	// Padd empty for correct display
	if(pvarr->GetSize() == 0)	
		pvarr->Add(0);
	
	return 0;
}

#endif

//////////////////////////////////////////////////////////////////////////
// Thicken the lines for quantization error

void	CFragUtil::_ThickenConvArr(CPtrArray *parr, CPtrArray *pout, int skip)

{
	int alen = parr->GetSize();

	ASSERT(pout->GetSize() == 0);

	//pout->RemoveAll();				// Just a safety measure

	for(int loops2 = 0; loops2 < alen; loops2++)
		{
		CIntArr *ttt = (CIntArr *) parr->GetAt(loops2);		
		int old = 0, old2 = 0, old3 = 0, old4 = 0;
		int blen = ttt->GetSize();

		if(blen == 0)
			continue;

		// Create a copy
		CIntArr *tmp = new CIntArr; ASSERT(tmp); 
		
		tmp->Copy(*ttt);
		
		//////////////////////////////////////////////////////////////////		
		if(!skip)
			{
			for(int loops3 = 0; loops3 < blen; loops3++)
				{
				int curr = ttt->GetAt(loops3);

				// Switch them on one by one
				
				//tmp->SetAt(loops3, curr);					
				tmp->SetAt(loops3, old | curr);								
				//tmp->SetAt(loops3, old | old2 | curr);
				//tmp->SetAt(loops3, old | old2 | old3 | curr );
				//tmp->SetAt(loops3, old | old2 | old3 | old4 | curr );

				old4 = old3; old3 = old2; old2 = old; old = curr;
				}
			}

		// Output it
		pout->Add(tmp);
		}
}

//////////////////////////////////////////////////////////////////////////

void	CFragUtil::_VisConvArr(CPtrArray *parr, CPtrArray *pout)

{
	int alen = parr->GetSize();

	ASSERT(pout->GetSize() == 0);

	//pout->RemoveAll();				// Just a safety measure

	for(int loops2 = 0; loops2 < alen; loops2++)
		{
		CIntArr *ttt = (CIntArr *) parr->GetAt(loops2);		

		CIntArr *tmp = new CIntArr; ASSERT(tmp);
		
		_VisConv(ttt, tmp);

		pout->Add(tmp);
		}
}

//////////////////////////////////////////////////////////////////////////
// Pre process visualizer (with visual conversion)

void CFragUtil::_DumpSpect(CPtrArray *parr, int start, int len)

{	
	int alen = parr->GetSize();	start = min(start, alen);

	if(len >= 0)
		alen = min(len + start, alen);

	for(int loop = start; loop < alen; loop++)
		{
		CIntArr *tmp = (CIntArr*)parr->GetAt(loop);

		// This is with visual conversion
		CIntArr tmp2;	_VisConv(tmp, &tmp2);
		
		if(xdllrecog._spectrec)
			xdllrecog._spectrec(tmp2.GetData(), tmp2.GetSize() );

		if(xdllrecog._spectrec2)
			xdllrecog._spectrec2(tmp2.GetData(), tmp2.GetSize() );
		}

	if(xdllrecog._spectrec)
		xdllrecog._spectrec(NULL, 0);

	if(xdllrecog._spectrec2)
		xdllrecog._spectrec2(NULL, 0);
}

