/**
*		@file main.c
*		@brief this is the main file that controls the
*		robot.
*
*		Contains the mission planner and runs all
*		initialisation of maze. offloads most functionality
*		to external functions.
*
*
*		@author		Nick Appleton @ UWE Robotics
*
*		@date	21/2/19
*/


#include <stdlib.h>
#include <stdio.h>
#include "p30F4011.h"
#include "Integration/defs.h"
#include "Integration/Motors.h"
#include "Algorithm/MappingFunctions.h"
#include "Algorithm/MapMaze.h"
#include "Algorithm/Dijekstra.h"

//_FWDT(WDT_OFF); 
////watch dog is disabled
void setupA2D(void);
float Sensor_Read(int sensor);
void IOSetup(void);

_FOSC(PRI  &  XT_PLL8 & CSW_FSCM_OFF  ); 
 //primary oscillator with 8 times pll no clock switching

_FWDT(WDT_OFF); 
//watch dog is disabled

        
_FBORPOR( PBOR_OFF & MCLR_EN & PWRT_64 & PWMxL_ACT_LO &  PWMxH_ACT_HI &RST_PWMPIN); 
//brown out disabled, master-clear enabled, power on reset time = 64ms
// pwm low side is active high, pwm high side is active low, reset state controlled with HPOL/LPOL bits    
void myDelay(unsigned int t);
int main(void)
{
    /**** SETUP INTERRUPTS ****/
    
    
    PWMSetup();
    UARTSetup();
    setupA2D();
    IOSetup();
    timer1Setup();
    int i;
//    myDelay(200);
    //t1Enable = 1;
    while(1){
//    LED4Latch = 1;
//    LED6Latch = 1;
//    LED3Latch = 1;
    //Turn(T180);
        
//        while(1){
//        int Left, Right, Front, check = 0;
//        t1Enable = 0;
//        
//
//            Front = Wall_Check(1);
//            Right = Wall_Check(2);
//            Left = Wall_Check(3);
//            if(Left == 1){
//                LED5Latch = 1;
//            }else{
//                LED5Latch = 0;
//            }
//            if(Front == 1){
//                LED5Latch = 1;
//            }else{
//                LED5Latch = 0;
//            }
//            if(Right == 1){
//                LED7Latch = 1;
//            }else{
//                LED7Latch = 0;
//            }
//        }
//    
    //create maze
    struct Maze Cellmaze = {{0}};

    //create array of Nodes
    Node nodelist[MAX_NODES] = {{0}};

    //Map the entire maze
    mapmaze(&Cellmaze, nodelist);
    
//    
//    for ( i=0; i<7; i++ ){
//        
//        LED4Latch = 1;
//        LED5Latch = 1;
//        LED7Latch = 1;
//
//        myDelay(40);
//
//        LED4Latch = 0;
//        LED5Latch = 0;
//        LED7Latch = 0;
//
//        myDelay(40);
//    
//    }
//       
//    //find end Node
//    unsigned char EndNode = 0;
//    while ( !nodelist[EndNode].isEnd )
//        EndNode++;
//    
//    
//    Stack fast;
//    fast = dijekstra(&Cellmaze, nodelist, &nodelist[0], &nodelist[EndNode], 0x02);
//    
//    Fast_Run(fast);
    
        for ( i=0; i<7; i++ ){
        
        LED4Latch = 1;
        LED5Latch = 1;
        LED7Latch = 1;

        myDelay(40);

        LED4Latch = 0;
        LED5Latch = 0;
        LED7Latch = 0;

        myDelay(40);
        
        Turn(T180);
    
    }
    
    while(1);
    
	return;
}
}

   void myDelay(unsigned int t){
    //Variables
    unsigned int i, x, inner;
    
    //Relate input to cycles needed, @ 570 function runs for 1ms
    inner = t * 571;
    
    for(i = 0; i < 40; i++){
            for(x = 0; x < inner; x++){
                
            }
         
        }
    return;
   }
   



