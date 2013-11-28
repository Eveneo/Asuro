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
#include "switch.h"
#include "adc.h"
#include "line_follow.h"

/** Test **/
#include "test.h"


int main(void)
{    
    /** Initialisierungen **/    
    init_uart();                            // initialisiere IR Übertragung
    init_led();                             // initialisiere LED Steuerung
    init_motor();                           // initialisiere Motor Steuerung
    init_adc();                             // initialisiere ADC
    init_timer();                           // initialisiere Timer
    init_line();                            // initialisiere Linienerkennung
    init_switch();                          // initialisiere Taster
    
    status_led( _ORANGE);                    
    line_led(_ON);
    uart_puts("all inits done..." _CR);
    sei();                                  // aktiviere globale Interrupts
    
    motor_dir(_FWD, _FWD);
    calibrate_line_sens();
    
    status_led(_GREEN);
         
    while(1)
    {

      follow_line();
      //uart_puti(get_line_diff());
      //uart_puts(_CR);

    }//while(1)
    
    return 0;
    
}//int main(void)