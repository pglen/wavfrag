
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

#include "Recog.h"
#include "mxpad.h"
#include "support.h"
#include "frag.h"
#include "FragColl.h"

#include "FftBuff.h"
#include "freqscan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Make sure we use async only
#undef P2N

//extern	CRecog		dllrecog;
extern	CFragColl	fcoll;
extern	CFftBuff	fftbuff;
extern	CFreqScan	fscan;

#define	NORM_SOUND	1

//////////////////////////////////////////////////////////////////////////
// Call this from recording

int		CRecog::_statRec(void *cls, char *buff, int len)
 
{
 	//P2N("CRecog::statRec %p %d\r\n");
 
 	((CRecog*)cls)->Recognize(buff, len);

 	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecog::CRecog()

{
	fcoll.precog = this;

	// Set histeresis here.
	change_tresh = 4;
	
	// Wave is scanned by this much at a time
	acnt = 300;

	// This is the sample value for minimum noise level
	noiselevel	= 3000;

	_perfrec = _ledrec = _fragrec = _wavrec = _strrec = NULL;
	_spectrec = NULL;

	bigmatch = strict = xreenter = meshutdown =  0;
	
	xnoised = 0, xsigged = 0;
	xin_useful = false;

	lastbuff	= NULL;
	lastbuflen	= 0;
	noprompt		= false;
}

//////////////////////////////////////////////////////////////////////////

CRecog::~CRecog()

{
	//TRACE("CRecog::~CRecog()\r\n");	

	// So it rejects and frees newly passed buffers
	meshutdown = true;

	//TRACE("CRecog::~CRecog buffarr=%d\r\n", buffarr.GetSize());

	if(lastbuff)
		free(lastbuff);

	// Free stale recognition buffers
	for(int loop = 0; loop < buffarr.GetSize(); loop++)
		{
		free ((char*) buffarr[loop]);
		}
}

//////////////////////////////////////////////////////////////////////////
// Entry point to send sound samples to

int		CRecog::Recognize(char *buff, int len)

{
	//AP2N("CRecog::Recognize(char *buff=%p, int len=%d)\r\n", buff, len);

	//CPtrArray *tmparr = &fcoll.fragarr;
	//int len2f = tmparr->GetSize();
	//AP2N("CRecog::Recognize len2f=%d\r\n", len2f);

	if(meshutdown)
		{
		free(buff);
		return 0;
		}

	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	// Quick analysys of the buffer
	short *buffs = (short*)buff;
	int peak = abs(buffs[0]) + abs(buffs[1]) 
						+ abs(buffs[2]) + abs(buffs[3]);
	peak /= 4;

	// See if buffer contains any signal
	short *buff2 = (short*)buff;
	int sig = 0, step = 4, len2 = len / sizeof(short);
	for(int loop = 0; loop < len2; loop += step)
		{
		if(abs(*buff2) > noiselevel)
			sig++;
		buff2 += step;
		}
	
	//AP2N("count %d\r\n", sig);

	// Early out to save processor
	if(sig < 20)
		{
		if(_ledrec)
			_ledrec((const char *)peak, false);

		//AP2N("Noise %d %d\r\n",  sig, noiselevel);
		//blank++;

		xnoised++;
		}
	else
		{
		//AP2N("Sig %d\r\n",  sig);

		//pwnd->m_led.SetState(true);
		//blank = 0;

		if(_ledrec)
			_ledrec((const char *)peak, true);

		xsigged++;
		}

	xlastlen = len;

	if(xin_useful)
		{		
		buffarr.Add(buff);
		
		// In signal, watch for noise switch
		if(xnoised > change_tresh)
			{
			//AP2N("xSwitched sig->noise =%d\r\n", buffarr.GetSize());
			xsigged = 0;	xin_useful = false;
			Emit(1);
			}
		}
	else
		{
		// In noise, watch for signal treshold
		if(xsigged > change_tresh)
			{
			//AP2N("xSwitched noise->sig %d\r\n", buffarr.GetSize());	
			xnoised = 0;	xin_useful = true;
			}

		buffarr.Add(buff);

		int pullback = 4;
		// Pull it back to change_tresh
		int blen = buffarr.GetSize();
		if(blen >  change_tresh + pullback)
			{
			for(int loopb = 0; loopb < blen - change_tresh - pullback; loopb++)
				{
				free(buffarr.GetAt(loopb));
				}
			buffarr.RemoveAt(0, blen - change_tresh - pullback);
			}
		}			
 	
	//AP2N("Sig %d\r\n", sig);	
	
	// Buffer too big, go recog
	if(buffarr.GetSize() > 300)
		{
		//AP2N("Forced recog\r\n");
		Emit();
		}

	//free(buff);

	return 0;
}

//////////////////////////////////////////////////////////////////////////

void CRecog::NormalizeWav(char *buff, int len, char *out)

{
	int len2 = len / sizeof(short);	
	
	//AP2N("void CRecog::Normalize(char *buff, int len=%d, char *out)\r\n", len);
		
	short *pptr = (short*)buff, *lptr = (short*)out;
	short *outptr = lptr;

#ifdef NORM_SOUND

	double factor;
	//int	loop, maxx;
	
#if 0
	// Compress to square root
	double rate;

	short *tmpptr = (short*)malloc(len);

	pptr = (short*)buff; outptr = tmpptr;
	//rate = (double)SHRT_MAX / sqrt((double)SHRT_MAX);
	rate = (double)SHRT_MAX / log((double)SHRT_MAX);

	for(int loop = 0; loop < len2; loop++)
		{
		double dval = (double) *pptr++;

		// SQRT pos and neg
		if(dval > 0 )
			dval = rate * log(dval);
		else
			dval = - (rate * log(-dval));

		*outptr++ = short(dval);
		}
	pptr = (short*)tmpptr; 
#else
	pptr = (short*)buff; 
	
#endif

#if 1
	// Calc maximum value
	// Calc avarage value (2)
	int maxx = 0; double sum = 0;
	for(int loop = 0; loop < len2; loop++)
		{
		short val = abs(*pptr++);

		//if(maxx < val)
		//	maxx = val;

		sum += val;
		}
	maxx = int(sum / len2);

	//AP2N("avg = %d\r\n", maxx);
	
	// Calc scaling factor
	factor = (double)SHRT_MAX / maxx;

	factor /= 10;	// Assume some dynamics
	
	//AP2N("CRecog::Normalize factor=%.f\r\n", factor);

	// Limit scaling factor
	if(factor < 100)
		{
		// Multiply
		outptr = lptr;	
		pptr = (short*)buff;				// Original
		//pptr = (short*)tmpptr;			// Compressed

		for(loop = 0; loop < len2; loop++)
			{
			short val = *pptr++; 
			double dval = factor * val;		

			// Clip it, so no artifacts, just a clip
			if(dval > SHRT_MAX) dval  = SHRT_MAX;
			if(dval < -SHRT_MAX) dval = -SHRT_MAX;

			*outptr++ = short(dval);
			}
		}
	else
		{
		// Too big scale factor, copy straight
		outptr = lptr;	pptr = (short*)buff;
		for(loop = 0; loop < len2; loop++)
			{
			*outptr++ = *pptr++;
			}
		}
#endif

	//if(((CWavfragDlg*)AfxGetApp()->m_pMainWnd)->record)
	//	{
	//	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	//	//pwnd->playsound.PlayWave((char*)ptr, len);
	//	}

#else
	memcpy(lptr, buff, len);
#endif
	
}

//////////////////////////////////////////////////////////////////////////
//

void	CRecog::xScanSpectra(short *ptr, int len, CIntArr *piarr, CIntArr *pvarr)

{	
	CPtrArray tmparr;		

	//AP2N("CRecog::ScanSpectra(short *ptr=%p, int len=%d\r\n", ptr, len);
	
//////////////////////////////////////////////////////////////////////////

	support.MarkPerf();

	// Do analisys with FFT
	//fftbuff.Transform(ptr, len, &tmparr);

	// Do analisys with scan buffer
	fscan.ScanBuff(ptr, len / 2, &tmparr);

	int perf = support.QueryPerf();
	
	CString tmp; tmp.Format("Spectral scan in %d msec\r\n", perf);
	if(_perfrec)
		_perfrec(tmp, tmp.GetLength());

 	// Pre process visualizer 
 #if 1
 		for(int loopd = 0; loopd < tmparr.GetSize(); loopd += 1)
 			{
 			if(_spectrec2)
				{
				CIntArr *tmp = (CIntArr*)tmparr.GetAt(loopd);
				_spectrec2(tmp->GetData(), tmp->GetSize() );
				}
 			}	
		if(_spectrec2)
			_spectrec2(NULL, 0);
 		
 #endif

	support.MarkPerf();

	fftbuff.GetDominant(&tmparr, piarr, pvarr);

	int perf2 = support.QueryPerf();

	CString tmp2; tmp2.Format("Dominant conversion in %d msec\r\n", perf2);
	if(_perfrec)
		_perfrec(tmp2, tmp2.GetLength());

	int alen = piarr->GetSize();

#if 0
	// Post scan visualizer 
		
	for(int loopd = 0; loopd < alen; loopd += FRAG_STEP)
		{
		CIntArr arr3;
		arr3.Fill(MAXFFTVAL + 1, 0);

		// Create new sums
		int sum = 0;	
		
		// Convert it back to plottable
		for(int loop = 0; loop < FRAG_STEP; loop++)
			{
			int loopx = loopd + loop;
			int vol =  pvarr->GetAt(loopx);
			sum += vol;								
			arr3.SetAt(piarr->GetAt(loopx), vol);	
			}

		if(_spectrec2)
			{
			_spectrec2(arr3.GetData(), arr3.GetSize() );
			}
		}
			
	if(_spectrec2)
		_spectrec2(NULL, 0);

#endif

	xFreeArr(&tmparr);
}

//////////////////////////////////////////////////////////////////////////

void	CRecog::xFreeArr(CPtrArray *parr)

{
	// Free array
	int alen2 = parr->GetSize();

	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loop2);

		ASSERT(tmp->magic == INTARR_MAGIC);
		delete tmp;
		}
	parr->RemoveAll();
}

