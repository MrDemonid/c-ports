/****************************************************************************
 *  loc9.c: part of the C port of Intel's ISIS-II locate             *
 *  The original ISIS-II application is Copyright Intel                     *
 *																			*
 *  Re-engineered to C by Mark Ogden <mark.pm.ogden@btinternet.com> 	    *
 *                                                                          *
 *  It is released for hobbyist use and for academic interest			    *
 *                                                                          *
 ****************************************************************************/

#include "loc.h"

byte ToUpper(byte ch)
{
	if (ch < 'a' )
		return ch;
	if (ch > 'z' )
		return ch;
	return ch & 0xdf;
} /* ToUpper */
