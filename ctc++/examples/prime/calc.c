/* File calc.c ----------------------------------------------- */
#include "calc.h"
/* Tell if the argument is a prime (ret 1) or not (ret 0) */
int is_prime(unsigned val)
{
    unsigned divisor;

    if (val == 1 || val == 2 || val == 3)
        return 1;
    if (val % 2 == 0)
        return 0;
    for (divisor = 3; divisor < val / 2; divisor += 2)
    {
        if (val % divisor == 0)
            return 0;
    }
    return 1;
}
