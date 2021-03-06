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
#include <stdbool.h>
#include "init.h"
#include "LCD.h"
#include "columnas.h"
#include "filas.h"
#include "screen.h"
#include "control.h"
#include "colisiones.h"
#include "puntuacion.h"
#include <pic16f877a.h>

#define _XTAL_FREQ 4000000

void checkCount(void);
void gire(void);
int main(int argc, char** argv) {
    
    //uint16_t corazon[8] = {0x0030, 0x0048, 0x0044, 0x0022, 0x0044, 0x0048, 0x0030, 0x0000};
    //uint16_t test[8] =  {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};
    init_timer();
    init_pines();
    init_LCD();
    
    int i=0, j=5;
    con.girar =0;
    con.ficha_Vpos = 16;
    con.ficha_Hpos = 2;
    con.puntaje = 0;
    srand(2);
    con.ficha_actual = rand() % 7;

    while(1){
        checkCount();
        updateScreen(pantalla);
    }
    return (EXIT_SUCCESS); 
}

void gire(void){
    int i=0, j=0, k=0;
    uint8_t aux[4]={0x0000};
    uint8_t mask = 0x00;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            mask = (figuras[con.ficha_actual][j] >> i) & 0x01;
            aux[i] = aux[i] | (mask<<(3-j));
        }
    }

    /*
     * Ajustar "cero"
     */
    while(k<3){
        for(i=0; i<4; i++){
            if( aux[i] & 0x01 ){
                break;
            }
            if(i==3){
                for(j=0; j<4; j++){
                    aux[j] = aux[j]>>1;
                }
            }
        }
        k++;
    }

    if((aux[0] & 0xF) == 0){
        aux[0] = aux[1];
        aux[1] = aux[2];
        aux[2] = aux[3];
        aux[3] = 0x0;
    }

    for(i=0; i<4; i++){
        figuras[con.ficha_actual][i] = aux[i];
    }
}

void leerEntradas(void){
    //leer Entradas
    if(con.girar){
        con.girar=0;
        gire();
        drawFigure();
        return;
    }
    
    if(con.derecha == 1 ){
        con.derecha = 0;
        if(checkColission_R() | checkRight()){
            return;
        }
        con.ficha_Hpos++;
        drawFigure();
        return;
    }
    else if(con.izquierda == 1 && con.ficha_Hpos>0){
        con.izquierda = 0;
        if(checkColission_L()==true){
            return;
        }
        con.ficha_Hpos--;
        drawFigure();
        return;
    }
}

void checkCount(void){
    if(con.check_count == 1){ 
        int i=0, j=0;
        con.check_count = 0;
        
        leerEntradas();
        
        //Cuando transcurre un segundo
        if(timerCount >= 15 ){
            timerCount = 0;
            
            PORTBbits.RB0 = con.led;
            con.led= ~con.led;
            
            con.ficha_Vpos--;
            
            checkBottom();
            checkColission_D();
            drawFigure();
            
            perdio();
            sumaPuntos();
        }
    }
}

void __interrupt() Timer0_ISR(void){      
    if(INTCONbits.TMR0IF){  
        INTCONbits.TMR0IF=0;
        timerCount ++;
        con.check_count = 1;
    }
    
    if(PORTBbits.RB5 == 0){
        con.derecha = 1;
        con.izquierda = 0;
    }
    if(PORTBbits.RB4 == 0){
        con.derecha = 0;
        con.izquierda = 1;
    }
    if(PORTBbits.RB3== 0){
        con.girar = 1;
    }
}

