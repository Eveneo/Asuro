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

/** Test **/
#include "test.h"


int main(void)
{	
	/** Initialisierungen **/	
	init_uart();							// initialisiere IR Übertragung
	init_led();								// initialisiere LED Steuerung
	init_motor();							// initialisere Motor Steuerung
	init_od();								// initialisiere odometrie
	init_timer();							// initialisiere Timer
	
	status_led( _GREEN);
	uart_puts("all inits done..." _CR);
	sei();
	
	
	
	/** DEBUG-Startwert **/
	motor_dir( _BRK, _FWD);
		
    while(1)
    {

		test();

    }//while(1)
	
	return 0;
	
}//int main(void)