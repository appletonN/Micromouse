#include "Setup.h"
#include "IO.h"
#include "Motors.h"


//Encoder counts global Variables
int MLEncCount, MREncCount;
float MLVel, MRVel;

//************************M1 PID*************************
//PID control is for ensuring central travel 
float PID(int close_Sensor_Side){
    
    //Variable Initialisation
    float P, I, D, drive, error; //PID components, drive output and error
    static float prevError, ISum; //Previous error and sum of all differences between desired and out
    float DError; //change in difference between desired + actual values and Gain variables 
        
    //Reset variables 
    if(close_Sensor_Side == 9){
        prevError = 0;
        ISum = 0;
        return 0;
    }
    //Calculate error
    error = Des_Sensor_Val - Sensor_Read(close_Sensor_Side);
    
    //Proportional
    P = error * Kp;

    //Integral
    if(ISum > 32000)
        ISum = 32000;   // To prevent integral overflow
    if(ISum < -32000)
        ISum = -32000;  // To prevent integral underflow
    ISum = ISum + error; 
    I = ISum * Ki;

    //Derivative
    DError = error - prevError;
    D = DError * Kd;
    prevError = error; 

    //Finalise
    drive = P + I + D;

    return drive; 
}
//************************U1RX Interrupt*************************
//Every interrupt = 1*(encoder resolution) encoder transmission from ATtiny
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    //Reset the flag 
    U1_RXIF = 0;
    //Read from Receive buffer
    char in = U1RXREG;
    //Increment encoder count
    MLEncCount++;
}
//************************U2RX Interrupt*************************
//Every interrupt = 1*(encoder resolution) encoder transmission from ATtiny
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){
    //Reset the flag 
    U2_RXIF = 0;
    //Read from Receive buffer
    char in = U2RXREG;
    //Increment encoder count
    MREncCount++;
}
//************************Speed up/slow down motor vel curve**********************
void Velocity_Curve(unsigned char direction){
    //Small velocity curve to speed up if 1 input
    if(direction == 1){
        while (MLEncCount < ML_F0_5 || MREncCount < MR_F0_5){
            
                PDC1++;
                        
                PDC2++;
            
        }
    }
    //Small velocity curve to slow down if 0 input
    if(direction == 0){
        while (PDC1 > CreepSpeed || PDC2 > CreepSpeed){
            if(PDC1 > CreepSpeed){
                PDC1--;
            }
            if(PDC2 > CreepSpeed){
                PDC2--;
            }
        }
    }
    return;
}
//************************Speed up/slow down turning motor vel curve**********************
void Turn_Velocity_Curve(unsigned char direction){
    //Small velocity curve to speed up if 1 input
    if(direction == 1){
        while (PDC1 < MLTurnSpeed || PDC2 < MRTurnSpeed){
            if(PDC1 < MLTurnSpeed){
                PDC1++;
            }
            if(PDC2 < MRTurnSpeed){
                PDC2++;
            }
        }
    }
    //Small velocity curve to slow down if 0 input
    if(direction == 0){
        while (PDC1 > 0 || PDC2 > 0){
            if(PDC1 > 0){
                PDC1--;
            }
            if(PDC2 > 0){
                PDC2--;
            }
        }
    }
}
//************************Set Motor Directions**********************
void M_Dir(int MLDir, int MRDir){
    switch (MLDir){
        case F: MLDirALatch = 1; MLDirBLatch = 0; break;
        case B: MLDirALatch = 0; MLDirBLatch = 1; break;
        case 0: MLDirALatch = 0; MLDirBLatch = 0; break;
        default:MLDirALatch = 0; MLDirBLatch = 0; break;
    }
    switch (MRDir){
        case F: MRDirALatch = 0; MRDirBLatch = 0; break;
        case B: MRDirALatch = 0; MRDirBLatch = 0; break;
        case 0: MRDirALatch = 0; MRDirBLatch = 0; break;
        default:MRDirALatch = 0; MRDirBLatch = 0; break;
    }
    return;
}
//************************Turn Left**********************
void Turn(int turn){

    //Create encoder variables
    int left_Enc, right_Enc;
    //Turning direction switch case 
    switch (turn){
        case R90:   M_Dir(F, B); left_Enc = ML_90R; right_Enc = MR_90R; break;
        case L90:   M_Dir(B, F); left_Enc = ML_90L; right_Enc = MR_90L; break;
        case T180:   M_Dir(B, F); left_Enc = ML_180; right_Enc = MR_180; break;          
        default:    M_Dir(0,0); break;
    }
    //Reset Encoder counts
    MLEncCount = 0;
    MREncCount = 0;
    //Speed up velocity curve
    Turn_Velocity_Curve(1);
    //While the appropriate encoder count has not been met 
    while ((MLEncCount < left_Enc) && (MREncCount < right_Enc)){
        
        //Turn off when Encoder value reached
        if ((MLEncCount == left_Enc-turnStopEnc) && (MREncCount == right_Enc-turnStopEnc)){
            
            //Set the velocity curve to slow down to 0
            Turn_Velocity_Curve(0);
            
        }
    }
    return;
}
//************************Set M1 Direction**********************
void Fwd_One_Cell(void){
    //Initialise Sensor Variables
    float sensorLeft, sensorRight, driveError;
    
    //set direction
    M_Dir(F,F);
    
    //Reset Encoder counts
    MLEncCount = 0;
    MREncCount = 0;
    
    //Speed up velocity curve
    Velocity_Curve(1);
    
    //While the appropriate encoder count has not been met 
    while (MLEncCount != ML_F1-stopEnc && MREncCount != MR_F1-stopEnc){
        
        //Get sensor Values
        sensorLeft = Sensor_Read(3);
        sensorRight = Sensor_Read(2);
        
        //PID Controller
        if(sensorLeft > sensor_Threshold){
            //Run PID preference to the right
            driveError = PID(3);
            PDC2 = MRSpeed - driveError;
        }
        if(sensorRight > sensor_Threshold){
            //Run PID preference to the left
            driveError = PID(2);
            PDC1 = MLSpeed - driveError;
        }
        //If in the middle keep everything the same and reset PID
        if((sensorRight && sensorLeft) < sensor_Threshold){
            PID(Reset);
            PDC1 = MLSpeed;
            PDC2 = MRSpeed;
        }
    }
    //Set the velocity curve to slow down
    Velocity_Curve(0);
    //Creep Forward
    while ((MLEncCount < ML_F1) && (MREncCount < MR_F1)){
        
        if(MLEncCount == ML_F1){
            PDC1 = 0;
        }
        if(MREncCount == MR_F1){
            PDC2 = 0;
        }  
    }

    return;
}


