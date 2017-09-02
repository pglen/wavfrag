
/* =====[ Reso.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Reso.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  9/15/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_RESO_H__5DBD20C0_3DBD_49C6_B582_EAA692275583__INCLUDED_)
#define AFX_RESO_H__5DBD20C0_3DBD_49C6_B582_EAA692275583__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReso  
{
public:
	void DumpSine(CPlot *plot);
	int Resonate(short *ptr, int len, CPtrArray *parr);
	CReso();
	virtual ~CReso();

	CPtrArray	sarrarr;

protected:

	int CReso::xResonate(short *ptr, int len, CIntArr *piarr);
	int CReso::xResonate2(short *ptr, int len, CIntArr *psarr);


};

#endif // !defined(AFX_RESO_H__5DBD20C0_3DBD_49C6_B582_EAA692275583__INCLUDED_)
