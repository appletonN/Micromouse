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

/** 
 * @brief Use simulator or Mouse.
 * 
 * If the variable is set to 1, the simulator will be used. Otherwise the target will be
 * the actual mouse.
 */
#define SIMULATOR 1

#if SIMULATOR
	#include "simulator.h"
#endif


#include "MappingFunctions.h"

int main(void)
{
	/** @brief representation of the mouse */
	Mouse* mouse;

	
	return 0;
}