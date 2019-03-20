/**
 *		@file LED.h
 *		@brief Defines all LEDs and associated functions.
 * 
 *      defines names for all LED latches, ports and Tris bits.
 *      contains all functions for setting LEDs and making them
 *      display things. This includes timer interrupt.
 *
 *
 *		@author		Nick Appleton @ UWE Robotics
 *
 *		@date	23/3/19
 */


#include "p30F4011.h"

#ifndef LED_H
#define	LED_H

/**
 * @brief number of LEDs on the mouse
 */
#define LEDN 5


#define INSTRUCTIONSPEED 16000000    
    
//defining the TRIS Latch and Port of the required pins
    //  LED 2 is PORT D, bit 1
#define LED2TRIS   TRISDbits.TRISD1
#define LED2Latch  LATDbits.LATD1
#define L2Port   PORTDbits.RD1

    //  SW3 is PORT D, bit 2
#define SW3TRIS   TRISDbits.TRISD2
#define SW3Latch  LATDbits.LATD2
#define SW3Port   !PORTDbits.RD2

    //  LED 3 is PORT D, bit 3
#define LED3TRIS   TRISDbits.TRISD3
#define LED3Latch  LATDbits.LATD3
#define LED3Port   PORTDbits.RD3

    //  LED 4 is PORT E, bit 0
#define LED4TRIS   TRISEbits.TRISE0
#define LED4Latch  LATEbits.LATE0
#define LED4Port   PORTEbits.RE0
    

#define T1on                T1CONbits.TON 
#define T1Prescaler         T1CONbits.TCKPS 
#define T1inputClock        T1CONbits.TCS
#define T1IdleStop          T1CONbits.TSIDL
#define T1Gate              T1CONbits.TGATE 

#define T1Flag              IFS0bits.T1IF  
#define T1Priority          IPC0bits.T1IP
#define T1InteruptEnable    IEC0bits.T1IE 


//function to set up timer 1
//to change the setup, go into the function
void timer1Setup();

void setupLEDs(void);


void SetLED(unsigned int LED, unsigned int set);


//Timer 1 ISR
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);


void SetLED(unsigned int LED, unsigned int set);

void Display(unsigned int setmode, unsigned int speedchange);

#endif	/* LED_H */