//////////////////////////////////////////////////////////////////////////
// Process all accumulated scans ...

void CRecog::Emit(int minlen)

{
	if(xreenter)
		{
		//AP2N("*****Reentering CRecog::Emit\r\n");
		return;
		}

	xreenter = true;
	bigmatch = 0;

	int alen = buffarr.GetSize();

	if(_ledrec)
		_ledrec(NULL, false);

	//AP2N("CRecog::Emit() alen = %d\r\n", alen);

	if(alen > minlen)
		{
		lastbuflen = alen * xlastlen;		
		char *sound = (char*)malloc(lastbuflen); ASSERT(sound);

		for(int loop = 0; loop < alen; loop++)
			{
			char *val = (char*)buffarr.GetAt(loop);
			memcpy(sound + (loop * xlastlen), val, xlastlen);
			}

		char *newbuff  = (char*)malloc(lastbuflen);
		if(_wavrec)
			{
			_wavrec(sound, lastbuflen);
			}

		// Normalize
		NormalizeWav(sound, lastbuflen, newbuff);
		free(sound);
	
		CPtrArray sparr; CIntArr siarr;
		PowerSplit(newbuff, lastbuflen, &sparr,  &siarr);
		PowerCombine(sparr, siarr);

		free(newbuff);

		// Show post split / normalized sound
		if(_wavrec2)
			{
			_wavrec2(lastbuff, lastbuflen);
			}

		//////////////////////////////////////////////////////////////////
		// Fresh start for arrays

		CIntArr  iarr, varr;

		Scan(lastbuff, lastbuflen, &iarr, &varr);	
		
#if 0
		if(pwnd->stablized)
			{
			for(int loopdd = 0; loopdd < arrarr.GetSize(); loopdd++)
				{
				CPtrArray *ddd = (CPtrArray*) arrarr.GetAt(loopdd);

		 		for(int loopd = 0; loopd < ddd->GetSize(); loopd += 1)
					{
 					pwnd->visdlg.m_vis.AddIntArr((CIntArr*)ddd->GetAt(loopd));	
 					}	
				pwnd->visdlg.m_vis.AddMarker();
				}
			}
#endif
		//free(buff2);

		result = "";

		// Do the analisys
		SplitSpectra(&iarr, &varr);

		CIntArr icum, vcum;
		RecombineSpectra(&icum, &vcum);

		CContain contain;
		xCmpSpectra(&icum, &vcum, &contain);

		if(contain.GetArr()->GetSize())
			{
			CContain::CResult *xres = (CContain::CResult*)contain.GetArr()->GetAt(0);
			result = *xres->name; 
			if(_strrec)
				{
				if(strict)
					{
					if(!bigmatch)
						result = "-";
					}
				_strrec(result, result.GetLength());
				}
			}
		}
	
	// Free sound buffer arrays
	int alen2 = buffarr.GetSize();
	for(int loop2 = 0; loop2 < alen2; loop2++)
		{
		char *val = (char*)buffarr.GetAt(loop2);
		free(val);
 		}
	buffarr.RemoveAll();		

	xreenter = false;
}

