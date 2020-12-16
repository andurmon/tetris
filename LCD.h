/* 
 * File:   LCD.h
 * Author: ASUS
 *
 * Created on 15 de mayo de 2020, 11:52 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    void init_LCD(void);
    void clearDisplay(void);
    void returnHome(void);
    void displayONOFF(bool D, bool C, bool B);
    void functionSet(bool DL, bool N, bool F);
    void entryModeSet(bool ID, bool SH);
    void setRS(void);
    void clearRS(void);
    void setRW(void);
    void clearRW(void);
    void setE(void);
    void clearE(void);
    void setData(uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

