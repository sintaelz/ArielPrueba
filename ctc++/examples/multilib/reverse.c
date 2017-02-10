/***********************************************************************
*
* MODULE       : REVERSE.C
* PART OF      : Utility modules
* DESCRIPTION  : Implements reversing of a string
*
*                    Copyright (c) 1993-1995 Testwell Oy
************************************************************************
*/
#include <string.h>
#include "reverse.h"

/*************************************************************************
 *
 * FUNCTION  : reverse
 * PURPOSE   : Reverses charachters of a string
 * ARGUMENTS : - string: string to reverse
 * RETURNS   : void
 *
 *************************************************************************/

void reverse(char *string)
{
    char *end = string + strlen(string) - 1;
    char c;

    while (string < end)
    {
        c = *string;
        *string++ = *end;
        *end-- = c;
    }
}
