#include <xc.h>
#include "init.h"
#include <pic16f877a.h>

void init_pines(void){
    init_pines_LCD();
    init_pines_fil();
    init_pines_col();
    init_pines_in();
}

void init_pines_in(void){
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB4 = 1; 
    TRISBbits.TRISB3 = 1;
}

void init_pines_LCD(void){
    //ADCON1bits.PCFG0 = 1;
    ADCON1 = 0x7;
    
    TRISAbits.TRISA0 = 0; //D0
    TRISAbits.TRISA1 = 0; //D1
    TRISAbits.TRISA2 = 0; //D2
    TRISAbits.TRISA3 = 0; //D3
    TRISAbits.TRISA4 = 0; //D4
    TRISAbits.TRISA5 = 0; //D5
    TRISEbits.TRISE0 = 0; //D6
    TRISEbits.TRISE1 = 0; //D7
    
    TRISCbits.TRISC0 = 0; //RS
    TRISCbits.TRISC1 = 0; //R/W
    TRISCbits.TRISC2 = 0; //E
    
    PORTAbits.RA0 = 0;  //D0
    PORTAbits.RA1 = 0;  //D1
    PORTAbits.RA2 = 0;  //D2
    PORTAbits.RA3 = 0;  //D3
    PORTAbits.RA4 = 0;  //D4
    PORTAbits.RA5 = 0;  //D5
    PORTEbits.RE0 = 0;  //D6
    PORTEbits.RE1 = 0;  //D7
    
    PORTCbits.RC0 = 0;  //RS
    PORTCbits.RC1 = 0;  //R/W
    PORTCbits.RC2 = 0;  //E
}

void init_pines_fil(void){
    
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 0;
}

void init_pines_col(void){
    TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;
    
    TRISDbits.TRISD4 = 0; //Data
    TRISDbits.TRISD5 = 0; //OE
    TRISDbits.TRISD6 = 0; //Latch
    TRISDbits.TRISD7 = 0; //Shift

    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
}

void init_interrupt(void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    
    OPTION_REGbits.nRBPU = 0;
}

void init_timer(void){
    
    TMR0=0;
    
    /* ITCON Register
     * The INTCON register is a readable and writable register,
     * which contains various enable and flag bits for the
     * TMR0 register overflow, RB port change and external
     * RB0/INT pin interrupts
     */
    INTCONbits.GIE = 1;     //Global Interrupt Enable bit
    INTCONbits.TMR0IE = 1;  //TMR0 Overflow Interrupt Enable bit
    INTCONbits.TMR0IF = 0;  //TMR0 Overflow Interrupt Flag bit
    
    /* OPTION_REG Register
     * The OPTION_REG Register is a readable and writable
     * register, which contains various control bits to configure
     * the TMR0 prescaler/WDT postscaler (single assignable
     * register known also as the prescaler), the external
     * INT interrupt, TMR0 and the weak pull-ups on PORTB.
    */
    OPTION_REGbits.PSA = 0;     //Prescaler Assignment bit 
    OPTION_REGbits.PS0 = 1;     //Prescaler Rate Select bits
    OPTION_REGbits.PS1 = 1;     // 111 => 1:256 prescaler
    OPTION_REGbits.PS2 = 1;     // 000 => 1:2 prescaler
    OPTION_REGbits.T0CS = 0;    //TMR0 Clock Source Select bit
}
