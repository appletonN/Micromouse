#include "defs.h"
#include "Motors.h"
#include "p30F4011.h"
//Encoder counts global Variables
int first, offset, desiredVelocity, lastVelR, lastVelL, MLEncCount, MREncCount, MLDirection, MRDirection, curveCount, desiredPosL, desiredPosR;
float velocityL, velocityR;
int w15;

////Timer 1 interrupt every 10ms to run PID
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    //Reset the Timer
    t1Flag = 0;

    velocityL = MLEncCount - lastVelL; 
    velocityR = MREncCount - lastVelR; 
    PID();
    
    lastVelL = MLEncCount;
    lastVelR = MREncCount;


    return;
} 

//PID control is for positional control 
void PID(){
    
    //Variable Initialisation
    float P, I, D, error; //PID components, drive output and error
    int position;
    static float prevError, ISum; //Previous error and sum of all differences between desired and out
    float DError; //change in difference between desired + actual values and Gain variables 
    PDC2 = desiredVelocity;
    
    if(velocityR > velocityL){

        error = (velocityR - velocityL);
        //Proportional
        P = error*Kp;
        //Derivative
        DError = error - prevError;
        D = DError * Kd;
        prevError = error; 
        //Final
        PDC1 = desiredVelocity-P;;
                //-D
        return;
    }
    if(velocityR < velocityL){

        //error
        error = (velocityL - velocityR)*Kp;
        //Proportional
        P = error*Kp;
        //Derivative
        DError = error - prevError;
        D = DError * Kd;
        prevError = error; 
        //Final
        PDC1 = desiredVelocity+P;
                //+D//offset;
        return;
    }
    //PDC1 = desiredVelocity;
//    LED5Latch = 0;
//    LED7Latch = 0;
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
    MREncCount++;
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
    MLEncCount++;
    return;
}

//Motor direction functions
void M_Dir(int Left, int Right){
    
    switch(Left){
        case F: MLDirALatch = 1; MLDirBLatch = 0; MLDirection = 1; break;
        case B: MLDirALatch = 0; MLDirBLatch = 1; MLDirection = -1; break;
        case 0: MLDirALatch = 0; MLDirBLatch = 0; MLDirection = 0; break;
        default:MLDirALatch = 0; MLDirBLatch = 0; MLDirection = 0;break;
    }
    switch (Right){
        case F: MRDirALatch = 1; MRDirBLatch = 0; MRDirection = 1; break;
        case B: MRDirALatch = 0; MRDirBLatch = 1; MRDirection = -1; break;
        case 0: MRDirALatch = 0; MRDirBLatch = 0; MRDirection = 0; break;
        default:MRDirALatch = 0; MRDirBLatch = 0; MRDirection = 0;break;
    }
    
    return;
}
void Turn_Velocity_Curve(unsigned char direction){
    //Small velocity curve to speed up if 1 input
    if(direction == 1){
        while (PDC1 < MLTurnSpeed || PDC2 < MRTurnSpeed){

            desiredVelocity += 80;
            myDelay(1);
        }
        //LED5Latch = 0;
    }
    //Small velocity curve to slow down if 0 input
//    if(direction == 0){
//        while (PDC1 > 0 || PDC2 > 0){
//            if(PDC1 > 0){
//                PDC1--;
//            }
//            if(PDC2 > 0){
//                PDC2--;
//            }
//        }
//    }
}
//************************Turn Left**********************
void Turn(int turn){
    //Create encoder variables
    int left_Enc, right_Enc, check = 0;
    //Turning direction switch case 
    switch (turn){
        case R90:   M_Dir(F, B); left_Enc = ML_90R; right_Enc = MR_90R; break;
        case L90:   M_Dir(B, F); left_Enc = ML_90L; right_Enc = MR_90L; break;
        case T180:  M_Dir(F, B); left_Enc = ML_180; right_Enc = MR_180; turn = 180; break;          
        default:    M_Dir(0,0); return;
    }
    
    //Reset Encoder counts
    MLEncCount = 0;
    MREncCount = 0;
    t1Enable = 1;
    //Turn_Velocity_Curve(1);
    
    desiredVelocity = CreepSpeed;
    while((MLEncCount < left_Enc) || (MREncCount < right_Enc)){
        if(MLEncCount > left_Enc){
            MLDirALatch = 0; MLDirBLatch = 0;
        }
        if(MREncCount > right_Enc){
            MRDirALatch = 0; MRDirBLatch = 0;
        }

    }
    desiredVelocity = 0;
    t1Enable = 0;

        switch (turn){
        case 3: M_Dir(-1,-1); break;
        case 4: M_Dir(1,1); break;
        case L90: M_Dir(1,-1); break;
        case R90: M_Dir(-1,1); break;
        case 180: M_Dir(-1,1); break;
        default: return;
        
    }

    PDC1 = 3000;
    PDC2 = 3000;
    myDelay(5);
    PDC1 = 0;
    PDC2 = 0;
    M_Dir(0,0);
    MLEncCount = 0;
    MREncCount = 0;
    return;

}