//Stack of maze directions 
void Fast_Run(Stack instructions, unsigned char speed){
    
    int MLTopSpeed, MRTopSpeed;
    
    //Determine if fast run or not 
    if (speed == 1){
        MLTopSpeed = MLSpeed;
        MRTopSpeed = MRSpeed;
    }else{  MLTopSpeed = MLSpeed/2;
            MRTopSpeed = MRSpeed/2;
    }
    
    //rotate the correct amount to face way to move
    //as told by the top of the stack
    Turn( pop(&instructions) );
    
    //up to speed. Once encoders say we're at half a cell, jump to full speed
    Velocity_Curve(1);
    PDC1 = MLSpeed;
    PDC2 = MRSpeed;
    
    //ready for run
    while ( instructions.head > 1 ) {
        
        //move forward correct number of cells
        Fwd( pop(&instructions) );
        
        //make turn
        Fast_Turn( pop(&instructions) );
        
    }
    //facing final cell in corridor
    Fwd( pop(&instructions) -1 );
    //at boundary of final cell
    Velocity_Curve(0);
}

//************************Forward x Cells**********************
void Fwd(int cells){
    
    //Initialise Sensor Variables
    float sensorLeft, sensorRight, driveError;
    //Initialise encoder variables
    int MLEnc, MREnc;
    //Variable to check for first and last movement 
    static int count;

    //Switch between no. of cells
    switch(cells){
        case 1: MLEnc = ML_F1; MREnc = MR_F1; break;
        case 2: MLEnc = ML_F2; MREnc = MR_F2; break;
        case 3: MLEnc = ML_F3; MREnc = MR_F3; break;
        case 4: MLEnc = ML_F4; MREnc = MR_F4; break;
        case 5: MLEnc = ML_F5; MREnc = MR_F5; break;
        case 6: MLEnc = ML_F6; MREnc = MR_F6; break;
        case 7: MLEnc = ML_F7; MREnc = MR_F7; break;
        case 8: MLEnc = ML_F8; MREnc = MR_F8; break;     
        default: return;
    }
    //set direction
    M_Dir(F,F);
    
    //Reset Encoder counts
    MLEncCount = 0;
    MREncCount = 0;

    //While the appropriate encoder count has not been met 
    //Turn off when Encoder value reached
    while (MLEncCount != MLEnc && MREncCount != MREnc){
        
        //Get sensor Values
        sensorLeft = Sensor_Read(3);
        sensorRight = Sensor_Read(2);
        
        //PID Controller
        if(sensorLeft > sensor_Threshold){
            //Run PID preference to the right
            driveError = PID(3);
            PDC2 = MRSpeed - driveError;
        }
        if(sensorRight > sensor_Threshold){
            //Run PID preference to the left
            driveError = PID(2);
            PDC1 = MLSpeed - driveError;
        }
        if((sensorRight && sensorLeft) < sensor_Threshold){
            PID(Reset);
            PDC1 = MLSpeed;
            PDC2 = MRSpeed;
        }
    }
    //Add to count, later can also add final turn count to return a value 
    count++;
    
    return;
}
//************************Turn Left or Right Fast**********************
void Fast_Turn(unsigned char dir){

    //Create encoder variables
    int left_Enc, right_Enc;
    int rightLED, leftLED;
    //Reset Encoder counts
    MLEncCount = 0;
    MREncCount = 0;
    
    //Turning direction & speeds switch case 
    switch (dir){
        case R:   left_Enc = outer_R; PDC1 = outerSpeed; 
                  right_Enc = inner_R; PDC2 = innerSpeed; 
                  break;
        case L:   left_Enc = inner_L; PDC1 = innerSpeed;
                  right_Enc = outer_L; PDC2 = outerSpeed;
                  break;     
        default:  M_Dir(0,0); break;
    }
    
    //While the appropriate encoder count has not been met 
    while ((MLEncCount < left_Enc) && (MREncCount < right_Enc)){
        
        //Turn on LED indicating turning direction 
        if(dir == R){
            //Replace with actual LED's later
            rightLED = 1;
        }else{
            leftLED = 1;
        }
    }
    
    return;
}
