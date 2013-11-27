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

#define _DEBUG  1                               // 0= keine infos über UART; 1= aktivere debuginfos über UART

int8_t cal_factor = 0;                          // Kalibierungsfaktor der Liniensensoren


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
uint16_t get_line_adc(char side)
{    
    uint8_t i;

    for ( i=0; i<255; i++)
    {
        //Warteschleife für Kanalwechsel
    }

    if (side == _LEFT)                       // Auswahl ADC für den linken Liniensensor
    {
        ADMUX |=  ( 1 << MUX0);
        ADMUX |=  ( 1 << MUX1);
        ADMUX &= ~( 1 << MUX2);
        ADMUX &= ~( 1 << MUX3);
    }
    
    else if (side == _RIGHT)                 // Auswahl ADC für den rechten Liniensensor
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
int16_t get_line_diff(void)
{
    int16_t buffer;
    
    buffer = get_line_adc(_LEFT) - get_line_adc(_RIGHT) - cal_factor;                        // Errechnen der Helligkeitsdifferenz der Sensoren
    
    return buffer;
}

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
void calibrate_line_sens(void)
{
    uint8_t i = 0;                                                          // variable für Zählerschleife
    int16_t diff_data[12];                                                  // Array für die ADC Messwerte
    int16_t buffer = 0;                                                     // Zwischenspeicher zur Mittelwert errechnung
    
    diff_data[11] = get_line_adc(_LEFT) - get_line_adc(_RIGHT);             // dummy Messung, da erste ADC Messung immer fehlerhaft
    
    for ( i=0; i<10; i++)                                                   // 10x durchlaufen der Schleife für 10 Messungen
    {
        diff_data[i] = get_line_adc(_LEFT) - get_line_adc(_RIGHT);          // Bilden der Differenz der Sensoren 
        buffer += diff_data[i];                                             // Differenz addieren
      
        #if _DEBUG
        uart_puts("Wert ");
        uart_puti(i);
        uart_puts(": ");
        uart_puti(diff_data[i]);
        uart_puts("   ;   ");
        uart_puti(buffer);
        uart_puts(_CR);
        #endif
      
    }
 
    cal_factor = buffer/10;                                                 // Teile Addition aller Differenzen durch 10 -> Mittelwert
    
    #if _DEBUG    
    uart_puts("Summe : ");
    uart_puti(buffer);
    uart_puts(_CR);
    uart_puts("Faktor: ");
    uart_puti(cal_factor);
    #endif
    
}