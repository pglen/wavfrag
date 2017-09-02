
/* =====[ AnalRes.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the AnalRes.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "frag.h"
#include "AnalRes.h"

#include "mxpad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnalRes::CAnalRes()

{
	// Check, just for compile sanity
	ASSERT(MID_TRESH > LOW_TRESH);	ASSERT(MID_TRESH < HIGH_TRESH);

	// Dynamically determined tresholds
	lowtresh = CFrag::onefraglen / 8;
	midtresh = 3 * CFrag::onefraglen / 8;
	hightresh = CFrag::onefraglen;

	low = med = high = 0;

	//AP2N("CAnalRes::CAnalRes lowtresh:%d midtresh:%d hightresh:%d\r\n", 
	//						lowtresh, midtresh, hightresh);
	//

	magic = CAnalRes_Magic;
	opcomm = 0;
}

//////////////////////////////////////////////////////////////////////////

CAnalRes::~CAnalRes()

{
	// Check assumptions
	ASSERT(magic == CAnalRes_Magic);

	// Array sizes should match
	ASSERT(all.GetSize() == vall.GetSize());		
}

//////////////////////////////////////////////////////////////////////////
// Create new arrays and add to output
	
void CAnalRes::AddOne()

{
	all.Add(); vall.Add(); 	
	//leftd.Add(); rightd.Add(); 	
	pow.Add();
}

// Macro to allocate an array

#define ADD_ARRINTARR(arrto, sss)					\
		ptmp = new CIntArrRec(sss);  ASSERT(ptmp);	\
		arrto.Add(ptmp);

//////////////////////////////////////////////////////////////////////////
// Add N lenght empty array. Update if new data members added

void CAnalRes::AddNull(int nitems)

{
	CIntArrRec *ptmp;

	for(int loopp = 0; loopp < nitems; loopp++)
		{		
		//ADD_ARRINTARR(raw, CFrag::onefraglen);	
		//ADD_ARRINTARR(phase, CFrag::onefraglen);
		ADD_ARRINTARR(all, 8);	
		ADD_ARRINTARR(vall, 8); 
		//ADD_ARRINTARR(leftd);	ADD_ARRINTARR(rightd);  
		ADD_ARRINTARR(pow, 8);	
		
		sig.Add(0); sig2.Add(0);
		}
}

//////////////////////////////////////////////////////////////////////////
// Update if new data members are added. Order must match for to / from

int CAnalRes::FromFile(CFile *fp)

{
	int ret = true, xmagic = 0;

	fp->Read(&xmagic, sizeof(int));

	if(xmagic != magic)
		{
		AP2N("CAnalRes::FromFile BAD magic\r\n");
		return 0;
		}

	// Load Data
	raw.FromFile(fp);	phase.FromFile(fp);
	all.FromFile(fp);	vall.FromFile(fp);	
	//leftd.FromFile(fp);	rightd.FromFile(fp);
	pow.FromFile(fp);

	sig.FromFile(fp);	sig2.FromFile(fp);

	if(all.GetSize() != vall.GetSize())
		{
		AP2N("CAnalRes::FromFile uneven load.\r\n");
		}

	if(raw.GetSize() != pow.GetSize())
		{
		AP2N("CAnalRes::FromFile uneven load (raw vs pow)\r\n");
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Update if new data members are added. Order must match for to / from

int CAnalRes::ToFile(CFile *fp)

{
	int ret = true;

	//AP2N("CAnalRes::ToFile\r\n");

	fp->Write(&magic, sizeof(int));

	// Write out raw scan 
	raw.ToFile(fp); phase.ToFile(fp);

	// Write out all and volumes
	all.ToFile(fp);	vall.ToFile(fp); 
	
	//leftd.ToFile(fp); rightd.ToFile(fp); 
	
	pow.ToFile(fp);	

	sig.ToFile(fp); sig2.ToFile(fp);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int CAnalRes::Save(CFile *fp)

{
	int ret = 0;

	fp->Write(&magic, sizeof(int));

	// Write out all and volumes
	all.ToFile(fp);	vall.ToFile(fp); 
	pow.ToFile(fp);	
	sig.ToFile(fp); sig2.ToFile(fp);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int CAnalRes::Load(CFile *fp)

{
	int ret = 0;

	fp->Read(&magic, sizeof(int));

	// Read all
	ret += all.FromFile(fp);	ret += vall.FromFile(fp); 
	ret += pow.FromFile(fp);	
	ret += sig.FromFile(fp);    ret += sig2.FromFile(fp);

	return ret;
}
