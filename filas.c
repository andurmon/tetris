#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <pic16f877a.h>


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