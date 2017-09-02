
/* =====[ FftBuff.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the FftBuff.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/7/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "FftBuff.h"
#include "mxpad.h"
#include "intArr.h"
//#include "play.h"

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
	// Optimized for the amount of delivered information

	//fft = new CFft(512, 44100);	
	//fft = new CFft(256, 44100);
	fft = new CFft(128, 44100);
	//fft = new CFft(64, 44100);
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

int		CFftBuff::Transform(short *buff, int len, CPtrArray *parr)

{
	//AP2N("CFftBuff::Transform %p len=%d\r\n", buff, len);
	
	int len2 = len; // / sizeof(short);
	
	CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd; 	

	int		step = fft->Points();

	short	*data = buff;
	short	*endd = buff + (len2 - step);  // Miss the last one
	
	while(TRUE)
		{
		if(data > endd)
			break;

		Transform2(data, step, parr);

		data += step;
		}

#if 0
	int alen = arr->GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		pwnd->visdlg.m_vis.AddIntArr((CIntArr*)arr->GetAt(loop));	
 		}
	pwnd->visdlg.m_vis.AddMarker();
#endif

	//GetPeaks(parr);

	return 0;
}

//////////////////////////////////////////////////////////////////////////

int		CFftBuff::Transform2(short *buff, int len, CPtrArray *arr)

{
	int len2 = len; /// sizeof(short);

	std::vector<int> vec;

	//CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;
	//pwnd->plotdlg.m_vis.AddBuff(buff, len);	
 	
	vec.resize(len);
	for(int loop = 0; loop < len; loop++)
		{
		short val = *buff++;
		//vec.push_back((int)val);
		vec[loop] = val;
		}

#if 1
	// Ramp up / down
	int ramp = 20;
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

	fft->Transform(vec);

	CIntArr *tmp = new CIntArr; ASSERT(tmp);

	int  pts = fft->Points() / 2;
	for(loop = 0; loop < pts; loop++)
		{ 
		//int val = fft->GetIntensity(loop) / 512;
		//int val = sqrt(fft->GetIntensity(loop) * loop) / 4;

		int val = (fft->GetIntensity(loop) * loop) / 1500;
		
		//val = min(val, 255);

		//if(val > 100)
		//	val = 255;
		//else
		//	val = 0;

		//tmp->SetAt(loop, fft.GetIntensity(loop));
		//tmp->SetAtGrow(loop, val);

		//tmp->Add(val);
		//if(loop < 180)
	
		if(loop < 60 && loop >= 0)
			tmp->Add(val);
		else
			tmp->Add(0);
		}	

	//tmp->Smooth(1);
	//tmp->NormArrHeight(255, 3);
	
	// Kill lower half
	//int alen2 = tmp->GetSize();
	//for(int loop2 = 0; loop2 < alen2; loop2++)
	//	{
	//	int val = tmp->GetAt(loop2);
	//	if(val < 50)
	//		tmp->SetAt(loop2, 0);
 	//	}

	arr->Add(tmp);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// This is the simple version of getpeaks

void	CFftBuff::GetDominant(CPtrArray *parr, CIntArr *ouarr, CIntArr *volarr)

{
	CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;
	
	int prev = 0;
	//////////////////////////////////////////////////////////////////////

	for(int loopd2 = 0; loopd2 < parr->GetSize(); loopd2 += 1)
		{
		int curr = 0;
		CIntArr *val = (CIntArr*)parr->GetAt(loopd2);
	
		// Locate peaks
		CIntArr xx, vv, ss;	val->TurnArr(&xx, &vv, 1); 
		
		if(vv.GetSize() > 0)
			{
			// Order it by max amplitude			
			//vv.Sort(&ss); int vidx = xx.GetAt(ss.GetAt(0)); 
			//ouarr->Add(vidx);					// Output it
			
			// Order it by max amplitude, single scan version			
			int xxx, vvv, xxx2, vvv2, xxx3, vvv3; 
			vv.FindMax3(&xxx, &vvv, &xxx2, &vvv2, &xxx3, &vvv3);				

			curr = xxx;

			// Try assign close to old value
#if 0
			if(ABS(xxx - prev) > ABS(xxx2 - prev))
				{
				curr = xxx2;
				}
			if(ABS(xxx2 - prev) > ABS(xxx3 - prev))
				{
				curr = xxx3;
				}			
#endif
			ouarr->Add(xx.GetAt(curr));	
			volarr->Add(vv.GetAt(curr));
			}
		else
			{
			//AP2N("CFftBuff::GetDominant nul turns idx=%d\r\n", loopd2);
			ouarr->Add(0);
			volarr->Add(0);
			}
		prev = curr;
		}

	if(pwnd->stablized)
		{
		//ouarr->Plot(pwnd->plotarr[0]);	
		//pwnd->plotarr[0]->AddMarker();		
		}

	// Bad Idea
	//ouarr->Smooth(2);
}

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

#define QUAD_DEPTH 2		// New optimum, sorted -> dominance -> freq

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

void	CFftBuff::GetPeaks(CPtrArray *parr, CPtrArray *ouarr)

{
	CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;
	
	//////////////////////////////////////////////////////////////////////

	for(int loopd2 = 0; loopd2 < parr->GetSize(); loopd2 += 1)
		{
		CIntArr *val = (CIntArr*)parr->GetAt(loopd2);
	
		// Locate peaks
		CIntArr xx, vv, ss;	val->TurnArr(&xx, &vv, 1); 

		// Order it fby max amplitude
		vv.Sort(&ss);

		CIntArr peaks, vpeaks, *quads = new CIntArr;

		for(int loop = 0; loop < min(QUAD_DEPTH, ss.GetSize()); loop++)
			{
			int idx = ss.GetAt(loop);

			// Test unsorted
			//int idx = loop;

			int vidx = xx.GetAt(idx),  vval = vv.GetAt(idx);

			// Output to temporary
			peaks.Add(vidx); vpeaks.Add(vval);
			}

		//////////////////////////////////////////////////////////////////
		// Correct quads to be QUAD_DEPTH sized

		int alenq = peaks.GetSize();
		for(int loopq = alenq; loopq < QUAD_DEPTH; loopq++)
			peaks.Add(0), vpeaks.Add(0);

		//ASSERT(peaks.GetSize() == QUAD_DEPTH);
 		//ASSERT(peaks.GetSize() == vpeaks.GetSize());

		//////////////////////////////////////////////////////////////////
		// Sort it by volume

		CIntArr peaks2, peaks3, vtmp, ftmp;	

#if 0
		vpeaks.Sort(&peaks2, false);
		
		int alenp = peaks.GetSize();
		for(int loopp = 0; loopp < alenp; loopp++)
			{
			int sidx = peaks.GetAt(peaks2.GetAt(loopp));
			int sval = vpeaks.GetAt(peaks2.GetAt(loopp));
			
			// Test unsorted
			//int sidx = peaks.GetAt(loopp);
			//int sval = vpeaks.GetAt(loopp);
			
			ftmp.Add(sidx); vtmp.Add(sval);
			}
#endif

		//////////////////////////////////////////////////////////////////
		// Sort it by frequency 

		//ftmp.Sort(&peaks3, true);
		peaks.Sort(&peaks3, true);
		
		//int alenf = ftmp.GetSize();
		int alenf = peaks.GetSize();
		for(int loopf = 0; loopf < alenf; loopf++)
			{
			//int sidx = ftmp.GetAt(peaks3.GetAt(loopf));
			//int sval = vtmp.GetAt(peaks3.GetAt(loopf));

			int sidx = peaks.GetAt(peaks3.GetAt(loopf));
			int sval = vpeaks.GetAt(peaks3.GetAt(loopf));

			// Test unsorted
			//int sidx = ftmp.GetAt(loopf);
			//int sval = vtmp.GetAt(loopf);

			quads->Add(sidx | sval << 16);			
			}

		// Output to result
		ouarr->Add(quads);
		}
}

//////////////////////////////////////////////////////////////////////////
// Make the volume component uniform, in place. 
// Default to 255 (max volume)

void	CFftBuff::Flatten(CPtrArray *parr, int vol)

{
	int alen2 = parr->GetSize();

	for(int loopd2 = 0; loopd2 < alen2; loopd2 += 1)
		{
		CIntArr *val = (CIntArr*)parr->GetAt(loopd2);

		int alen3 = val->GetSize();

		for(int loopd3 = 0; loopd3 < alen3; loopd3 += 1)
			{
			int iii = val->GetAt(loopd3);

			val->SetAt(loopd3, (iii & 0xffff) | (vol << 16) );
			}
		}
}

//////////////////////////////////////////////////////////////////////////
//
// Unroll an array of pointers -> intarr(s) to a flat intarr
// This is a speed hack for the analisys  (will be chars soon)
//

void	CFftBuff::Unroll(CPtrArray *parr, CIntArr *out)

{
	int alen2 = parr->GetSize();

	for(int loopd2 = 0; loopd2 < alen2; loopd2 += 1)
		{
		CIntArr *val = (CIntArr*)parr->GetAt(loopd2);

		int alen3 = val->GetSize();
		for(int loopd3 = 0; loopd3 < alen3; loopd3 += 1)
			{
			out->Add(val->GetAt(loopd3));
			}
		}
}

//////////////////////////////////////////////////////////////////////////

void CFftBuff::ScaleDown(CPtrArray *parr)

{
	CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;
	
	// Mark top peaks
	for(int loopd2 = 0; loopd2 < parr->GetSize(); loopd2 += 1)
		{
		CIntArr nnn, *val = (CIntArr*)parr->GetAt(loopd2);

		nnn.SetSize(val->GetSize());

		int alen = val->GetSize();
		for(int loop = 0; loop < alen; loop++)
			{
			int intval = val->GetAt(loop);
			nnn.SetAt(70 * loop / 100, intval);
 			}
		val->Copy(nnn);
		}
}

//////////////////////////////////////////////////////////////////////////

void CFftBuff::ScaleUp(CPtrArray *parr, CPtrArray *outarr)

{
	CPlay *pwnd = (CPlay*)AfxGetApp()->m_pMainWnd;
	
	// Mark top peaks
	for(int loopd2 = 0; loopd2 < parr->GetSize(); loopd2 += 1)
		{
		CIntArr *narr = new CIntArr; 
		CIntArr	*val = (CIntArr*)parr->GetAt(loopd2);

		narr->SetSize(val->GetSize());

		int alen = val->GetSize();
		for(int loop = 0; loop < alen; loop++)
			{
			int intval = val->GetAt(loop);

			// Loose the overflows
			if(100 * loop / 90 < val->GetSize())
				narr->SetAt(100 * loop / 90, intval);
 			}
		outarr->Add(narr);
		}
}

