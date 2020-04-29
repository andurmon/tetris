#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <pic16f877a.h>

void latchClock_Col(void){
    PORTBbits.RB4 = 1;
    //wait_ms(1);
    PORTBbits.RB4 = 0;
}

void shiftClock_Col(void){
    PORTBbits.RB5 = 0;
    PORTBbits.RB5 = 1;
    //wait_ms(1);
    PORTBbits.RB5 = 0;
}

void enableFilas(void){
    PORTDbits.RD3 = 0;
}

void disableFilas(void){
    PORTDbits.RD3 = 1;
}

void latchClock_Fil(void){
    PORTDbits.RD4 = 0;
    //for(int i =0; i<100;i++);
    PORTDbits.RD4 = 1;
    //for(int i =0; i<100;i++);
    PORTDbits.RD4 = 0;
}

void shiftClock_Fil(void){
    PORTDbits.RD5 = 0;
    //for(int i =0; i<100;i++);
    PORTDbits.RD5 = 1;
    //for(int i =0; i<100;i++);
    PORTDbits.RD5 = 0;
}

void setColumnas(uint8_t reg_value){
    int i = 0;
    uint8_t indice = (1<<2);
    uint8_t valor = reg_value & indice;
    for(i=0;i<8;i++){
        valor = (reg_value & (1<<i) )>>i;
        PORTBbits.RB1 = valor; 
        shiftClock_Col();
        
        //wait_ms(5000);
    }
    latchClock_Col();
    return;
}

void setFilas(uint16_t reg_value){
    
    int i = 0;
    uint16_t valor = 0;
    
    /*for(i=0;i<16;i++){
        PORTDbits.RD2 = 1;//valor; 
        shiftClock_Fil();
    }
    latchClock_Fil();*/
    
    for(i=0;i<16;i++){
        //valor = (reg_value & (1<<i) )>>i;
        PORTDbits.RD2 = (reg_value & (1<<i) )>>i;//valor; 
        
        shiftClock_Fil();
        
    }
    //latchClock_Fil();
    enableFilas();
    return;
}

void shiftBitColumna(uint8_t bit){
    PORTBbits.RB1 = bit & 0x01;
    shiftClock_Col();
    latchClock_Col();
    latchClock_Fil();
}