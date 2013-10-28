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
*/

/************************************************************************
* /brief	Initialisierung
*			- Definieren der I/O's
*
* /param	none
*
* /return	none
*
*
************************************************************************/
void init_led (void)
{
	DDRD |= (1 << PD7);						// PD7 als Ausgang für Back LEDs
	DDRD |= (1 << PD2);						// PD2 als Ausgang für RG_LED
	DDRB |= (1 << PB0);						// PB0 als Ausgang für RG_LED
	
	uart_puts("led init done..." _CR);
}

/************************************************************************
* /brief	Initialisierung und Steuerund des Back LEDs
*
* /param	left:	_ON		linke LED an
*					_OFF	linke LED aus
*
*			right:	_ON		rechte LED an
*					_OFF	rechte LED aus
*
* /return	none
*
*
************************************************************************/
void back_led (char left, char right)
{
  if ( (left == _ON) || (right == _ON) )
  {
	  PORTD &= ~(1 << PD7);					// Rad-LED's OFF
	  DDRC |= (1 << PC0) | (1 << PC1);		// Port als Output => KEINE Odometrie
	  PORTC |= (1 << PC0) | (1 << PC1);		// PC0 und PC1 auf HIGH
  } 
 
  if ( left != _ON )
  {
	  PORTC &= ~(1 << PC1);				// PC1 auf LOW
  }

  if ( right != _ON )
  {
	  PORTC &= ~(1 << PC0);				// PC0 auf LOW
  }
  
 }
 
 
/************************************************************************
* /brief	Steuern der Rot-Grün-Orange Status LED
*
* /param	colour:	_GREEN		Farbe Grün
*					_RED		Farbe Rot
*					_ORANGE		Farbe Orange
*
* /return	none
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
 }
 
 
 
 
 