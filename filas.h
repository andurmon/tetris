/* 
 * File:   filas.h
 * Author: ASUS
 *
 * Created on 1 de mayo de 2020, 10:17 AM
 */

#ifndef FILAS_H
#define	FILAS_H

#ifdef	__cplusplus
extern "C" {
#endif

void latchClock_Fil(void);
void shiftClock_Fil(void);
void setFilas(uint16_t reg_value);
void enableFilas(void);
void disableFilas(void);



#ifdef	__cplusplus
}
#endif

#endif	/* FILAS_H */

