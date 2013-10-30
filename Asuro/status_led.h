/*
 * status_led.h
 *
 * Created: 08.10.2013 23:30:08
 *  Author: Dante999
 */ 


#ifndef STATUS_LED_H_
#define STATUS_LED_H_

/** bereits in asuro.h definiert **/
//#define _OFF    0
//#define _ON    1

#define _GREEN  1
#define _RED    2
#define _ORANGE 3



/************************************************************************
* /brief    Initialisierung
*            - Definieren der I/O's
*
* /param     none
*
* /return    none
*
*
************************************************************************/
void init_led (void);


/************************************************************************
* /brief    Initialisierung und Steuerund des Back LEDs
*
* /param    left:   _ON         linke LED an
*                   _OFF        linke LED aus
*
*           right:  _ON         rechte LED an
*                   _OFF        rechte LED aus
*
* /return   none
*
*
************************************************************************/
void back_led (char left, char right);


/************************************************************************
* /brief    Steuern der Rot-Grün-Orange Status LED
*
* /param    colour: _GREEN      Farbe Grün
*                   _RED        Farbe Rot
*                   _ORANGE     Farbe Orange
*
* /return   none
*
*
************************************************************************/
void status_led( char colour);


/************************************************************************
* /brief    Steuern der LED zur Linienverfolgung
*
* /param    status: _ON     LED an
*                   _OFF    LED aus
*
* /return    none
*
*
************************************************************************/
void line_led(char status);


#endif /* STATUS_LED_H_ */