#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include "init.h"
#include "columnas.h"
#include "filas.h"
#include "control.h"
#include "screen.h"
#include <pic16f877a.h>

/*
 * Funcion encargada de renderizar en las matrices de LEDs lo que está en 
 * pantalla
 */
void updateScreen(uint16_t screen[8]){
    int i=0;
    
    addToScreen();
    
    for(i=0; i<=7;i++){
       if(i == 0){
            //setColumnas(0x00);
            setFilas(~screen[i]);
            shiftBitColumna(1);
            //setColumnas(1>>i);
        }
        else{
            //setColumnas(0x00);
            setFilas(~screen[i]);
            shiftBitColumna(0);
            //setColumnas(1>>i);
        }  
    }
}

/*
* Hace una OR entre la ficha y el fondo para obtener lo que se
* mostrara en pantalla. Esto me permite poder borrar todo lo otro
* y que no queden remanentes del movimiento de la figura
*/
void addToScreen(void){
    int i=0;
    for(i=0; i<8; i++){
        pantalla[i] = ficha[i] | fondo[i];
    }
}

void drawBground(void){
    int i=0;
    for(i=0; i<8; i++){
        fondo[i] = fondo[i] | ficha[i];
    }
}

/*
 * Dibuja la figuta que está cayendo. Hpos y Vpos son las posiciones horizontal
 * y vertical respectivamente. 
 */
void drawFigure(void){
    memset(ficha, 0, sizeof(ficha));    
    ficha[con.ficha_Hpos   ] = figuras[con.ficha_actual][0] << (con.ficha_Vpos-1);
    ficha[con.ficha_Hpos +1] = figuras[con.ficha_actual][1] << (con.ficha_Vpos-1);
    ficha[con.ficha_Hpos +2] = figuras[con.ficha_actual][2] << (con.ficha_Vpos-1);
    ficha[con.ficha_Hpos +3] = figuras[con.ficha_actual][3] << (con.ficha_Vpos-1);
}

