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
#include "switch.h"
#include "line.h"


/** DEBUG **/
uint8_t counter = 0;            // Anzahl Schleifendurchläufe
uint8_t counter_long = 0;




void test(void)
{   

#if 1


#endif
 
#if 0
    /** Ausgeben der ADC Werte der Liniensensoren **/

    line_right = get_line_adc(_RIGHT); 
    line_left = get_line_adc(_LEFT);  
    line_diff = line_left - line_right;

    uart_puti(line_left);
    uart_puts(";");
    uart_puti(line_right);
    uart_puts(";");
    uart_puti(line_diff);
    uart_puts(_CR);
#endif 


#if 0 
    /** Testen der Tasterabfrage **/
    int i;
    
    for(i=1 ; i <= 6 ; i++)
    {
        uart_puti(switch_press[i]);
        uart_puts(" ");
    }
    
    uart_puts(_CR);
        
#endif                    

    


        
#if 0
    /** Ansteuern des Motors in 6 Stufen **/
    for(counter= 0; counter < 255; counter++);
    {

    }

    counter_long++;

    switch(counter_long)
    {
        case 0:
                    motor_pwr( 85, 85);
                    uart_puts(_CR);
                    uart_puts(_CR);
                    uart_puts("PWM 85");
                    uart_puts(_CR);
                    break;    
    
        case 50:    
                    motor_pwr(100, 100);
                    uart_puts(_CR);
                    uart_puts(_CR);
                    uart_puts("PWM 100");
                    uart_puts(_CR);
                    break;
    
        case 100:
                    motor_pwr(150, 150);
                    uart_puts(_CR);
                    uart_puts(_CR);
                    uart_puts("PWM 150");
                    uart_puts(_CR);
                    break;
    
        case 150:
                    motor_pwr(200, 200);
                    uart_puts(_CR);
                    uart_puts(_CR);
                    uart_puts("PWM 200");
                    uart_puts(_CR);
                    break;
    
        case 200:
                    motor_pwr(255, 255);
                    uart_puts(_CR);
                    uart_puts(_CR);
                    uart_puts("PWM 255");
                    uart_puts(_CR);
                    break;
    
        case 250:
                    uart_puts(_CR);
                    uart_puts("done...");
                    uart_puts(_CR);
                    uart_puts(_CR);
                    break;
    
    }//switch(counter)

#endif

} // void test();