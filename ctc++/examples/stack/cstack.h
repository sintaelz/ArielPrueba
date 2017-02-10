// ---------------------------------------------------------------------
//
// Class    : STACK from STACK.HXX
// Parents  : 
// Friends  :
// Part of  :
// Created  : 12 Oct 1990 by A.C.Coder
// Abstract : This module implements a dynamic stack for integers.
//            Other stacks can be easily constructed by changing the
//            defintion of STACK_ITEM type. Note: STACK_ITEM should not
//            be any array type.
// Revision : 1.0, 12 Oct 1990 12:00:00, by ACC
//
//              Copyright (C) 1990 Sample Software Ltd.
// ---------------------------------------------------------------------
// Revision history
//
// 1.0: Initial revision
//
// ---------------------------------------------------------------------

#ifndef STACK_HXX
#define STACK_HXX
 
// --------------------------- PUBLIC TYPES ----------------------------

//
// STACK_ITEM: The items stored in the stack are of this type
//

typedef int STACK_ITEM;

// ------------------------- CLASS DECLARATION -------------------------

// ---------------------------------------------------------------------
//
// Function  : Stack::Stack
// Purpose   : Constructor
// Arguments : None
// Returns   :
// See also  :
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// Function  : Stack::~Stack
// Purpose   : Destructor
// Arguments : None
// Returns   :
// See also  :
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// Function  : Stack::clear
// Purpose   : Make the stack empty
// Arguments : None
// Returns   : void
// See also  :
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// Function  : Stack::empty
// Purpose   : Check whether the stack is empty
// Arguments : None
// Returns   : 1, if stack is empty, 0 otherwise
// See also  :
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// Function  : Stack::push
// Purpose   : Push element onto the stack. push() is not protected
//             against running out of memory.
// Arguments : - item: the item to be pushed onto the stack
// Returns   : void
// See also  :
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// Function  : Stack::pop
// Purpose   : Pop value out of stack. If stack is empty, the returned
//             value has no meaning.
// Arguments : None
// Returns   : The popped element
// See also  :
//
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//
// Function  : Stack::top
// Purpose   : Return the value of the topmost element of the stack
//             without popping it away. If stack is empty, the returned
//             value has no meaning.
// Arguments : None
// Returns   : The value of the topmost element of the stack.
// See also  :
//
// ---------------------------------------------------------------------

class Stack
{
public:
    Stack();
    ~Stack();
    void clear();
    unsigned height();
    void push(
        STACK_ITEM item);
    STACK_ITEM pop();
    STACK_ITEM top();
protected:
    STACK_ITEM &element(unsigned index);
private:
    unsigned   myheight; // current height of stack
    unsigned   size;   // current size (max. height)
    STACK_ITEM *value; // the data in stack
};

// --------------------- INLINE MEMBER DEFINTIONS ----------------------


#endif
