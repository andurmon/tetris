/* 
 * File:   matriz_leds.h
 * Author: ASUS
 *
 * Created on 11 de marzo de 2020, 09:51 PM
 */

#ifndef MATRIZ_LEDS_H
#define	MATRIZ_LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif
void latchClock_Col(void);

void shiftClock_Col(void);

void latchClock_Fil(void);

void shiftClock_Fil(void);

void setRegister(uint16_t reg_value[8]);

void setColumnas(uint8_t reg_value);

void setFilas(uint16_t reg_value);

void shiftBitColumna(uint8_t bit);

void enableFilas(void);

void disableFilas(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MATRIZ_LEDS_H */

