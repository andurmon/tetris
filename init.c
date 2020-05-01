#include <xc.h>
#include <pic16f877a.h>

void init_pines_fil(void){
    
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    
    PORTDbits.RD2 = 0;
    PORTDbits.RD3 = 0;
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
}

void init_pines_col(void){
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
    PORTBbits.RB4 = 0;
    PORTBbits.RB5 = 0;
}
void init_pines(void){
    
    init_pines_fil();
    init_pines_col();
    
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
    OPTION_REGbits.PSA = 1;   //Prescaler Assignment bit 
    OPTION_REGbits.PS0 = 1;   //Prescaler Rate Select bits
    OPTION_REGbits.PS1 = 1;   // 111 => 1:256 prescaler
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.T0CS = 0;  //TMR0 Clock Source Select bit
}
