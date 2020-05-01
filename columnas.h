/* 
 * File:   matriz_leds.h
 * Author: ASUS
 *
 * Created on 11 de marzo de 2020, 09:51 PM
 */

#ifndef COLUMNAS_H
#define	COLUMNAS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void latchClock_Col(void);
    void shiftClock_Col(void);
    void setColumnas(uint8_t reg_value);
    void shiftBitColumna(uint8_t bit);


#ifdef	__cplusplus
}
#endif

#endif	/* COLUMNAS_H */

