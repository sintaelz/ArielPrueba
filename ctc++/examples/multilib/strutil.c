/***********************************************************************
*
* MODULE       : STRUTIL.C
* PART OF      : Utility modules
* DESCRIPTION  : Implements some string handling routines.
*
*                    Copyright (c) 1993-1995 Testwell Oy
************************************************************************
*/

/********************** STANDARD LIB. INCLUDES *************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/********************** APPL. SPECIFIC INCLUDES ************************/

#include "strutil.h"

/************************ PUBLIC FUNCTIONS *****************************/

/*************************************************************************
 *
 * FUNCTION    : str_delete_blanks
 * DESCRIPTION :
 *
 *************************************************************************/

void str_delete_blanks(
    char string[])
{
    const char *start;
    int        length;
    int        i;

    start = string + strspn(string," \t\n");
    length = strlen(start);
    while (length > 0 &&
           (start[length - 1] == ' ' ||
            start[length - 1] == '\t' ||
            start[length - 1] == '\n'))
        length--;

    for (i = 0; i < length; i++)
        string[i] = start[i];
    string[i] = '\0';
}


/*************************************************************************
 *
 * FUNCTION    : str_toupper
 * DESCRIPTION :
 *
 *************************************************************************/

char *str_toupper(
    char string[])
{
    int i = 0;

    while (string[i] != 0)
    {
        string[i] = (char) (islower(string[i]) ?
            toupper(string[i]) : string[i]);
        i++;
    }

    return string;
}


