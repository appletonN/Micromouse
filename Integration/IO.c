#include "Integration/Setup.h"
#include "IO.h"
#include <p30Fxxxx.h>
#include "Motors.h"





//Sensor read global variable 
int sensorVal;

//speed and mode of LEDs global
unsigned int speed;
unsigned char mode;

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
    //LED5Latch = 1;
    IFS0bits.ADIF=0; //reset the interrupt flag
    ADCON1bits.ASAM=0; //stop the sampling
    //now read the data from the buffers ADCBUF0, ADCBUF1 etc.
    
    sensorVal=ADCBUF0; //get the result

    //LED5Latch = 0;
}

float Sensor_Read(int sensor){
    //Array of sensor pin outputs
    switch(sensor){
        case 1: Sensor1Latch = 1;break;
        case 2: Sensor2Latch = 1; break;
        //case 3: PDC3 = 16000; break;
        case 3: Sensor3Latch = 1; break;
        default: return;
    }
    myDelay(1);    
    ADCON1bits.ASAM=1;
    
    //Reset Sensor Pins
    Sensor1Latch = 0;
    Sensor2Latch = 0;
    Sensor3Latch = 0;
    //OVDCONbits.POUT3H = 1;
    //PDC3 = 0;
    //LED5Latch = 0;
    //LED7Latch = 0;
    
    return sensorVal;
}

//Starting Position Finding
void Start_Position(void){
    
    //Initialise variables
    int FUp, FLo, SUp, SLo, frontSensor, sideSensor, timer, check;
    float sideLED, frontLED; //CHANGE THESE TO LEDS WHEN KNOWN
    //Set bandwidth of correct placement
    FUp = 200; //Front Upper Limit
    FLo = 190; //Front Lower Limit
    SUp = 200; //Side Upper Limit
    SLo = 190; //Side Lower Limit
    
    //While loop 
    while(1){
        
        //Read the sensors
        frontSensor = Sensor_Read(1);
        sideSensor = Sensor_Read(2);
        
        //Turn on front LED when in correct range
        if(frontSensor < FUp && frontSensor > FLo){
            //Front LED
            SetLED(5,1);
        }else{
            //Front LED
            SetLED(5,0);
        }
        //Turn on side LED when in correct range
        if(sideSensor < SUp && sideSensor > SLo){
            //Left LED
            SetLED(3,1);
        }else{
            //Left LED
            SetLED(3,0);
        }
        
        //while within bandwidth add to counter
        while((frontSensor < FUp && frontSensor > FLo) && (sideSensor < SUp && sideSensor > SLo)){
            
            //Add to counter
            timer++;
            
            //Read Sensors
            frontSensor = Sensor_Read(1);
            sideSensor = Sensor_Read(2);
            
            //if in bandwidth for long enough then check = 1
            if(timer == 20000){
                
                //INSERT FLASHING LED's HERE
                return;
                
            }
            
        }

        //Reset counter when out of bandwidth
        timer = 0;
    }
}


////For mapping, function to see the wall
int Wall_Check(int side){
    
    //Variable Initialisation
    int division = 100, ret, i, p, stop;
    float sensorRead[division], sum, finalValue, frontVal;
    
    LED5Latch = 1;
    
    //Loop to check the wall
    for (i = 0; i < division; i++){
        
        //Read that side and store in array 
        sensorRead[i] = Sensor_Read(side);
        
    }
    
    //Check the average of these 
    for (p = 0; p < division; p++){
        
        //Omit results if outside of the correct band
        if((sensorRead[p] > upperError) || (sensorRead[p] < lowerError)){
            sensorRead[p] = 0;
            division--;
        }
        //Sum the sensor results
        sum += sensorRead[p];
    }
    
    //Return the final value
    finalValue = sum/division;
    
    //Return binary check
    if(finalValue < WallThres){
        //turn off LED 
        //SetLED(side, 0);
        LED5Latch = 0;
        myDelay(10);
        return (0);
    }
    else{
        //Check front wall
        if(side == 1){
            LED7Latch = 1;
            frontVal = Sensor_Read(1);
            //While front wall not in desired position with tolerance
            //while((frontVal < Des_Sensor_Val - Tolerance) || (frontVal < Des_Sensor_Val + Tolerance) || (frontVal > Des_Sensor_Val + Tolerance)||(frontVal > Des_Sensor_Val - Tolerance)){
            while((frontVal < Des_Sensor_Val - Tolerance) || (frontVal > Des_Sensor_Val + Tolerance)){
                //Read sensor
                frontVal = Sensor_Read(1);
                //If statements to set direction dependant on too close or too far
                if(frontVal < Des_Sensor_Val - Tolerance){
                    M_Dir(1,1);
                    stop = 3;
                }else if(frontVal> Des_Sensor_Val + Tolerance){
                    M_Dir(-1,-1);
                    stop = 4;
                }
                //Power Motors
                PDC1 = CreepSpeedR;
                PDC2 = CreepSpeedL;
                if((frontVal > Des_Sensor_Val - Tolerance) && (frontVal < Des_Sensor_Val + Tolerance)){
                    Stop(stop);
                }
            }
        }
        
        
        LED5Latch = 0;
        LED7Latch = 0;
        myDelay(10);
        return(1);
    }
}

