/*
 * test.c
 *
 * Created: 22.10.2013 23:11:47
 *  Author: Dante999
 */ 

#include <avr/io.h>
#include "uart.h"
#include "odometrie.h"
#include "motor_control.h"
#include "asuro.h"

extern char tmr_ovf;			// deklariert in timer.c
uint8_t ticks_left = -1;		// änderung links
uint8_t ticks_right = -1;		// änderung rechts
uint8_t rpm_right = -1;			// drehzahl rechts
uint8_t rpm_left = -1;			// drehzahl links

/** DEBUG **/
uint8_t counter = 0;			// Anzahl Schleifendurchläufe
uint8_t timer_counter;			// Anzahl der Timer Interrupts



void test(void)
{	
	switch(counter)
	{
		case 0:		motor_pwr( 0, 85);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 85");
					uart_puts(_CR);
					break;
		
		case 50:	motor_pwr(0, 100);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 100");
					uart_puts(_CR);
					break;
		
		case 100:	motor_pwr(0, 150);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 150");
					uart_puts(_CR);
					break;
		
		case 150:	motor_pwr(0, 200);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 200");
					uart_puts(_CR);
					break;
		
		case 200:	motor_pwr(0, 255);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 255");
					uart_puts(_CR);
					break;
		
		case 250:	uart_puts(_CR);
					uart_puts("done...");
					uart_puts(_CR);
					uart_puts(_CR);
					break;
	}//switch(counter)	
	
	counter++;
	
	uart_puti(get_od_adc(_RIGHT));
	uart_puts(";");
	
	
	
	
#if 0		
	switch(counter)
	{
		case 0:		motor_pwr( 0, 85);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 85");
					uart_puts(_CR);
					break;
					
		case 50:	motor_pwr(0, 100);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 100");
					uart_puts(_CR);
					break;
					
		case 100:	motor_pwr(0, 150);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 150");
					uart_puts(_CR);
					break;
					
		case 150:	motor_pwr(0, 200);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 200");
					uart_puts(_CR);
					break;
					
		case 200:	motor_pwr(0, 255);
					uart_puts(_CR);
					uart_puts(_CR);
					uart_puts("PWM 255");
					uart_puts(_CR);
					break;
					
		case 250:	uart_puts(_CR);
					uart_puts("done...");
					uart_puts(_CR);
					uart_puts(_CR);
					break;
	}//switch(counter)

	
	int_buffer = get_tick(_RIGHT);
	ticks_right = ticks_right + int_buffer;

/** Timer interrupt overflow ausgelöst **/
	if ( tmr_ovf == _SET)								// Timer interrupt ausgelöst
	{
		tmr_ovf = _CLR;								// timer-overflow flag löschen
		timer_counter++;
	
		if(timer_counter == _RPM_TIME)					// Zeit der Drehzahl erreicht
		{
			counter++;
			rpm_left = ticks_left;
			rpm_right = ticks_right;
		
			/** Reset **/
			ticks_left = 0;
			ticks_right = 0;
			timer_counter = 0;
		
			uart_puti(rpm_right);
			uart_puts(_CR);
		}
		
      }//( tmr_ovf == _SET)
#endif	  
}//void test(void)

