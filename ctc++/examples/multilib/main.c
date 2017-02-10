

#include <stdio.h>
#include "strutil.h"
#include "reverse.h"

static char s[] = "  This is a string";

int main(void)
{
    printf("Original string: \"%s\"\n", s);
    str_delete_blanks(s);
    printf("Blanks deleted : \"%s\"\n", s);
    (void) str_toupper(s);
    printf("Upper case     : \"%s\"\n", s);
    reverse(s);
    printf("Reversed       : \"%s\"\n", s);

    return 0;
}
