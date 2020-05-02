#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include "init.h"
#include "columnas.h"
#include "filas.h"
#include "control.h"
#include <pic16f877a.h>

void updateScreen(uint16_t screen[8]){
    if(con.columna == 9){
        con.columna = 1;
        setFilas(~screen[con.columna-1]);
        shiftBitColumna(1);
    }
    else{
        con.columna++;
        setFilas(~screen[con.columna-1]);
        shiftBitColumna(0);
    }
}

void drawBground(void){

    fondo[0] = 0x0030;
    fondo[1] = 0x0048;
    fondo[2] = 0x0044;
    fondo[3] = 0x0022;
    fondo[4] = 0x0044;
    fondo[5] = 0x0048;
    fondo[6] = 0x0030;
    fondo[7] = 0x0000;
}

void drawFigure(void){
    memset(ficha, 0, sizeof(ficha));
    if(con.derecha == 1 && con.ficha_Hpos<4){
        con.ficha_Hpos++;
        con.derecha = 0;
    }else if (con.izquierda == 1 && con.ficha_Hpos>0){
        con.ficha_Hpos--;
        con.izquierda = 0;
    }
    ficha[con.ficha_Hpos   ] = figuras[con.ficha_actual][0] << (con.ficha_Vpos -1);
    ficha[con.ficha_Hpos +1] = figuras[con.ficha_actual][1] << (con.ficha_Vpos -1);
    ficha[con.ficha_Hpos +2] = figuras[con.ficha_actual][2] << (con.ficha_Vpos -1);
    ficha[con.ficha_Hpos +3] = figuras[con.ficha_actual][3] << (con.ficha_Vpos -1);
}
