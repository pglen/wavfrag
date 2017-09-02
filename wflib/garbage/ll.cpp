
#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////
// Looking for match in three sorted lists


typedef struct LL
{
    int val;
    LL *next;
} LLL;

LL list_one;
LL list_2;
LL list_3;


int is_match()

{
    LL *nnn  = &list_one;
    LL *nn2  = &list_2;
    LL *nn3  = &list_3;

    int found = 0;

    // Iterate first list ... bail if passed sorted GT point
    while(true)
        {       
        if(found)            // Got it, terminate search
            break;

        if(nnn->next == NULL)
            break;

        int vvv = nnn->val; // Avoids pointer access

    // Walk list 2
        while(true)
            {       
            if(nn2->next == NULL)
                break;
             
            // Passed the sorted list GT value
            if(nn2->val > vvv)
                break;
            else
                if(nn2->val == vvv)
                    {                    
                    // Walk list 3
                    while(true)
                        {       
                        if(nn3->next == NULL)
                            break;
            
                        // Passed the sorted list
                        if(nn3->val > vvv)
                            break;
                        else
                            // Found!
                            if(nn3->val == vvv)
                                {
                                found = true;
                                break;
                                }
                        nn3 = nn3->next;
                        }
                    break;
                    }
            nn2 = nn2->next;                       
            }            
        nnn = nnn->next;
        }
    return found;
}


