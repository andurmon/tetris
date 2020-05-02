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
#include <time.h> 
#include "init.h"
#include "columnas.h"
#include "filas.h"
#include <pic16f877a.h>

#define _XTAL_FREQ 4000000

uint8_t columna = 1;
uint16_t corazon[8] = {0x0030, 0x0048, 0x0044, 0x0022, 0x0044, 0x0048, 0x0030, 0x0000};
uint16_t test[8] =  {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};

uint16_t pantalla[8] =  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
uint16_t figuras[6][4]= {{0x2, 0x2, 0x3, 0x0},
                        {0x0,0x3,0x2,0x2},
                        {0x1,0x3,0x2,0x0},
                        {0x0, 0x2, 0x3, 0x1},
                        {0x1,0x1,0x1,0x1},
                        {0x0, 0x3,0x3,0x0}};

unsigned char led = 0;
int counter = 0;
uint8_t ficha_pos = 16;
uint8_t ficha_actual = 0;
void updateScreen(uint16_t screen[8]);
uint8_t tecla = 0;

void __interrupt() Timer0_ISR(void){
            
    if(INTCONbits.TMR0IF){
        
        INTCONbits.TMR0IF=0;
        counter ++;
        if(counter >= 3906){
            PORTBbits.RB0 = led;
            led= ~led;
            ficha_pos--;
            counter=0;
            if(ficha_pos==0){
                ficha_pos=16;
                ficha_actual = rand() % 5;
            }
        }
    }
    else if(INTCONbits.RBIF){
        if(PORTBbits.RB5 == 0){
            ficha_pos=16;
        }
        INTCONbits.RBIF=0;
        
    }
}

int main(int argc, char** argv) {
    
    //srand((unsigned) time(NULL));
    init_pines();
    init_interrupt();
    init_timer();
    int i=0;
    setColumnas(0x00);
    setFilas(0x0000);
    
    while(1){
        pantalla[2]=  figuras[ficha_actual][0] << (ficha_pos-1);
        pantalla[3]=  figuras[ficha_actual][1] << (ficha_pos-1);
        pantalla[4]=  figuras[ficha_actual][2] << (ficha_pos-1);
        pantalla[5]=  figuras[ficha_actual][3] << (ficha_pos-1);
        
        updateScreen(pantalla);
        
    }
    return (EXIT_SUCCESS); 
}



void updateScreen(uint16_t screen[8]){
    if(columna == 9){
        columna=1;
        setFilas(~screen[columna-1]);
        shiftBitColumna(1);
    }
    else{
        columna++;
        setFilas(~screen[columna-1]);
        shiftBitColumna(0);
    }
}