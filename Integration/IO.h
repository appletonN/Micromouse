/**
*		@file IO.c
*		@brief Functions for input and output Integration
* 
*       Includes the interrupts for sensor inputs and LED outputs
*       as well as functions to decode values and make use of the IO
*
*
*		@author		Christian Woof @ UWE Robotics
*
*/

#ifndef IO_H
#define	IO_H

/**
 * @brief ADC interrupt for use with sensors.
 */
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void);

/**
 * @brief read the Sensors using the ADC.
 * 
 * @param sensor    which sensor to read from.
 * @return          value between 0 and 255 of sensor read.
 */
float Sensor_Read(int sensor);

/**
 * @brief Use LEDs to give feedback on position in cell.
 * 
 * used to setup the mouse in the maze at the beginning by holding
 * the mouse in the cell until the 2 LEDs turn off. This means that
 * the mouse is in the correct position.
 */
void Start_Position(void);

/**
 * @brief check if there is a wall or not.
 * 
 * Uses Sensor_Read() to get an average of the sensor values and uses
 * this to determine whether there is a wall or not in the direciton of
 * the sensor.
 *  
 * @param side      which side of the mouse is being checked.
 * @return          1 or 0 (Wall or no Wall).
 */
//int Wall_Check(int side);

/**
 * @brief Test sensors
 */
void Sensor_Test(void);

/**
 * @brief Timer1 interrupt for LED display.
 */
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void);

/**
 * @brief Turn LED on or off.
 * 
 * @param LED       which LED is being set.
 * @param set       Set or Clear.
 */
void SetLED(unsigned char LED, unsigned char set);

/**
 * @brief Set what is displayed on the LEDs
 * 
 * @param setmode       Which display Mode is to be used.
 * @param speedchange   Speed the display should go at.
 */
void Display(unsigned char setmode, unsigned int speedchange);

#endif	/* IO_H */

