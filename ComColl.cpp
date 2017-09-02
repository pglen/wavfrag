
/* =====[ ComColl.cpp ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the ComColl.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/29/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "wavfrag.h"
#include "ComColl.h"

#include "mxpad.h"
#include "support.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComColl::CComColl()

{
	changed = false;
}

//////////////////////////////////////////////////////////////////////////

CComColl::~CComColl()

{
	int alen = arr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CCommand *com = (CCommand*)arr.GetAt(loop);

		ASSERT(com->magic == CCommand_Magic);

		delete com;
		}
}

//////////////////////////////////////////////////////////////////////////

void		CComColl::LoadComms(const char *dir)

{
	CFile fp;

	if(fp.Open(dir, CFile::modeRead) == 0)
		{
		//AfxMessageBox(dir);

		AP2N("Cannot open file %s\r\n", dir);
		return;
		}

	int cnt = 0, cnt2 = 0;

	//AP2N("CCommand::Load from %s\r\n", dir);
	//AfxMessageBox(dir);
		
	while(true)
		{
		CString name, comstr, comstr2, comstr3, comm, para, tmp;

		if(!support.ReadLine(fp, name, 512))
			break;

		if(!support.ReadLine(fp, comstr, 512))
			break;

		if(!support.ReadLine(fp, comstr2, 512))
			break;

		if(!support.ReadLine(fp, comstr3, 512))
			break;

		if(!support.ReadLine(fp, comm, 512))
			break;

		if(!support.ReadLine(fp, para, 512))
			break;

		if(!support.ReadLine(fp, tmp, 512))
			break;

		//AfxMessageBox(name);
	
		CCommand *com = new CCommand;

		sscanf(tmp, "%d %d", &com->kind, &com->prompt);

		*com->name   = name;	*com->comm = comm;
		*com->comstr = comstr;	
		*com->comstr2 = comstr2;	
		*com->comstr3 = comstr3;	
		
		*com->para = para;
	
		arr.Add(com);

		cnt++;
		}

	changed = false;

	//AP2N("Loaded %d command entries\r\n", cnt);
}

//////////////////////////////////////////////////////////////////////////

void		CComColl::Save(const char *dir)

{
	//AP2N("CComColl::Save changed=%d %s\r\n", changed, dir);
	
	if(!changed)
		return;

	AP2N("CComColl::Save %s\r\n", dir);

	CFile fp;
	if(fp.Open(dir, CFile::modeCreate | CFile::modeWrite) == 0)
		{
		P2N("Cannot create file %s\r\n", dir);
		return;
		}

	int cnt = 0, alen = arr.GetSize();
	for(int loop = 0; loop < alen; loop++)
		{
		CCommand *com = (CCommand*)arr.GetAt(loop);

		fp.Write(*com->name, com->name->GetLength()); fp.Write("\r\n", 2);
		fp.Write(*com->comstr, com->comstr->GetLength()); fp.Write("\r\n", 2);
		fp.Write(*com->comstr2, com->comstr2->GetLength()); fp.Write("\r\n", 2);
		fp.Write(*com->comstr3, com->comstr3->GetLength()); fp.Write("\r\n", 2);
		fp.Write(*com->comm, com->comm->GetLength()); fp.Write("\r\n", 2);
		fp.Write(*com->para, com->para->GetLength()); fp.Write("\r\n", 2);

		CString tmp; tmp.Format("%d %d", com->kind, com->prompt);
		fp.Write(tmp, tmp.GetLength()); fp.Write("\r\n", 2);

		cnt++;
		}

	AP2N("CComColl::Saved %d entries.\r\n", cnt);
}

//////////////////////////////////////////////////////////////////////////

int		CComColl::Dump()

{
	int alen = arr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CCommand *com = (CCommand*)arr.GetAt(loop);

		AP2N("%s %s %s\r\n", *com->name, *com->comm, *com->para);
		}

	return alen;
}

//////////////////////////////////////////////////////////////////////////

CCommand *CComColl::GetComm(int idx)

{
	CCommand *ret = NULL;

	if(arr.GetSize() > idx)
		ret = (CCommand*)arr.GetAt(idx);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

CCommand *CComColl::GetComm(const char *name)

{
	CCommand *ret = NULL;

	int alen = arr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CCommand *com = (CCommand*)arr.GetAt(loop);

		if(*com->name == name)
			{
			ret  = com;
			break;
			}
 		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////

CCommand *CComColl::GetComStr(const char *comstr)

{
	CCommand *ret = NULL;

	int alen = arr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CCommand *com = (CCommand*)arr.GetAt(loop);

		if(	*com->comstr == comstr  || 
			*com->comstr2 == comstr || 
			*com->comstr3 == comstr  )
			{
			ret  = com;
			break;
			}
 		}

	return ret;
}

//////////////////////////////////////////////////////////////////////////

void	CComColl::DelComm(const char *name)

{
	CCommand *ret = NULL;

	int alen = arr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CCommand *com = (CCommand*)arr.GetAt(loop);

		if(*com->name == name)
			{
			delete com;
			arr.RemoveAt(loop);

			changed = true;
			break;
			}
 		}
}

//////////////////////////////////////////////////////////////////////////


void	CComColl::AddComm(const char *name, const char *comm, const char *para)
 
{
	CCommand *com = new CCommand;

	*com->name = name;
	*com->comm = comm;
	*com->para = para;

	changed = true;

	arr.Add(com);
}
