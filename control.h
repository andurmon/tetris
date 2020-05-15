/* 
 * File:   control.h
 * Author: ASUS
 *
 * Created on 2 de mayo de 2020, 01:15 PM
 */

#ifndef CONTROL_H
#define	CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    struct controlSign {
        uint8_t girar;
        uint8_t led;
        uint8_t ficha_Vpos;     //Posicion VERTICAL de la ficha que cae
        uint8_t ficha_Hpos;     //Posicion HORIZONTAL de la ficha que cae
        uint8_t ficha_actual;
        uint8_t derecha;
        uint8_t izquierda;
        uint8_t check_count;
        uint16_t puntaje;
    };
    struct controlSign con;

    uint8_t figuras[7][4]= {
        {0x2, 0x2, 0x3, 0x0},
        {0x3, 0x2, 0x2, 0x0},
        {0x1, 0x3, 0x2, 0x0},
        {0x2, 0x3, 0x1, 0x0},
        {0x1, 0x1, 0x1, 0x1},
        {0x3, 0x3, 0x0, 0x0},
        {0x1, 0x3, 0x1, 0x0}
    };


    uint32_t timerCount = 0;
    uint16_t pantalla[8] =  {0x0000};
    uint16_t fondo[8] = {0x0000};
    uint16_t ficha[8] = {0x0000};

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROL_H */

