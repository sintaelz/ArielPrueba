// ---------------------------------------------------------------------
//
// Class    : STACK from STACK.CXX
// Parents  :
// Friends  :
// Part of  :
// Created  : 12 Oct 1990 by A.C.Coder
// Abstract : This module implements a stack.
// Revision : 1.0, 12 Oct 1990 12:00:02, by ACC
//
//              Copyright (C) 1990 Sample Software Ltd.
// ---------------------------------------------------------------------
// Revision history
//
// 1.0: Initial revision
//
// ---------------------------------------------------------------------

// ----------------------- APPLICATION INCLUDES ------------------------

#include "cstack.h"

// ------------------------- PRIVATE CONSTANTS -------------------------

//
// - SIZE_STEP: defines the number of new stack elements allocated
//   each time the stack becomes full
//

int const SIZE_STEP = 40;

// ---------------------------------------------------------------------
//
// Function    : Stack::Stack
// Description : Initializes the private members, all to 0. Memory is
//               not allocated before the first push.
// Updates     : - height
//               - size
//               - value
//
// ---------------------------------------------------------------------

Stack::Stack():
    myheight(0),
    size(0),
    value(0)
{
    // Nothing
}

// ----------------------------------------------------
//
// Function    : Stack::~Stack
// Description : 
// Updates     : - value
//
// ----------------------------------------------------

Stack::~Stack()
{
    delete[] value;
}

// ----------------------------------------------------
//
// Function    : Stack::clear
// Description : 
// Updates     : - height
//
// ----------------------------------------------------

void Stack::clear()
{
    myheight = 0;
}

// ----------------------------------------------------
//
// Function    : Stack::empty
// Description : 
// Updates     : 
//
// ----------------------------------------------------

unsigned Stack::height()
{
    return myheight;
}

// ----------------------------------------------------
//
// Function    : Stack::push
// Description : 
// Updates     : - height
//               - size
//               - value
//
// ----------------------------------------------------

void Stack::push(
    STACK_ITEM item)
{
    if (myheight >= size)
    {
        size += SIZE_STEP;
        STACK_ITEM *new_value = new STACK_ITEM[size];
        for (unsigned i = 0; i < myheight; i++)
            new_value[i] = value[i];
        delete[] value;
        value = new_value;
    }
    value[myheight++] = item;
}

// ----------------------------------------------------
//
// Function    : Stack::pop
// Description : 
// Updates     : - height
//
// ----------------------------------------------------


STACK_ITEM Stack::pop()
{
    STACK_ITEM item = -2147483648;

    if (myheight > 0)
        item = value[--myheight];

    return item;
}

// -----------------------------------------------------
//
// Function    : Stack::top
// Description : 
// Updates     : 
//
// -----------------------------------------------------

STACK_ITEM Stack::top()
{
    STACK_ITEM item = -2147483648;

    if (myheight > 0)
        item = value[myheight - 1];

    return item;
}

STACK_ITEM &Stack::element(unsigned index) { return value[index]; }
