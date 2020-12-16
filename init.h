/* 
 * File:   init.h
 * Author: ASUS
 *
 * Created on 11 de marzo de 2020, 09:42 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif
    void init_pines_LCD(void);
    void init_pines_fil(void);
    void init_pines_col(void);
    void init_pines(void);
    void init_timer(void);
    void init_interrupt(void);
    void init_pines_in(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */
