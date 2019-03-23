#include "Setup.h"

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

void PWMSetup(void){
    //PTEN Turns off PWM
    PTEN = 0;
    //Set PreScaler to 4
    PTCKPS = 1;
    
    //Set the PWM Period to 250Hz
    PTPER = 16000;
    //Set PWM Mode
    PTMOD = 2;
    //Enable PWM 1 low-side driver
    PEN1L = 1;
    //Enable PWM 1 high-side driver
    PEN1H = 1;
    //Enable PWM 2 low-side driver
    PEN2L = 1;
    //Enable PWM 2 high-side driver
    PEN2H = 1;
    //Turn PWM On
    PTEN = 1;
}

void UARTSetup(void){
    //*****UART1 SETUP
    U1_UARTEN = 0;
    U1BRG = 16;
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
    U1_RXIP = 3; 
    U1_RXIE = 1; 
    //Clear TX register
    U1TXREG = 0; 
    //enable UART and enable transmission 
    U1_UARTEN = 1; 
    U1_UTXEN = 1; 
    
    //*****UART2 SETUP
    U2_UARTEN = 0;
    U2BRG = 16;
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
    U2_RXIP = 3;
    U2_RXIE = 1;
    //Clear TX register
    U2TXREG = 0;
    //enable UART and enable transmission 
    U2_UARTEN = 1;
    U2_UTXEN = 1;
}

void ADC_Setup(void)
{
    ADCON1bits.ADON=0; //switch the A2D converter off during configuration
    //configure the analog input
    //the default state of the TRIS register is 1, i.e. they are inputs
    //additionally we configure the ports we are going to use in the
    //A2D peripheral
    ADPCFG=0xffff; //make all of them digital
    //and then select the ones we use in analog mode
    ADPCFGbits.PCFG0=0; //we use analog input 0
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
    ADCON1bits.ADON=1; //ready to convert!
}



void timer1Setup(void){
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