//////////////////////////////////////////////////////////////////////////
// Execute all the scanning / partitioning / filtering

void CRecog::Scan(char *buff, int len, CIntArr *piarr, CIntArr *pvarr)

{
//////////////////////////////////////////////////////////////////////////

//#define REDUNDTANT   // for getting rid of duplicate spectra

#ifdef REDUNDTANT

	CIntArr	ss, vv;
	
	xScanSpectra((short*)buff, len / sizeof(short), &ss, &vv);		

	int alen = ss.GetSize();
	
	// Self similarity scan
	int span = 4 * FRAG_STEP;	// how much data to consider on self similarity

	for(int loopd2 = span; loopd2 < alen - span; loopd2 += FRAG_STEP)
		{
		int cno = 0;

		// Output
		for(int loopd3a = loopd2; loopd3a < loopd2 + FRAG_STEP; loopd3a +=1)
			{
			piarr->Add(ss.GetAt(loopd3a));
			pvarr->Add(vv.GetAt(loopd3a));
			}

		// Scan for self similarity
		for(int loopd3 = loopd2; loopd3 < loopd2 + span; loopd3 +=1)
			{
			int idx1 =  ss.GetAt(loopd3 - span);
			int idx2 =  ss.GetAt(loopd3);

			// Similarity criteria
			if(ABS(idx1 - idx2) < 1)
				cno++;
			}

		// Self similarity - skip
		if(cno > span - span / 4)
			{
			loopd2 +=  FRAG_STEP;
			}		
		
		pdlg->m_plot1.AddLine(cno);
		}
#else

	xScanSpectra((short*)buff, len / sizeof(short), piarr, pvarr);			

#endif	// REDUNDANT

#if 0
	// Convert it back to plottable, visualize it
	int alenb = piarr->GetSize();
	
	for(int loopdb = 0; loopdb < alenb; loopdb += FRAG_STEP)
		{
		CIntArr arr3; arr3.Fill(MAXFFTVAL + 1, 0);
			
		// Bend post process visualizer 
		for(int loop = 0; loop < FRAG_STEP; loop++)
			{
			int loopx = loopdb + loop, vol =  pvarr->GetAt(loopx);
			arr3.SetAt(piarr->GetAt(loopx), vol);	
			}

		if(_spectrec2)
			{
			_spectrec2(arr3.GetData(), arr3.GetSize() );
			}
		}
	
	if(_spectrec2)
		{
		// Send NULL for boundary 
		_spectrec2(NULL, 0);
		}

#endif

}	

