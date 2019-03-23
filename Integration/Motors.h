/* 
 * File:   Motors.h
 * Author: nick
 *
 * Created on 22 March 2019, 11:30
 */

#ifndef MOTORS_H
#define	MOTORS_H

#include "../Stacks.h"

//*****************Encoder Counts*******************
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

//*****************PWM Values*******************
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

//*****************Misc. Definitions*******************
//Directions
#define F 1
#define B -1

//turn Directions
#define L 1
#define R 2

//PID Control Gains
#define Kp 1
#define Ki 1
#define Kd 1

//Desired sensor value
#define Des_Sensor_Val 1
#define sensor_Threshold 1

//Reset State for PID
#define Reset 9


float PID(int close_Sensor_Side);

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void);

void Velocity_Curve(unsigned char direction);

void Turn_Velocity_Curve(unsigned char direction);

void M_Dir(int MLDir, int MRDir);

void Turn(int turn);

void Fwd(int cells);

void Fwd_One_Cell(void);

void Fast_Run(Stack instructions, unsigned char speed);

void Fast_Turn(unsigned char dir);


#endif	/* MOTORS_H */