////************************Set M1 Direction**********************
void Fwd_One_Cell(){
    
    //set direction
    int count, dir = 3;
    M_Dir(1,1);
//    MLDirALatch = 1; MLDirBLatch = 0; MLDirection = 1; 
//    MRDirALatch = 1; MRDirBLatch = 0; MRDirection = 1;
    //desiredVelocity = 5000;
    t1Enable = 1;
    //while(1);


//    while (MLEncCount < ML_F0_5){
//            
////        PDC1 += 80;
////        PDC2 += 80;
//        desiredVelocity += 80;
//        myDelay(1);
//             
//     }
    desiredVelocity = CreepSpeed;
//    PDC1 = CreepSpeed;
//    PDC2 = CreepSpeed;
    while((MLEncCount < ML_F1)||(MREncCount < MR_F1)){
        if(MLEncCount > ML_F1){
            MLDirALatch = 0; MLDirBLatch = 0;
        }
        if(MREncCount > MR_F1){
            MRDirALatch = 0; MRDirBLatch = 0;
        }
    }
    desiredVelocity = 0;
    t1Enable = 0;
    
    
//        switch (dir){
//        case 3: M_Dir(-1,-1); break;
//        case 4: M_Dir(1,1); break;
//        case L90: M_Dir(1,-1); break;
//        case R90: M_Dir(-1,1); break;
//        default: return;
//        
//    }
    switch (dir){
        case 3: MLDirALatch = 0; MLDirBLatch = 1; MLDirection = -1; MRDirALatch = 0; MRDirBLatch = 1; MRDirection = -1; break;
        case 4: M_Dir(1,1); break;
        case L90: M_Dir(1,-1); break;
        case R90: M_Dir(-1,1); break;
        default: return;
    }

    PDC1 = 1500;
    PDC2 = 1500;
    myDelay(10);
    PDC1 = 0;
    PDC2 = 0;
    M_Dir(0,0);
    MLEncCount = 0;
    MREncCount = 0;
    Stop(3);
    return;
    
}
void Stop(int dir){

    switch (dir){
        case 3: M_Dir(-1,-1); break;
        case 4: M_Dir(1,1); break;
        case L90: M_Dir(1,-1); break;
        case R90: M_Dir(-1,1); break;
        default: return;
        
    }

    PDC1 = 1500;
    PDC2 = 1500;
    myDelay(10);
    PDC1 = 0;
    PDC2 = 0;
    M_Dir(0,0);
    MLEncCount = 0;
    MREncCount = 0;
    return;
    
} 


