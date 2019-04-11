#include "defs.h"
#include "p30F4011.h"
#include "Motors.h"
int Sensor_Val;

//speed and mode of LEDs global
unsigned int speed;
unsigned char mode;

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
    //LED5Latch = 1;
    IFS0bits.ADIF=0; //reset the interrupt flag
    ADCON1bits.ASAM=0; //stop the sampling
    //now read the data from the buffers ADCBUF0, ADCBUF1 etc.
    
    Sensor_Val=ADCBUF0; //get the result

    //LED5Latch = 0;
}

float Sensor_Read(int sensor){
    //Array of sensor pin outputs
    switch(sensor){
        case 1: Sensor1Latch = 1;break;
        case 2: Sensor2Latch = 1; break;
        case 3: Sensor3Latch = 1; break;
        default: return;
    }
    myDelay(1);    
    ADCON1bits.ASAM=1;
    

    Sensor1Latch = 0;
    Sensor2Latch = 0;
    Sensor3Latch = 0;

    
    return Sensor_Val;
}
////For mapping, function to see the wall
int Wall_Check(int side){
    //LED7Latch = 1;
    //Variable Initialisation
    int  division = 10, ret, i, p, stop;
    float  sensorRead[division], sum, finalValue, frontVal;
    
    
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
    finalValue = Sensor_Read(side);
            //sum/division;



    
    //Return binary check
    if(finalValue < WallThres){
        switch (side) {
            case 1: LED5Latch = 0; break;
            case 2: LED7Latch = 0; break;
            case 3: LED4Latch = 0; break;
            }
        return (0);
    }
    
    else{ 
                
        switch (side) {
            case 1: LED5Latch = 1; break;
            case 2: LED7Latch = 1; break;
            case 3: LED4Latch = 1; break;
        }
        
        //Check front wall     
        if(side == 1){

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
                PDC1 = 2000;
                PDC2 = 2000;
                if((frontVal > Des_Sensor_Val - Tolerance) && (frontVal < Des_Sensor_Val + Tolerance)){
                    Stop(stop);
                }
            }
            
        
        }
        return(1);
        
    }

}