//Sensor testing function
void Sensor_Test(void){
    //Variables
    float left, front, right;
    int thresh = 200;
    while(1){
        
        //Read sensors
        left = Sensor_Read(3);
        front = Sensor_Read(1);
        right = Sensor_Read(2);
        
        while(left > thresh){
            M_Dir(0,1);
            PDC1 = 10000;
            PDC2 = 10000;
            left = Sensor_Read(3);
        }
        while(right > thresh){
            M_Dir(1,0);
            PDC1 = 10000;
            PDC2 = 10000;
            right = Sensor_Read(2);
        }
        while(front > thresh){
            M_Dir(0,0);
            PDC1 = 10000;
            PDC2 = 10000;
            front = Sensor_Read(1);
        }
        
    }
    return;
}

/**** TIMER 1 ****/

//void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
//{
//    T1Flag = 0; ///reset the timer 1 interrupt flag
//    static unsigned char count = 0;
//    static unsigned char LEDs;
//    static unsigned char dir = 1;
//    unsigned char i;
//  
//    
//    
//    if (count == speed) {
//        
//        //display the correct mode
//        switch (mode) {
//            case 0:
//                //use speed as an error code
//                LEDs = speed;
//
//                break;
//                
//            case 1:
//                //flash 
//                if ( LEDs == 0x0A )
//                    LEDs = ~LEDs;
//                else
//                    LEDs = 0x0A;
//                break;
//
//            case 2:
//                //wake up
//                if ( LEDs == 0x1F) {
//                    //reset LEDs
//                    LEDs = 0;
//                    
//                } else if ( LEDs == 0x0E ) {
//                    //add next layer
//                    LEDs |= 0x11;
//                    
//                } else if ( LEDs == 0x04 ) {
//                    LEDs |= 0x0A;
//                    
//                } else {
//                    //if all LEDs are off
//                    LEDs = 0x04;
//                }
//                break;
//
//            case 3:
//                //scan
//                
//                if ( LEDs == 0x01 ) {
//                    dir = 1;
//                    LEDs = 0x02;
//                } else if ( LEDs == 0x10 ) {
//                    dir = 0;
//                    LEDs = 0x08;
//                } else if ( LEDs != 0x01 && LEDs != 0x02 
//                        && LEDs != 0x04 && LEDs != 0x08 && LEDs != 0x10 ) {
//                    LEDs = 0x01;
//                } else { 
//                    if ( dir )
//                        LEDs = LEDs << 1;
//                    else
//                        LEDs = LEDs >> 1;
//                }
//                
//                break;
//
//            case 4:
//                //cylon
//                if ( LEDs == 0x04 ) {
//                    //middle LED is lit
//                    //so light LEDs either side of it
//                    //switch direction so it knows what to do next
//                    LEDs = 0x0A;
//                    dir = 1;
//                    
//                } else if ( LEDs == 0x0A && dir ) {
//                    //move out
//                    LEDs = 0x11;
//                    
//                } else if ( LEDs == 0x0A && !dir ) {
//                    //move in
//                    LEDs = 0x04;
//                    
//                } else {
//                    //outermost
//                    LEDs = 0x0A;
//                    dir = 0;
//                }
//                break;
//            
//            case 5:
//                //shift
//                LEDs = LEDs << 1;
//                //set first LED again if second LED is off
//                if ( ~LEDs & 0x02 && ~LEDs & 0x10 )
//                    LEDs |= 0x01;
//                break;
//                
//                
//        }//SWITCH
//        count = 0;
//    }//IF
//    
//    
//    count++;
//    
//    //set all LEDs
//    //loop through LEDs Variable and display each value
//    for ( i=0; i<5; i++ )
//    {
//        //if each bit is set, change LED
//        if ( LEDs >> i & 0x01 ) {
//            SetLED(i, 1);
//        
//        } else {
//            SetLED(i, 0);
//        }
//    }
//}


void SetLED(unsigned char LED, unsigned char set)
{
    switch (LED) {
        case 0:
            LED3Tris = set;
            break;
        case 1:
            LED4Tris = set;
            break;
        case 2:
            LED5Tris = set;
            break;
        case 3:
            LED6Tris = set;
            break;
        case 4:
            LED7Tris = set;
            break;
    }
}



/**** CALL FROM PROGRAM ****/

void Display(unsigned char setmode, unsigned int speedchange)
{
    mode = setmode;
    speed = speedchange;
}

