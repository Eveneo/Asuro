/*
 * odometrie.c
 *
 * Created: 11.10.2013 01:41:25
 *  Author: Dante999
 * ____________________________
 *|   PINBELEGUNG AUSG�NGE     |
 *|____________________________|
 *| SIDE  | REF  | PIN  | WERT |
 *|----------------------------|
 *| LEFT  |  D13 | PD7 | HIGH  |
 *| RIGHT |  D14 | PD7 | HIGH  |
 *|____________________________|
 *
 *_____________________________
 *|     PINBELEGUNG EING�NGE   |
 *|____________________________|
 *| SIDE  | REF  | PIN  | ADC  |
 *|----------------------------|
 *| LEFT  | T11  | PC1  | ADC1 |
 *| RIGHT | T12  | PC0  | ADC0 |
 *|____________________________|
 *
 */
#include <avr/io.h>
#include "uart.h"
#include "odometrie.h"
#include "asuro.h"

char toggle_bit;                            // toggle bit f�r Odometrie



/************************************************************************
* /brief    ADC Wert der Odometrie bestimmen
*
* /param    side:    _RIGHT    Auswahl des rechten Reifens
*                    _LEFT    Auswahl des linken Reifens
*
* /return    uint16 Wert des ADCs
*
*
************************************************************************/
uint16_t get_od_adc(char side)
{
    PORTD |= ( 1 << PD7);               // PD7 auf HIGH -> keine LED Steuerung
    
    
    if( side == _RIGHT)                 // aktivieren des rechten ADC
    {
    ADMUX &= ~( 1 << MUX0);
    ADMUX &= ~( 1 << MUX1);
    ADMUX &= ~( 1 << MUX2);
    ADMUX &= ~( 1 << MUX3);
    }
    
    else if ( side == _LEFT)            // aktivieren des linken ADC
    {
    ADMUX |= ( 1 << MUX0);
    ADMUX &= ~( 1 << MUX1);
    ADMUX &= ~( 1 << MUX2);
    ADMUX &= ~( 1 << MUX3);        
    }      
      
    ADCSRA |= ( 1 << ADSC);             // Starte ADC Messung    
    
    while( ADSC == 1)                   // Warte bis ADC-Messung beendet
    {
        //wait
    }
        
    return ADC;                         // gib ADC Wert zur�ck
}


/************************************************************************
* /brief    Erkennung eines schwarz-wei� Wechsels der Drehzahlscheibe    
*            Der gemessene ADC Wert wird mit dem _RPM_TRIGGER (siehe odometrie.h) verglichen. 
*            Ist der Wert �ber diesem Trigger, wird das toggle_bit auf 1 gesetzt, ansonsten
*            auf 0. Nun wird verglichen ob zwischen der vorigen Messung und der aktuellen
*            ein unterschied besteht. War der ADC Wert vorher �ber dem Trigger und ist jetzt darunter
*            hat ein Wechsel von schwarz auf wei� der Drehzahlscheibe stattgefunden. 
*            In diesem Fall gibt die Funktion eine 1 zur�ck
*
* /param    side:    _RIGHT    Auswahl des rechten Reifens
*                    _LEFT    Auswahl des linken Reifens
*
* /return    1:     schwarz-wei� Wechsel stattgefunden
*            0:     kein schwarz-wei� Wechsel 
*
************************************************************************/
uint8_t get_tick( char side)
{
    uint16_t adc_value;                 // buffer f�r adc Wert
    char toggle_bit_old;                // Toggle Bit
    uint8_t tick_bit = 0;               // Wechselbit ( schwarz-wei� wechsel)
    
    toggle_bit_old = toggle_bit;        // alten Wert des Toggle bit zwischenspeichern
    adc_value = get_od_adc(side);       // ADC Wert ermitteln
    
    if( adc_value > _RPM_TRIGGER)       // ADC Wert �ber dem Triggerlevel?
    {
        toggle_bit = 1;
    }
    else if( adc_value < _RPM_TRIGGER)  // ADC Wert unter dem Triggerlevel?
    {
        toggle_bit = 0;
    }
    
    if ( toggle_bit != toggle_bit_old)  // �nderung des Bits stattgefunden?
    {
        tick_bit = 1;                   // ja
    }
    else
    {
        tick_bit = 0;                   // nein
    }
    
    return tick_bit;                    // Wert des Bits zur�ckgeben
}