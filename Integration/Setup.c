#include "defs.h"
#include "p30F4011.h"

void setupA2D(void)
{
ADCON1bits.ADON=0; //switch the A2D converter off during configuration
//configure the analog input
//the default state of the TRIS register is 1, i.e. they are inputs
//additionally we configure the ports we are going to use in the
//A2D peripheral
ADPCFG=0xffff; //make all of them digital
//and then select the ones we use in analog mode
ADPCFGbits.PCFG0=0; //we use analog input 0
ADPCFGbits.PCFG1=0; // and analog input 1
//we now need configure the "scan sequence", we set the whole register
ADCSSL=0x0003 ; //select scanned channels: 0b 0000 0000 0000 0011
ADCON2bits.CSCNA=1; //this enables the scanning
//we will sample those channels in (close) sequence
//and connect the negative input of the s&h to VrefADCHSbits.CH0NA=0;
ADCHSbits.CH0SA=0b0000; //we scan through the other channels,
//so this does not matter
ADCON1bits.SIMSAM=0; //no simultaneous sampling
ADCON2bits.CHPS=0b00; //and we only sample and hold unit 0 (Ch0)
ADCON2bits.SMPI=0b0001; // generate an interrupt after conversion of
//two channels (0b0001 + 1)
//select the conversion clock
ADCON2bits.ALTS=0; //always use multiplexer settings A, i.e. scanning through inputs
ADCON2bits.BUFM=0; //the conversion buffer is selected to use all 16 words
//(not 2 x 8 words)
ADCON2bits.VCFG=0b000; //this selects the AVdd and AVss as voltage reference
ADCON1bits.FORM=0b00; //we use the (unsigned) integer format for the A2D value
ADCON3bits.ADRC=0; //clock is derived from internal clock;
//Tad needs to be selected and must be a minimum of 83.33 ns
//we derive Tad from Tcyc ==> Tad=32xTcyc = 2us
ADCON3bits.ADCS=0b111111; //sets the conversion period to 32 x Tcyc (slowest possible)
ADCON3bits.SAMC=0b11111; // sets the auto sample speed to 32xTad ==> slowest setting
//we need to select the source to start a conversion
ADCON1bits.SSRC=0b111; //conversion (not sampling) is started with A2D clock
//afer SAMC (see above) cycles
ADCON1bits.SAMP=1; //we are ready for sampling
ADCON1bits.ASAM=0; //we start the autosampling in the timer ISR
//lets now enable the interrupt and set the prio
IFS0bits.ADIF=0 ; //clear the interrupt flag (in case it was on)
IPC2bits.ADIP=5 ; // lets set the A2D prio to 5;
IEC0bits.ADIE=1; //enable a2d interrupts
//finally, we switch on the A2D converter again
ADCON1bits.ADON=1; //ready to convert
}

void IOSetup(void){
    //SETUP THE TRISTATES TO DETERMINE INPUT OR OUTPUT

    //disable PWM3 so LED can be used
    PWMCON1bits.PEN3H = 0;

    //Sensors

    Sensor1Tris  = 0;    //Output
    Sensor2Tris  = 0;    //Output
    Sensor3Tris  = 0;    //Output
    //Motor Direction
    MLDirATris   = 0;    //Output
    MLDirBTris   = 0;    //Output
    MRDirATris   = 0;    //Output
    MRDirBTris   = 0;    //Output
    //LED's
    LED3Tris = 0;        //Output
    LED4Tris = 0;        //Output
    LED5Tris = 0;        //Output
    LED6Tris = 0;        //Output
    LED7Tris = 0;        //Output

 }
//
void UARTSetup(void){
    //*****UART1 SETUP
    U1_UARTEN = 0;
    U1BRG = 104;
    U1_LPBACK = 0;
    U1_WAKE = 0;
    U1_ABAUD = 0;
    U1_PDSEL0 = 0;
    U1_PDSEL1 = 0;
    U1_STSEL = 0;
    //interrupt select bits 
    U1_URXISEL0 = 0;
    U1_URXISEL1 = 0;
    //clear flag, set priority and enable recieve
    U1_RXIF = 0; 
    U1_RXIP = 1; 
    U1_RXIE = 1; 
    //Clear TX register
    U1TXREG = 0; 
    U1_UARTEN = 1; 
    U1_UTXEN = 1; 
    
//    //*****UART2 SETUP
    U2_UARTEN = 0;
    U2BRG = 104;
    U2_LPBACK = 0;
    U2_WAKE = 0;
    U2_ABAUD = 0;
    U2_PDSEL0 = 0;
    U2_PDSEL1 = 0;
    U2_STSEL = 0;
    //interrupt select bits 
    U2_URXISEL0 = 0;
    U2_URXISEL1 = 0;
    //clear flag, set priority and enable recieve
    U2_RXIF = 0;
    U2_RXIP = 1;
    U2_RXIE = 1;
    //Clear TX register
    U2TXREG = 0;
    //enable UART and enable transmission 
    //enable UART and enable transmission 

    U2_UARTEN = 1;
    U2_UTXEN = 1;
    
    return;
}
void PWMSetup(void){
    TRISE = 0x00; // make sure PWM pins are set to be outputs
    PORTE = 0x00; // clear the outputs 
    
    //PTCONbits.PTOPS = 1; // PWM timer post-scale
    //PTCONbits.PTCKPS = 0; // PWM timer pre-scale
    PTCONbits.PTMOD = 2; // PWM operates in Up-down Mode continuously

    PTMR = 0; // PWM counter value, start at 0
    
    //Set PreScaler to 4
    PTCKPS0 = 1;
    PTCKPS1 = 0;
    
    PTPER = 16000; // PWM Timebase period
    //PWMCON1bits.PMOD3 = 0; // PWM in complimentary mode
    PWMCON1bits.PMOD2 = 0; // PWM in complimentary mode
    PWMCON1bits.PMOD1 = 0; // PWM in complimentary mode
    PWMCON1bits.PEN3H = 0; // PWM High pin is enabled
    PWMCON1bits.PEN2H = 1; // PWM High pin is enabled
    PWMCON1bits.PEN1H = 1; // PWM High pin is enabled
    PWMCON1bits.PEN3L = 0; // PWM Low pin enabled (direction control later?)
    PWMCON1bits.PEN2L = 1; // PWM Low pin enabled (direction control later?)
    PWMCON1bits.PEN1L = 1; // PWM Low pin enabled (direction control later?)
//    OVDCONbits.POVD3L = 0;
//    OVDCONbits.POVD3H = 0;
    //OVDCONbits.POUT3H = 1;
    PTCONbits.PTEN = 1; // Enable PWM Timerbase!
}
void timer1Setup(){
    //Cyclic Timer Setup
        //Clear TON
        TON = 0;
        //Reset the timer register start
        TMR1 = 0;
        //Prescaler Set
        TCKPS0 = 1;
        TCKPS1 = 0;
        //Choose Period
        PR1 = 10000;
        //Internal clock
        TCS = 0;
        //Priority Setup
        t1Priority0 = 1;
        t1Priority1 = 1;
        t1Priority2 = 0;
        //Flag Setup
        t1Flag = 0;
        //Enable Interrupt
       // t1Enable = 1;
//        //Set TON on
        TON = 1;
        return;
}


