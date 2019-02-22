/**
 *		@file globalFunctions.h
 *		@brief Prototype the global functions, structures
 *		and data types.
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

/** @brief Number of Debugging LEDs on the mouse */
#define LEDN 8

	/** height of the maze to be solved. If maze height is not known, set as largest value maze width that could occour. */
	#define HEIGHT	8
	/** marker to check if dimensions already defined. */
	#define MAX_DIMENSIONS
#endif
///@}

/** @brief Number of Debugging LEDs on the mouse */
#define LEDN 8

/**
 * @brief Connection between 2 nodes.
 */
struct connection{
	Node* connection;					/**< Pointer to the connected Node */
	unsigned int cost;					/**< Cost to get to connected Node */
	unsigned int direction : 4; 		/**< direction to exit cell to get to connected Node */
};

/**
 * @brief All info about a given cell
 */
typedef struct cell {
	unsigned int walls : 4;				/**< Layout of walls; 1 denotes a wall, 0 is no wall. bit-order is N>E>S>W */
	unsigned int noOfWalls : 3;			/**< Number of walls of cell. can never be more than 4 */
	unsigned int isNode : 1;			/**< Marks whether cell is a Node or not */
	Node* nodeAddress;					/**< Pointer to Node that references this cell (if applicable) */
} cell;

/**
 * @brief All info about a given Node.
 */
typedef struct Node {
	unsigned int index;					/**< index of the cell that this node references */
	unsigned int isEnd : 1;				/**< Marks whether the Node is at the centre of the maze */
	unsigned int noOfConnections : 3; 	/**< Number of Nodes connected to this one */

	struct connection connections[3];	/**< Array  of connected nodes */
	int distToCentre = -1;				/**< Shortest distance found to centre of maze. -1 represents infinite distance */  
} Node;

/**
 * @brief Contains the representation of the maze itself
 */ 
struct Maze {
	cell cellno[HEIGHT][WIDTH];			/**< Array of cells used as the maze representation */
};

/**
 * @brief Representation of the Mouse in virtual space
 *
 * represents the mosue that inhabits the virtual maze. including physical
 * attributes and debugging info.
 */
struct Mouse {
	unsigned int dir : 4;				/**< Direction the mouse is facing */
	unsigned int index;					/**< Position of the mouse within the maze */
	unsigned int LEDs : LEDN; 			/**< State of each debugging LED on the mouse */
	Maze* maze;
};

/**
 * @brief Turn the right mouse within the virtual maze.
 *
 * Bitshifts the direction register of the mouse right by N places.
 * Also corrects for if the 1 bit falls off the end of the register.
 *
 * @param N 	Number of turns to make.
 * @param mouse Pointer to the mouse representation.
 */
void turn(int N, struct Mouse* mouse);

