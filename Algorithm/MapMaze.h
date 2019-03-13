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
 * @brief Representation of the Mouse in virtual space
 *
 * represents the mouse that inhabits the virtual maze. including physical
 * attributes and debugging info.
 */
typedef struct Mouse
{
	unsigned int dir : 4;				/**< Direction the mouse is facing */
	unsigned int index;					/**< Position of the mouse within the maze */
    unsigned int DeadEnd : 1;           /**< Marks whether backtracking from a dead end */
	unsigned int LEDs;              	/**< What is being displayed on the LEDs using Timer 5 */
	struct Maze* maze;                  /**< contains the mouse's model of the maze */
    unsigned int parentNode;            /**< index of Node last viseted in nodelist, next node found will be connected to this */
    struct connection currentConnection;/**< Info about current exploration from parent Node */
} Mouse;


/**
 * @brief main maze-mapping function.
 * 
 * calls all the other functions to map out the whole
 * reachable maze.
 * 
 * @param mouse     representation of the mouse in the maze.
 * @param nodelist  list of all the Nodes in the maze. can be considered the Nodemap.
 * @return          the index of the Node the mouse is currently at in the nodelist
 */
void mapmaze(struct Maze* mazeArg, Node* nodelist);

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
void SetupMapping(Mouse* mouse, Stack* openlist, Node* nodelist);

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
unsigned int createNode(Mouse* mouse, unsigned int index, Node* nodelist);

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
void checkcurrentcell(Mouse* mouse, Stack* openlist, Node* nodelist, Stack* history);

/**
 * @brief Connects the parent node to the current cell.
 * 
 * Adds a connection to the parent Node to the current cell, also
 * adds the connection back from current cell to parent Node. If the
 * current cell is not a Node, it creates a new node to use.
 * 
 * @param mouse
 * @param nodelist
 * @param dir           direction in which the mouse entered the cell to be connected to the parent.
 */
void ConnectNodes(Mouse* mouse, Node* nodelist, unsigned int dir);

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
void ExploreNewCell(Mouse* mouse, Stack* openlist, Stack* history, Node* nodelist);

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

/**
 * @brief corrects any known but unexplored dead-ends.
 * 
 * Checks every cell in the maze, if the cell is unexplored and has 3
 * walls, then it will mark the cell as explored. This will get the 
 * cell removed from the openlist during the mapmaze function.
 * 
 * @param maze      the maze that needs to be checked.
 */
void virtualMouse(Mouse* mouse, Node* nodelist);

/**
 * @brief checks one cell for dead end and corrects it.
 * 
 * checks if cell is dead end by looking at wall pattern. If it is, it
 * sets all the walls to 1, moves into the cell that connects to it and
 * runs the check on that cell too. This means the "virtual mouse" will 
 * move back through the dead-end corridor, correcting it cell by cell,
 * until it gets to either a non-fully-mapped cell or the end of that
 * corridor.
 * 
 * @param maze      The maze in which the cell being checked is held.
 * @param index     The index of the cell within the maze.
 */
void VMcheck(Mouse* mouse, int index, Node* nodelist);

void DestroyNode(Mouse* mouse, Node* nodelist, unsigned int index);


#endif	/* MAPMAZE_H */