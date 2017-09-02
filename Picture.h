
/* =====[ Picture.h ]========================================================== 
                                                                             
   Description:     The wavfrag project, implementation of the Picture.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  10/1/2010  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#if !defined(AFX_PICTURE_H__6098A4C3_D6D5_4711_BC7B_1595F459B480__INCLUDED_)
#define AFX_PICTURE_H__6098A4C3_D6D5_4711_BC7B_1595F459B480__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPicture  
{
	static	bool	_GetResource(LPSTR lpName, LPSTR lpType, void* pResource, int& nBufSize);

public:
	
	CPicture();
	virtual ~CPicture();

	bool	Load(CString sResourceType, CString sResource);
	bool	Load(CString sFileName);
	
	bool	Draw(CDC* pDC);
	bool	Draw(CDC* pDC, CPoint Pos);
	bool	Draw(CDC* pDC, CPoint Pos, CSize Size);
	bool	Draw(CDC* pDC, double nSizeRatio);
	bool	Draw(CDC* pDC, CPoint Pos, double nSizeRatio);
	bool	Draw(CDC* pDC, int x, int y, int cx, int cy);
	bool	Draw(CDC* pDC, int xx, int yy);

	CSize	GetSize(CDC* pDC);

protected:

	enum { HIMETRIC_INCH	= 2540	};

	bool	xDraw(CDC* pDC, int x, int y, int cx, int cy);
	void	xUnLoad();
	bool	xLoadFromBuffer(BYTE* pBuff, int nSize);
	
private:

	IPicture*		m_pPicture;
	
};

#endif // !defined(AFX_PICTURE_H__6098A4C3_D6D5_4711_BC7B_1595F459B480__INCLUDED_)
