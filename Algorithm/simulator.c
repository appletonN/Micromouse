/**
 *		@file simulator.c
 *		@brief Display the maze for debugging
 *
 *		Displays the maze live on stdout for when the micromouse
 *		is not available. The simulator displays the current status
 *		of teh maze as well as teh status of the mouse including it's
 *		location, the direction it is facing and the status of all
 *		the debugging LEDs.  
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	21/2/19
 */

#include "simulator.h"

#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


/**
 * @name Maze Actual Simulated Dimensions
 *
 * @brief The actual size of the simulated maze.
 *
 * This section defines sizes that the simulated maze actually is.
 * The maze is used in the readSensors function as all the other functions
 * will refer to the mouses view of the maze.
 */
///@{
#define ACTUAL_WIDTH 6		/**< the Width the simulated maze actually is */
#define ACTUAL_HEIGHT 6		/**< the Height the simulated maze actually is */
///@}


int readSensor(int index, int direction)
{

	static int completeMaze[ACTUAL_HEIGHT][ACTUAL_WIDTH][4] = {
		{ {1,0,0,1}, {1,0,0,0}, {1,1,0,0}, {1,0,0,1}, {1,1,0,0}, {1,1,0,1} },
		{ {0,1,0,1}, {0,1,1,1}, {0,1,1,1}, {0,1,0,0}, {0,0,1,1}, {0,1,0,0} },
		{ {0,0,1,1}, {1,1,0,0}, {1,0,0,1}, {0,1,0,0}, {1,1,0,1}, {0,1,0,1} },
		{ {1,0,0,1}, {0,1,0,0}, {0,0,1,1}, {0,1,1,0}, {0,0,1,1}, {0,1,0,0} },
		{ {0,1,0,1}, {0,1,0,1}, {1,0,0,1}, {1,1,1,0}, {1,0,0,1}, {0,1,0,0} },
		{ {0,0,1,1}, {0,0,1,0}, {0,0,1,0}, {1,0,1,0}, {0,1,1,0}, {0,1,1,1} },
	};

	/** @brief Which wall is being checked */
	int wall = 0;

	switch (direction) {
		case 0x02:
			wall++;
		case 0x04:
			wall++;
		case 0x08:
			wall++;
	}

	if (completeMaze[index+wall])
		return 1;
	else
		return 0;

}


 void printStatus(Mouse* mouse)
 {
 	int i, j;

 	for (i = HEIGHT-1 ; i<=0 ; i--)	//for every row (top-down)
 	{
 		//Start by drawing the south facing walls of the row
 		for (j = 0; i < WIDTH ; i++)
 		{
 			
 			if (mouse->maze->cellno[i][j].walls | 0x04) {
 				//print a wall if there is a wall to the south of the cell
 				printf("+---");

 			} else {
 				printf("+   ");
 			}

 		} //FOR j

 		printf("+\n"); 	//finish off row


 		//Next draw the East walls, and cell info
 		for (j = 0; i < WIDTH ; i++)
 		{ 
 			//draw east wall
 			if (mouse->maze->cellno[i][j].walls | 0x08) {
 				//print a wall if there is a wall to the south of the cell
 				printf("|");

 			} else {
 				printf(" ");
 			}

 			//draw cell info
 			// if (current cell == mouse cell)
 			if ( WIDTH*i + j == mouse->index ){
 				//print the mouse in red faving the correct direction
 				switch (mouse->dir){
 					case 0x01:
 						printf(ANSI_COLOR_RED "/^\\" ANSI_COLOR_RESET);
 						break;
 					case 0x02:
 						printf(ANSI_COLOR_RED " > " ANSI_COLOR_RESET);
 						break;
 					case 0x04:
 						printf(ANSI_COLOR_RED " v " ANSI_COLOR_RESET);
 						break;
 					case 0x08:
 						printf(ANSI_COLOR_RED " < " ANSI_COLOR_RESET);
 						break;
 				}//SWITCH

 			} else if ( mouse->maze->cellno[WIDTH*i + j]->isNode ) {
 				//if it's a node then print a Magenta N
 				printf(ANSI_COLOR_MAGENTA " N " ANSI_COLOR_RESET);
 			}
 		} //FOR j

 	} //FOR i
 }