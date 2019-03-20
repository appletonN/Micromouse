#include "LED.h"

#include <stdio.h>

static int mode = 0;
static int speed = 0;


/****   SETUPS ****/
void setupLEDs(void)
{
    //1 is input, 0 is output
    LED2TRIS = 0;
    LED3TRIS = 0;
    LED4TRIS = 0;
}

void timer1Setup(){
    T1on = 0;  //turn off timer during setup
    TMR1 = 0;   //clear timer 1
    
    T1Prescaler = 2;     //sets prescaler to 64
    
    PR1 = 290;    //set timer period to relevant number
    
    T1inputClock = 0;       //sets to internal clock
    T1IdleStop = 1;     //stops timer in idle mode
    T1Gate = 0;         //do not gate the timer
    T1Flag = 0;         //clear the flag
    
    T1Priority = 5;      //set Priority
    
    T1InteruptEnable = 1;
    T1on = 1;       //Turn on the timer
    
}



/**** TIMER 1 ****/

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    T1Flag = 0; ///reset the timer 1 interrupt flag
    static char count = 0;
    static unsigned char LEDs;
    static char dir = 1;
    int i;
  
    
    
    if (count == speed) {
        
        //display the correct mode
        switch (mode) {
            case 0:
                //use speed as an error code
                LEDs = speed;

                break;
                
            case 1:
                //flash 
                if ( LEDs == 0x0A )
                    LEDs = ~LEDs;
                else
                    LEDs = 0x0A;
                break;

            case 2:
                //wake up
                if ( LEDs == 0x1F) {
                    //reset LEDs
                    LEDs = 0;
                    
                } else if ( LEDs == 0x0E ) {
                    //add next layer
                    LEDs |= 0x11;
                    
                } else if ( LEDs == 0x04 ) {
                    LEDs |= 0x0A;
                    
                } else {
                    //if all LEDs are off
                    LEDs = 0x04;
                }
                break;

            case 3:
                //scan
                
                if ( LEDs == 0x01 ) {
                    dir = 1;
                    LEDs = 0x02;
                } else if ( LEDs == 0x10 ) {
                    dir = 0;
                    LEDs = 0x08;
                } else if ( LEDs != 0x01 && LEDs != 0x02 
                        && LEDs != 0x04 && LEDs != 0x08 && LEDs != 0x10 ) {
                    LEDs = 0x01;
                } else { 
                    if ( dir )
                        LEDs = LEDs << 1;
                    else
                        LEDs = LEDs >> 1;
                }
                
                break;

            case 4:
                //cylon
                if ( LEDs == 0x04 ) {
                    //middle LED is lit
                    //so light LEDs either side of it
                    //switch direction so it knows what to do next
                    LEDs = 0x0A;
                    dir = 1;
                    
                } else if ( LEDs == 0x0A && dir ) {
                    //move out
                    LEDs = 0x11;
                    
                } else if ( LEDs == 0x0A && !dir ) {
                    //move in
                    LEDs = 0x04;
                    
                } else {
                    //outermost
                    LEDs = 0x0A;
                    dir = 0;
                }
                break;
            
            case 5:
                //shift
                LEDs = LEDs << 1;
                //set first LED again if second LED is off
                if ( ~LEDs & 0x02 && ~LEDs & 0x10 )
                    LEDs |= 0x01;
                break;
                
                
        }//SWITCH
        count = 0;
    }//IF
    
    
    count++;
    
    //set all LEDs
    //loop through LEDs Variable and display each value
    for ( i=0; i<LEDN; i++ )
    {
        //if each bit is set, change LED
        if ( LEDs >> i & 0x01 ) {
            SetLED(i, 1);
            printf("X ");
        
        } else {
            SetLED(i, 0);
            printf("0 ");
        }
    }
    printf("\n");
}


void SetLED(unsigned int LED, unsigned int set)
{
    switch (LED) {
        case 0:
            LED3TRIS = set;
            break;
        case 1:
            LED4TRIS = set;
            break;
        case 2:
            LED2TRIS = set;
            break;
    }
}



/**** CALL FROM PROGRAM ****/

void Display(unsigned int setmode, unsigned int speedchange)
{
    mode = setmode;
    speed = speedchange;
}
