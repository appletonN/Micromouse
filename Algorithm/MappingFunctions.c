/**
 *		@file globalFunctions.c
 *		@brief Hold all the global functions, structures
 *		and data types.
 *
 *		Functions are used throughout the program, 
 *		mostly to edit the maze information.  
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	23/2/19
 */

#include "MappingFunctions.h"


void turn(int N, Mouse* mouse)
{
	int i;

	for (i=0; i<N; i++)
	{ 
		mouse->dir = mouse->dir >> 1;

		if (mouse->dir == 0x00) 	//if mouse has shifted too far right
			mouse->dir = 0x08; 		//bring it back around to 1000 (facing North)
	}
}