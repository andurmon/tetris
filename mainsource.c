/* 
 * File:   mainsource.c
 * Author: Andres Uribe Montoya
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
#include <string.h> 
#include "init.h"
#include "columnas.h"
#include "filas.h"
#include "screen.h"
#include "control.h"
#include <pic16f877a.h>

#define _XTAL_FREQ 4000000

/*struct controlSign {
    uint8_t columna;
    uint8_t tecla;
    uint8_t led;
    uint8_t ficha_Vpos;     //Posicion VERTICAL de la ficha que cae
    uint8_t ficha_Hpos;     //Posicion HORIZONTAL de la ficha que cae
    uint8_t ficha_actual;
    uint8_t derecha;
    uint8_t izquierda;
};

struct controlSign con;

uint16_t figuras[6][4]= {{0x2, 0x2, 0x3, 0x0},
                        {0x0,0x3,0x2,0x2},
                        {0x1,0x3,0x2,0x0},
                        {0x0, 0x2, 0x3, 0x1},
                        {0x1,0x1,0x1,0x1},
                        {0x0, 0x3,0x3,0x0}};


uint16_t timerCount = 0;
uint16_t pantalla[8] =  {0x0000};
uint16_t fondo[8] = {0x0000};
uint16_t ficha[8] = {0x0000};*/

void updateScreen(uint16_t screen[8]);
void drawFigure(void);
void drawBground(void);

int main(int argc, char** argv) {
    
    //uint16_t corazon[8] = {0x0030, 0x0048, 0x0044, 0x0022, 0x0044, 0x0048, 0x0030, 0x0000};
    //uint16_t test[8] =  {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};
    
    init_pines();
    init_interrupt();
    init_timer();
    int i=0;
    con.columna = 1;
    con.ficha_Vpos = 16;
    con.ficha_Hpos = 2;
    
    drawBground();
    
    while(1){
        drawFigure();
        for(i=0; i<8; i++){
            pantalla[i] = ficha[i] | fondo[i];
        }
        
        updateScreen(pantalla);
        
    }
    return (EXIT_SUCCESS); 
}

void __interrupt() Timer0_ISR(void){
            
    if(INTCONbits.TMR0IF){
        
        INTCONbits.TMR0IF=0;
        timerCount ++;
        if(timerCount >= 3906){
            PORTBbits.RB0 = con.led;
            con.led= ~con.led;
            con.ficha_Vpos--;
            timerCount = 0;
            if(con.ficha_Vpos==0){
                con.ficha_Vpos = 16;
                con.ficha_actual = rand() % 5;
            }
        }
    }
    else if(INTCONbits.RBIF){
        if(PORTBbits.RB5 == 0){
            con.derecha = 1;
            con.izquierda = 0;
        }
        if(PORTBbits.RB4 == 0){
            con.derecha = 0;
            con.izquierda = 1;
        }
        INTCONbits.RBIF=0;
        
    }
}

