
/* =====[ ContColl.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the ContColl.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/13/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wflib.h"
#include "ContColl.h" 
#include "support.h"
#include "intarr.h"
#include "mxpad.h"
#include "xRecog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#undef P2N

extern	CxRecog		xdllrecog;

CStrColl dicstrcoll;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStrColl::CStrColl()

{
	magic = CStrColl_Magic;

	minlen = 1000; maxidx = maxlen = 0;
}

//////////////////////////////////////////////////////////////////////////

CStrColl::~CStrColl()

{	
	ASSERT(magic == CStrColl_Magic);
	
	ASSERT(xarr.GetSize() == xnamearr.GetSize());

	Clear(NULL);
}

//////////////////////////////////////////////////////////////////////////

void CStrColl::AddCont(CString &name, CString &str)

{
	xchanged = true;

	//////////////////////////////////////////////////////////////////////////
	// Index it

	int tmpidx = 0, found = 0, alens = xnamearr.GetSize();
	for(int loops = 0; loops < alens; loops++)
		{
		if(xnamearr.GetAt(loops) == name)
			{
			tmpidx = loops; found = true; break;
			}
		}

	if(!found)
		tmpidx = xnamearr.Add(name);

	//AP2N("CStrColl::Add tmpidx=%d name=%s '%s'\r\n", tmpidx, name, str);
	
	// Make sure it is created
	while(true)
		{
		if(tmpidx < xarr.GetSize())
			break;

		CStringArray *sa = new CStringArray; ASSERT(sa);

		xarr.Add(sa);
		}
	
	CStringArray *psa = (CStringArray*)xarr.GetAt(tmpidx);

	psa->Add(str); 

}

//////////////////////////////////////////////////////////////////////////

void CStrColl::AddCont(CContain *pcont)

{
	AddCont(*pcont->name, pcont->GetConcatStrx());	
}


//////////////////////////////////////////////////////////////////////////
// Compare this item to the whole collectoin

int CStrColl::CmpCont(CContain *pcont, int *match1, int *match2)

{
	int ret = -1;

	CString tmp = pcont->GetConcatStrx();

	int tmplen = tmp.GetLength();

	CIntArr outarr;

	//AP2N("CStrColl::CmpCont '%s' =>\r\n", tmp);
 		
	int alen = xnamearr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CIntArr arr; CString &nnn =  xnamearr.GetAt(loop);

		CStringArray *psa = (CStringArray*) xarr.GetAt(loop);		
		psa->AssertValid();

		int blen = psa->GetSize();
		for(int loop2 = 0; loop2 < blen; loop2++)
			{
			CString &sss =  psa->GetAt(loop2);
			int ssslen = sss.GetLength();

			int res = xsd.Similar(&tmp, &sss);
			//int res = xld.Cmp(tmp, sss);
			//AP2N("    %d (%s) =>  %s\r\n", res, nnn, sss.Left(80));

			arr.Add(res);
			}

		int xx1, vv1, xx2, vv2, xx3, vv3; 
		arr.FindMax3(&xx1, &vv1, &xx2, &vv2, &xx3, &vv3); 
		//arr.FindMin2(&xx1, &vv1, &xx2, &vv2);

		if(xx1 >= 0)
			{
			//AP2N("max=%d  max2=%d max3=%d in %s\r\n", 
			//		vv1, vv2, vv3, nnn);		

			//outarr.Add( (vv1 + vv2 + vv3) / 3);
			outarr.Add( (vv1 + vv2) / 2);
			}
 		}
	
	int oxx, ovv, oxxx, ovvv; 
	outarr.FindMax2(&oxx, &ovv, &oxxx, &ovvv);
	//outarr.FindMin2(&oxx, &ovv, &oxxx, &ovvv);

	if(oxx >= 0)
		{
		AP2N("max=%d %s ---- max2=%d %s\r\n", ovv, xnamearr.GetAt(oxx), 
			ovvv, xnamearr.GetAt(oxxx));		

		ret = oxx;

		if(match1)	*match1 = ovv;
		if(match2)	*match2 = ovvv;
		}

	return ret;
}


//////////////////////////////////////////////////////////////////////////

void	CStrColl::Dump()

{
	int ret = -1;

	//ASSERT(xnamearr.GetSize() == xstrarr.GetSize());

	int alen = xnamearr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CString &nnn = xnamearr.GetAt(loop);
		CStringArray *psa = (CStringArray*) xarr.GetAt(loop);
		psa->AssertValid();

		AP2N("%s=>\r\n", nnn); 		

		int blen = psa->GetSize();
		for(int loop2 = 0; loop2 < blen; loop2++)
			{
			CString &sss =  psa->GetAt(loop2);

			AP2N("   %s\r\n", sss);
			}
 		}
}

//////////////////////////////////////////////////////////////////////////

int	CStrColl::Load(const char *fname)

{
	int ret = 0;
	
	//if(fname)
	//	filename = fname;

	//AP2N("CStrColl::Load %s\r\n", fname);

	CFile fp;		
	if(!fp.Open(fname, CFile::modeRead))
		{
		AP2N("CStrColl::Load -- Cannot load file %s\r\n", fname);
		return -1;
		}
	
	while(true)
		{
		CString item, line;

		int endd = support.ReadLine(fp, item, 1000);
		
		//AP2N("\r\nItem '%s'\r\n", item);

		int endd2 = support.ReadLine(fp, line, 15000);
			
		AddCont(item, line);

		if(endd || endd2)
			break;
		
		ret++;
		}
	
	//Dump();

	AP2N("CStrColl::Load -- loaded %d items\r\n", 	ret);

	xchanged = false;

	return ret;		
}

//////////////////////////////////////////////////////////////////////////

int	CStrColl::Save(const char *fname)

{
	int ret = 0;

	//AP2N("CStrColl::preSave %s\r\n", filename);

	if(!xchanged)
		return ret;

	AP2N("CStrColl::Save %s\r\n", fname);

	CFile fp; 
	if(!fp.Open(fname, CFile::modeCreate | CFile::modeWrite))
		{
		AP2N("CStrColl::Save - Cannot create file %s\r\n", fname);
		ret = -1;
		return ret;
		}

	int alen = xnamearr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{		
		CString &name = xnamearr.GetAt(loop); name += "\r\n";
		//AP2N("Name='%s'", name);

		CStringArray *psa = (CStringArray*) xarr.GetAt(loop);
		psa->AssertValid();

		int alen2 = psa->GetSize();
		for(int loop2 = 0; loop2 < alen2; loop2++)
			{
			CString tmp = psa->GetAt(loop2); tmp += "\r\n";

			fp.Write(name, name.GetLength());			
			fp.Write(tmp, tmp.GetLength());

			AP2N("   %s", tmp);
			ret++;
			}
		}		

	fp.Close();

	AP2N("CStrColl::Save(d) %d items to %s\r\n", ret, fname);

	return ret;		
}

//////////////////////////////////////////////////////////////////////////
// Clear one word out

void CStrColl::Clear(const char *str)

{
	//AP2N("CStrColl::Clear %s\r\n", str);

	int alen = xarr.GetSize();
	if(str == NULL)
		{
		xchanged = true; 

		for(int loop = 0; loop < alen; loop++)
			{
			CStringArray *psa = (CStringArray*) xarr.GetAt(loop);
			psa->AssertValid();

			delete psa;
 			}
		xnamearr.RemoveAll();
		xarr.RemoveAll();
		}
	else
		{
		int blen = xnamearr.GetSize();

		for(int loop2 = 0; loop2 < blen; loop2++)
			{
			CString pstr = xnamearr.GetAt(loop2);
			
			if(pstr == str )
				{
				AP2N("Deleting entry %s at %d\r\n", pstr, loop2);
				
				CStringArray *psa = (CStringArray*) xarr.GetAt(loop2);							
				delete psa;
				
				xnamearr.RemoveAt(loop2);
				xarr.RemoveAt(loop2);

				if(!xchanged) xchanged = true;
				}
			}
		}
}

//////////////////////////////////////////////////////////////////////////
// Clear one word item out

void CStrColl::ClearItem(const char *str, const char *item)

{
	//AP2N("CStrColl::ClearItem %s %s\r\n", str, item);

	int blen = xnamearr.GetSize();

	for(int loop2 = 0; loop2 < blen; loop2++)
		{
		CString pstr = xnamearr.GetAt(loop2);
		
		if(pstr == str)
			{
			//AP2N("CStrColl::ClearItem word %s at %d\r\n", pstr, loop2);
			
			CStringArray *psa = (CStringArray*) xarr.GetAt(loop2);							
			psa->AssertValid();
			
			int clen = psa->GetSize();

			for(int loop3 = 0; loop3 < clen; loop3++)
				{
				CString istr = psa->GetAt(loop3);

				if(istr == item)
					{
					//AP2N("CStrColl::ClearItem entry %s\r\n", istr);
			
					psa->RemoveAt(loop3);

					if(!xchanged) xchanged = true;
					
					break;
					}
				}			
			}
		}	
}

//////////////////////////////////////////////////////////////////////////

CString CStrColl::GetAt(int idx)

{
	CString ret = xnamearr.GetAt(idx);
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// Getters

int  CStrColl::GetCollName(int idx, CString &str)

{
	if(idx < 0 || idx >= xnamearr.GetSize())
		return -1;

	str = xnamearr.GetAt(idx);

	return str.GetLength();
}

//////////////////////////////////////////////////////////////////////////
// Get subitem

int  CStrColl::GetCollStr(int idx, int idx2, CString &str)

{
	if(idx < 0 || idx >= xnamearr.GetSize())
		return -1;

	CStringArray *psa = (CStringArray*) xarr.GetAt(idx);
	psa->AssertValid();

	if(idx2 < 0 || idx2 >= psa->GetSize())
		return -1;

	str = psa->GetAt(idx2);

	return str.GetLength();
}
