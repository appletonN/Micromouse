/**
 *		@file simulator.c
 *		@brief Display the maze for debugging
 *
 *		Adds functionality for the simulator to be used. This will
 *		mean that the program can be run without using the physical
 *		Micromouse. The functions have the same name as in the non-
 *		simulator functions so by defining SIMULATOR in the main it
 *		will run these instead of the actual mouse integratiion funtions.
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	22/2/19
 */

#include "MappingFunctions.h"

/**
 * @brief used to find if a wall is there or not.
 *
 * contains the array of the actual maze walls and uses the index and
 * direction of the mouse to determine if there is a wall or not. This is
 * a simulated version of reading the sensor values and passing a 1 or 0
 * depending on the status of the wall.
 *
 * @param index			index that the mouse is at within the maze.
 * @param direction		direction register of the mouse.
 */
int readSensors(int index, int direction);

/**
 * @brief Print out the maze to stdout.
 *
 * Prints the maze in it's current state to the standard output, including
 * state of the LEDs, position and direction of the mouse and the mouse's 
 * model of the maze - this will display the walls and nodes graphically.
 *
 * @param mouse			representation of the mouse to be referenced.
 */
 void printStatus(Mouse* mouse);