#ifndef SETUP_H
#define	SETUP_H

#include <p30Fxxxx.h>



////////////////////////////////////////////////////
/////                   I/O                    /////
////////////////////////////////////////////////////   


//********** Sensors Selection **********************

//Sensor 1 RB1 
#define Sensor1Port     PORTFbits.RF1
#define Sensor1Latch    LATFbits.LATF1
#define Sensor1Tris     TRISFbits.TRISF1
//Sensor 2 RB2
#define Sensor2Port     PORTFbits.RF0
#define Sensor2Latch    LATFbits.LATF0
#define Sensor2Tris     TRISFbits.TRISF0
//Sensor 3 RB2
#define Sensor3Port     PORTEbits.RE5
#define Sensor3Latch    LATEbits.LATE5
#define Sensor3Tris     TRISEbits.TRISE5
#define Sensor3         OVDCONbits.POVD3H 
//********** Motor Direction **********************
//Motor 1 Direction A (RD1)
#define MRDirATris      TRISDbits.TRISD1 
#define MRDirALatch     LATDbits.LATD1
#define MRDirAPort      PORTDbits.RD1   
//Motor 1 Direction B (RD3)
#define MRDirBTris      TRISDbits.TRISD3
#define MRDirBLatch     LATDbits.LATD3
#define MRDirBPort      PORTDbits.RD3  
//Motor 2 Direction A (RD2)
#define MLDirATris      TRISDbits.TRISD2 
#define MLDirALatch     LATDbits.LATD2
#define MLDirAPort      PORTDbits.RD2
//Motor 2 Direction B (RD0)
#define MLDirBTris      TRISDbits.TRISD0
#define MLDirBLatch     LATDbits.LATD0
#define MLDirBPort      PORTDbits.RD0

//********** LED's **********************
//LED3 - pin 9 - RE4
#define LED3Tris      TRISEbits.TRISE4
#define LED3Latch     LATEbits.LATE4
#define LED3Port      PORTEbits.RE4
 
#define LED3 OVDCONbits.POVD3L

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






/////////////////////////////////////////////////
/////               PWM                     /////
/////////////////////////////////////////////////

//PWM1 Bit Definitions
//PT1ConBits
#define PTCKPS0  PTCONbits.PTCKPS0
#define PTCKPS1  PTCONbits.PTCKPS1
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
#define U1_RXIE IEC0bits.U1RXIE
    
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
    

//********Timer 1 Defines*************************
//Flag bit
#define t1Flag IFS0bits.T1IF
//Enable bit
#define t1Enable IEC0bits.T1IE
//Priority Bits
#define t1Priority0 IPC0bits.T1IP0
#define t1Priority1 IPC0bits.T1IP1
#define t1Priority2 IPC0bits.T1IP2
//TCON
#define TCS T1CONbits.TCS
#define TSYNC T1CONbits.TSYNC
#define TCKPS T1CONbits.TCKPS
#define TGATE T1CONbits.TGATE
#define TSIDL T1CONbits.TSIDL
#define TON T1CONbits.TON
#define TCKPS0 T1CONbits.TCKPS0
#define TCKPS1 T1CONbits.TCKPS1




void IOSetup(void);
//
void PWMSetup(void);
//
void UARTSetup(void);
//
void timer1Setup(void);
//


#endif	/* SETUP_H */

