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


/** 
 * @brief Linked list implementation of each item in a stack. 
 */
struct stackitem 
{
    unsigned int data;              /**< contains the data that is to be stored in this item of teh struct. */
    struct stackitem* nextitem;     /**< points to the item below in the stack */
};

/**
 * @brief points to the head of a stack.
 * 
 * Currently stacks DO NOT have a max size. If this becomes
 * an issue, this can be changed to a structure containing 
 * the pointer as well as a max-size. This then needs to be
 * chekced when pushing and popping.
 */
typedef struct stackitem* Stack;

/**
 * @brief pushes item onto a stack.
 * 
 * creates a new stackitem which contains the new data and 
 * points to the current head of the stack. The stack pointer
 * is then moved to point at the new stackitem.
 * 
 * @param stack        the stack that the data will be pushed to.
 * @param Newdata      the data that will be pushed to the stack.
 */
void push(Stack* stack, unsigned int Newdata);

/**
 * @brief pops an item from the top of the stack.
 * 
 * returns the data from the top-most stackitem, points the stack
 * pointer to the item below where it was and frees the topmost
 * item.
 * 
 * @param stack     the stack from which the data will be popped.
 */
unsigned int pop(Stack* stack);


#endif	/* STACKS_H */

