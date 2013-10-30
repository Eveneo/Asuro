/*
 * motor_control.c
 *
 * Created: 09.10.2013 01:19:07
 *  Author: Dante999
 */ 

/*
*___________________________
*|       LEFT MOTOR         |
*|__________________________|
*| TURN | PD4  | PD5  | PB1 |
*|--------------------------|
*| FWR  | LOW  | HIGH | PWM |
*| RWD  | HIGH | LOW  | PWM |
*|__________________________|
*
*___________________________
*|       RIGHT MOTOR        |
*|__________________________|
*| TURN | PB4  | PB5  | PB2 |
*|--------------------------|
*| FWR  | LOW  | HIGH | PWM |
*| RWD  | HIGH | LOW  | PWM |
*|__________________________|
*
*/

#include <avr/io.h>
#include "motor_control.h"
#include "uart.h"

/************************************************************************
* /brief    Initialisierung 
*            - Definieren der I/O's
*            - Stoppen des Motors
*            - Konfigurieren des PWM Timers
*
* /param    none
*
* /return   none
*
*
************************************************************************/
void init_motor(void)
{
    /** IOs definieren **/
    DDRD |= (1 << PD4) | (1 << PD5);                // Pins f�r linken Motor als Ausg�nge
    DDRB |= (1 << PB4) | (1 << PB5);                // Pins f�r rechten Motor als Ausg�nge
    DDRB |= (1 << PB1) | (1 << PB2);                // PWM Pins als Ausg�nge
    
    /** Motor stoppen **/
    PORTD |= (1 << PD4) | (1 << PD5);               // Ausg�nge auf HIGH -> Motor blockiert
    PORTB |= (1 << PB4) | (1 << PB5);               // Ausg�nge auf HIGH -> Motor blockiert
        
    /** Timer konfigurieren **/
    TCCR1A |= (1 << COM1A1) | (1 << WGM10) | (1 << COM1B1);
    TCCR1B |= (1 << CS11);
    
    uart_puts("motor init done..." _CR);
}


/************************************************************************
* /brief    Drehrichtung der Motoren vorgeben
*
* /param    left:   _FWD -> Vorw�rts
*                   _RWD -> R�cks�rts
*                   _BRK -> Bremsen
*
*           right: _FWD -> Vorw�rts
*                   _RWD -> R�cks�rts
*                   _BRK -> Bremsen
*
* /return   none
*
*
************************************************************************/
void motor_dir( char left, char right)
{
    /** Linke Seite **/
    if ( left == _FWD)                              // Motor vorw�rts
    {
        PORTD |= (1 << PD5);
        PORTD &= ~(1 << PD4);        
    }
        
    else if ( left == _RWD)                         // Motor r�ckw�rts
    {
        PORTD &= ~(1 << PD5);
        PORTD |=  (1 << PD4);        
    }
        
    else                                            // ung�ltige Auswahl
    {
    PORTD |= (1 << PD4) | (1 << PD5);               // Ausg�nge auf HIGH -> Motor blockiert
    }
    
    
    /** Rechte Seite **/
    if ( right == _FWD)                             // Motor vorw�rts
    {
        PORTB |= (1 << PB5);
        PORTB &= ~(1 << PB4);
    }
    
    else if ( right == _RWD)                        // Motor r�ckw�rts
    {
        PORTB &= ~(1 << PB5);
        PORTB |=  (1 << PB4);
    }
    
    else                                            // ung�ltige Auswahl
    {
        PORTB |= (1 << PB4) | (1 << PB5);           // Ausg�nge auf HIGH -> Motor blockiert
    }    
}

/************************************************************************
* /brief    PWM Verh�ltnis der Motoren vorgeben
*
* /param    left:   0           (Motor stoppt)
*                   ...         ...
*                   255         (Motor vollgas)
*
*           right:  0           (Motor stoppt)
*                   ...         ...
*                   255         (Motor vollgas)
*
* /return   none
*
*
************************************************************************/
void motor_pwr( uint8_t left, uint8_t right)
{
    _PWM_LEFT = left;
    _PWM_RIGHT = right;
}

