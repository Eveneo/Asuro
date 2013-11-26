/*
 * line.h
 *
 * Created: 29.10.2013 21:47:36
 *  Author: Dante999
 */ 


#ifndef LINE_H_
#define LINE_H_

/************************************************************************
* /brief    initialisieren der Liniensensoren
*
* /param    none
*
* /return   none
*
************************************************************************/
void init_line(void);

/************************************************************************
* /brief    Auswerten der Liniensensoren
*
* /param    side:   _LEFT   linker Liniensensor
*                   _RIGHT  rechter Liniensensor
*
* /return   ADC Wert (uint16_t)
*           0       max. dunkel
*           ...
*           65536   max. hell
*
************************************************************************/
uint16_t get_line_adc(char side);


#endif /* LINE_H_ */