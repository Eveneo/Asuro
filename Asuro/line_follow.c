/*
 * line_follow.c
 *
 * Created: 27.11.2013 17:53:53
 *  Author: Dante999
 */
 
 #include <avr/io.h>
 #include "asuro.h"
 #include "motor_control.h"
 #include "uart.h"
 #include "line.h"
  
int16_t line_diff  = 0;
uint16_t line_left  = 0;
uint16_t line_right = 0;
uint8_t  pwr_left   = 255;
uint8_t  pwr_right  = 255;

#define _TRIGGER_LINE   15
#define _COR_LEVEL1     20



 void follow_line(void)
 {
     line_diff = get_line_adc(_LEFT) - get_line_adc(_RIGHT);
     
     if ( (line_diff > 15) && (pwr_left > (255-_COR_LEVEL1)) )
     {
      //  uart_puts("15");
         pwr_left -= _COR_LEVEL1;
         pwr_right = 255;
     }

     else if ( (line_diff < -15) && (pwr_right > (255-_COR_LEVEL1)) )
     {
       // uart_puts("-15");
         pwr_left = 255;
         pwr_right -= _COR_LEVEL1;
     }

     else
     {
     uart_puts("0");
     }

//      else
//      {
//          if ( pwr_left < (255-_COR_LEVEL1) )
//          {
//              uart_puts("r+");
//              pwr_left += _COR_LEVEL1;
//          }
// 
//          if ( pwr_right < 255-_COR_LEVEL1 )
//          {
//             uart_puts("l+");
//              pwr_right += _COR_LEVEL1;
//          }
//      }

//          motor_pwr(pwr_left, pwr_right);
// 
          uart_puti(pwr_left);
          uart_puts(";");
          uart_puti(pwr_right);
         uart_puts(";");
         uart_puti(line_diff);
         uart_puts(_CR);
 }