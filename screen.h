/* 
 * File:   screen.h
 * Author: ASUS
 *
 * Created on 2 de mayo de 2020, 01:13 PM
 */

#ifndef SCREEN_H
#define	SCREEN_H

#ifdef	__cplusplus
extern "C" {
#endif

    void updateScreen(uint16_t screen[8]);
    void addToScreen(void);
    void drawBground(void);
    void drawFigure(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SCREEN_H */

