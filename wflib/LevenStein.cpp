
/* =====[ LevenStein.cpp ]========================================================== 
                                                                             
   Description:     The wflib project, implementation of the LevenStein.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  2/10/2011  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "LevenStein.h"

#include <string.h>
#include <malloc.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//****************************
// Get minimum of three values
//****************************

int LevDistance::xMinimum (int a, int b, int c)

{
	int mi;

	mi = a;
	if (b < mi) 
		{
		mi = b;
		}
	if (c < mi) 
		{
		mi = c;
		}
	return mi;
}

//**************************************************
// Get a pointer to the specified cell of the matrix
//************************************************** 

int *LevDistance::xGetCellPointer (int *pOrigin, int col, int row, int nCols)
{
  return pOrigin + col + (row * (nCols + 1));
}

//*****************************************************
// Get the contents of the specified cell in the matrix 
//*****************************************************

int LevDistance::xGetAt (int *pOrigin, int col, int row, int nCols)
{
int *pCell;

  pCell = xGetCellPointer (pOrigin, col, row, nCols);
  return *pCell;

}

//*******************************************************
// Fill the specified cell in the matrix with the value x
//*******************************************************

void LevDistance::xPutAt (int *pOrigin, int col, int row, int nCols, int x)
{
int *pCell;

  pCell = xGetCellPointer (pOrigin, col, row, nCols);
  *pCell = x;

}

//*****************************
// Compute Levenshtein distance
//*****************************

int LevDistance::Cmp (char const *s, char const *t)
{
	int *d;			// pointer to matrix
	int n;			// length of s
	int m;			// length of t
	int i;			// iterates through s
	int j;			// iterates through t

	char s_i;		// ith character of s
	char t_j;		// jth character of t

	int cost;		// cost
	int result;		// result
	int cell;		// contents of target cell
	int above;		// contents of cell immediately above
	int left;		// contents of cell immediately to left
	int diag;		// contents of cell immediately above and to left
	int sz;			// number of cells in matrix

	//////////////////////////////////////////////////////////////////////
	// Step 1	

	n = strlen (s);  m = strlen (t);

	if (n == 0) 
		{
		return m;
		}
	if (m == 0) 
		{
		return n;
		}

	sz = (n+1) * (m+1) * sizeof (int);
	d = (int *) malloc (sz);

	//////////////////////////////////////////////////////////////////////
	// Step 2

	for (i = 0; i <= n; i++) 
		{
		xPutAt (d, i, 0, n, i);
		}

	for (j = 0; j <= m; j++) 
		{
		xPutAt (d, 0, j, n, j);
		}

	//////////////////////////////////////////////////////////////////////
	// Step 3

  for (i = 1; i <= n; i++) 
	{
    s_i = s[i-1];

    // Step 4

    for (j = 1; j <= m; j++) 
		{
		t_j = t[j-1];

		// Step 5

		if (s_i == t_j) 
			{
			cost = 0;
			}
		else 
			{
			cost = 1;
			}

      // Step 6 
      above = xGetAt (d,i-1,j, n);
      left = xGetAt (d,i, j-1, n);
      diag = xGetAt (d, i-1,j-1, n);
      cell = xMinimum (above + 1, left + 1, diag + cost);
      xPutAt (d, i, j, n, cell);
    }
  }

  // Step 7

  result = xGetAt (d, n, m, n);
  free (d);
  return result;
	
}

