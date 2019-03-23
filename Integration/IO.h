/* 
 * File:   IO.h
 * Author: nick
 *
 * Created on 22 March 2019, 11:39
 */

#ifndef IO_H
#define	IO_H


void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void);

float Sensor_Read(int sensor);

void Start_Position(void);

//int Wall_Check(int side);

void Sensor_Test(void);

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);

void SetLED(unsigned char LED, unsigned char set);

void Display(unsigned char setmode, unsigned int speedchange);

#endif	/* IO_H */

