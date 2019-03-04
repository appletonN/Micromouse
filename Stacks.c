#include <stdlib.h>
#include "Stacks.h"


void push(Stack* stack, unsigned int Newdata)
{   
    
    // add data to element
    stack->data[stack->head] = Newdata;
    // increment head
    stack->head++;
}

unsigned int pop(Stack* stack)
{
    stack->head--;
    return stack->data[stack->head];
}