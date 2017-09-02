
/* =====[ WavCmp.cpp ]========================================================== 
                                                                             
   Description:     The daco project, implementation of the WavCmp.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/9/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "WavCmp.h"
#include "support.h"
#include "mxpad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//undef P2N

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWavCmp::CWavCmp()

{
	minskip = 5;
	divisor = 16;
}

CWavCmp::~CWavCmp()

{

}

//////////////////////////////////////////////////////////////////////////
// Fill in array of short offsets
//

void	CWavCmp::SplitZcross(short *buff, int slen, CIntArr *parr)

{
	//AP2N("CWavCmp::SplitZcross(char *buff=%p, int len=%d)\r\n", buff, slen);

	short	*fdata = buff;
	int		prev = 0;

	for(int loop = 0; loop < slen - 1; loop++)
		{
		if( (*fdata) < 0 && *(fdata + 1) >= 0)
			{
			//P2N("ZCross at %d   %d->%d\r\n", loop, *fdata, *(fdata+1));

			if(loop - prev > 5)
				{
				// Output if less than min freq away
				parr->Add(loop);
				prev = loop;
				}
			}
		fdata++;
		}
}

//////////////////////////////////////////////////////////////////////////
//

int CWavCmp::SplitBend(char *ptr, int len, CIntArr *varr, CIntArr *darr)

{
	//P2N("CWavCmp::SplitBend %p %d ", ptr, len);

	// Easier for visualization
	#define UPT		1
	#define DOWNT	-1
	#define NULLT	0

	short	*data = (short*)ptr, prev = 0, lastturn = 0, lastturnd = 0;

	int		prevd = 0, prevh = 0;
	int		pptrend = NULLT, ptrend = NULLT, trend = NULLT;
	int		ndist = 0, len2 = len / sizeof(short); 

	//int		sustain_up = 0, sustain_down;

	//darr->RemoveAll(); varr->RemoveAll();
	
	for (int loop = 0; loop < len2; loop++)
		{
		//short curr = abs(*data);
		short curr = *data;

		//////////////////////////////////////////////////////////////////
		//    |^^^|
		//  __|   |__
		//
		
		short	ddiff = prev - curr;

		if(ddiff > 0) 		
			trend = UPT;
		else if(ddiff < 0)  
			trend = DOWNT;

		//else 
		//	trend = NULLT;
	
		// Trend Change
		if(ptrend != trend)	
			{
			int height = abs(curr - lastturn);

			//int height = curr - lastturn;
			
			if(trend == UPT && ptrend == DOWNT)
				{
				varr->Add(height);
				darr->Add(loop);
				}
			else if(trend == DOWNT && ptrend == UPT)
				{
				varr->Add(height);
				darr->Add(loop);
				}

#if 0
			else if(trend == DOWNT && ptrend == NULLT && pptrend == UPT)
				{
				varr->Add(height);
				darr->Add(loop);
				}
			else if(trend == UPT && ptrend == NULLT && pptrend == DOWNT)
				{
				varr->Add(height);
				darr->Add(loop);
				}
#endif

			lastturn  = curr;
			lastturnd = loop;

			pptrend = ptrend; 
			ptrend = trend;
			}
	
		data++;
		prev = curr;	
		}

	//P2N("Produced array len=%d\r\n", darr->GetSize());

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//

void	CWavCmp::CmpBuff(char *fbuff, int flen, char *buff, int len, CIntArr *parr)

{
	int flenx = flen / (int)sizeof(short);
	int lenx = len / (int)sizeof(short);

	short *fdata = (short*)fbuff;
	short *flim = fdata + flenx;
		
	//AP2N("fdata=%p flim=%d\r\n", fdata, flim);

#if 0
	// Get Max factor
	int maxval2 = 0, maxval = 0;
	short *tmpptr2 = (short*)buff;
	for(int loop2 = 0; loop2 < lenx;  loop2++)
		{
		int val = *tmpptr2;
		val = abs(val);
		maxval2 = max(maxval2, val);
		tmpptr2++;
		}
	short *tmp = (short*)malloc(len);

	// Normalize a copy of the sample
	short *tmpptr2a = (short*)buff;
	double factor = (double)SHRT_MAX / maxval2;
	for(int loops2 = 0; loops2 < lenx; loops2++)
		{
		short val = short(factor * *tmpptr2a++);
		tmp[loops2] = val;
		}
	maxval2 = SHRT_MAX;
#endif

	char *buff2 = buff; int len2 = len;
	AdjZero(&buff2, &len2);
	int lenx2 = len2 / sizeof(short);

	// Dump originator
	//for(int loop2d = 0; loop2d < lenx; loop2d++)
	//	pplot->AddLine(((short*)buff)[loop2d]);
	//pplot2->AddMarker();
	// Dump zero crossing
	for(int loop2e = 0; loop2e < lenx2; loop2e++)
		pplot2->AddLine(((short*)buff2)[loop2e]);

	while(true)
		{	
		int skip;

		if(fdata >= flim)
			break;

		char *buff4 = (char*)fdata; int len4 = flim - fdata;
		AdjZero(&buff4, &len4);
		int lenx4 = len4 / sizeof(short);

		//int diff = xCmpOneBuff((short*)buff4, lenx4, (short*)buff2, len2, &skip);			
		
		int diff = xHitCmp((short*)buff4, lenx4, (short*)buff2, len2, &skip);
	
		//fdata += max(skip, minskip);
		//fdata += 200;
		fdata += lenx / 4;

		parr->Add(diff);
		}

	//free (tmp);
}

int		CWavCmp::SubCmp(short *buff, int len, short *buff2, int len2)

{
	int skip;

		// Bail out if dis-similar frequency
	int rat = abs(len - len2) * 1000 / (len+len2);

	//AP2N("CWavCmp::HitCmp rat=%d len=%d / len2=%d\r\n", rat, len, len2);

	if(rat > 200)
		{
		//AP2N("CWavCmp::HitCmp (SC) len=%d / len2=%d\r\n", len, len2);
		return 0;
		}

	int ret = xCmpOneBuff(buff, len, buff2, len, &skip);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int		CWavCmp::xCmpOneBuff(short *fbuff, int flen, short *buff, int len, int *skip)

{
	//AP2N("CWavCmp::CmpBuffs(fbuff=%p, flen=%d, buff=%p, len=%d) ", 
	//						fbuff, flen, buff, len);

	// Only scan till common length
	len = min(len, flen);
	
	if(len == 0)
		return 0;

	// Normalize to curr
	int maxval = 0;
	short *tmpptr = (short*)fbuff;
	for(int loop2a = 0; loop2a < flen; loop2a++)
		{
		int val = *tmpptr;
		val = abs(val);
		maxval = max(maxval, val);
		tmpptr++;
		}

	// Prevent blow up
	if(maxval == 0)
		maxval = 1;

	// Normalize to curr
	int maxval2 = 0;
	short *tmpptr2 = buff;
	for(int loop2b = 0; loop2b < len; loop2b++)
		{
		int val2 = *tmpptr2;
		val2 = abs(val2);
		maxval2 = max(maxval2, val2);
		tmpptr2++;
		}

	//P2N("maxval = %d maxval2=%d\r\n", maxval, maxval2);

	short *tmpptr6 = buff;
	short *tmpptr7 = fbuff;

	int		diff = 0;

	for(int loop2c = 0; loop2c < len; loop2c++)
		{
		int val = *tmpptr7, val2 = *tmpptr6;
		
		// Normalize
		val  *= SHRT_MAX;	val /= maxval;
		val2 *= SHRT_MAX;	val2 /= maxval2;

		// Dump normalized
		//pplot2->AddLine(val);

		diff += abs(val2 - val);	
	
		tmpptr6++; tmpptr7++; 
		}

	int ret = diff;

	// Make it distance neutral
	if(len)
		ret /= len;

	//AP2N("%d\r\n", ret);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int		CWavCmp::HitCmp(short *buff, int len, short *buff2, int len2)

{
	int skip, ret;

	// Bail out if dis-similar frequency
	int rat = abs(len - len2) * 1000 / (len+len2);

	//AP2N("CWavCmp::HitCmp rat=%d len=%d / len2=%d\r\n", rat, len, len2);

	if(rat > 200)
		{
		//AP2N("CWavCmp::HitCmp (SC) len=%d / len2=%d\r\n", len, len2);
		return 0;
		}

	ret =	xHitCmp(buff, len, buff2, len2, &skip);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int		CWavCmp::xHitCmp(short *buff, int len, short *buff2, int len2, int *skip)

{
	int ret = 0;

	len = min(len, len2);

	//AP2N("CWavCmp::HitCmp(buff=%p, len=%d, buff2=%p len2=%d) ", 
	//											buff, len, buff2, len2);

	// Find peaks
	int maxval = xGetPeak(buff, len);
	int maxval2 = xGetPeak(buff2, len2);

	for(int loop2 = 0; loop2 < len; loop2++)
		{
		//int val = *buff;	 val *= INT_MAX;  val  /= maxval;
		//int val2 = *buff2; val2 *= INT_MAX; val2 /= maxval2;
		
		int val = *buff;	val <<= 16;  val /= maxval;
		int val2 = *buff2;	val2 <<= 16; val2 /= maxval2;
		
		int  yy = val / divisor;

		if( (val2 > val - yy) && val2 < val + yy)
			{
			ret += 1000;
			}

		buff++; buff2++;
		}

	if(len)
		ret /= len;

	//AP2N(" ret=%d\r\n", ret);

	return ret;
}



//////////////////////////////////////////////////////////////////////////
// Adjust buffer to have zero crossings

void CWavCmp::AdjZero(char **buff, int *len)

{
	ASSERT(*len >= 0);

	char *buff3 = *buff; int len3 = *len;

	// Walk forward till next zero crossing
	short *elim2 = (short*)(buff3 + len3);
	short *tmpptr3 = (short*)buff3;

	while(true)
		{
		if(tmpptr3 >= elim2)
			break;

		if(*tmpptr3 < 0 && *(tmpptr3+1) >= 0)
			break;

		tmpptr3++;
		}
	
	// Walk back for ending zero cross
	short *tmpptr5 = (short*)(buff3 + len3);
	while(true)
		{		
		if((char*)tmpptr5 <= buff3)
			break;

		if(*tmpptr5 < 0 && *(tmpptr5+1) >= 0)
			break;
		
		tmpptr5--;
		}
	
	//AP2N("CWavCmp::AdjZero %p %d -> %p %d\r\n",
	//			*buff, *len, tmpptr3, tmpptr5 - tmpptr3);

	// Limit length to zero
	int tmplen = (tmpptr5 - tmpptr3) * sizeof(short);
	
	// Not found, limit damage
	if(tmplen < 0)
		{
		tmplen = 0;	tmpptr3 = (short*)buff3;
		}

	*buff = (char*) tmpptr3;
	*len = tmplen;
}

//////////////////////////////////////////////////////////////////////////

int CWavCmp::xGetPeak(short *buff, int len)

{
	// Find peak 1
	int maxval = 0;
	
	for(int loop2a = 0; loop2a < len; loop2a++)
		{
		int val = *buff;	val = abs(val);
		maxval = MAX(maxval, val);
		buff++;
		}
	return maxval;
}
