/*
 * adc.h
 *
 * Created: 26.11.2013 23:01:18
 *  Author: Dante999
 */ 


#ifndef ADC_H_
#define ADC_H_

/************************************************************************
* /brief    Initialisierung des Analog-Digital-Converters ( ADC) :
*            - Als Spannungsreferenz den AVCC Pin verwenden
*            - ADC Aktivieren
*            - Messdauer bestimmen: 1/(Frequenz/Prescaler)= 4µs
*
* /param    none
*
* /return    none
*
*
************************************************************************/
void init_adc(void);



#endif /* ADC_H_ */