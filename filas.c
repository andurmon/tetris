#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <pic16f877a.h>

void latchClock_Fil(void){
    PORTCbits.RC6 = 0;
    PORTCbits.RC6 = 1;
    PORTCbits.RC6 = 0;
}

void shiftClock_Fil(void){
    PORTCbits.RC7 = 0;
    PORTCbits.RC7 = 1;
    PORTCbits.RC7 = 0;
}

void setFilas(uint16_t reg_value){
    int i = 0;
    for(i=0;i<16;i++){
        PORTCbits.RC4 = (reg_value & (1<<i) )>>i;//valor; 
        shiftClock_Fil();
    }
    return;
}