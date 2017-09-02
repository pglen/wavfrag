
/* =====[ Frag.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the Frag.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/25/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>

#include "mxpad.h"
#include "support.h"
#include "Frag.h"
#include "fragcoll.h"

extern	CxRecog xdllrecog;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CFrag::fragext = ".wfa";
CString CFrag::wavext = ".wav";

int CFrag::onefraglen = 512;	// Default to 1024 points of FFT	

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CFrag::CFrag()

{
	magic = CFrag_Magic;
	

#ifdef _DEBUG
	verbose = 0;
#endif
	
	//needsave =  0;

	idx = -1;				// Default to an invalid value

	name = new CString;	shortname = new CString; fname = new CString;
}

//////////////////////////////////////////////////////////////////////////

CFrag::~CFrag()

{
	ASSERT(magic == CFrag_Magic);

	delete name, delete shortname; delete fname;
}

//////////////////////////////////////////////////////////////////////////
// Parse frag wav, check if compiled version exists.
// If does not, save compiled frag to fdir (fragdir)

int CFrag::ParseFragWav(const char *pname, const char *wdir, const char *fdir, int force)

{
	int ret = 0; char *buff4 = NULL;

	//AP2N("ParseFragWav pname='%s' wdir='%s' fdir='%s'\r\n", pname, wdir, fdir);

	// Construct output names
	CString basename = pname; basename = support.GetFilename(basename);

	CString fragname, wavname; wavname.Format("%s%s", wdir, pname);
	fragname.Format("%s%s%s", fdir, basename, CFrag::fragext);

	//AP2N("ParseFragWav wavname='%s' fragname='%s'\r\n", wavname, fragname);
	
	// See if wave is newer 
	struct _stat sbuff1; memset(&sbuff1, 0, sizeof(sbuff1));
	struct _stat sbuff2; memset(&sbuff2, 0, sizeof(sbuff2));

	_stat(wavname, &sbuff1); _stat(fragname, &sbuff2);

	//P2N("sbuff1=%d sbuff2=%d\r\n", sbuff1.st_mtime, sbuff2.st_mtime);

	if((sbuff1.st_mtime > sbuff2.st_mtime) || force)
		{
		int		len2, len22;
		char	*buff2;

		WAVEFORMATEX wfx; 

		if(dsp.LoadWave(wavname, &buff2, &len2, &wfx) == 0)
			{
			AP2N("CFrag::ParseFragWav Cannot load Wave %s\r\n", wavname);
			return false;
			}
		
		if(wfx.nChannels == 2)
			{
			//AP2N("CFrag::Load Convering to mono %d bytes\r\n", len2);
		
			len22 = len2 / 2;
			short *lptr = (short*)malloc(len22); ASSERT(lptr);
			short *rptr = (short*)malloc(len22); ASSERT(rptr);

			buff4 = (char*)lptr;
			
			dsp.SplitWave((short*)buff2, len2, lptr, rptr, len22);
			free(rptr); free(buff2);
			}
		else
			{
			len22 = len2;
			buff4 = buff2;
			}

		CPtrArray arr, arr2; CIntArr sarr;

		char *buff3 = (char*)malloc(len22);
		dsp.NormalizeWav(buff4, len22, buff3);
		free(buff4);

		// Show post-cut sound
		//if(xdllrecog._wavrec2)
			{
			//xdllrecog._wavrec2(xdllrecog.lastbuff, xdllrecog.lastbuflen);
			//xdllrecog._wavrec2(buff3, len22);
			}
	
		//////////////////////////////////////////////////////////////////
		// Fresh start for arrays
	
		CAnalRes res; xdllrecog.ScanSpectra(buff3, len22, &res);				
		free(buff3); 

		xdllrecog.analproc.ProcSpectra(&res, xdllrecog.FreqCompCnt);

		CFile fp;
		
		if(!fp.Open(fragname, CFile::modeCreate | CFile::modeWrite))
			{				
			AP2N("CFrag::ParseFragWav Cannot create/open frag file for %s\r\n", fragname);
			ret = -1;		
			}		
		else
			{ 
			int smagic = CFrag_Magic;

			fp.Write(&smagic, sizeof(int));

			res.ToFile(&fp);

			// Final magic for checking 
			fp.Write(&smagic, sizeof(int));	
			ret = true;
			}

		//AP2N("Wrote '%s' %d (%d) scan units \r\n", pname, cnt, pcnt);	
		//AP2N("Wrote %s %d buffers\r\n", pname, cnt);
		}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Load frag data
//

int CFrag::LoadFrag(const char *str, int force)

{
	ASSERT(magic == CFrag_Magic);

	//AP2N("CFrag::LoadFrag '%s'\r\n", str);

	*fname = str; *name = str;
	
	support.PathToFname(*name); *name = support.GetFilename(*name);

	int idxx = name->FindOneOf("1234567890-");
	
	if(idxx >= 0)
		*shortname = name->Left(idxx);
	else
		*shortname = *name;

	shortname->MakeLower();	name->MakeLower();

	//AP2N("CFrag::LoadFrag for '%s'\r\n", *name);

	CFile fp;		
	if(!fp.Open(str, CFile::modeRead))
		{
		AP2N("CFrag::LoadFrag Cannot open file %s\r\n", str);
		return -1;
		}

	// Get saved entries
	//int cnt = 0, pcnt = 0, vcnt = 0;
	int sss = 0, ppp = 0, vvv = 0, xmagic = 0; 
	
	fp.Read(&xmagic, sizeof(int));
	if(xmagic != magic)
		{
		AP2N("CFrag::LoadFrag BAD magic (start)\r\n");
		}

	xres.FromFile(&fp);
	
	fp.Read(&xmagic, sizeof(int));
	if(xmagic != magic)
		{
		AP2N("CFrag::LoadFrag BAD magic (end)\r\n");
		}			
			
	fp.Close();

	if(xres.raw.GetSize() == 0)
		{
		AP2N("CFrag::LoadFrag empty buffer on %s\r\n", *name);
		}
	else
		{
		//onefraglen = xres.raw.GetAt(0)->GetSize();
		}

	//AP2N("Loaded '%s' %d buffers %d entries each\r\n", *name, cnt, sss);

	// Dumper for loads
#if 0
	AP2N("CFrag::LoadFrag  Dump: '%s'\r\n", *name);

	for(int loopd = 0; loopd < xres.all.GetSize(); loopd++)
		{
		CIntArr *ptmp = xres.all.GetAt(loopd);		
		CIntArr *vtmp = xres.vall.GetAt(loopd);		
	
		int alen3 = ptmp->GetSize();
				
		for(int loopd3 = 0; loopd3 < alen3; loopd3++)
			{
			AP2N("%3d-%3d  ", ptmp->GetAt(loopd3),
						vtmp->GetAt(loopd3));
			}
	
		if(alen3)
			AP2N("\r\n");
		}
#endif

#if 0
	int powlen = xres.pow.GetSize();
	AP2N("CFrag::LoadFrag  Power Dump: '%s' (%d)\r\n", *name, powlen);
	for(int loopd2 = 0; loopd2 < powlen; loopd2++)
		{		
		CIntArr *ptmp = xres.pow.GetAt(loopd2);

		for(int loopd3 = 0; loopd3 < ptmp->GetSize(); loopd3++)
			AP2N("%3d ", ptmp->GetAt(loopd3));							

		AP2N("\r\n");
		}
#endif

#if 1
	// Visualizer for loads
	xdllrecog.analproc.VisRaw(xres.raw.GetData());
	xdllrecog.analproc.Vis(xres.all.GetData(), xres.vall.GetData());
#endif

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Compare this frag with the unknown. The start index (offs) to the
// unknown array provided.
//

int CFrag::CmpFrags(CAnalRes *parr, int offs, CCmpRes *pxres)

{	
	//AP2N("CFrag::CmpFrags %s:  ", *name);

	int ret = 0;		// Maximizers default to small returns
		
	// xreset xresult output
	pxres->nfund = pxres->nharm = pxres->nhiss = 0;

	int arrlen = parr->all.GetSize(), reflen = xres.all.GetSize();
	
	// No array ... bail out
	if(reflen == 0)
		{
		//AP2N("CFrag::CmpFrags zero length ref array in %s\r\n", *fname);
		return ret;
		}

	// Passes the end ... shorten scan
	if(arrlen <= offs + reflen)
		{
		//AP2N("CFrag::CmpFrags passes the end at %s\r\n", *fname);
		reflen = arrlen - offs;
		//return ret;	
		}

#ifdef _DEBUG

	// Visualizer, only print some of the data
	//if(offs == 15)
	//	verbose = true;
	//else
	//	verbose = false;

#endif

	int sum = 0, wobble = 1;

	CIntArrRec	arr;

	// Walk reference
	for(int loopr = 0; loopr < reflen; loopr++)
		{	
		int diff = 0, offs2 = loopr + offs;		
		
		// Contain offsets
		int ss = MAX(0, offs2 - wobble), ee = MIN(arrlen, offs2 + wobble + 1);
			
		// Wobble into array
		for(int loopw = ss; loopw < ee; loopw++)
			{
			int hit = xHitFrags(parr, loopw, loopr, xdllrecog.Strictness);
			//int hit = xHitPow(parr, loopw, loopr, xdllrecog.Strictness);
			
			// What to propagate over to the compare		
			diff = MAX(hit, diff);
			}		
		arr.Add(diff);
		}

	// Calculate the sum of hits, calc length neutral 
	ret = arr.Sum(); ret /= reflen;
	
#ifdef _DEBUG

	//if(verbose)
	//	{
	//	xdllrecog._plotrec(arr.GetData(), arr.GetSize(), 0);cfr
	//	xdllrecog._plotrec(NULL, 0, 0);
	//	}

	// Animate for observation
	//Sleep(2);

#endif

	return (ret);
}

//////////////////////////////////////////////////////////////////////////
// Actual compare takes place here.
//
// Description of experimental parameters:
//	
//		cnt		-	arbitrary constant (cent, mille)
//		wobble	-	How many spaces to wobble up and down 
//		divi	-	tolenrancy of the actual compare		
//		decrem	-	diminishing importance of compare
//		subit	-	mismatch penalty
//

int CFrag::xHitFrags(CAnalRes *parr, int offs, int loopr, int nlim)

{
	int ret = 0;
	
	// Estabilish current arrays
	CIntArr *ref = (CIntArr *)xres.all.GetAt(loopr);	
	CIntArr *tmp = (CIntArr *)parr->all.GetAt(offs);
	
	int tlen = tmp->GetSize(), rlen = ref->GetSize();
	
	// Safety measuxres for index 0 access or overmach by low count
	if(tlen < 2)
		{
		//AP2N("CFrag::xHitFrags zero tlen\r\n");
		return ret;
		}
	if(rlen < 2)
		{
		//AP2N("CFrag::xHitFrags zero rlen\r\n");
		return ret;
		}

	// Estabilish compare parameters. Determined experimentally.
	
	int adder = 100, vert_wobble = 1;
	int decrem  = adder / (rlen * 2);

	//////////////////////////////////////////////////////////////////////
	// Compare with vertical wobble

	// Aliases into data
	int *ddd = ref->GetData();	int *ttt = tmp->GetData();

	for(int rloop = 0; rloop < rlen; rloop++)
		{ 
		//int rfreq	= ref->GetAt(rloop);
		int rfreq	= ddd[rloop];		// Direct access
	
		if(rfreq == 0)		// Empty 
			continue;

		int match = false;
		
		// Tolerances to the frequency difference
		int lim  = rfreq / 15;
		
		// Fetch offsets into vertical wobble, contain them
		int ss = rloop - vert_wobble; ss = MAX(0, ss);
		int ee = rloop + vert_wobble + 1; ee = MIN(tlen, ee);

		// Actual search
		for(int tloop = ss; tloop < ee; tloop++)
			{	
			//int tfreq = tmp->GetAt(tloop);
			int tfreq = ttt[tloop]; // Direct access
				
			// Compare freq indexes
			if(ABS(tfreq - rfreq) <= lim)			
				{
				match = true;				
				break;
				}	
			}
 
		if(match)
			{
			ret += adder;			// Reward for match
			}
		
		// Diminish count as we head towards the end
		adder -= decrem; 
		}

	//////////////////////////////////////////////////////////////////////	
	// Kill negatives, square function would create false positive
	ret = MAX(ret, 0); 	
		
	//if(verbose)
	//	AP2N("   xHitFrags tlen=%d rlen=%d ret=%d\r\n", tlen, rlen, ret);

	return ret; 
}

//////////////////////////////////////////////////////////////////////////

int CFrag::xHitPow(CAnalRes *parr, int offs, int loopr, int nlim)

{
	int ret = 0;
	
	// Estabilish current arrays
	CIntArr *ref = (CIntArr *)xres.pow.GetAt(loopr);	
	CIntArr *tmp = (CIntArr *)parr->pow.GetAt(offs);
	
	int tlen = tmp->GetSize(), rlen = ref->GetSize();
	
	// Safety measuxres for index 0 access or overmach by low count
	if(tlen < 2)
		{
		//AP2N("CFrag::xHitFrags zero tlen\r\n");
		return ret;
		}
	if(rlen < 2)
		{
		//AP2N("CFrag::xHitFrags zero rlen\r\n");
		return ret;
		}

	// Estabilish compare parameters. Determined experimentally.
	
	int adder = 100, wobble = 2;
	int decrem  = adder / (rlen * 2);

	//////////////////////////////////////////////////////////////////////
	// Compare with vertical wobble

	// Aliases into data
	int *ddd = ref->GetData();	int *ttt = tmp->GetData();

	for(int rloop = 0; rloop < rlen; rloop++)
		{ 
		int rfreq	= ref->GetAt(rloop);
		//int rfreq	= ddd[rloop];		// Direct access
	
		if(rfreq == 0)		// Empty 
			continue;

		int match = false;
		
		// Tolerances to the frequency difference
		int lim  = rfreq / 20;
		//int lim = 1;
		
		// Fetch offsets into vertical wobble, contain them
		int ss = rloop - wobble; ss = MAX(0, ss);
		int ee = rloop + wobble + 1; ee = MIN(tlen, ee);

		// Actual search
		for(int tloop = ss; tloop < ee; tloop++)
			{	
			int tfreq = tmp->GetAt(tloop);
			//int tfreq = ttt[tloop]; // Direct access
				
			// Compare freq indexes
			if(ABS(tfreq - rfreq) <= lim)			
			//if(rfreq == tfreq)
				{
				match = true;				
				break;
				}	
			}
 
		if(match)
			{
			ret += adder;			// Reward for match
			}
		
		// Diminish count as we head towards the end
		adder -= decrem; 
		}

	//////////////////////////////////////////////////////////////////////	
	// Kill negatives, square function would create false positive
	ret = MAX(ret, 0); 	
		
	//if(verbose)
	//	AP2N("   xHitFrags tlen=%d rlen=%d ret=%d\r\n", tlen, rlen, ret);

	return ret; 
}

//////////////////////////////////////////////////////////////////////////

int CFrag::Save(CFile *pfp)

{
	//AP2N("CFrag::Save\r\n");

	int ret = 0;

	ret = xres.Save(pfp);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int CFrag::Load(CFile *pfp)

{
	//AP2N("CFrag::Load\r\n");

	int ret = 0;

	ret = xres.Load(pfp);

	return ret;
}

// EOF
