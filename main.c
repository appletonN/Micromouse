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

int main(void)
{
    
	Mouse mouse;
    
    mapmaze(&mouse);
	
	return 0;
}