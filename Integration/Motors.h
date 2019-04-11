/* 
 * File:   Motors.h
 * Author: crt2-woof
 *
 * Created on 02 April 2019, 19:22
 */

#ifndef MOTORS_H
#define	MOTORS_H

#include "../Stacks.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define ML_F0_5 168           
#define MR_F0_5 168         
//  1
#define ML_F1 335             
#define MR_F1 335

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
#define stopEnc 30           //10
#define turnStopEnc 0       //10

//Fast Turning encoder counts
#define inner_L 0   //215
#define outer_L 0   //215
#define inner_R 0   //215
#define outer_R 0   //215

//Turning encoder counts
#define ML_90L  95//118//110   //215
#define MR_90L  95//118//110    //215
#define ML_90R  95//110   //215
#define MR_90R  95//110   //215
#define ML_180  206//216    //430
#define MR_180  206//216    //430

//*****************PWM Values*******************
//Max Linear Movement Motor Speed
#define MLSpeed 16000   //15000
#define MRSpeed 16000       //15000
#define CreepSpeedL 1500//2000    //2000
#define CreepSpeedR 1550//2000   //2000
#define CreepSpeed 10000   //2000
//Turning Speeds for 90 Degrees
#define MLTurnSpeed 2000    //16000
#define MRTurnSpeed 2000    //16000
//Acceleration Curve Speeds
#define Acc_R   450
#define Acc_L   500
//Turning Speeds for Fast Run
#define innerSpeed 0    //8000
#define outerSpeed 0    //16000

//Turning parameter arguments
#define L90 2
#define R90 1
#define T180 3

//*****************Misc. Definitions*******************
//Directions
#define F 1
#define B -1

//turn Directions
#define L 1
#define R 2

//PID Control Gains
#define Kp 5//6//1.5//20
#define Ki 1
#define Kd 0
#define PosKp 50
#define PosKi 1
#define PosKd 5
    
    
//Desired sensor value
#define Des_Sensor_Val  190
#define sensor_Threshold 150
#define Tolerance 10
#define WallThres 80
#define upperError 600
#define lowerError 100

//float PIDPos(int side);
void PID();
float PIDPos();
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void);

void Velocity_Curve(unsigned int direction);
void reverse(int motor);
void Turn_Velocity_Curve(unsigned char direction);

void M_Dir(int Left, int Right);

void Turn(int turn);
//void Fwd(int cells);
void Stop(int dir);
void Fwd_One_Cell(void);

void Fast_Run(Stack instructions);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTORS_H */

