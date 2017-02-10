/***********************************************************************
*
* MODULE       : STRUTIL.H
* PART OF      : Utility modules
* DESCRIPTION  : Implements some string handling routines.
*
*                    Copyright (c) 1993-1995 Testwell Oy
************************************************************************
*/

/*************************************************************************
 *
 * FUNCTION  : str_delete_blanks
 * PURPOSE   : Deletes blank characters from the start and from the
 *               beginning of a string
 * ARGUMENTS : - string: string from which the blanks will be deleted
 * RETURNS   : void
 *
 *************************************************************************/

void str_delete_blanks(
    char string[]);

/*************************************************************************
 *
 * FUNCTION  : str_toupper
 * PURPOSE   : Converts chars in string to upper case.
 * ARGUMENTS : - string: string to convert
 * RETURNS   : - the address of the converted string
 *
 *************************************************************************/

char *str_toupper(
    char string[]);


