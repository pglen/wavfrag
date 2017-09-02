
#if 0
	CIntArr ratsort, ratarr, sarr2;	cmparr.Sort(&sarr2);

	int salen22 = sarr2.GetSize();
	salen22 = 6;
	for(int loops2 = 0; loops2 < salen22; loops2++)
		{
		int idx = sarr2.GetAt(loops2);
		CFrag *fr  = (CFrag *)tmparr->GetAt(idx);
		AP2N("%s %d  ", *fr->name, cmparr[idx]);

		ratarr.AddToVal(fr->idx, 1);
 		}

	AP2N("\r\n############################\r\n");

	//ratarr.DumpAll();
	
	ratarr.Sort(&ratsort);
	int idxx = ratsort.GetAt(0);

	// Get Frag from index
	for(int loopfx = 0; loopfx < len2f; loopfx++)
		{
		CFrag *frfx = ((CFrag *)tmparr->GetAt(loopfx));	
		if(frfx->idx == idxx)
			{
			//AP2N("Main hit: %s\r\n", *frfx->xname);
			//result += *frfx->xname;	result += " ";
			break;
			}
 		}
#endif


	
#if 0
	// Plot middle record
	if(alen)
		{
		CIntArr *piarr = (CIntArr*)parr->GetAt(alen / 2);

		if(_plotrec)
			{
			//_plotrec(piarr->GetData(), piarr->GetSize(), 1);
			//_plotrec(NULL, 0, 1);
			}	
		}
#endif

#if 0
	//////////////////////////////////////////////////////////////////////
	// Log it with square root

	for(int loopb = 0; loopb < alen; loopb++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopb);
		int alenc = tmp->GetSize();

		for(int loopc = 0; loopc < alenc; loopc++)
			{
			int val = tmp->GetAt(loopc);				
			
			int val2 = sqrt(val) * 12;
			//int val2 = log(val) * 40;
			//AP2N("%d (%d)   ", val, val2);
			tmp->SetAt(loopc, val2);
			}
		}
#endif

#if 0
	//////////////////////////////////////////////////////////////////////
	// Smooth out scan

	for(int looph2 = 0; looph2 < alen; looph2++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(looph2);
		
		tmp->RunAve(1);
		//tmp->Smooth(2);
		}
#endif


#if 0
	//////////////////////////////////////////////////////////////////////
	// Contain dynamics to factor of x

	int avx = 0;
	for(int loop = 0; loop < alen; loop++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loop);
		
		int aval = tmp->Avg();
		//avx = MAX(aval, avx);			
		avx = aval +  avx;			
		}

	avx /= alen;
	avx *= 20;

	//AP2N("CxRecog::ScanSpectra %d\r\n", mxx);
	
	double fact = 255L / (double)avx;

	// Apply
	for(int loopa = 0; loopa < alen; loopa++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopa);
		tmp->Multiply(fact);		
		}
#endif


#if 0
	//////////////////////////////////////////////////////////////////////
	// Clip to 255

	for(int loopclip = 0; loopclip < alen; loopclip++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopclip);
		int clen = tmp->GetSize();

		for(int loopc = 0; loopc < clen; loopc++)
			{
			int val = tmp->GetAt(loopc);
			if(val > 255) tmp->SetAt(loopc, 255);
 			}
		}
#endif

#if 0
	//////////////////////////////////////////////////////////////////////
	// Bell curve it

	for(int loopbell = 0; loopbell < alen; loopbell++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(loopbell);
		int clen = tmp->GetSize();

		for(int loopc = 0; loopc < clen; loopc++)
			{
			int mul = 0;

			if(loopc < clen / 3)
				mul = loopc;
			else
				mul = clen / 3; //clen - loopc;
				
			mul *= 4; //mul /= 1;	
			//mul += 64;	
			
			//if(loopbell == 0)
			//	AP2N("mul=%d ", mul);

			int val = tmp->GetAt(loopc);

			tmp->SetAt(loopc, val * mul / clen);
 			}
		}
#endif


#if 0
	//////////////////////////////////////////////////////////////////////
	// Remove below treshold power

	for(int looph4 = 0; looph4 < alen; looph4++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(looph4);
		int clen = tmp->GetSize();

		for(int loopc = 0; loopc < clen; loopc++)
			{
			int val = tmp->GetAt(loopc);
			if(val < 128) tmp->SetAt(loopc, 0);
 			}
		}
#endif
	
#if 0
	//////////////////////////////////////////////////////////////////////
	// Remove below treshold freq

	for(int looph = 0; looph < alen; looph++)
		{
		CIntArr *tmp = (CIntArr *)parr->GetAt(looph);
		int clen = tmp->GetSize();

		for(int loopc = 0; loopc < 10; loopc++)
			{
			tmp->SetAt(loopc, 0);
 			}
		}
#endif
