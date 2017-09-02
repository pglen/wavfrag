
/* =====[ LevenStein.h ]========================================== 
                                                                             
   Description:     The yellowmemo project, implementation of the LevenStein.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  6/4/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// LevenStein.h: interface for the LevenStein class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVENSTEIN_H__39CAA9C6_55BD_4F72_9A21_95DE640EC1F2__INCLUDED_)
#define AFX_LEVENSTEIN_H__39CAA9C6_55BD_4F72_9A21_95DE640EC1F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LevDistance

{
  public:

    int		Cmp(char const *s, char const *t);

  private:

    inline	int		xMinimum (int a, int b, int c);
    inline	int		*xGetCellPointer (int *pOrigin, int col, int row, int nCols);

    inline	int		xGetAt (int *pOrigin, int col, int row, int nCols);
    inline	void	xPutAt (int *pOrigin, int col, int row, int nCols, int x);
}; 

#endif // !defined(AFX_LEVENSTEIN_H__39CAA9C6_55BD_4F72_9A21_95DE640EC1F2__INCLUDED_)
