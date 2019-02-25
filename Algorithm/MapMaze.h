/**
*		@file MapMaze.c
*		@brief Fully maps the maze,
*
*		Maps the full maze including placing nodes
*       and finding the connections between those
*       Nodes.s
*
*
*		@author		Nick Appleton @ UWE Robotics
*
*		@date	24/2/19
*/

#ifndef MAPMAZE_H
#define	MAPMAZE_H

#include "../Stacks.h"

/**
 * @brief main maze-mapping function.
 * 
 * calls all the other fuctions to map out the whole
 * reachable maze.
 * 
 * @param mouse     representation of the mouse in the maze.
 */
void mapmaze(Mouse* mouse);

/**
 * @brief sets up the mouse ready to map out the maze.
 * 
 * Initialises the mouse's maze model as all 0s with a 
 * border of 1s. Sets the mouse's index to 0 and direction
 * to 0b1000 (North). Creates the start Node and seets it 
 * as the parent node.
 * 
 * @param mouse
 */
void SetupMapping(Mouse* mouse);

/**
 * @brief creates a new node.
 * 
 * Initialises all the Node variables, sets the cell at
 * the correct index to a node and adds a pointer to the
 * new node.
 * 
 * @param mouse
 * @param index     index at which the new Node is to be created
 * @return          a pointer to the newly created node
 */
Node* createNode(Mouse* mouse, unsigned int index);

/**
 * @brief updates info on the cell currently occupied.
 * 
 * This includes correcting all the walls in the current
 * cell and all adjacent cells, adding unexplored adjacent
 * cells to the openlist and changing the cells properties
 * to reflect it's status (it's now been explored).
 * 
 * @param mouse     representation of the mouse in the maze.
 * @param openlist  The stack of unexplored cells.
 */
void checkcurrentcell(Mouse* mouse, Stack* openlist);

#endif	/* MAPMAZE_H */

