/* 
 * File:   mainsource.c
 * Author: ASUS
 *
 * Created on 28 de febrero de 2020, 03:11 PM
 */

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "init.h"
#include "matriz_leds.h"
#include <pic16f877a.h>

void wait_ms(uint16_t time);
unsigned char value[8]={1,0,0,1,0,1,1,0};
uint8_t value2 = 0b10010110;
uint16_t value3 = 0b1001011010101010;
uint16_t value4 = 0xffff;
//unsigned char value[8]={1,0,0,0,0,0,0,0};
uint16_t columna = 1;

int main(int argc, char** argv) {
    init_pines();
    
    int i=0;
    /*for(i=0;i<=8;i++){
        PORTBbits.RB2 = 0; 
        shiftClock_Col();
        latchClock_Col();
    }*/

    setColumnas(0x00);
    //
    setFilas(0x0000);
    i=0;
    PORTBbits.RB0 = 1;
    while(1){
        
        //setFilas(0x3000);
        /*PORTBbits.RB1 = 1;
        wait_ms(50);
        PORTBbits.RB1 = 0;
        wait_ms(50);*/
        switch(columna){
            case 1:
                //disableFilas();
                setFilas(0xffcf);
                shiftBitColumna(1);
                columna=2;
                
                break;
            case 2:
                //disableFilas();
                
                setFilas(0xffb7);
                shiftBitColumna(0);
                columna=3;
                break;            
            case 3:
                //disableFilas();
                
                setFilas(0xffbb);
                shiftBitColumna(0);
                columna=4;
                break;
            case 4:
                //disableFilas();
                setFilas(0xffdd);
                shiftBitColumna(0);
                columna=5;
                break;
            case 5:
                //disableFilas();
                
                setFilas(0xffbb);
                shiftBitColumna(0);
                columna=6;
                break;
            case 6:
                //disableFilas();
                
                setFilas(0xffb7);
                shiftBitColumna(0);
                columna=7;
                break;
            case 7:
                //disableFilas();
                
                setFilas(0xffcf);
                shiftBitColumna(0);
                columna=8;
                break;
            case 8:
                //disableFilas()
                setFilas(0xffff);
                shiftBitColumna(0);
                columna=1;
                break;
        }
    }
    return (EXIT_SUCCESS); 
}


/*void wait_ms(int time){
    static long timel = 0;
    timel = (long) time; //* 500;
    for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}*/

void wait_ms(uint16_t time)
{
    static long timel = 0;
    timel = time*1000L;
    for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}