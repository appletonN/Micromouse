/**
*		@file Motors.c
*		@brief Motor Functions and Defines
*
*		@author		Christian Woof @ UWE Robotics
*
*/

#ifndef MOTORS_H
#define	MOTORS_H

#include "../Stacks.h"

/**
 * @brief Encoder Counts
 */
//@{
//Linear Movement encoder counts
//  0.5

#define ML_F0_5 0           //
#define MR_F0_5 0           //
//  1
#define ML_F1 0             //1
#define MR_F1 0             //1
//  2
#define ML_F2 1
#define MR_F2 1
//  3
#define ML_F3 1
#define MR_F3 1
//  4
#define ML_F4 1
#define MR_F4 1
//  5
#define ML_F5 1
#define MR_F5 1
//  6
#define ML_F6 1
#define MR_F6 1
//  7
#define ML_F7 1
#define MR_F7 1
//  8
#define ML_F8 1
#define MR_F8 1

//Stopping velocity curve encoder count
#define stopEnc 0           //10
#define turnStopEnc 0       //10

//Fast Turning encoder counts
#define inner_L 0   //215
#define outer_L 0   //215
#define inner_R 0   //215
#define outer_R 0   //215

//Turning encoder counts
#define ML_90L  0    //215
#define MR_90L  0    //215
#define ML_90R  0    //215
#define MR_90R  0    //215
#define ML_180  0    //430
#define MR_180  0    //430
//@}

/**
 * @brief PWM speed values
 */
//@{
//Max Linear Movement Motor Speed
#define MLSpeed 0       //15000
#define MRSpeed 0       //15000
#define CreepSpeed 0    //2000

//Turning Speeds for 90 Degrees
#define MLTurnSpeed 0    //16000
#define MRTurnSpeed 0    //16000

//Turning Speeds for Fast Run
#define innerSpeed 0    //8000
#define outerSpeed 0    //16000

//Turning parameter arguments
#define R90 2
#define L90 1
#define T180 3
//@}

/**
 * @brief PID controller for moving through the maze.
 * 
 * Checks the sensor and slows down the opposite wheel if needed to keep
 * the mouse in the centre of the maze.
 * 
 * @param close_Sensor_Side     Side which sensor to be checked is on.
 * @return                      how much the opposite wheel needs to slow down by.
 */
float PID(int close_Sensor_Side);

/**
 * @brief UART 1 receive interrupt for encoder 1 and programmer.
 */
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);

/**
 * @brief UART 2 receive interrupt for encoder 2 and USB interface.
 */
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void);

/**
 * @brief accelerate the mouse up to speed, or from speed to static.
 * 
 * @param direction whether accelerating (1) or decelerating (0).
 */
void Velocity_Curve(unsigned char direction);

/**
 * @brief accelerate or decelerate the mouse for the turns when exploring.
 * 
 * @param direction whether accelerating (1) or decelerating (0).
 */
void Turn_Velocity_Curve(unsigned char direction);

/**
 * @brief sets motor directions.
 * 
 * 1 for forward. 0 for stop. -1 for backwards.
 * 
 * @param MLDir     Direction to set left motor to go.
 * @param MRDir     Direction to set right motor to go.
 */
void M_Dir(int MLDir, int MRDir);

/**
 * @brief turn the mouse 90 degrees in a given direction.
 * 
 * Used in the exploring of the maze.
 * @param turn      direction to turn the mouse.
 */
void Turn(int turn);

/**
 * @brief move the mouse forward the number of cells given.
 * 
 * @param cells     How many cells forward to move.
 */
void Fwd(int cells);

/**
 * @brief move the mouse forward one cell.
 */
void Fwd_One_Cell(void);

/**
 * @brief complete a fast run of a stack of instructions.
 * 
 * follows the instructions in the given stack to get from the current location
 * to the destination using the fast move functions. This will be used for the
 * final run.
 *  
 * @param instructions  Stack of instructions to follow to get to the destination.
 * @param speed         Whether it is going full or half speed.
 */
void Fast_Run(Stack instructions, unsigned char speed);

/**
 * @brief make a turn at full speed.
 * 
 * @param dir       Direction to turn.
 */
void Fast_Turn(unsigned char dir);


#endif	/* MOTORS_H */

