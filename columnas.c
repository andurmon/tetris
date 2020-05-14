#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <pic16f877a.h>
#include "filas.h"

void latchClock_Col(void){
    PORTDbits.RD6 = 1;
    PORTDbits.RD6 = 0;
}

void shiftClock_Col(void){
    PORTDbits.RD7 = 0;
    PORTDbits.RD7 = 1;
    PORTDbits.RD7 = 0;
}

void setColumnas(uint8_t reg_value){
    int i = 0;
    uint8_t indice = (1<<2);
    uint8_t valor = reg_value & indice;
    for(i=0;i<8;i++){
        valor = (reg_value & (1<<i) )>>i;
        PORTDbits.RD4 = valor; 
        shiftClock_Col();
    }
    latchClock_Col();
    return;
}


void shiftBitColumna(uint8_t bit){
    PORTDbits.RD4= bit & 0x01;
    shiftClock_Col();
    latchClock_Col();
    latchClock_Fil();
}