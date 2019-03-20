/**
 *		@file Dijekstra.h
 *		@brief dijekstra's function and cocktail sort.
 * 
 *      Cocktail sort is used to order the priority queue 
 *      after each time a Node has finished being checked 
 *      by the dijekstra's function. 
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	16/3/19
 */


#ifndef DIJEKSTRA_H
#define	DIJEKSTRA_H

#include "MappingFunctions.h"

/**
 * @brief Find fastest route between 2 Nodes.
 * 
 * Uses dijekstra's algorithm to find the shortest route thorugh the
 * Nodemap. It routes through the maze, pushing each move that needs to 
 * be made to a stack. This stack is then returned.
 * 
 * The stack's format is: initial on-the-spot turn to face the correct
 * direction, then it has the initial forward move (or 0 if there isn't
 * one). From there it alternates between each forward move and each turn
 * required to get into the next cell. The turns include the move into the
 * Next cell. Last item in stack is a straight, moves into the end Node cell.
 * 
 * @param maze      maze to search through
 * @param nodemap   nodemap of the maze given
 * @param start     location of the Node to start from
 * @param end       location of the Node to get to
 * @param startdir  direction the mouse is facing at the start
 * @return          satck of moves to get from start to finish
 */
Stack dijekstra( struct Maze* maze, Node nodemap[MAX_NODES], Node* start, Node* end, int startdir);

/**
 * @brief cocktail sorts given array.
 * 
 * @param arr       array to be sorted
 */
void cocktail(Node* arr[MAX_NODES]);


#endif	/* DIJEKSTRA_H */

