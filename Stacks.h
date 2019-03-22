/**
 *		@file Stacks.h
 *		@brief Defines everything needed to implement stacks.
 *
 *      Includes the stack datatype, as well as the stackitem
 *      structure used to creat stacks. Stacks can have data
 *      pushed to them and popped from them. Uses Linked lists 
 *      to do this.
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	23/2/19
 */


#ifndef STACKS_H
#define	STACKS_H

#include "Algorithm/MappingFunctions.h"

/** 
 * @brief array of data that is the Stack.
 * 
 * The size of the stack equal to number of cells in the maze.
 */
typedef struct Stack {
    unsigned char data[WIDTH*HEIGHT*2];
    unsigned char head;
} Stack ;

/**
 * @brief pushes item onto a stack.
 * 
 * creates a new stackitem which contains the new data and 
 * points to the current head of the stack. The stack pointer
 * is then moved to point at the new stackitem.
 * 
 * @memberof Stack
 * 
 * @param stack        the stack that the data will be pushed to.
 * @param Newdata      the data that will be pushed to the stack.
 */
void push(Stack* stack, unsigned char Newdata);

/**
 * @brief pops an item from the top of the stack.
 * 
 * returns the data from the top-most stackitem, points the stack
 * pointer to the item below where it was and frees the topmost
 * item.
 * 
 * @memberof Stack
 * 
 * @param stack     the stack from which the data will be popped.
 */
unsigned char pop(Stack* stack);


#endif	/* STACKS_H */

