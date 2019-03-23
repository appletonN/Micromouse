#ifndef SETUP_H
#define	SETUP_H

#include <p30Fxxxx.h>



////////////////////////////////////////////////////
/////                   I/O                    /////
////////////////////////////////////////////////////   


//********** Sensors Selection **********************

//Sensor 1 RB1 
#define Sensor1Port     PORTBbits.RB1
#define Sensor1Latch    LATBbits.LATB1
#define Sensor1Tris     TRISBbits.TRISB1
//Sensor 2 RB2
#define Sensor2Port     PORTBbits.RB2
#define Sensor2Latch    LATBbits.LATB2
#define Sensor2Tris     TRISBbits.TRISB2
//Sensor 2 RB2
#define Sensor3Port     PORTBbits.RB3
#define Sensor3Latch    LATBbits.LATB3
#define Sensor3Tris     TRISBbits.TRISB3

//********** Motor Direction **********************
//Motor 1 Direction A (RD1)
#define MLDirATris      TRISDbits.TRISD1 
#define MLDirALatch     LATDbits.LATD1
#define MLDirAPort      PORTDbits.RD1   
//Motor 1 Direction B (RD3)
#define MLDirBTris      TRISDbits.TRISD3
#define MLDirBLatch     LATDbits.LATD3
#define MLDirBPort      PORTDbits.RD3  
//Motor 2 Direction A (RD2)
#define MRDirATris      TRISDbits.TRISD2 
#define MRDirALatch     LATDbits.LATD2
#define MRDirAPort      PORTDbits.RD2
//Motor 2 Direction B (RD0)
#define MRDirBTris      TRISDbits.TRISD0
#define MRDirBLatch     LATDbits.LATD0
#define MRDirBPort      PORTDbits.RD0

//********** LED's **********************
//LED3 - pin 9 - RE4
#define LED3Tris      TRISEbits.TRISE4
#define LED3Latch     LATEbits.LATE4
#define LED3Port      PORTEbits.RE4
//LED4 - pin 24 - RB5
#define LED4Tris      TRISBbits.TRISB5
#define LED4Latch     LATBbits.LATB5
#define LED4Port      PORTBbits.RB5
//LED5 - pin 25 - RB6
#define LED5Tris      TRISBbits.TRISB6
#define LED5Latch     LATBbits.LATB6
#define LED5Port      PORTBbits.RB6
//LED6 - pin 26 - RB7
#define LED6Tris      TRISBbits.TRISB7
#define LED6Latch     LATBbits.LATB7
#define LED6Port      PORTBbits.RB7
//LED7 - pin 27 - RB8
#define LED7Tris      TRISBbits.TRISB8
#define LED7Latch     LATBbits.LATB8
#define LED7Port      PORTBbits.RB8


//*****************Misc. Definitions*******************
//Directions
#define F 1
#define B -1

//turn Directions
#define L -1
#define R 1

//PID Control Gains
#define Kp 1
#define Ki 1
#define Kd 1

//Desired sensor value
#define Des_Sensor_Val 1
#define sensor_Threshold 1

//Reset State for PID
#define Reset 9




/////////////////////////////////////////////////
/////               PWM                     /////
/////////////////////////////////////////////////

//PWM1 Bit Definitions
//PT1ConBits
#define PTMOD   PTCONbits.PTMOD
#define PTCKPS  PTCONbits.PTCKPS
#define PTOPS   PTCONbits.PTOPS
#define PTSIDL  PTCONbits.PTSIDL
#define PTEN    PTCONbits.PTEN
//PWMCONBits
#define PMOD1   PWMCON1bits.PMOD1
#define PEN1L   PWMCON1bits.PEN1L
#define PEN1H   PWMCON1bits.PEN1H
//PWM2CONBits
#define PMOD2   PWMCON1bits.PMOD2
#define PEN2L   PWMCON1bits.PEN2L
#define PEN2H   PWMCON1bits.PEN2H

//PWM2 Bit Definitions 
//PT2ConBits



/////////////////////////////////////////////
/////               UART                /////
/////////////////////////////////////////////


//***********UART 1 Mode bits *****************
#define U1_UARTEN U1MODEbits.UARTEN
#define U1_LPBACK U1MODEbits.LPBACK    
#define U1_ABAUD U1MODEbits.ABAUD   
#define U1_WAKE U1MODEbits.WAKE    
#define U1_PDSEL0 U1MODEbits.PDSEL0
#define U1_PDSEL1 U1MODEbits.PDSEL1
#define U1_STSEL U1MODEbits.STSEL

//U2STA bits 
#define U1_URXISEL0 U1STAbits.URXISEL0
#define U1_URXISEL1 U1STAbits.URXISEL1
    
//Flag and priority bits 
#define U1_RXIF IFS0bits.U1RXIF
#define U1_RXIP IPC2bits.U1RXIP 
#define U1_RXIE C1INTEbits.IRXIE
    
//Enable transmission bit 
#define U1_UTXEN U1STAbits.UTXEN  
    
    
//***********UART 2 Mode bits *****************
#define U2_UARTEN U2MODEbits.UARTEN
#define U2_LPBACK U2MODEbits.LPBACK    
#define U2_ABAUD U2MODEbits.ABAUD   
#define U2_WAKE U2MODEbits.WAKE    
#define U2_PDSEL0 U2MODEbits.PDSEL0
#define U2_PDSEL1 U2MODEbits.PDSEL1
#define U2_STSEL U2MODEbits.STSEL

//U2STA bits 
#define U2_URXISEL0 U2STAbits.URXISEL0
#define U2_URXISEL1 U2STAbits.URXISEL1
    
//Flag and priority bits 
#define U2_RXIF IFS1bits.U2RXIF
#define U2_RXIP IPC6bits.U2RXIP
#define U2_RXIE IEC1bits.U2RXIE
    
//Enable transmission bit 
#define U2_UTXEN U2STAbits.UTXEN      
    

#define T1on                T1CONbits.TON 
#define T1Prescaler         T1CONbits.TCKPS 
#define T1inputClock        T1CONbits.TCS
#define T1IdleStop          T1CONbits.TSIDL
#define T1Gate              T1CONbits.TGATE 

#define T1Flag              IFS0bits.T1IF  
#define T1Priority          IPC0bits.T1IP
#define T1InteruptEnable    IEC0bits.T1IE 



void IOSetup(void);

void PWMSetup(void);

void UARTSetup(void);

void timer1Setup(void);



#endif	/* SETUP_H */

