/**
*		@file MapMaze.c
*		@brief Fully maps the maze,
*
*		Maps the full maze including placing nodes
*       and finding the connections between those
*       Nodes.
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
 * calls all the other functions to map out the whole
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

/**
 * @brief Connects the parent node to the current cell.
 * 
 * Adds a connection to the parent Node to the current cell, also
 * adds the connection back from current cell to parent Node. If the
 * current cell is not a Node, it creates a new node to use.
 * 
 * @param mouse
 */
void ConnectNodes(Mouse* mouse);

/**
 * @breif Used to get to new areas.
 * 
 * Pops the first item from the openlist and explores the cell
 * at that index. If the cell is not accessible from the current
 * cell, then it backtracks until it finds it.
 * 
 * @param mouse
 * @param openlist
 */
void ExploreNewCell(Mouse* mouse, Stack* openlist, Stack* history);

/**
 * @brief identify in which direction a cell is.
 * 
 * Identifies which direction an adjacent cell is in, if the
 * target cell is not adjacent, then 0 is returned.
 * 
 * @param mouse
 * @param target    the cell that the mouse is trying to get to.
 * @return          the direction of the adjacent cell.
 */
unsigned int identifyDirection(Mouse* mouse, unsigned int target);

/**
 * @brief move mouse into an adjacent cell in the direction given.
 * 
 * Moves the physical mouse into a cell geven in the direction param.
 * 
 * @param mouse
 * @param direction     the direction in which the adjacent cell is.
 */
void moveToAdjacentCell(Mouse* mouse, unsigned int direction);

#endif	/* MAPMAZE_H */

