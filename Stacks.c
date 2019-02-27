/**
 *		@file Stacks.c
 *		@brief Implement stack interaction.
 *
 *      contains functions to push and pop stackitems, as defined
 *      in Stacks.h.
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	23/2/19
 */

#include <stdlib.h>
#include "Stacks.h"


void push(Stack* stack, unsigned int Newdata)
{
    // allocate memory to new item
    struct stackitem* newelement;
    newelement = malloc(sizeof(struct stackitem));
    
    
    // add data to element
    newelement->data = Newdata;
    // add pointer to current top of stack
    newelement->nextitem = *stack;
    
    // move stack pointer to the new item
    *stack = newelement;
}

unsigned int pop(Stack stack)
{
    // mark top element
    Stack temp = stack;
    
    //point to item below current
    stack = stack->nextitem;
    
    //extract data and free top element
    unsigned int data = temp->data;
    free(temp);
    
    return data;
}