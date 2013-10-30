/*
 * status_led.c
 *
 * Created: 08.10.2013 22:59:35
 *  Author: Dante999
 */ 
#include <avr/io.h>
#include "asuro.h"
#include "status_led.h"
#include "uart.h"


/*
*
*_____________________
*|  D15 (BACK LEFT)   |
*|____________________|
*| STAT | PD7  | PC1  |
*|--------------------|
*| ON   | LOW  | HIGH |
*| OFF  | LOW  | LOW  |
*|____________________|
*
*
*_____________________
*|  D16 (BACK RIGHT)  |
*|____________________|
*| STAT | PD7  | PC0  |
*|--------------------|
*| ON   | LOW  | HIGH |
*| OFF  | LOW  | LOW  |
*|____________________|
*
*
*________________________
*|      D12 (RG LED)    |
*|______________________|
*| STAT   | PB0  | PD2  |
*|----------------------|
*| RED    | LOW  | HIGH |
*| GREEN  | HIGH | LOW  |
*| ORANGE | HIGH | HIGH |
*|______________________|
*
*__________________
*| D11 (LINE LED) |
*|________________|
*| STAT  | PD6    |
*|-------|--------|
*| ON    | HIGH   |
*| OFF   | LOW    |
*|________________|
*/

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
void init_led (void)
{
    DDRD |= (1 << PD7);                        // PD7 als Ausgang für Back LEDs
    DDRD |= (1 << PD2);                        // PD2 als Ausgang für RG_LED
    DDRB |= (1 << PB0);                        // PB0 als Ausgang für RG_LED
    DDRD |= (1 << PD6);
    
    uart_puts("led init done..." _CR);
}

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
void back_led (char left, char right)
{
    if ( (left == _ON) || (right == _ON) )
    {
        PORTD &= ~(1 << PD7);                   // Rad-LED's OFF
        DDRC |= (1 << PC0) | (1 << PC1);        // Port als Output => KEINE Odometrie
        PORTC |= (1 << PC0) | (1 << PC1);       // Beide LEDs an
    } 
 
    if ( left != _ON )                          // Linke LED aus? 
    {
        PORTC &= ~(1 << PC1);                   // -> linke LED aus
    }

    else if ( right != _ON )                    // Rechte LED aus?
    {
        PORTC &= ~(1 << PC0);                   // -> rechte LED aus
    }
  
}
 
 
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
void status_led( char colour)
{
    if ( colour == _GREEN)
    {
        PORTB |=  ( 1 << PB0 );
        PORTD &= ~( 1 << PD2 );
    }
     
    else if ( colour == _RED )
    {
        PORTB &= ~( 1 << PB0 );
        PORTD |=  ( 1 << PD2 );
    }
     
    else if ( colour == _ORANGE )
    {
        PORTB |= ( 1 << PB0 );
        PORTD |= ( 1 << PD2 );
    }
     
    else
    {
        uart_puts("falsche Eingabe bei status_led()");
    }     
     
}
 
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
void line_led(char status)
{
    if(status == _ON)
    {
        PORTD |= ( 1 << PD6 );
    }
    
    else if( status == _OFF)
    {
        PORTD &= ~( 1 << PD6);
    }
    
    else
    {
        uart_puts("falsche Eingabe bei line_led()");
    }
}