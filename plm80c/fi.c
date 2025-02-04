/****************************************************************************
 *  fi.c: part of the C port of Intel's ISIS-II plm80c             *
 *  The original ISIS-II application is Copyright Intel                     *
 *																			*
 *  Re-engineered to C by Mark Ogden <mark.pm.ogden@btinternet.com> 	    *
 *                                                                          *
 *  It is released for hobbyist use and for academic interest			    *
 *                                                                          *
 ****************************************************************************/

#include "plm.h"

void FindInfo()
{
    word i;

    if (SymbolP(curSymbolP)->infoP == 0) {
        curInfoP = 0;
        return;
    }
    i = blockDepth;
    while (i != 0) {
        FindScopedInfo(procChains[i]);
        if (curInfoP != 0)
            return;
        i = i - 1;
    }
}
