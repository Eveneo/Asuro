/*
 * line.c
 *
 * Created: 29.10.2013 21:27:09
 *  Author: Dante999
 */ 

/**
 *_____________________________
 *|     PINBELEGUNG EINGÄNGE   |
 *|____________________________|
 *| SIDE  | REF  | PIN  | ADC  |
 *|----------------------------|
 *| LEFT  | T9   | PC3  | ADC3 |
 *| RIGHT | T10  | PC2  | ADC2 |
 *|____________________________|
 *
 **/
#include <avr/io.h>
#include "asuro.h"
#include "uart.h"


/************************************************************************
* /brief    initialisieren der Liniensensoren
*
* /param    none
*
* /return   none
*
************************************************************************/
void init_line(void)
{
    DDRC &= ~( 1 << PC3);                   // Pin als Eingang
    DDRC &= ~( 1 << PC2);                   // Pin als Eingang

    uart_puts("line init done...");
    uart_puts(_CR);
}


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
uint8_t get_line_adc(char side)
{
    if(side == _LEFT)                       // Auswahl ADC für den linken Liniensensor
    {
        ADMUX |=  ( 1 << MUX0);
        ADMUX |=  ( 1 << MUX1);
        ADMUX &= ~( 1 << MUX2);
        ADMUX &= ~( 1 << MUX3);
    }
    
    else if(side == _RIGHT)                 // Auswahl ADC für den rechten Liniensensor
    {
        ADMUX &= ~( 1 << MUX0);
        ADMUX |=  ( 1 << MUX1);
        ADMUX &= ~( 1 << MUX2);
        ADMUX &= ~( 1 << MUX3);
    }

    else                                    // Ungültige Auswahl
    {
        uart_puts("kein gültiger ADC Kanal in get_line_adc()");
    }

    ADCSRA |= ( 1 << ADSC);                 // Starte ADC Messung
            
    while( ADSC == 1)                       // Warte bis ADC-Messung beendet
    {
        //wait
    }
        
    return ADC;                             // gib ADC Wert zurück
}