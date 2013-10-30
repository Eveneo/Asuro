/*
 * Asuro.c
 *
 * Created: 08.10.2013 22:56:14
 *  Author: Dante999
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "asuro.h"
#include "uart.h"
#include "status_led.h"
#include "motor_control.h"
#include "odometrie.h"
#include "timer.h"
#include "line.h"

/** Test **/
#include "test.h"


int main(void)
{    
    /** Initialisierungen **/    
    init_uart();                            // initialisiere IR ‹bertragung
    init_led();                             // initialisiere LED Steuerung
    init_motor();                           // initialisiere Motor Steuerung
    init_od();                              // initialisiere Odometrie
    init_timer();                           // initialisiere Timer
    init_line();                            // initialisiere Linienerkennung
    
    status_led( _GREEN);                    
    line_led(_ON);
    uart_puts("all inits done..." _CR);
    sei();                                  // aktiviere globale Interrupts
    
         
    while(1)
    {

        test();

    }//while(1)
    
    return 0;
    
}//int main(void)