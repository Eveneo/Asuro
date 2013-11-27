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

/************************************************************************
* /brief    Kalibrieren der Liniensensoren
*
*           Es wird 10x die Differenz der beiden Liniensensoren gemessen.
*           Aus diesen Werten wird anschließend der Mittelwert gebildet.
*           Daraus resultiert anschließend der Korrekturfaktor für die
*           spätere Linienauswertung. Dieser wird in der Variable
*           cal_factor gespeichert.
*
* /param    none
*
* /return   none
*
************************************************************************/
void calibrate_line_sens(void);

/************************************************************************
* /brief    Auswerten der Differenz der Liniensensoren
*
*           Hier wird die Differenz der Helligkeitswerte der beiden
*           Liniensensoren bestimmt, sowie der Korrekturfaktor aus
*           der Funktion calibrate_line_sens(void) mit einbezogen
*
* /param    none
*
* /return   Differenz der Liniensensoren (int16_t)
*           ?32768  linker Sensor max. dunkel, rechter Sensor max hell
*           ...
*           32767   linker Sensor max. hell, rechter Sensor max. dunkel
*
************************************************************************/
int16_t get_line_diff(void);


#endif /* LINE_H_ */