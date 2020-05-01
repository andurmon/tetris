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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "init.h"
#include "columnas.h"
#include "filas.h"
#include <pic16f877a.h>

#define _XTAL_FREQ 4000000

uint8_t columna = 1;
//uint16_t corazon[8] = {0xffcf, 0xffb7, 0xffbb, 0xffdd, 0xffbb, 0xffb7, 0xffcf, 0xffff};
uint16_t corazon[8] = {0x0030, 0x0048, 0x0044, 0x0022, 0x0044, 0x0048, 0x0030, 0x0000};
uint16_t pantalla[8] =  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

uint16_t figura[4]= {0x4, 0x4, 0x6, 0x0};//{0x4000, 0x4000, 0x6000, 0x0000};

unsigned char led = 0;
int counter = 0;
void updateScreen(uint16_t dibujo[8]);

void __interrupt() Timer0_ISR(void){
    
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF=0;
        counter ++;
        if(counter >= 3906){
            counter=0;
            PORTBbits.RB0 = led;
            led= ~led;
        }
    }
}

int main(int argc, char** argv) {
    
    init_pines();
    init_timer();
    int i=0;

    setColumnas(0x00);
    setFilas(0x0000);

    pantalla[2]= pantalla[2] | figura[0]<<13;
    pantalla[3]= pantalla[3] | figura[1]<<13;
    pantalla[4]= pantalla[4] | figura[2]<<13;
    pantalla[5]= pantalla[5] | figura[3]<<13;
    
    while(1){
        
        updateScreen(pantalla);
    }
    return (EXIT_SUCCESS); 
}



void updateScreen(uint16_t dibujo[8]){
    switch(columna){
        case 1:
            setFilas(~dibujo[0]);
            shiftBitColumna(1);
            columna=2;
            break;
        case 2:
            setFilas(~dibujo[1]);
            shiftBitColumna(0);
            columna=3;
            break;            
        case 3:
            setFilas(~dibujo[2]);
            shiftBitColumna(0);
            columna=4;
            break;
        case 4:
            setFilas(~dibujo[3]);
            shiftBitColumna(0);
            columna=5;
            break;
        case 5:
            setFilas(~dibujo[4]);
            shiftBitColumna(0);
            columna=6;
            break;
        case 6:
            setFilas(~dibujo[5]);
            shiftBitColumna(0);
            columna=7;
            break;
        case 7:
            setFilas(~dibujo[6]);
            shiftBitColumna(0);
            columna=8;
            break;
        case 8:
            setFilas(~dibujo[7]);
            shiftBitColumna(0);
            columna=1;
            break;
    }
}