//Stack of maze directions 
void Fast_Run(Stack instructions){
    
    LED5Latch = 0;
    LED7Latch = 0;
    LED4Latch = 0;
    myDelay(100);
    int Speed;
    
    //rotate the correct amount to face way to move
    //as told by the top of the stack
    Turn( pop(&instructions) );
    
    //up to speed. Once encoders say we're at half a cell, jump to full speed
//    desiredVelocity = CreepSpeed;
    unsigned char i, moves, turning;
    //ready for run
    
    push(&instructions, 1);
    
    while ( instructions.head > 0 ) {

        moves = pop(&instructions);
        
        //move forward correct number of cell
        for (i=0; i<moves; i++){
                //set direction
                int count;
                MLEncCount = 0;
                MREncCount = 0;
                MLDirALatch = 1; MLDirBLatch = 0; MLDirection = 1; 
                MRDirALatch = 1; MRDirBLatch = 0; MRDirection = 1;
                //desiredVelocity = 5000;
                t1Enable = 1;
                //while(1);


                while (MLEncCount < ML_F0_5){

            //        PDC1 += 80;
            //        PDC2 += 80;
                    desiredVelocity += 80;
                    myDelay(1);

                 }
                desiredVelocity = CreepSpeed;
            //    PDC1 = CreepSpeed;
            //    PDC2 = CreepSpeed;
                while((MLEncCount < ML_F1)||(MREncCount < MR_F1)){
                    if(MLEncCount > ML_F1){
                        MLDirALatch = 0; MLDirBLatch = 0;
                    }
                    if(MREncCount > MR_F1){
                        MRDirALatch = 0; MRDirBLatch = 0;
                    }
                }
                desiredVelocity = 0;
                t1Enable = 0;

                MLDirALatch = 0; MLDirBLatch = 1; MRDirALatch = 0; MRDirBLatch = 1; break;

                PDC1 = 1500;
                PDC2 = 1500;
                myDelay(10);
                PDC1 = 0;
                PDC2 = 0;
                MRDirALatch = 0; MRDirBLatch = 0; 
                MLDirALatch = 0; MLDirBLatch = 0; 
                MLEncCount = 0;
                MREncCount = 0;
        }
        
        LED7Latch = 0;
        LED4Latch = 0;
        //make turn
        if(instructions.head > 0 ){
        moves = pop(&instructions) ;

                //Create encoder variables**************************************************
            int left_Enc, right_Enc, check = 0;
            //Turning direction switch case 
            switch (moves){
                case R90:   MLDirALatch = 1; MLDirBLatch = 0; MRDirALatch = 0; MRDirBLatch = 1; left_Enc = ML_90R; right_Enc = MR_90R; break;
                case L90:   MLDirALatch = 0; MLDirBLatch = 1; MRDirALatch = 1; MRDirBLatch = 0; left_Enc = ML_90L; right_Enc = MR_90L; break;
                case T180:  MLDirALatch = 1; MLDirBLatch = 0; MRDirALatch = 0; MRDirBLatch = 1; left_Enc = ML_180; right_Enc = MR_180; break;          
                default: break;
            }

            //Reset Encoder counts
            MLEncCount = 0;
            MREncCount = 0;
            t1Enable = 1;
            while (PDC1 < MLTurnSpeed || PDC2 < MRTurnSpeed){
                desiredVelocity += 80;
                myDelay(1);
            }

            desiredVelocity = CreepSpeed;
            while((MLEncCount < left_Enc) || (MREncCount < right_Enc)){
                if(MLEncCount > left_Enc){
                    MLDirALatch = 0; MLDirBLatch = 0;
                }
                if(MREncCount > right_Enc){
                    MRDirALatch = 0; MRDirBLatch = 0;
                }

            }
            desiredVelocity = 0;
            t1Enable = 0;

                switch (moves){
//                case 3: M_Dir(-1,-1); break;
//                case 4: M_Dir(1,1); break;
                case L90: MLDirALatch = 0; MLDirBLatch = 1; MRDirALatch = 1; MRDirBLatch = 0;  break;
                case R90: MLDirALatch = 1; MLDirBLatch = 0; MRDirALatch = 0; MRDirBLatch = 1;  break;
                case T180: MLDirALatch = 0; MLDirBLatch = 1; MRDirALatch = 1; MRDirBLatch = 0; break;
                default: break;

            }

            PDC1 = 3000;
            PDC2 = 3000;
            myDelay(5);
            PDC1 = 0;
            PDC2 = 0;
                MRDirALatch = 0; MRDirBLatch = 0; 
                MLDirALatch = 0; MLDirBLatch = 0; 
            MLEncCount = 0;
            MREncCount = 0;
        LED5Latch = 0;
        LED7Latch = 0;
        

        
        
    
        }
    }
    for ( i=0; i<7; i++ ){
        
        LED4Latch = 1;
        LED5Latch = 1;
        LED7Latch = 1;

        myDelay(40);

        LED4Latch = 0;
        LED5Latch = 0;
        LED7Latch = 0;

        myDelay(40);
    }
}
        


