#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include <stdbool.h>
#include "columnas.h"
#include "filas.h"
#include "control.h"
#include "screen.h"
#include "colisiones.h"
#include <pic16f877a.h>

/*
*  Verifica si la figura puede o no bajar mas
*/
void checkBottom(void){
    if(con.ficha_Vpos==0){
        drawBground();
        con.ficha_Vpos = 16;
        con.ficha_Hpos = 2;
        con.ficha_actual = rand() % 7;
    }
}

bool checkRight(void){
    if(ficha[7]!=0){
        return true;
    }
    return false;
}

/*
* Este for se encarga de verificar si la figura se choca con el
* Bground o no. Lo hace evaluando si la siguiente posicion vertical
* coincide con un pedazo del Bground
*/
void checkColission_D(void){
    int i = 0;
    for(i=con.ficha_Hpos; i<(con.ficha_Hpos+4); i++){
        if((ficha[i]>>1 & fondo[i]) != 0){
            drawBground();
            con.ficha_Vpos = 16;
            con.ficha_Hpos = 2;
            con.ficha_actual = rand() % 7;
            break;
        }
    }
}

bool checkColission_R(void){
    int i=0;
    for(i=(con.ficha_Hpos+3); i>=con.ficha_Hpos; i--){
        if((ficha[i] & fondo[i+1]) != 0){
            return true;
        }
    }
    return false;
}

bool checkColission_L(void){
    int i=0;
    for(i=con.ficha_Hpos; i<(con.ficha_Hpos+4); i++){
        if((ficha[i] & fondo[i-1]) != 0){
            return true;
        }
    }
    return false;
}