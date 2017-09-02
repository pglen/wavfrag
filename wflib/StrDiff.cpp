
/* =====[ StrDiff.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the StrDiff.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  4/14/2012  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "support.h"
#include "StrDiff.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStrDiff::CStrDiff()
{

}

CStrDiff::~CStrDiff()
{

}

//////////////////////////////////////////////////////////////////////////
// Override for str ptrs

int CStrDiff::Similar(CString *str1, CString *str2)

{
	return( Similar(*str1, str1->GetLength(), *str2, str2->GetLength()) );
}

//////////////////////////////////////////////////////////////////////////
// Compart to strings, deliver a similarity quote.
//
// This function recurses. Converted it into C++ and renamed short 
// variable declarations.


int CStrDiff::Similar(const char *str1, int len1, const char *str2, int len2)

{
	int ret = 0, avglen = MAX(len1, len2);
	
	if(len1 > 0 && len2 > 0)
		{
		ret = xSimilar(str1, len1, str2, len2);
		}
	ret *= 1000; 

	if(avglen) 
		ret /= avglen; 

	return ret;
}

//////////////////////////////////////////////////////////////////////////

int CStrDiff::xSimilar(const char *str1, int len1, const char *str2, int len2)

{
   int maxx = 0, walk, pos1, pos2, sum;
   const char *ptr, *ptr2, *end1, *end2;
   
   end1 = str1 + len1,  end2 = str2 + len2;
   
   for (ptr = str1; ptr < end1; ptr++)
		{
		for (ptr2 = str2; ptr2 < end2; ptr2++)
			{
			for (walk = 0; (ptr + walk < end1) 
						&& 	(ptr2 + walk < end2) 
							&&	ptr[walk] == ptr2[walk]; walk++);

			if (walk > maxx)
				{
				maxx = walk;
				pos1 = ptr - str1; pos2 = ptr2 - str2;
				}
			}
		}
   
   if (maxx == 0)
     return 0;
   
   sum = maxx;

   // Recurse before
   if (pos1 && pos2)
		{
		sum += xSimilar(str1, pos1, str2, pos2);
		}

   // Recurse after
   if ((pos1 + maxx < len1) && (pos2 + maxx < len2))
		{
		sum += xSimilar(str1 + pos1 + maxx, len1 - pos1 - maxx,
				str2 + pos2 + maxx, len2 - pos2 - maxx);
		}

   return sum;
}

//////////////////////////////////////////////////////////////////////////

int CStrDiff::xSimChar(char chh, char chh2)

{
	int ret =  chh - chh2;

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// testing ...

#if 0

int main(void)

{
   char a[] = "YelloDoggie";   char b[] = "FollowHoggie";

   printf("result: %d\n", sim_char(a, strlen(a), b, strlen(b)));
   
   // Calculate confidence level (0.0 to 1.0) with this formula
   // confidence = result * 2 / (strlen(a) + strlen(b))
}

#endif
