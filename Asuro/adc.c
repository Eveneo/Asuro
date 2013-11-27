/*
 * adc.c
 *
 * Created: 26.11.2013 23:00:06
 *  Author: Dante999
 */ 


#include <avr/io.h>
#include "asuro.h"
#include "uart.h"


/************************************************************************
* /brief    Initialisierung des Analog-Digital-Converters ( ADC) :
*            - Als Spannungsreferenz den AVCC Pin verwenden
*            - ADC Aktivieren
*            - Messdauer bestimmen: 1/(Frequenz/Prescaler)= 4µs
*
* /param    none
*
* /return   none
*
*
************************************************************************/
void init_adc(void)
{
    ADMUX |= (1 << REFS0);                      // AVCC mit externem Kondensator am AREF-Pin
    ADCSRA |= (1 << ADEN);                      // ADC Enable
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0);      // Abtastfrequenz: 8MHz/32=250kHz (4µs)

    ADCSRA |= ( 1 << ADSC);                     // Starte ADC Messung
     
    while( ADSC == 1)                           // Warte bis ADC-Messung beendet
    {
        //wait
    }


    (void) ADCW;                                // Verwerfen des ersten ADC Wertes (ungültig)                      
    
    uart_puts("ADC init done..." _CR);
}
