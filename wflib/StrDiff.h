
/* =====[ StrDiff.h ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the StrDiff.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/14/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_STRDIFF_H__B833A12B_0389_479E_8DFD_7C2885985626__INCLUDED_)
#define AFX_STRDIFF_H__B833A12B_0389_479E_8DFD_7C2885985626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStrDiff  
{

public:
	int xSimChar();

	CStrDiff();
	virtual ~CStrDiff();

	int Similar(CString *str1, CString *str2);
	int Similar(const char *str1, int len1, const char *str2, int len2);

protected:

	int xSimilar(const char *str1, int len1, const char *str2, int len2);
	inline int xSimChar(char chh, char chh2);

};

#endif // !defined(AFX_STRDIFF_H__B833A12B_0389_479E_8DFD_7C2885985626__INCLUDED_)
