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

void checkCount(void);

int main(int argc, char** argv) {
    
    //uint16_t corazon[8] = {0x0030, 0x0048, 0x0044, 0x0022, 0x0044, 0x0048, 0x0030, 0x0000};
    //uint16_t test[8] =  {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};
    init_timer();
    init_pines();
    //init_interrupt();
    
    int i=0, j=5;
    con.ficha_Vpos = 16;
    con.ficha_Hpos = 2;
    srand(1);
    con.ficha_actual = rand() % 7;
    //drawBground();
    
    while(1){
        //srand(TMR0);
        checkCount();
             
        updateScreen(pantalla);
        
    }
    return (EXIT_SUCCESS); 
}
void leerEntradas(void){
    //leer Entradas
    int i =0;
    if(con.derecha == 1 && con.ficha_Hpos<4){
        con.derecha = 0;
        for(i=(con.ficha_Hpos+4); i>con.ficha_Hpos; i--){
            if((ficha[i] & fondo[i+1]) != 0){
                return;
            }
        }
        con.ficha_Hpos++;
        drawFigure();
        return;
    }
    else if(con.izquierda == 1 && con.ficha_Hpos>0){
        con.izquierda = 0;
        for(i=con.ficha_Hpos; i<(con.ficha_Hpos+4); i++){
            if((ficha[i] & fondo[i-1]) != 0){
                return;
            }
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
            
            /*
             *  Verifica si la figura puede o no bajar mas
             */
            if(con.ficha_Vpos==0){
                drawBground();
                con.ficha_Vpos = 16;
                con.ficha_actual = rand() % 7;
            }
            
            /*
             * Este for se encarga de verificar si la figura se choca con el
             * fondo o no. Lo hace evaluando si la siguiente posicion vertical
             * coincide con un pedazo del fondo
             */
            for(i=con.ficha_Hpos; i<(con.ficha_Hpos+4); i++){
                if((ficha[i]>>1 & fondo[i]) != 0){
                    drawBground();
                    con.ficha_Vpos = 16;
                    con.ficha_actual = rand() % 7;
                    break;
                }
            }

           
            
            drawFigure();
            
            /*
             * Este for permite saber si el usuario ha perdido, comparando el
             * bit de mas arriba del tablero.
             */
            for(i=0; i<8; i++){
                if((fondo[i] & 0x8000) != 0){
                    memset(ficha, 0, sizeof(ficha));
                    memset(fondo, 0, sizeof(fondo));
                    con.ficha_Vpos = 16;
                    con.ficha_actual = rand() % 7;
                    break;
                }
                
            }
            
            /*
             * Con este for se busca que pueda detectar si se lleno toda una
             * fila para borrarla y bajar las demás.
             */
            for (i=0; i<16; i++){
                for(j=0; j<8; j++){
                   if( (fondo[i] & (1<<j)) == 0){
                       break;
                   } 
                }
                
            }
            
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
    if(PORTBbits.RB4 == 0){
        con.derecha = 0;
        con.izquierda = 1;
    }
}

