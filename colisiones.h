/* 
 * File:   colisiones.h
 * Author: ASUS
 *
 * Created on 14 de mayo de 2020, 01:15 PM
 */

#ifndef COLISIONES_H
#define	COLISIONES_H

#ifdef	__cplusplus
extern "C" {
#endif

void checkBottom(void);
bool checkRight(void);
void checkColission_D(void);
bool checkColission_R(void);
bool checkColission_L(void);


#ifdef	__cplusplus
}
#endif

#endif	/* COLISIONES_H */

