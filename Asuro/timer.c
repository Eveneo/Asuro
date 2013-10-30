/*
 * timer.c
 *
 * Created: 13.10.2013 16:31:02
 *  Author: Dante999
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "asuro.h"
#include "uart.h"



/************************************************************************
* /brief    Initialisierung Timer für Sekundentakt etc.
*            
*
* /param    none
*
* /return   none
*
*
************************************************************************/
void init_timer(void)
{
    TCCR0 |=  (1 << CS02) | (1 << CS00);                //prescaler 1024
                                                        // -> 8MHz/1024= 7,8Khz ~ 128µs
    TIMSK |= (1 << TOIE0);                                // enable Timer-Overflow interrupt
                                                        
    uart_puts("timer init done..." _CR);
}


/************************************************************************
* /brief    Interruptfunktion bei Timeroverflow
*           Wird automatisch ausgeführt wenn ein Timer overflow stattfindet
*
* /param    none
*
* /return   none
*
*
************************************************************************/
ISR (TIMER0_OVF_vect)
{
    //enter Code here    

}
