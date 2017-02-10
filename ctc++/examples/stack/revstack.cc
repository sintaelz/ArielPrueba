#include "cstack.h"
#include "revstack.h"

RevStack::RevStack()
{

}

RevStack::~RevStack()
{

}

void RevStack::reverse()
{
    unsigned   i;
    unsigned   half = height() / 2;

    for (i = 0; i < half; i++)
    {
        STACK_ITEM swapper = element(i);
        element(i) = element(height() - i - 1);
        element(height() - i - 1) = swapper;
    }
}
