/* File io.c ------------------------------------------------- */
#include <stdio.h>
#include "io.h"
/* Prompt for an unsigend int value and return it */
unsigned io_ask()
{
    unsigned    val;
    int         amount;

    printf("Enter a number (0 for stop program): ");
    if ((amount = scanf("%u", &val)) <= 0) {
        val = 0;    /* on 'non sense' input force 0 */
    }
    return val;
}    

/* Display an unsigned int value and associated string */
void io_report(unsigned val, char* str)
{
    printf("%u %s\n\n", val, str);
}
