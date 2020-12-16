#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "LCD.h"
#include <pic16f877a.h>

#define _XTAL_FREQ 4000000

void init_LCD(void){
    bool DL=true;   // 1 => 8 bit bus mode control
    bool N=true;    // 1 => 2 line display
    bool F=false;
    
    bool ID=true;   //1 => cursor move to right
    bool S=false;   //shift of entire display
    
    bool D = true, C=true, B=true;
    
    __delay_ms(200);
    functionSet(true, false, false);
    __delay_ms(10);
    functionSet(true, false, false);
    __delay_ms(10);
    functionSet(true, false, false);
    __delay_ms(10);
    
    functionSet(DL, N, F);
    __delay_ms(10);
    displayONOFF(false,false,false);
    clearDisplay();
    entryModeSet(ID, S);
    
    displayONOFF(D,C,B);
    returnHome();
}

void clearDisplay(void){
    clearRS();
    clearRW();
    setData(0x01);
    __delay_ms(10);
}

void returnHome(void){
    clearRS();
    clearRW();
    setData(0x2);
    __delay_ms(10);
}

void entryModeSet(bool ID, bool SH){
    uint8_t data = 0x04;
    clearRS();
    clearRW();
    data = data | (ID?0x2:0x0) | (SH?0x1:0x0);
    setData(data);
    __delay_ms(10);
}

void displayONOFF(bool D, bool C, bool B){
    uint8_t data = 0x08;
    clearRS();
    clearRW();
    data = data | (D?0x04:0x00) | (C?0x02:0x00) | (B?0x01:0x00);
    setData(data);
    __delay_ms(10);
}

void functionSet(bool DL, bool N, bool F){
    uint8_t data = 0x20;
    clearRS();
    clearRW();
    data = data | (DL?0x10:0x00) | (N?0x08:0x00) | (F?0x04:0x00);
    setData(data);
}

void setRS(void){
    PORTCbits.RC0 = 1;
}

void clearRS(void){
    PORTCbits.RC0 = 0;
}

void setRW(void){
    PORTCbits.RC1 = 1;
}

void clearRW(void){
    PORTCbits.RC1 = 0;
}

void setE(void){
    PORTCbits.RC2 = 1;
}

void clearE(void){
    PORTCbits.RC2 = 0;
}

void setData(uint8_t data){
    PORTAbits.RA0 = data & 0x1;  //D0
    PORTAbits.RA1 = (data >>1) & 0x1;  //D1
    PORTAbits.RA2 = (data >>2) & 0x1;  //D2
    PORTAbits.RA3 = (data >>3) & 0x1;  //D3
    PORTAbits.RA4 = (data >>4) & 0x1;  //D4
    PORTAbits.RA5 = (data >>5) & 0x1;  //D5
    PORTEbits.RE0 = (data >>6) & 0x1;  //D6
    PORTEbits.RE1 = (data >>7) & 0x1;  //D7
}