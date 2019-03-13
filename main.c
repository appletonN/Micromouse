/**
*		@file main.c
*		@brief this is the main file that controls the
*		robot.
*
*		Contains the mission planner and runs all
*		initialisation of maze. offloadds most functionality
*		to external functions.
*
*
*		@author		Nick Appleton @ UWE Robotics
*
*		@date	21/2/19
*/

#include "Algorithm/MappingFunctions.h"
#include "Algorithm/MapMaze.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    //create maze
    struct Maze Cellmaze;
    
    //create array of Nodes
    Node nodelist[MAX_NODES] = {{0}};
    
    //Map the entire maze
    mapmaze(&Cellmaze, nodelist);
     
    
    printf("done, bye bye\n\n\n");
	
	return 0;
}