/**
 *		@file MappingFunctions.h
 *		@brief contains all functions, structures
 *		and data types used by most files.
 *
 *		Functions are used throughout the program, 
 *		mostly to edit the maze information. Structures that are 
 *		used to store info about the maze are defined in this header
 *		so can be accessed from any file that includes it. This will
 *		be necessary for almost all navigating of the maze. 
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	21/2/19
 */

#ifndef MAPPING_FUNCTIONS_H
#define MAPPING_FUNCTIONS_H

/**
 * @name Maze Max Dimensions
 *
 * @brief The maximum dimensions the maze can be.
 *
 * This section will determine the size of most of the arrays and so
 * should be set to the smallest values that will definitely contain
 * the entire maze. If it is set to small then the mouse will not explore
 * the whole maze.
 */
///@{
#ifndef MAX_DIMENSIONS 
	/** Width of the maze to be solved. If maze width is not known, set as largest value maze width that could occour. */
	#define WIDTH	6
	/** height of the maze to be solved. If maze height is not known, set as largest value maze width that could occour. */
	#define HEIGHT	8
	/** marker to check if dimensions already defined. */
	#define MAX_DIMENSIONS
#endif
///@}


#include "../Stacks.h"

/**
 * @brief maximum number of Nodes that can be stored.
 * 
 * describes the amount of memory needed to store the list of Nodes.
 * Will not be able to store more Nodes than this.
 */
#define MAX_NODES 15 

/**
 * @brief cost of the movements between Nodes.
 */
///@{
#define TURN_COST 3
#define STRAIGHT_COST 1
///@}


/**
 * @brief Connection between 2 nodes.
 */
struct connection
{
	unsigned char connectedCell;			/**< Index of the connected Node in th maze */
	unsigned int cost;					/**< Cost to get to connected Node */
	unsigned int direction : 4; 		/**< direction to exit cell to get to connected Node */
};

/**
 * @brief All info about a given Node.
 */
typedef struct Node
{
	unsigned char index;					/**< index of the cell that this node references */
	unsigned int isEnd : 1;				/**< Marks whether the Node is at the centre of the maze */
	unsigned int noOfConnections : 3; 	/**< Number of Nodes connected to this one */

	struct connection connections[4];	/**< Array  of connected nodes */
	int distToStart;                    /**< Shortest distance found to centre of maze. -1 represents infinite distance */  
    unsigned char via;                            /**< Node shortest route goes through to get here. */
} Node; 

/**
 * @brief All info about a given cell
 */
typedef struct cell
{
	unsigned int walls : 4;				/**< Layout of walls; 1 denotes a wall, 0 is no wall. bit-order is N>E>S>W */
	unsigned int noOfWalls : 6;			/**< Number of walls of cell. can never be more than 4 */
    unsigned int explored : 1;          /**< Marks whether cell has been visited */
	unsigned int isNode : 1;            /**< Marks whether cell is a Node or not */
	unsigned char nodeAddress;			/**< Index of Node that references this cell in nodelist */
} cell;

/**
 * @brief Contains the representation of the maze itself
 */ 
struct Maze
{
	cell cellno[HEIGHT][WIDTH];			/**< Array of cells used as the maze representation */
};

/**
 * @brief Turn the right mouse within the virtual maze.
 *
 * Bitshifts the direction register of the mouse right by N places.
 * Also corrects for if the 1 bit falls off the end of the register.
 * 
 * @memberof mouse
 *
 * @param N 	Number of turns to make.
 * @param dir   Current direction to be turned.
 * @return      New direction after turning
 */
unsigned char turn(unsigned char N, unsigned char dir);

/**
 * @brief Changes the index of the mouse to move into an adjacent cell.
 *
 * looks at the direction the mouse is facing and changes the index by the
 * right amount to move the mouse into the adjacent cell in that direction.
 *
 * @memberof mouse
 * 
 * @param index     index to be incremented.
 * @param dir       direction to move into.
 * @return          the index having been incremented into the adjacent cell.
 */
unsigned char incrementIndex(unsigned char index, unsigned char dir);

#endif /* MAPPING_FUNCTIONS_H */
