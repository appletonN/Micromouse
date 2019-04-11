#include <stdlib.h>
#include "Stacks.h"


void push(Stack* stack, unsigned char Newdata)
{   
    
    // add data to element
    stack->data[stack->head] = Newdata;
    // increment head
    stack->head++;
}

unsigned char pop(Stack* stack)
{
    return stack->data[--stack->head];
}
