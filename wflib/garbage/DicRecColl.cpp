
/* =====[ DicRecColl.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the DicRecColl.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  3/28/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wflib.h"
#include "DicRecColl.h"

#include "intarr.h"
#include "mxpad.h"
#include "support.h"

// Remove mxpad sync calls
#undef P2N

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDicRecColl diccoll;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDicRecColl::CDicRecColl()

{
	magic = CDicRecColl_Magic;
	xchanged = 0;
}

CDicRecColl::~CDicRecColl()

{
	ASSERT(magic == CDicRecColl_Magic);	
	Empty();
}

//////////////////////////////////////////////////////////////////////////

int	CDicRecColl::Cmp(CContain *pcont)

{
	//AP2N("CDicRecColl::Cmp(CContain *pcont)\r\n");
	//pcont->Dump();

	CIntArr iarr;

	int alen = xdicarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CDicRec *val = (CDicRec*)xdicarr.GetAt(loop);
		ASSERT(val->magic == CDicRec_Magic);
				
		int diff = val->CmpDicRec(pcont);
		//int diff = val->CmpDicRec2(pcont);

		AP2N("CDicRecColl::CmpDic %4d %s\r\n", diff, val->GetName());

		iarr.Add(diff);
		}

	// Get top 2 entries
	int idx1, vol1, idx2, vol2, dummy = 0;

	iarr.FindMax2(&idx1, &vol1, &idx2, &vol2);

	int rat = 100 * MAX(vol1, vol2) / MAX(1, MIN(vol1, vol2));

	//AP2N("idx1=%d (%s), vol1=%d, idx2=%d (%s), vol2=%d rat=%d\r\n", 
	//				idx1, GetStrAt(idx1), vol1, 
	//					idx2, GetStrAt(idx2), vol2, rat);

	//if(rat < 120)
	//	idx1 = 0;

	return idx1;
}

//////////////////////////////////////////////////////////////////////////

//DEL int	CDicRecColl::CmpDic(const char *str)
//DEL 
//DEL {
//DEL 	int ret = 0, dummy = 0;
//DEL 
//DEL 	CString tmpstr(str);
//DEL 	CStringArray sarr;	CDicRec::_Parse(&tmpstr, &sarr);
//DEL 	CIntArr iarr;
//DEL 
//DEL 	int alen = xdicarr.GetSize();
//DEL 	for(int loop = 0; loop < alen; loop++)
//DEL 		{
//DEL 		CDicRec *val = (CDicRec*)xdicarr.GetAt(loop);
//DEL 
//DEL 		ASSERT(val->magic == CDicRec_Magic);
//DEL 		int diff = val->CmpDicRec(&sarr);
//DEL 
//DEL 		iarr.Add(diff);
//DEL 		AP2N("CDicRecColl::CmpDic %s %d\r\n", val->GetName(), diff);
//DEL 		}
//DEL 
//DEL 	// Get top entry
//DEL 	iarr.FindMax(&ret, &dummy);
//DEL 
//DEL 	return ret;
//DEL }

//////////////////////////////////////////////////////////////////////////

int	CDicRecColl::LoadDic(const char *fname)

{
	int cnt = 0, cnt2 = 0;

	ASSERT(magic == CDicRecColl_Magic);	

	Empty();

	AP2N("CDicRecColl::LoadDic fname='%s'\r\n", fname);

	CFile fp;

	if(fp.Open(fname, CFile::modeRead) == 0)
		{
		AP2N("CDicRecColl::LoadDic - cannot open file '%s'\r\n", fname);
		return cnt;
		}

	//AP2N("CDicRecColl::LoadDic: '%s' \r\n", fname);	

	lastfile = fname;
	
	CDicRec *dr = NULL;

	while(true)
		{
		CString line, baseline;

		if(!support.ReadLine(fp, baseline, 512))
			break;

		int len = baseline.GetLength();
		if(len == 0)
			{
			//AP2N("Empty line %s\r\n", baseline);
			continue;
			}

		// Skip til no space
		for(int loop = 0; loop < len; loop++)
			{
			if(baseline[loop] != ' ')
				break;
			}
		if(baseline.GetAt(loop) == '#')
			{
			//AP2N("Comment: '%s'\r\n", baseline);
			continue;
			}

		if(baseline[0] == ' ' || baseline[0] == '\t')
			{
			if(dr)
				{
				dr->Add(baseline);
				cnt2++;
				}
			}
		else
			{
			dr = new CDicRec(baseline); ASSERT(dr);
			xdicarr.Add(dr);
			cnt++;
			}
		}

	//xchanged = false;
	//Dump();

	//AP2N("Loaded %d dictionary entries %d strings total.\r\n", cnt, cnt2);

	return cnt;
}

//////////////////////////////////////////////////////////////////////////

int	CDicRecColl::SaveDic(const char *fname)

{
	int cnt = 0;

	if(!xchanged)
		return cnt;

	CString tmpname;

	if(fname)
		tmpname = fname;
	else
		tmpname = lastfile;

	//AP2N("Serialize dicarr to %s\r\n", tmpname);

	unlink(tmpname);

	int len = xdicarr.GetSize();
	for(int loopw = 0; loopw < len; loopw++)
		{
		CDicRec *dr = (CDicRec *)xdicarr[loopw];

		ASSERT(dr->magic == CDicRec_Magic);

		//dr->Serialize(tmpname);
		cnt++;
		}

	return cnt;
}

//////////////////////////////////////////////////////////////////////////

void CDicRecColl::Dump()

{
	int alen = xdicarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CDicRec *val = (CDicRec*)xdicarr.GetAt(loop);

		ASSERT(val->magic == CDicRec_Magic);
		val->Dump();
		}
}

//////////////////////////////////////////////////////////////////////////

void CDicRecColl::Empty()

{
	int alen = xdicarr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CDicRec *val = (CDicRec*)xdicarr.GetAt(loop);

		ASSERT(val->magic == CDicRec_Magic);
		delete val;
 		}
	xdicarr.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////

CDicRec *CDicRecColl::GetAt(int pos)

{
	ASSERT(pos >= 0); ASSERT(pos < xdicarr.GetSize());
	ASSERT(magic == CDicRecColl_Magic);	

	CDicRec *val = (CDicRec*)diccoll.GetData()->GetAt(pos);

	return val;
}

//////////////////////////////////////////////////////////////////////////

CString &CDicRecColl::GetStrAt(int pos)

{
	ASSERT(pos >= 0); ASSERT(pos < xdicarr.GetSize());
	ASSERT(magic == CDicRecColl_Magic);	

	CDicRec *val = (CDicRec*)diccoll.GetData()->GetAt(pos);

	return val->GetName();
}
