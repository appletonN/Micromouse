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
 *		@date	21/2/19
 */

#include "globalFunctions.h"


void turn(int N, Mouse* mouse){
	int i;

	for (i=0; i<N; i++)
	{ 
		mouse >> 1;

		if (mouse == 0) 	//if mouse has shifted too far right
			mouse = 8; 		//bring it back around to 1000 (facing North)
	}
}