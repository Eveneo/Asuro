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


/** DEBUG **/
uint8_t counter = 0;            // Anzahl Schleifendurchläufe



void test(void)
{    
    /** Ausgeben der ADC Werte der Liniensensoren **/
    uart_puti(get_line_adc(_LEFT));
    uart_puts(";");
    uart_puti(get_line_adc(_RIGHT));
    uart_puts(_CR);
    
                    
}
    


        
#if 0

counter++;

switch(counter)
{
    case 0:
    motor_pwr( 85, 85);
    uart_puts(_CR);
    uart_puts(_CR);
    uart_puts("PWM 85");
    uart_puts(_CR);
    counter_long++;
    break;    
    
    case 50:    
    motor_pwr(100, 100);
    uart_puts(_CR);
    uart_puts(_CR);
    uart_puts("PWM 100");
    uart_puts(_CR);
    counter_long++;
    break;
    
    case 100:
    motor_pwr(150, 150);
    uart_puts(_CR);
    uart_puts(_CR);
    uart_puts("PWM 150");
    uart_puts(_CR);
    counter_long++;
    break;
    
    case 150:
    motor_pwr(200, 200);
    uart_puts(_CR);
    uart_puts(_CR);
    uart_puts("PWM 200");
    uart_puts(_CR);
    counter_long++;
    break;
    
    case 200:
    motor_pwr(255, 255);
    uart_puts(_CR);
    uart_puts(_CR);
    uart_puts("PWM 255");
    uart_puts(_CR);
    counter_long++;
    break;
    
    case 250:
    uart_puts(_CR);
    uart_puts("done...");
    uart_puts(_CR);
    uart_puts(_CR);
    counter_long++;
    break;
    
}//switch(counter)

#endif