
/* =====[ Recog.cpp ]===================================================== 
                                                                             
   Description:     The daco project, implementation of the Recog.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/8/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"

#include "xRecog.h"
#include "mxpad.h"
#include "support.h"
#include "frag.h"
#include "fragcoll.h"
#include "FftBuff.h"
#include "ContColl.h"
#include "ContainArr.h"

#include "FragCollArr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Make sure we use async only
#undef P2N

extern	CxRecog		xdllrecog;
extern	CFragColl	*pfragcoll;
extern	CFftBuff	fftbuff;
extern	CStrColl	dicstrcoll;

extern  CFragCollArr	fragcollarr;

//////////////////////////////////////////////////////////////////////////
// Call this from recording with the sample buffer and regog object

int		CxRecog::_statRec(void *cls, char *buff, int len)
 
{
 	//AP2N("CxRecog::statRec %p %d\r\n");
 
 	((CxRecog*)cls)->Feed(buff, len);

 	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CxRecog::CxRecog()

{
	//////////////////////////////////////////////////////////////////////
	// Init configurable values

	// Set histeresis here. Change is registered when signal->noise 
	// or noise->signal transient is longer than this number of buffers
	ChangeTresh = 10;
	
	// This is the initial value for minimum noise level. Assumes 
	// 16 bit signal range. (65535 / 2)
	NoiseLevel = 3000;
	
	// How many frequency components to include
	FreqCompCnt = 8;

	// How many hits from the sorted list to include
	HowManyHits = 4;

	// How many entries to avarage for one index
	NumAverage = 2;

	// How tolerant on frequency compare. 	
	Strictness = 20;

	//////////////////////////////////////////////////////////////////////
	// Init the rest

	_perfrec = _ledrec = _fragrec = _fragrec2 = _wavrec = _strrec = NULL;
	_plotrec = NULL;  _spectrec = NULL;
	lastbuff = NULL; xpcurrcoll = NULL;

	noprompt = strict = meshutdown = lastbuflen = 0;	
	xreenter = xnoised = xsigged = xin_useful = false;
}
	
//////////////////////////////////////////////////////////////////////////

CxRecog::~CxRecog()

{
	//TRACE("CxRecog::~CxRecog()\r\n");	

	// So it rejects and frees newly passed buffers
	// (this is an async termination hack, the OS will free the rest)
	meshutdown = true;

	//TRACE("CxRecog::~CxRecog buffarr=%d\r\n", buffarr.GetSize());

	if(lastbuff)
		free(lastbuff);

	// Free stale recognition buffers
	for(int loop = 0; loop < xbuffarr.GetSize(); loop++)
		{
		free ((char*) xbuffarr[loop]);
		}
}

//////////////////////////////////////////////////////////////////////////
// Entry point to send sound samples to
// 
// The buffer sent is trusted to the callee for freeing
//

int		CxRecog::Feed(char *buff, int len)

{
	//AP2N("CxRecog::Recognize(char *buff=%p, int len=%d)\r\n", buff, len);

	if(meshutdown)
		{
		free(buff);
		return 0;
		}

	if(xreenter)
		{
		free(buff);
		return 0;
		}

	// Quick analysys of the buffer for signal
	short *buffs = (short*)buff;
	int peak = abs(buffs[0]) + abs(buffs[1]) 
						+ abs(buffs[2]) + abs(buffs[3]);
	peak /= 4;

	// See if buffer contains any signal, add it to the queue
	short *buff2 = (short*)buff;
	int sig = 0, step = 4, len2 = len / sizeof(short);
	for(int loop = 0; loop < len2; loop += step)
		{
		if(abs(*buff2) > NoiseLevel)
			sig++;
		buff2 += step;
		}
	
	//AP2N("count %d\r\n", sig);

	// Early out to save processor
	if(sig < 20)
		{
		if(_ledrec)
			_ledrec((const char *)peak, false);

		//AP2N("Noise %d %d\r\n",  sig, NoiseLevel);
		//blank++;

		xnoised++;
		}
	else
		{
		//AP2N("Sig %d\r\n",  sig);

		if(_ledrec)
			_ledrec((const char *)peak, true);

		xsigged++;
		}

	xlastlen = len;

	// Logic to filter the on / off state of the signal
	if(xin_useful)
		{		
		xbuffarr.Add(buff);
		
		// In signal, watch for noise switch
		if(xnoised > ChangeTresh)
			{
			//AP2N("xSwitched sig->noise =%d\r\n", buffarr.GetSize());
			xsigged = 0;	xin_useful = false;
			Recognize(1);
			}
		}
	else
		{
		// In noise, watch for signal treshold
		if(xsigged > ChangeTresh)
			{
			//AP2N("xSwitched noise->sig %d\r\n", buffarr.GetSize());	
			xnoised = 0;	xin_useful = true;
			}

		xbuffarr.Add(buff);

		int pullback = 4;
		// Pull it back to change_tresh
		int blen = xbuffarr.GetSize();
		if(blen >  ChangeTresh + pullback)
			{
			for(int loopb = 0; loopb < blen - ChangeTresh - pullback; loopb++)
				{
				free(xbuffarr.GetAt(loopb));
				}
			xbuffarr.RemoveAt(0, blen - ChangeTresh - pullback);
			}
		}			
 	
	//AP2N("Sig %d\r\n", sig);	
	
	// Buffer too big, force recog. This can happen for too much 
	// noise, or continuous speech for too long.

	if(xbuffarr.GetSize() > 300)
		{
		//AP2N("Forced recog\r\n");
		Recognize();
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Process all accumulated scans ...

 void CxRecog::Recognize(int minlen)

{
	if(meshutdown)
		return;

	if(xreenter)
		{
		//AP2N("*****Reentering CxRecog::Recognize\r\n");
		return;
		}

	xreenter = true;
	//bigmatch = 0;

	int alen = xbuffarr.GetSize();

	if(_ledrec)
		_ledrec(NULL, false);

	AP2N("CxRecog::Recognize() alen = %d train='%s'\r\n", alen, trainstr);

	if(alen > minlen)
		{
		lastbuflen = alen * xlastlen;		
		char *sound = (char*)malloc(lastbuflen); ASSERT(sound);

		for(int loop = 0; loop < alen; loop++)
			{
			char *val = (char*)xbuffarr.GetAt(loop);
			memcpy(sound + (loop * xlastlen), val, xlastlen);
			}

		char *newbuff  = (char*)malloc(lastbuflen);
		if(_wavrec)
			{
			_wavrec(sound, lastbuflen);
			}

		// Allocate
		lock.Lock();
		if(lastbuff)
			free(lastbuff);

		support.MarkPerf();

		lastbuff = (char*) malloc(lastbuflen); ASSERT(lastbuff);
		lock.Unlock();

		dsp.NormalizeWav(sound, lastbuflen, lastbuff);
		free(sound);	
		free(newbuff);

		xShowPerf("Wave processing");

		// Show post split / normalized sound
		if(_wavrec2)
			{
			_wavrec2(lastbuff, lastbuflen);
			}

		if(trainstr != "")
			{
			if(_strrec)
				_strrec("", 0);
			}
	
		//////////////////////////////////////////////////////////////////
		// Start of analisys
		
		CAnalRes res;

		// Scan it with fresh start for arrays		
		ScanSpectra(lastbuff, lastbuflen, &res);	

#if 0
		for(int loopms = 0; loopms < res.raw.GetSize(); loopms++)
			{
			CIntArr	*tmp = (CIntArr *)res.raw.GetAt(loopms);

			AP2N("CxRecog::Recognize ScanSpectra Dump:");
			for(int loopd2 = 0; loopd2 < tmp->GetSize(); loopd2++)
				{			
				AP2N("%3d  ", tmp->GetAt(loopd2));
				}
			AP2N("\r\n");
			}			
#endif
		
		// Free sound buffers and arrays
		int alen2 = xbuffarr.GetSize();
		for(int loop2 = 0; loop2 < alen2; loop2++)
			{
			char *val = (char*)xbuffarr.GetAt(loop2); free(val);
 			}
		xbuffarr.RemoveAll();		

		support.MarkPerf();

		analproc.ProcSpectra(&res, FreqCompCnt);

		xShowPerf("Spectral processing");

		//////////////////////////////////////////////////////////////////
		// Generate an array of match ordered items

		CContainArr *pcontarr = new CContainArr;	 ASSERT(pcontarr);
		//*pcontarr->name = trainstr;
	
		xCmpSpectra(&res, pcontarr);

		pcontarr->Dump();

		delete pcontarr;
		xreenter = false;
		return;

		//AP2N("Pre Weed:\r\n");	pcont->Dump();
		//pcont->WeedNX();		
		//AP2N("Pre Weed:\r\n"); pcont->DumpFilter();		
		
#if 0
		pcont->WeedEnds();	
		
		//pcont->Dump();
		
		CString tmps = pcont->Dump2Str();
	
		CString flist = pcont->GetConcatStrx();
		AP2N("Flist = '%s'\r\n", flist);
					
		if(_fragrec)
			{
			_fragrec(flist, flist.GetLength());	
			}
	
		if(trainstr == "")
			{			
			support.MarkPerf();

			int m1, m2, rec = strcoll.CmpCont(pcont, &m1, &m2);

			xShowPerf("Container search");

			CString strec = "Noise";

			if(rec >= 0 && m1 > 500)
				{				
				strec = strcoll.GetAt(rec);	
				}
			
			if(_strrec)
				_strrec(strec, strec.GetLength());

			delete pcont;	// Temporary results, dispose of it
			}
		else
			{	
			support.MarkPerf();

			strcoll.AddCont(pcont);

			xShowPerf("Training added");
			}

#endif

		}	

	xreenter = false;
}

//////////////////////////////////////////////////////////////////////////
// Execute all the scanning / partitioning / filtering / summing

void CxRecog::ScanSpectra(char *buff, int len, CAnalRes *pres)

{
	CPtrArray *parr = pres->raw.GetData();
	CPtrArray *parr2 = pres->phase.GetData();

	// Make sure they are all empty
	CFragUtil::_FreeArr(parr); 
		
	support.MarkPerf();

	// Convert it to entry point specific length
	int len2 = len / sizeof(short); short *ptr = (short*)buff;

	fftbuff.Transform(ptr, len2, parr, parr2);		// Do analisys with FFT
	//fscan.ScanBuff(ptr, len, parr);		// Do analisys with FREQ scan
	//wavelet.Transform(ptr, len, parr);	// Do analisys with WaveLet

	xShowPerf("Spectral Scan");

	// Fill in signal2
	xGetSigArr((short *)buff, len / sizeof(short), pres);

	// Visualizer for raw FFT data

#if 0

	support.MarkPerf();

	int alen = parr->GetSize();
 	for(int loopdy = 0; loopdy < alen; loopdy += 1)
 		{
 		CIntArr *tmp = (CIntArr*)parr->GetAt(loopdy);

		if(_spectrec)
			_spectrec(tmp->GetData(), tmp->GetSize() );

		if(_spectrec2)
			_spectrec2(tmp->GetData(), tmp->GetSize() );
		}	

	if(_spectrec)		
		_spectrec(NULL, 0);

 	if(_spectrec2)		
		_spectrec2(NULL, 0); 	

	xShowPerf("Spectral display");

#endif

}	

//////////////////////////////////////////////////////////////////////////
// Compare wave data with sample frags, put it in container
// Scan on a per user basis

int CxRecog::xCmpSpectra(CAnalRes *res, CContainArr *pcontarr)

{
	int prev = 0, ret = 0, alen = res->raw.GetSize();
	CFrag *prevf = NULL; 
	
	AP2N("CxRecog::xCmpSpectra len=%d\r\n", alen);

	if(alen == 0)
		{
		AP2N("CxRecog::xCmpSpectra: empty parr\r\n");
		return ret;
		}
	
	int fff = fragcollarr.GetSize();

	//////////////////////////////////////////////////////////////////////
	// Scan all users

	for(int loop = 0; loop < fff; loop++)
		{
		xpcurrcoll = fragcollarr.GetAt(loop);

		CContain *ucont = new CContain; ASSERT(ucont);

		*ucont->name = xpcurrcoll->user;
		pcontarr->Add(ucont);
		
		ASSERT(xpcurrcoll->magic == CFragColl_Magic);

		CPtrArray *tmparr = xpcurrcoll->GetData();	
		int len2f = tmparr->GetSize();

		if(len2f == 0)
			{
			if(_fragrec)
				{
				CString tmp; tmp.Format(
					"No frags are loaded into %s", xpcurrcoll->user);
				_fragrec(tmp, tmp.GetLength());
				}

			//AP2N("CxRecog::xCmpSpectra: empty fragarr\r\n");
			//return ret;
			}
	
		// ---------------------------------------------------------------
		// Scan the body of the array

		support.MarkPerf();			

		//int rrr = xCmpSpectra2(0, res, pcontarr);
		int rrr = xCmpSpectra2(0, res, ucont);
		
		xShowPerf("Frag search");

		//ucont->Dump();
		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Branch out to user by setting pcurrcoll

int CxRecog::xCmpSpectra2(int skip, CAnalRes *parr, CContain *pcont)

{
	int ret = 0;

	AP2N("CxRecog::xCmpSpectra2 user='%s'\r\n", xpcurrcoll->user);
		
	ASSERT(xpcurrcoll->magic == CFragColl_Magic);

	CPtrArray *tmparr = xpcurrcoll->GetData(); int len2f = tmparr->GetSize();


	if(len2f == 0)
		{
		AP2N("CxRecog::xCmpSpectra2: empty global fragarr\r\n");
		return ret;
		}

	int alen = parr->raw.GetSize();
	if(alen == 0)
		{
		AP2N("CxRecog::xCmpSpectra2: empty arrarr\r\n");
		return ret;
		}

	//AP2N("CxRecog::xCmpSpectra2: skip=%d, alen=%d\r\n", skip, alen);

	// Various length truncations for scan
	//int len = alen - (pcurrcoll->maxlen + pcurrcoll->minlen / 2);
	//int len = alen - pcurrcoll->maxlen;
	//int len = alen - pcurrcoll->minlen;
	int len = alen;

	//AP2N("1=====================\r\n");

	int aa = xCmpSpectra3(0, len, parr, pcont);
		
	if(_fragrec)
		{
		_fragrec("\r\n----------\r\n", 14);	
		}

	//AP2N("----------\r\n");
				
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Select top entries for this offset

int CxRecog::xPreSel(CAnalRes *parr, int offs, CContain::CContData *pdat)

{
	CIntArr valarr;	CPtrArray fragarr;
	CStringArray sarr;

	for(int loop3 = 0; loop3 < pdat->idxs.GetSize(); loop3++)
		{
		CIntArr  sdiff, diffarr;
		int idx = pdat->idxs.GetAt(loop3);

		//AP2N("idx=%d  ", idx);

		CPtrArray *parrx = (CPtrArray*)xpcurrcoll->GetIdxData()->GetAt(idx);
		int alen = parrx->GetSize();

		for(int loop = 0; loop < alen; loop++)
			{
			CFrag *pfr = ((CFrag *)parrx->GetAt(loop));
			ASSERT(pfr->magic == CFrag_Magic);

			//AP2N("	%9s \r\n", *pfr->name);

			CCmpRes pres;
			int diff3 = pfr->CmpFrags(parr, offs, &pres);	
			diffarr.Add(diff3);
			}

		diffarr.Sort(&sdiff);
	
		int diffsum = 0;
		int olen = MIN(sdiff.GetSize(), NumAverage);
		for(int loopsum = 0; loopsum < olen; loopsum++)
			{ 
			int idx = sdiff.GetAt(loopsum);
			//int idx2 = sdiff.GetAt(loopsum);

			// Only add the first one
			if(loopsum == 0)
				{
				CFrag *pfr = ((CFrag *)parrx->GetAt(idx));
				ASSERT(pfr->magic == CFrag_Magic);

				fragarr.Add(pfr);				
				}
			int diff = diffarr.GetAt(idx);
			diffsum += diff;
			}

		if(olen)
			diffsum /= olen;

		valarr.Add(diffsum);	
		}

	CIntArr sval; valarr.Sort(&sval);

	int nlim = MIN(pdat->outlim, sval.GetSize());

	for(int loop = 0; loop < nlim; loop++)
		{
		int idx = sval.GetAt(loop);
		CFrag *pfr = ((CFrag *)fragarr.GetAt(idx));
		int diff = valarr.GetAt(idx);
			
		//if(loop < 1)
		//	AP2N("%s=%d   ", *pfr->name, diff);

		//pdat->ppre.Add(pfr->idx);
		pdat->vals.Add(diff);	pdat->frags.Add(pfr);
		}

	//AP2N("\r\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Process slices by offset into the unknown

int CxRecog::xCmpSpectra3(int ss, int ee, CAnalRes *parr, CContain *pcont)

{
	CPtrArray *tmparr = xpcurrcoll->GetData();	int len2f = tmparr->GetSize();
	
	//AP2N("xCmpSpectra3 ss=%d ee=%d len=%d\r\n",  ss, ee, parr->all.GetSize());

	// Walk designated slices
	for(int loopx2 = ss; loopx2 < ee; loopx2 += 1)
		{	
		CIntArr cmparr, cmparr2, sarr, outarr; 
		//CIntArr	  pre, pre2, pre3, idxs;

		CContain::CContData *ppredat;  ppredat = new CContain::CContData;
		ppredat->outlim = HowManyHits;
	
		// Build indexes
		int alenx = xpcurrcoll->GetIdxData()->GetSize();
		for(int loopx = 0; loopx < alenx; loopx++)
			{
			ppredat->idxs.Add(loopx);
			}

		xPreSel(parr, loopx2, ppredat);
		
#if 0
		AP2N("xPreSel:\r\n");

		for(int loop2a = 0; loop2a < ppredat->frags.GetSize() / 2; loop2a++)
			{
			CFrag *pfr = (CFrag*)ppredat->frags.GetAt(loop2a);
			
			AP2N(" %s %d  -- ", pcurrcoll->Idx2Str(pfr->idx),
											ppredat->vals.GetAt(loop2a) );
			}
		AP2N("\r\n");
#endif

		// Copy over power formulas
		pcont->sig.Copy(parr->sig);
		pcont->sig2.Copy(parr->sig2);

		// Produce output:
		pcont->Add(ppredat);

#if 0
		int lenz = MIN(HowManyHits, ppredat->ppre.GetSize());
		for(int loops4 = 0; loops4 < lenz; loops4++)
			{
			// Calc rat
			if(loops4 + 1 < ppredat->ppre.GetSize())
				{
				int next = ppredat->vals.GetAt(loops4+1);
				int curr = ppredat->vals.GetAt(loops4);

				int rat = (100 *  curr) / MAX(1, next);
				//rat =  prev = curr;
				//rat =  prev - curr;
				
				CString str = pcurrcoll->Idx2Str(ppredat->ppre.GetAt(loops4));

				pcont->Add(ppredat);
				}
			}
#endif

		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////

void	CxRecog::xGetSigArr(short *ptr, int len2, CAnalRes *pres)

{
	int step = fftbuff.GetDepth();

	CIntArrRec *parr = &pres->sig2;

	short	*data = ptr;
	short	*endd = ptr + (len2 - step);  // Miss the last one
	
	while(TRUE)
		{
		if(data > endd)
			break;
	
		int val = xGetSig(data, step);

		parr->Add(val);

		// Make sure this formula is the same as the FFT
		//data += step;
		data += 3 * step / 4;
		}

	//parr->Smooth();
	//xdllrecog._plotrec(parr->GetData(), parr->GetSize(), 1);
	//xdllrecog._plotrec(0, 0, 1);
}

//////////////////////////////////////////////////////////////////////////

int		CxRecog::xGetSig(short *ptr, int len2)

{
	int sum = 0;
	for(int loop = 0; loop < len2; loop++)
		{
		int val = ptr[loop] / 100; sum += ABS(val);
		}
	return sum / len2;
}

//////////////////////////////////////////////////////////////////////////

void	CxRecog::xShowPerf(const char *str)

{
	int perf3 = support.QueryPerf();

	CString tmp3; tmp3.Format("%s in %d msec\r\n", str, perf3);

	if(_perfrec)
		_perfrec(tmp3, tmp3.GetLength());
}
