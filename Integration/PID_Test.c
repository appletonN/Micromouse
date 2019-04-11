#include "defs.h"
#include "Motors.h"
#include "p30F4011.h"
//Encoder counts global Variables
int desiredPosL, desiredPosR, desiredPos, stopLeft, stopRight;
int desiredVelocity, lastVelR, lastVelL, MLEncCount, MREncCount;
int x, desiredPos, MLDirection, MRDirection, encDirL, encDirR;
float velocityL, velocityR;


//Timer 1 interrupt every 10ms to run PID
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    LED7Latch = 1;
    //Reset the Timer
    t1Flag = 0;
    
    PIDPos(); //Right hand motor
    LED7Latch = 0;
    return;
} 

//PID control is for positional control 
float PIDPos(){
    
    //Variable Initialisation
    float Pr, Ir, Dr, Pl, Il, Dl, driveL, driveR;
    int errorL, errorR; //PID components, drive output and error
    int position;
    static float prevError, ISum; //Previous error and sum of all differences between desired and out
    float DError; //change in difference between desired + actual values and Gain variables 

    //Error
    errorL =  desiredPos - MLEncCount;
    //If error == 0 then stop
    if(errorL == 0){
        stopLeft = 1;
    }
    //Error
    errorR = desiredPos - MREncCount;
    //If error == 0 then stop
    if(errorR == 0){
        stopRight = 1;
    }
    //If shoot over then reverse direction
    if(errorL < 0){
        //LED5Latch = 1;
        reverse(2);
        encDirL = -1;
        errorL = -errorL;
    }
    //If shoot over then reverse direction
    if(errorR < 0){
        LED4Latch = 1;
        reverse(1);
        encDirR = -1;
        errorR = -errorR;
    }
    //Re-reverse if shoot back again
    if(errorR > 0 && encDirR == -1){
        LED4Latch = 0;
        reverse(1);
        encDirR = 1;
    }
    if(errorL > 0 && encDirL == -1){
        LED4Latch = 0;
        reverse(2);
        encDirL = 1;
    }
    //Proportional and drive
    Pl = errorL * PosKp;
    Pr = errorR * PosKp;
    PDC1 = Pl;
    PDC2 = Pr;

    return;


}
void reverse(int motor){
    
    if(motor == 1){
        if(MRDirection == 1){
            M_R_Dir(-1);
        }else{
            M_R_Dir(1);
            LED5Latch = 1;}
        return;
    }
    if(motor == 2){
        if(MRDirection == 1){
            M_L_Dir(-1);
        }else{M_L_Dir(1);}
        return;
    }
    return;
}
//************************U1RX Interrupt*************************
//Every interrupt = 1*(encoder resolution) encoder transmission from ATtiny
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    //Reset the flag 
    U1_RXIF = 0;
    //Read from Receive buffer
    char in = U1RXREG;
    //Increment encoder count
    if(encDirR == 1){
    MREncCount++;
    }else{MREncCount--;}
    return;
}
//************************U2RX Interrupt*************************
//Every interrupt = 1*(encoder resolution) encoder transmission from ATtiny
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){
    //Reset the flag 
    U2_RXIF = 0;
    //Read from Receive buffer
    char in = U2RXREG;
    //Increment encoder count
    if(encDirL == 1){
    MLEncCount++;
    }else{MLEncCount--;}
    return;
}
//Motor direction functions
void M_L_Dir(int dir){
    switch(dir){
        case F: MLDirALatch = 1; MLDirBLatch = 0; MLDirection = 1; break;
        case -1: MLDirALatch = 0; MLDirBLatch = 1; MLDirection = -1; break;
        case 0: MLDirALatch = 0; MLDirBLatch = 0; MLDirection = 0; break;
        default:MLDirALatch = 0; MLDirBLatch = 0; MLDirection = 0;break;
    }
    
    return;
}
void M_R_Dir(int dir){
        switch (dir){
        case F: MRDirALatch = 1; MRDirBLatch = 0; MRDirection = 1; break;
        case -1: MRDirALatch = 0; MRDirBLatch = 1; MRDirection = -1; break;
        case 0: MRDirALatch = 0; MRDirBLatch = 0; MRDirection = 0; break;
        default:MRDirALatch = 0; MRDirBLatch = 0; MRDirection = 0;break;
    }
        
    return;
}

//************************Turn Left**********************
void Turn(int turn){
    
    //Create encoder variables
    MLEncCount = 0;
    MREncCount = 0;
    //Turning direction switch case 
    switch (turn){
        case L90:   desiredPosL = ML_90L; desiredPosR = MR_90L; LED3Latch = 1; break;
        case R90:   desiredPosL = ML_90L; desiredPosR = MR_90L; LED3Latch = 1; break;
//        case T180:  M_Dir(B, F); desiredPosL = ML_180; desiredPosR = MR_180; break;          
        default:  break;
    }
    
    //While turn not complete
    while(turn == L90){
        
    }


    M_L_Dir(0);
    M_R_Dir(0);
    LED7Latch = 0;

    return;
}
void velCurve(int dir){
    int i;
    
    if(dir == 1){
        for (i = 0; i < 10; i++){
            PDC1 += 100;
            PDC2 += 100;
            myDelay(1);
        }
        
    }
    return;
}
////************************Set M1 Direction**********************
void Fwd_One_Cell(){
    
//    //set direction
    
    M_L_Dir(F);
    M_R_Dir(F);
    encDirR = 1;
    encDirL = 1;
    
    MREncCount = 0;
    MLEncCount = 0;
    PDC1 = 1500;
    PDC2 = 1500;
    desiredPos = MR_F1;
//    while(MREncCount < MR_F1){
//        
//    }
//    Stop(3);
//    return;
    stopRight = 0;
    stopLeft = 0;
    //velCurve(1);
    t1Enable = 1;
    while((stopRight == 0 || stopLeft == 0)){
        
    }
    
    t1Enable = 0;
    Stop(3);
    return;
    
}
void Stop(int dir){

    switch (dir){
        case 3: M_L_Dir(B); M_R_Dir(B); break;
        case 4: M_L_Dir(F); M_R_Dir(F); break;
        case R90: M_L_Dir(F); M_R_Dir(B); break;
        case L90: M_L_Dir(B); M_R_Dir(F); break;
        default: return;
        
    }
    LED5Latch = 1;
    LED7Latch = 1;
    LED3Latch = 1;
    PDC1 = 800;
    PDC2 = 800;
    myDelay(30);
    PDC1 = 0;
    PDC2 = 0;
    M_L_Dir(0);
    M_R_Dir(0);
    MLEncCount = 0;
    MREncCount = 0;
    LED5Latch = 0;
    LED7Latch = 0;
    LED3Latch = 0;
    return;
    
} 
