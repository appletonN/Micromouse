/* 
 * File:   Motors.h
 * Author: crt2-woof
 *
 * Created on 02 April 2019, 19:22
 */

#ifndef MOTORS_H
#define	MOTORS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ML_F0_5 00           
#define MR_F0_5 0         
//  1
#define ML_F1 0             
#define MR_F1 0

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
#define ML_90L  0//110   //215
#define MR_90L  0//110    //215
#define ML_90R  0   //215
#define MR_90R  0   //215
#define ML_180  0//216    //430
#define MR_180  0//216    //430

//*****************PWM Values*******************
//Max Linear Movement Motor Speed
#define MLSpeed 0   //15000
#define MRSpeed 0       //15000
#define CreepSpeedL 0//2000    //2000
#define CreepSpeedR 0//2000   //2000
#define CreepSpeed 0   //2000
//Turning Speeds for 90 Degrees
#define MLTurnSpeed 0    //16000
#define MRTurnSpeed 0    //16000
//Acceleration Curve Speeds
#define Acc_R   0
#define Acc_L   0
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
#define Des_Sensor_Val  0
#define sensor_Threshold 0
#define Tolerance 0
#define WallThres 0
#define upperError 0
#define lowerError 0

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


#ifdef	__cplusplus
}
#endif

#endif	/* MOTORS_H */

