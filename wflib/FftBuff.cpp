
/* =====[ FftBuff1.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the FftBuff1.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"

//#include "wavfrag.h"
#include "FftBuff.h"
#include "mxpad.h"
#include "intArr.h"

// Removed dependency .. needed only for research
//#include "wavfragDlg.h"

#undef P2N

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////////

CFftBuff::CFftBuff()

{
	// Optimized for the amount of delivered information vs. clarity

	//fft = new CFft(4096);	
	fft = new CFft(2048);	
	//fft = new CFft(1024);	
	//fft = new CFft(512);	
	//fft = new CFft(256);
	//fft = new CFft(128);
	//fft = new CFft(64);

	ASSERT(fft);

	//NoiseLevel = 50;
	fftpts = fft->Points();
}


CFftBuff::~CFftBuff()

{
	// Theoretically this cannot be NULL, but it is good practice ...
	if(fft)
		delete fft;
}

//////////////////////////////////////////////////////////////////////////
// Main entry point, will deliver an array of arrays on transformed 
// spectra
//

int		CFftBuff::Transform(short *buff, int len, CPtrArray *parr, CPtrArray *parr2)

{
	int len2 = len; // / sizeof(short);
	
	int		step = fft->Points() / 2;
	
	//AP2N("CFftBuff::Transform %p len=%d step=%d\r\n", buff, len, step);

	short	*data = buff;
	short	*endd = buff + (len2 - step);  // Miss the last one
	
	while(TRUE)
		{
		if(data > endd)
			break;

		CIntArr *tmp = new CIntArr; ASSERT(tmp);
		CIntArr *ph = new CIntArr; ASSERT(ph);

		xTransform(data, step, tmp, ph);

		// Tried a little overlap
		data += 3 * step / 4;
		//data += 5 * step / 6;
		//data += step / 2;
		//data += step;
		
		parr->Add(tmp);	 parr2->Add(ph);	
		}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int		CFftBuff::xTransform(short *buff, int len, CIntArr *tmp, CIntArr *ph)

{
	int len2 = len; /// sizeof(short);

	std::vector<int> vec;
 	
	vec.resize(len);
	for(int loop = 0; loop < len; loop++)
		{
		short val = *buff++;
		//vec.push_back((int)val);
		vec[loop] = val;
		}

#if 1
	// Ramp up / down
	int ramp = len / 10;
	//AP2N("len=%d   ", len);
	for(int loopr = 0; loopr < ramp; loopr++)
		{
		short val = vec[loopr];
		vec[loopr] = (1./ramp) * val *loopr;
		}

	for(loopr = 0; loopr < ramp; loopr++)
		{
		int idx = (len - 1) - loopr;
		short val = vec[idx];
		vec[idx] = (1./ramp) * val *  loopr;
		}
#endif

#if 1
	// Normalize this buffer in place
	int maxx = 0;
	for(int loopn = 0; loopn < len; loopn++)
		{
		short val = abs(vec[loopn]);
		
		if(val > maxx)
			maxx = val;
		}

	// Calc scaling factor
	double factor = (double)SHRT_MAX / maxx;

	if(factor < 10)
		{
		for(int loopn2 = 0; loopn2 < len; loopn2++)
			{
			short val = vec[loopn2];

			double dval = factor * val;		

			// Clip it, so no artifacts, just a clip
			//if(dval > SHRT_MAX) dval  = SHRT_MAX;
			//if(dval < -SHRT_MAX) dval = -SHRT_MAX;

			vec[loopn2] = short(dval);
			}
		}

	//AP2N("%d  ", maxx);
#endif

	fft->Transform(vec);

	// 44000 hz ... but sound goes to 10-12k at best
	int  pts = GetDepth() / 2;		

	//AP2N("fft points %d\r\n", pts);

	for(loop = 0; loop < pts; loop++)
		{ 
		// Different ways to extract data, freq proportional works best
	
		//int val = fft->GetIntensity(loop) / 512;
		//int val = sqrt(fft->GetIntensity(loop) * loop) / 4;
		//int val = (fft->GetIntensity(loop) / 500);	
		//int val = (fft->GetIntensity(loop) * loop) / (20 * pts);
		
		int val = (fft->GetIntensity(loop) * loop) / (10 * pts);
		tmp->Add(val);
		
		// Add phase info as well
		int phval = fft->GetPhase(loop);
		ph->Add(phval);		
		}	

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// This is the simple (unrolled) version of getpeaks

//DEL void	CFftBuff::GetDominant(CPtrArray *parr, CIntArr *ouarr, CIntArr *volarr)
//DEL 
//DEL {
//DEL 	//CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
//DEL 	//PlotDlg		*pdlg = &pwnd->plotdlg;
//DEL 
//DEL 	for(int loopd2 = 0; loopd2 < parr->GetSize(); loopd2 += 1)
//DEL 		{
//DEL 		CIntArr *val = (CIntArr*)parr->GetAt(loopd2);
//DEL 	
//DEL 		// Locate peaks
//DEL 		CIntArr xx, vv, ss; val->TurnArr(&xx, &vv, true); 
//DEL 
//DEL 		//CIntArr	xx2, vv2; xx.ConvDist(&vv, &xx2, &vv2);
//DEL 		//xx2.Plot(&pdlg->m_plot1); xx2.Plot(&pdlg->m_plot2);
//DEL 		//pdlg->m_plot1.AddMarker(); pdlg->m_plot2.AddMarker();
//DEL 
//DEL 		//vv.Plot(&pdlg->m_plot3); vv2.Plot(&pdlg->m_plot4);
//DEL 		//pdlg->m_plot3.AddMarker(); pdlg->m_plot4.AddMarker();
//DEL 
//DEL 		// Order it by max amplitude, grab first N, zero extend if needed			
//DEL 		vv.Sort(&ss); 
//DEL 
//DEL 		CIntArr tmpidx, tmpvol, tmpss;
//DEL 
//DEL 		// Push them into the mix
//DEL 		for(int loop = 0; loop < FRAG_STEP; loop++)
//DEL 			{
//DEL 			int vidx = 0, vol = 0;
//DEL 
//DEL 			if(loop < ss.GetSize())
//DEL 				{
//DEL 				int idx  = ss.GetAt(loop);
//DEL 				vidx = xx.GetAt(idx); 	vol  = vv.GetAt(idx); 
//DEL 
//DEL 				// Silence weak ones
//DEL 				if(vol < 50)
//DEL 					{	
//DEL 					vidx = 0;	vol = 0;
//DEL 					}
//DEL 				}
//DEL 			
//DEL 			// Output it  (no sort)
//DEL 			//ouarr->Add(vidx); 	volarr->Add(vol);				
//DEL 			
//DEL 			// Output to temp for sorting
//DEL 			tmpidx.Add(vidx); 	tmpvol.Add(vol);				
//DEL 			}
//DEL 
//DEL 		
//DEL 		// Filter out noise from the output
//DEL 		// Let the nose be part of the analisys, ...
//DEL 		// NEW ... we deal with it in the recognition
//DEL 
//DEL 		//if(sum > NoiseLevel)
//DEL 		//	{
//DEL 			// Sort them by freq
//DEL 			tmpidx.Sort(&tmpss, true);
//DEL 
//DEL 			for(int loopx = 0; loopx < tmpidx.GetSize(); loopx++)
//DEL 				{
//DEL 				int zidx  = tmpss.GetAt(loopx);
//DEL 				int sidx = tmpidx.GetAt(zidx), svol = tmpvol.GetAt(zidx); 
//DEL 
//DEL 				// Output it
//DEL 				ouarr->Add(sidx); volarr->Add(svol);				
//DEL 				}
//DEL 		//	}		
//DEL 		}		
//DEL }

//
// This define (QUAD_DEPTH) determines how many spectral components 
/// to deliver into the final array.
//
// Best results at two or three, shows that they are the major 
// information carriers of the spectra. One delivers too litle, 
// four delivers too much. This is also appearent from the plots,
// they look?? too simple on one, and look too complex on four
//
//  Additionally, looking at the waveform of 'one' it is appearent 
//  that the time line consists three major frequency components
//


//define SORTED				// Define this for ordered output

//////////////////////////////////////////////////////////////////////////
// Mark top peaks, Output val/idx quads.
// Sort it by power, pick top QUAD_DEPTH, sort it by frequency, encode it 
// into quads
//
// The sorting can be disabled for testing, but it makes for a fully 
// sprinkled #ifdef code. Sorry. Testing is done by plotting the 
// val/freq in the higher level routine
//

//DEL void	CFftBuff::GetPeaks(CPtrArray *parr, CPtrArray *ouarr)
//DEL 
//DEL {
//DEL 	//////////////////////////////////////////////////////////////////////
//DEL 
//DEL 	for(int loopd2 = 0; loopd2 < parr->GetSize(); loopd2 += 1)
//DEL 		{
//DEL 		CIntArr *val = (CIntArr*)parr->GetAt(loopd2);
//DEL 	
//DEL 		// Locate peaks
//DEL 		CIntArr xx, vv, ss;	val->TurnArr(&xx, &vv, 1); 
//DEL 
//DEL 		// Order it fby max amplitude
//DEL 		vv.Sort(&ss);
//DEL 
//DEL 		CIntArr peaks, vpeaks, *quads = new CIntArr;
//DEL 
//DEL 		for(int loop = 0; loop < min(QUAD_DEPTH, ss.GetSize()); loop++)
//DEL 			{
//DEL 			int idx = ss.GetAt(loop);
//DEL 
//DEL 			// Test unsorted
//DEL 			//int idx = loop;
//DEL 
//DEL 			int vidx = xx.GetAt(idx),  vval = vv.GetAt(idx);
//DEL 
//DEL 			// Output to temporary
//DEL 			peaks.Add(vidx); vpeaks.Add(vval);
//DEL 			}
//DEL 
//DEL 		//////////////////////////////////////////////////////////////////
//DEL 		// Correct quads to be QUAD_DEPTH sized
//DEL 
//DEL 		int alenq = peaks.GetSize();
//DEL 		for(int loopq = alenq; loopq < QUAD_DEPTH; loopq++)
//DEL 			peaks.Add(0), vpeaks.Add(0);
//DEL 
//DEL 		//ASSERT(peaks.GetSize() == QUAD_DEPTH);
//DEL  		//ASSERT(peaks.GetSize() == vpeaks.GetSize());
//DEL 
//DEL 		//////////////////////////////////////////////////////////////////
//DEL 		// Sort it by volume
//DEL 
//DEL 		CIntArr peaks2, peaks3, vtmp, ftmp;	
//DEL 
//DEL #if 0
//DEL 		vpeaks.Sort(&peaks2, false);
//DEL 		
//DEL 		int alenp = peaks.GetSize();
//DEL 		for(int loopp = 0; loopp < alenp; loopp++)
//DEL 			{
//DEL 			int sidx = peaks.GetAt(peaks2.GetAt(loopp));
//DEL 			int sval = vpeaks.GetAt(peaks2.GetAt(loopp));
//DEL 			
//DEL 			// Test unsorted
//DEL 			//int sidx = peaks.GetAt(loopp);
//DEL 			//int sval = vpeaks.GetAt(loopp);
//DEL 			
//DEL 			ftmp.Add(sidx); vtmp.Add(sval);
//DEL 			}
//DEL #endif
//DEL 
//DEL 		//////////////////////////////////////////////////////////////////
//DEL 		// Sort it by frequency 
//DEL 
//DEL 		//ftmp.Sort(&peaks3, true);
//DEL 		peaks.Sort(&peaks3, true);
//DEL 		
//DEL 		//int alenf = ftmp.GetSize();
//DEL 		int alenf = peaks.GetSize();
//DEL 		for(int loopf = 0; loopf < alenf; loopf++)
//DEL 			{
//DEL 			//int sidx = ftmp.GetAt(peaks3.GetAt(loopf));
//DEL 			//int sval = vtmp.GetAt(peaks3.GetAt(loopf));
//DEL 
//DEL 			int sidx = peaks.GetAt(peaks3.GetAt(loopf));
//DEL 			int sval = vpeaks.GetAt(peaks3.GetAt(loopf));
//DEL 
//DEL 			// Test unsorted
//DEL 			//int sidx = ftmp.GetAt(loopf);
//DEL 			//int sval = vtmp.GetAt(loopf);
//DEL 
//DEL 			quads->Add(sidx | sval << 16);			
//DEL 			}
//DEL 
//DEL 		// Output to result
//DEL 		ouarr->Add(quads);
//DEL 		}
//DEL }

//////////////////////////////////////////////////////////////////////////
// Convert spectral peaks to deltas
//
// Version 1:  delta of consecutive spectras
// Version 1a: delta of secondary consecutive spectras
// Version 2:  change of deltas of consecutive spectras
// Version 3:  ratio of the first and second order spectra  
// Version 4:  frequency separation  (at 25 which is (44100 / 256) ~ 4k
//				low:	ratio of the first and second order spectra  
//				high:	 mean of the first and second order spectra 
//						
//				(Remember log sub => multiply)
//
// On sounds containing low frequency components only, V3 is the best
// On sounds containing full spectra v4 is appropriate
//
// Commented entries are dead reseach, left in for documenting ...
//  ... previous tries.



//DEL void	CFftBuff::Deltas(CIntArr *iarr, CIntArr *varr, CIntArr *deltas, CIntArr *deltas2)
//DEL 
//DEL {
//DEL 	CWavfragDlg *pwnd = (CWavfragDlg*)AfxGetApp()->m_pMainWnd;
//DEL 	PlotDlg		*pdlg = &pwnd->plotdlg;
//DEL 	
//DEL 	//int prev0 = 0,	prev1 = 0,	prev2 = 0;
//DEL 	//int prev3 = 0,	prev4 = 0,	prev5 = 0;
//DEL 
//DEL 	int len = iarr->GetSize();
//DEL 	
//DEL 	// Create deltas
//DEL 	for(int loopd = 0; loopd < len - FRAG_STEP; loopd += FRAG_STEP)
//DEL 		{
//DEL 		int val0f = iarr->GetAt(loopd);
//DEL 		int val1f = iarr->GetAt(loopd + 1);
//DEL 		int val2f = iarr->GetAt(loopd + 2);
//DEL 		int val3f = iarr->GetAt(loopd + 3);
//DEL 		int val4f = iarr->GetAt(loopd + 4);
//DEL 		int val5f = iarr->GetAt(loopd + 5);
//DEL 		
//DEL 		// Get frequency progression:
//DEL 		//int diff = val0f - prev0; 				
//DEL 		//int diff2 = val1f - prev1; 				
//DEL 		
//DEL 		//diff = LIM(-5, 5, diff);		// limit jump
//DEL 		//if(diff < 0) diff = -100;		// clip it to extreme
//DEL 		//else if (diff > 0) diff = 100;
//DEL 
//DEL 		//if(diff != pdiff)				// delta of delta
//DEL 			//deltas->Add(diff);
//DEL 
//DEL 		// The dominant is always the lower, no need to sort it
//DEL 		//int f1 = min(val0f, val1f), f2 = max(val0f, val1f);
//DEL 		//int diff3 = f2 - f1;
//DEL 
//DEL 		// Ended up to be a one liner  (obsolete, ratios worked better)
//DEL 		//int diff3 = val0f - val1f;			
//DEL 
//DEL 		int diff1 = 0, diff2 = 0, diff3 = 0;
//DEL 		int	diff4 = 0, diff5 = 0, diff6 = 0;
//DEL 
//DEL 		// Different variations of 1st and 2nd order ratios
//DEL 		//diff3 = val1f / max(1, val0f);			// good no.1
//DEL 		//diff3 = val0f - val1f;					// good no.2
//DEL 
//DEL 		// The harmonics calculate better from the fundamental (duh!)
//DEL 		//diff3 =  val3f / max(1, val0f);			// good no.2			
//DEL 		//diff3 = 100 * (val0f - prev0);			// no good no.4
//DEL 		//diff3 = 100 * (val1f - prev1);			// no good no.5
//DEL 		//diff3 = val0f;							// no good no.6
//DEL 	
//DEL 		// Just like the scientific theory suggests, the harmonic ratio		
//DEL 		// of the first and secord order dominant spectrum
//DEL 		// We clip the division to a straight thru if no fundmental
//DEL 
//DEL 		//diff1 =  val1f / max(1, val0f);				// good no.1
//DEL 		diff1 =  1 * val0f;
//DEL 		deltas->Add(diff1);
//DEL 		
//DEL 		//diff2 =  val2f / max(1, val1f);				// good no.2
//DEL 		diff2 =  1 * val1f;
//DEL 		deltas->Add(diff2);				
//DEL 
//DEL 		//diff3 =  val3f / max(1, val1f);				// good no.3
//DEL 		diff3 =  1 * val2f;			
//DEL 		deltas->Add(diff3);						
//DEL 		
//DEL 		//diff4 =  val4f / max(1, val1f);				// good no.4
//DEL 		diff4 = 1 * val3f;
//DEL 		deltas->Add(diff4);						
//DEL 		
//DEL 		//diff5 =  val5f / max(1, val1f);				// good no.5
//DEL 		diff5 = 1 * val4f;
//DEL 		deltas->Add(diff5);						
//DEL 		
//DEL 		diff6 = 1 * val5f;
//DEL 		deltas->Add(diff6);						
//DEL 		
//DEL 		//pdlg->m_plot1.AddLine(diff1);
//DEL 		//pdlg->m_plot2.AddLine(diff2);
//DEL 		//pdlg->m_plot3.AddLine(diff3);
//DEL 		//pdlg->m_plot4.AddLine(diff4);
//DEL 		//pdlg->m_plot5.AddLine(diff5);
//DEL 		//pdlg->m_plot6.AddLine(diff6);
//DEL 
//DEL 		deltas2->Add(1 * varr->GetAt(loopd+0));		
//DEL 		deltas2->Add(1 * varr->GetAt(loopd+1));		
//DEL 		deltas2->Add(1 * varr->GetAt(loopd+2));		
//DEL 		deltas2->Add(1 * varr->GetAt(loopd+3));		
//DEL 		deltas2->Add(1 * varr->GetAt(loopd+4));		
//DEL 		deltas2->Add(1 * varr->GetAt(loopd+5));	
//DEL 		
//DEL 		//pdlg->m_plot1.AddLine(10 * varr->GetAt(loopd+0));
//DEL 		//pdlg->m_plot2.AddLine(10 * varr->GetAt(loopd+1));
//DEL 		//pdlg->m_plot3.AddLine(10 * varr->GetAt(loopd+2));
//DEL 		//pdlg->m_plot4.AddLine(10 * varr->GetAt(loopd+3));
//DEL 		//pdlg->m_plot5.AddLine(10 * varr->GetAt(loopd+4));
//DEL 		//pdlg->m_plot6.AddLine(10 * varr->GetAt(loopd+5));
//DEL 		}
//DEL }