//////////////////////////////////////////////////////////////////////////

int CRecog::SplitSpectra(CIntArr *piarr, CIntArr *pvarr)

{
	// Build sum array
	CIntArr		sumarr;
	
	// Push them into the mix
	int alen = piarr->GetSize();
	for(int loop = 0; loop < alen; loop += FRAG_STEP)
		{
		int sum = 0;
		for(int loop2 = 0; loop2 < FRAG_STEP; loop2++)
			{
			sum += pvarr->GetAt(loop + loop2);
			}		
		sumarr.Add(sum);
 		}
	
	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
	//PlotDlg		*pdlg = &pwnd->plotdlg;
	//sumarr.Plot(&pdlg->m_plot1);

	if(_plotrec)
		{
		//_plotrec(sumarr.GetData(), sumarr.GetSize(), 0);
		//_plotrec(NULL, 0, 0);
		}

	// Set histeresis here
	int		change_tresh = 3, noised = 0, sigged = 0;
	int		in_useful = false;

	int		nlen = sumarr.GetSize();
	
	//AP2N("Histeresis on %d items\r\n", nlen);
	
	CIntArr *iarr = new CIntArr, *varr = new CIntArr;

	for(int loopn = 0; loopn < nlen; loopn++)
		{
		int val = sumarr.GetAt(loopn);

		//AP2N("%d   ", val);

		if(val > 200)
			{
			sigged++; 
			}
		else
			{	
			noised++; 
			}

		if(in_useful)
			{		
			for(int loopc = 0; loopc < FRAG_STEP; loopc++)
				{
				iarr->Add(piarr->GetAt(loopc + loopn * FRAG_STEP));
				varr->Add(pvarr->GetAt(loopc + loopn * FRAG_STEP));
				}
			
			// In signal, watch for noise switch
			if(noised > change_tresh)
				{
				//AP2N("Switched sig->noise loopn=%d\r\n", loopn);
				
				xAddSpectra(iarr, varr);
				iarr = new CIntArr; varr = new CIntArr;
				sigged = 0; in_useful = false;
				}
			}
		else
			{
			// In noise, watch for signal treshold
			if(sigged > change_tresh)
				{
				//AP2N("Switched noise->sig loopn=%d\r\n", loopn);	
				noised = 0;	in_useful = true;
				}
			}			
 		}

	// If leftovers, go recog or free
	if(iarr->GetSize() > change_tresh)
		xAddSpectra(iarr, varr);
	else
		{
		delete iarr; delete varr;
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int CRecog::xAddSpectra(CIntArr *piarr, CIntArr *pvarr)

{

	if(_plotrec)
		{
		//_plotrec(piarr->GetData(), piarr->GetSize(), 1);
		//_plotrec(NULL, 0, 1);
		}

	iarrarr.Add(piarr); varrarr.Add(pvarr);
	return 0;
}

//////////////////////////////////////////////////////////////////////////

void	CRecog::RecombineSpectra(CIntArr *picum, CIntArr *pvcum)

{
	int prevmax = 0;

	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	// Disabled it to one scan per uttering (for now)
	int loopx = 0;
	//for(int loopx = 0; loopx < iarrarr.GetSize(); loopx++)
		{		
		for(int loop = loopx; loop < iarrarr.GetSize(); loop++)
			{
			CIntArr *ival = (CIntArr *)iarrarr.GetAt(loop);
			CIntArr *vval = (CIntArr *)varrarr.GetAt(loop);

			picum->Append(*ival);	pvcum->Append(*vval);
			}

		// Convert it back to plottable, visualize it	

		int alenb = picum->GetSize();
		
		for(int loopdb = 0; loopdb < alenb; loopdb += FRAG_STEP)
			{
			CIntArr arr3; arr3.Fill(MAXFFTVAL + 1, 0);
				
			// Bend post process visualizer 
			for(int loop = 0; loop < FRAG_STEP; loop++)
				{
				int loopx = loopdb + loop, vol =  pvcum->GetAt(loopx);
				arr3.SetAt(picum->GetAt(loopx), vol);	
				}

			if(_spectrec)
				{
				_spectrec(arr3.GetData(), arr3.GetSize() );
				}
			}
		
		if(_spectrec)
			{
			// Send NULL for boundary 
			_spectrec(NULL, 0);
			}


#if 0
		// Pick the max from this batch
		int maxres = INT_MIN, maxidx = -1;
		int clen = contain.GetArr()->GetSize();
		for(int loopc = 0; loopc < clen; loopc++)
			{
			CContain::CResult *res = (CContain::CResult*)contain.GetArr()->GetAt(loopc);
			
			//AP2N("CContain::CResult %s %d\r\n", *res->name, res->val);
			
			if(maxres < res->val)
				{
				maxidx = loopc;
				maxres = res->val;
				}
 			}
#endif


#if 0
		if(maxidx >= 0)
			{
			CContain::CResult *xres = (CContain::CResult*)contain.GetArr()->GetAt(maxidx);

			//AP2N("CContain::CResult max result %s %d\r\n", *xres->name, xres->val);

			//if(xres->val)

			if(maxres > prevmax)
				{
				result += *xres->name; 

				//result += " ";
				//pwnd->m_pick.SetText(result);

				if(_strrec)
					{
					if(strict)
						{
						if(!bigmatch)
							result = "-";
						}
					_strrec(result, result.GetLength());
					}

				}
			prevmax = maxres;
			loopx += maxidx;
			}
#endif
		}

	xFreeArr(&iarrarr);	xFreeArr(&varrarr);
}
		
//////////////////////////////////////////////////////////////////////////

int CRecog::xCmpSpectra(CIntArr *piarr, CIntArr *pvarr, CContain *cout)

{
//	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
//	PlotDlg		*pdlg = &pwnd->plotdlg;

	CFrag *prevf = NULL;
	int prev = 0, ret = 0;

	CPtrArray *tmparr = &fcoll.fragarr;
	int len2f = tmparr->GetSize();

	if(len2f == 0)
		{
		if(_strrec)
			{
			CString tmp; tmp = "No Dictionary Loaded";
			_strrec(tmp, tmp.GetLength());
			}

		AP2N("CRecog::xCmpSpectra: empty global fragarr\r\n");
		return ret;
		}

	int alen = piarr->GetSize();

	if(alen == 0)
		{
		AP2N("CRecog::xCmpSpectra: empty piarr\r\n");
		return ret;
		}

	ASSERT(piarr->GetSize() == pvarr->GetSize());

	//AP2N("CRecog::xCmpSpectra len=%d\r\n", alen);

#if 0
	// Convert it back to plottable, visualize it
	int alenb = piarr->GetSize();
	
	for(int loopdb = 0; loopdb < alenb; loopdb += FRAG_STEP)
		{
		CIntArr arr3; arr3.Fill(MAXFFTVAL + 1, 0);
			
		// Bend post process visualizer 
		for(int loop = 0; loop < FRAG_STEP; loop++)
			{
			int loopx = loopdb + loop, vol =  pvarr->GetAt(loopx);
			arr3.SetAt(piarr->GetAt(loopx), vol);	
			}
		pwnd->visdlg.m_vis.AddIntArr(&arr3);
		}
	pwnd->visdlg.m_vis.AddMarker(); 
#endif

	// -------------------------------------------------------------------
	// Scan the body of the array

	support.MarkPerf();	
		
	CIntArr iarr; CPtrArray pfarr;

	// Loop to shift on the initial time line
	//for(int loop = 0; loop < alen; loop += 8)
	//for(int loop = 0; loop < 1; loop += 8)
	int loop = 0;
		{	
		//pwnd->m_log3.printf("Entered new cycle: loop=%d\r\n", loop);

		int rrr = xCmpSpectra2(loop, piarr, pvarr, &iarr, &pfarr);
		}

	int perf = support.QueryPerf();

	CString tmp; tmp.Format("Frag search in %d msec\r\n", perf);
	//AP2N(tmp);

	if(_perfrec)
		_perfrec(tmp, tmp.GetLength());

	// Find the result of the timeline scan
	int mxx, mvv; iarr.FindMax(&mxx, &mvv);	// Largest match
	if(mxx >= 0)
		{
		CFrag *frx = (CFrag*)pfarr.GetAt(mxx);

		//pwnd->m_log.printf("Timeline: %s\r\n", *frx->xname);

		//AP2N("xCmpSpectra %8d %s\r\n", mvv, *frx->xname);

		cout->Add(*frx->xname, mvv);
		}
				
	return ret;
}

//////////////////////////////////////////////////////////////////////////

int CRecog::xCmpSpectra2(int skip, CIntArr *piarr, CIntArr *pvarr, CIntArr *priarr, CPtrArray *prvarr)

{
	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;

	int ret = 0;

	CPtrArray *tmparr = &fcoll.fragarr;
	int len2f = tmparr->GetSize();
	if(len2f == 0)
		{
		AP2N("CRecog::xCmpSpectra2: empty global fragarr\r\n");
		return ret;
		}

	int alen = piarr->GetSize();

	if(alen == 0)
		{
		AP2N("CRecog::xCmpSpectra2: empty arrarr\r\n");
		return ret;
		}

	//AP2N("CRecog::xCmpSpectra2: skip, len=%d minlen=%d\r\n", skip, alen);
	
	CIntArr		lenarrv; CPtrArray	cmpxx;
		
	// -------------------------------------------------------------------
	// Scan the body of the array

	int loopx = alen;
	//for(int loopx = CFrag::minlen; loopx < CFrag::maxlen; loopx += 8)
		{
		CIntArr cmparrx, cmparry, cmparrz; 
		CPtrArray cmpx;
		
		CIntArr cmparr;

		// Just compare
		for(int loopw = 0; loopw < len2f; loopw++)
		//for(int loopw = 0; loopw < 2; loopw++)
			{
			CFrag *fr = ((CFrag *)tmparr->GetAt(loopw));	
			ASSERT(fr->magic == CFrag_Magic);

			int	diff2 = fr->CmpDeltas(skip, loopx, piarr, pvarr, 0);		
			
			cmparr.Add(diff2);	
			}

		//cmparr.DumpAll();

		int mval, mval2, midx, midx2, mval3, mval4, midx3, midx4; 
		cmparr.FindMax4(&midx, &mval, &midx2, &mval2, &midx3, &mval3, &midx4, &mval4);

		// If found max, and frag scan has hits
		//if(midx >= 0 && mval > 0) 
		if(midx >= 0) 
			{		
			CString fstr = "%16s %8d %3d %3d - ";

			CFrag *fr2  = (CFrag *)tmparr->GetAt(midx);

			CString tmp; tmp.Format(fstr, 
						*fr2->name, mval, fr2->GetUnitSize(), fr2->idx);
		
			if(midx2 >= 0 && mval2 > 0)
				{
				CFrag *fr3 = (CFrag *)tmparr->GetAt(midx2);
			
				CString tmp2; tmp2.Format(fstr, 
						*fr3->name, mval2, fr3->GetUnitSize(), 
							mval * 100 / mval2 - 100);

				tmp += "  "; tmp += tmp2;

				if(fr2->idx == fr3->idx)
					{
					bigmatch = 1;
					}
				}
		
			if(midx3 >= 0 && mval3 > 0)
				{
				CFrag *fr4 = (CFrag *)tmparr->GetAt(midx3);
			
				CString tmp2; tmp2.Format(fstr, 
						*fr4->name, mval3, fr4->GetUnitSize(),
							mval * 100 / mval3 - 100);

				tmp += "  "; tmp += tmp2;
				}	

#if 1
			if(midx4 >= 0 && mval4 > 0)
				{
				CFrag *fr5 = (CFrag *)tmparr->GetAt(midx4);
			
				//pwnd->m_log3.printf(fstr, 
				//		*fr5->name, mval4, fr5->GetUnitSize(), 
				//						(100 * (mval - mval4)  / max(mval4, 1)));				
				}	

			if(_fragrec)
				_fragrec(tmp, tmp.GetLength());		
	
#endif
			cmparrx.Add(mval);  cmpx.Add(fr2); 
			//pwnd->m_log3.printf("\r\n");

			resarr.AddToVal(fr2->idx, mval);
			}

		//pwnd->m_log3.printf("---\r\n");
						
		int mx, mv;
		cmparrx.FindMax(&mx, &mv);			// Largest match
		if(mx >= 0)
			{
			CFrag *frx = (CFrag*) cmpx.GetAt(mx);
				
			//AP2N("largest match in loopx group %d loop=%d %s %d\r\n", loopx,
			//				cmparrz.GetAt(mx), *frx->xname, mv);
			// Skip ahead
			//result +=  *frx->xname; result += " ";

			// Let it flick'a
			//pwnd->m_pick.SetText(result);

			//pwnd->m_log.printf("%s\r\n", *frx->xname);
	
			//AP2N("%8d %s\r\n", mv, *frx->xname);

			lenarrv.Add(mval); cmpxx.Add(frx);
			}

		} // loopx
	
	// Find the result of the size scan
	int mxx, mvv; lenarrv.FindMax(&mxx, &mvv);	// Largest match
	if(mxx >= 0)
		{
		CFrag *frx = (CFrag*)cmpxx.GetAt(mxx);

		//pwnd->m_log.printf("Cummulative: %s\r\n", *frx->xname);

		//AP2N("xCmpSpectra2 %8d %s\r\n", mvv, *frx->xname);

		priarr->Add(mvv); 	prvarr->Add(frx);

		ret = frx->GetUnitSize();
		}
	
	//resarr.DumpAll("resarr\r\n");

	int xxx, vvv; resarr.FindMax(&xxx, &vvv);
	//AP2N("Resarr idxmax = %d, mval=%d ", xxx, vvv);

	// Get frag from idx
	for(int loopfx = 0; loopfx < len2f; loopfx++)
		{
		CFrag *fr = ((CFrag *)tmparr->GetAt(loopfx));	
		if(fr->idx == xxx)
			{
			//AP2N("'%s'", *fr->xname);
			break;
			}
		}
	//AP2N("\r\n");

	resarr.RemoveAll();

	return ret;
}

//////////////////////////////////////////////////////////////////////////

void CRecog::PowerAnal(CIntArr *piarr, int *pss, int *pee)

{
	int alen = piarr->GetSize();
	
	int midx, mval; piarr->FindMax(&midx, &mval);
	int tresh = mval / 10;
	
	//AP2N("PowerAnal midx=%d (of %d) mval=%d\r\n", midx, alen, mval);

	// Go to left
	for(int loopx = midx; loopx >= 0; loopx--)
		{
		if(piarr->GetAt(loopx) < tresh)
			break;
 		}
	// Go to right
	for(int loopxx = midx; loopxx < alen - 1; loopxx++)
		{
		if(piarr->GetAt(loopxx) < tresh)
			break;
 		}

	// Limit to boundaries
	loopx = MAX(loopx, 0); loopxx = MIN(loopxx, alen - 1);

	// Output results
	*pss = loopx;	*pee = loopxx;
}

//////////////////////////////////////////////////////////////////////////

void CRecog::PowerSplit(char *buff, int len, CPtrArray *parr, CIntArr *iarr)

{
	// Get power array
	CIntArr  marr; 	Powers(buff, len, &marr);
	int alen = marr.GetSize();

	if(alen == 0)
		return;

	if(_plotrec)
		{
		_plotrec(marr.GetData(), marr.GetSize(), 0);
		_plotrec(NULL, 0, 0);
		}	

	int ss = 0, ee = alen, ss2 = 0, ee2 = alen;
	int ss3 = 0, ee3 = alen;

	// Get the middle one
	PowerAnal(&marr, &ss2, &ee2);
	
	// Before
	if(ss2 > 0)
		{
		CIntArr larr; 
		for(int loopl = 0; loopl < ss2; loopl++)
			larr.Add(marr.GetAt(loopl));
 		
		PowerAnal(&larr, &ss, &ee);
		}

	// After
	if(ee2 < alen)
		{
		CIntArr rarr; 
		for(int loopr = ee2; loopr < alen; loopr++)
			rarr.Add(marr.GetAt(loopr));
 		
		PowerAnal(&rarr, &ss3, &ee3);

		// Adjust for original offset
		ss3 += ee2; ee3 += ee2;
		}

	// Visualize
	if(_plotrec)
		{
		_plotrec(marr.GetData() + ss, ee - ss, 1);
		_plotrec(NULL, 0, 1);

		_plotrec(marr.GetData() + ss2, ee2 - ss2, 1);
		_plotrec(NULL, 0, 1);
		
		_plotrec(marr.GetData() + ss3, ee3 - ss3, 1);
		_plotrec(NULL, 0, 1);
		}

	// Calc splits into wave
	ss  *= acnt * 2; ee  *= acnt * 2;	ss2 *= acnt * 2; ee2 *= acnt * 2;
	ss3 *= acnt * 2; ee3 *= acnt * 2;
	int lenx  = ee - ss, lenx2 = ee2 - ss2, lenx3 = ee3 - ss3;
	
	// Output split params:
	iarr->Add(lenx); iarr->Add(lenx2); iarr->Add(lenx3);
	parr->Add(buff + ss);parr->Add(buff + ss2); parr->Add(buff + ss3);
}

//////////////////////////////////////////////////////////////////////////
// Convert to amplitude array

void CRecog::Powers(char *buff, int len, CIntArr *piarr)

{
	int len2 = len / sizeof(short);	
	short *pptr = (short*)buff;

	//AP2N("void CRecog::PowerAnal(char *buff=%p, int len2=%d)\r\n", pptr, len2);
	//short old = 0, old2 = 0;
	
	for(int loop = 0; loop < len2; loop++)
		{
		int avg = 0;

		for(int loop3 = 0; loop3 < acnt; loop3++)
			{
			if(loop + loop3 > len2)
				break;

			short sval = *pptr++; sval = ABS(sval);
			avg += sval;
			}

		loop += loop3;
		avg /= acnt;
		piarr->Add(avg);
		}
}

//////////////////////////////////////////////////////////////////////////
// See if buffer contains any signal

int CRecog::IsSignal(char *buff, int len)

{
	short *buff2 = (short*)buff;

	int sig = 0, step = 1, len2 = len / sizeof(short);
	for(int loop = 0; loop < len2; loop += step)
		{
		if(abs(*buff2) > noiselevel)
			sig++;

		buff2 += step;
		}
	return sig;
}

//////////////////////////////////////////////////////////////////////////

int CRecog::PowerCombine(CPtrArray &sparr, CIntArr &siarr)

{
	ASSERT(sparr.GetSize() == 3); ASSERT(siarr.GetSize() == 3);

	int newlen = siarr[0] + siarr[1] + siarr[2];
		
	// Allocate
	lock.Lock();
	if(lastbuff)
		free(lastbuff);

	lastbuff = (char*) malloc(newlen); ASSERT(lastbuff);
	lock.Unlock();

	// Re - assemble wave - if there is some signal

	int sig  = IsSignal((char*)sparr[0], siarr[0]);
	int sig2 = IsSignal((char*)sparr[1], siarr[1]);
	int sig3 = IsSignal((char*)sparr[2], siarr[2]);

	AP2N("CRecog::Emit sig=%d sig2=%d sig3=%d\r\n", sig, sig2, sig3);

	char *cpbuff = lastbuff;

	if(sig > 1)
		memcpy(cpbuff, sparr[0], siarr[0]), cpbuff += siarr[0];
		
	if(sig2 > 1)
		memcpy(cpbuff, sparr[1], siarr[1]), cpbuff += siarr[1];

	if(sig3 > 1)
		memcpy(cpbuff, sparr[2], siarr[2]), cpbuff += siarr[2];

	lastbuflen = cpbuff - lastbuff;

	return 0;
}