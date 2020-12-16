#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "control.h"
#include <pic16f877a.h>

/*
* Este for permite saber si el usuario ha perdido, comparando el
* bit de mas arriba del tablero.
*/
void perdio(void){
    int i = 0;
    for(i=0; i<8; i++){
        if((fondo[i] & 0x8000) != 0){
            memset(ficha, 0, sizeof(ficha));
            memset(fondo, 0, sizeof(fondo));
            con.ficha_Vpos = 16;
            con.ficha_actual = rand() % 7;
            break;
        }
    }
}

/*
* Con este for se busca que pueda detectar si se lleno toda una
* fila para borrarla y bajar las demás.
*/
void sumaPuntos(void){
    int i=0, j=0;
    uint8_t aux = 1;
    for (i=0; i<16; i++){
        for(j=0; j<8; j++){
            aux = aux & fondo[j]>>i;
        }
        if(aux == 1){
            //Sume puntos
            //borre fila y baje las demas
            
        }
    }
    
}