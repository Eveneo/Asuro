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
uint8_t  pwr_left   = 80;
uint8_t  pwr_right  = 80;

#define _LDIFF_STEPS  10
#define _LDIFF_LVL1     20
#define _LREG_LVL1   20
#define _LREG_STEPS 10

#define _DEBUG 0





 void follow_line(void)
 {
     int8_t pwr_corlef, pwr_corrig;
     uint8_t i;
     
     
    line_diff = get_line_diff(); 
/** VERSUCH FEINERE ABSTUFUNG DER ERKENNUNG  **/  

    /** Linker Sensor dunkler **/
    if ( line_diff < -_LDIFF_STEPS )
    {
        for ( i=5 ; i > 0; i--)
        {
            if ( line_diff < i*-_LDIFF_STEPS)
            {
                pwr_corlef = i*_LREG_STEPS;
            }            
        }
    }

    /** Rechter Sensor dunkler **/
    if ( line_diff > _LDIFF_STEPS )
    {
        for ( i=5 ; i > 0; i--)
        {
            if ( line_diff < i*-_LDIFF_STEPS)
            {
                pwr_corrig = i*_LREG_STEPS;
            }
        }
    }

    /** Beide Sensoren gleich hell/dunkel **/
    else if ( (-_LDIFF_LVL1 < line_diff) && (line_diff < _LDIFF_LVL1) )
    {
        if ( pwr_left < (255-_LREG_LVL1) )
        {
            pwr_left += _LREG_LVL1;
        }

        if ( pwr_right < 255-_LREG_LVL1 )
        {
            pwr_right += _LREG_LVL1;
        }
    }

    motor_pwr(pwr_left, pwr_right);




  
  
#if 0  
    /** Linker Sensor dunkler **/   
    if ( (line_diff < -_LDIFF_LVL1) && (pwr_left > _LREG_LVL1) )
    {
        pwr_left -= _LREG_LVL1;                                                     // linken Motor verlangsamen
        pwr_right = 255;                                                            // rechter Motor vollgas
    }

    /** Rechter Sensor dunkler **/
    else if ( (_LDIFF_LVL1 < line_diff) && (pwr_right > _LREG_LVL1) )
    {
        pwr_left = 255;                                                             // linker Motor vollgas
        pwr_right -= _LREG_LVL1;                                                    // rechten Motor verlangsamen
    }

    /** Beide Sensoren gleich hell/dunkel **/
    else if ( (-_LDIFF_LVL1 < line_diff) && (line_diff < _LDIFF_LVL1) )
    {
         if ( pwr_left < (255-_LREG_LVL1) )
         {
             pwr_left += _LREG_LVL1;
         }

         if ( pwr_right < 255-_LREG_LVL1 )
         {
             pwr_right += _LREG_LVL1;
         }
     }

    motor_pwr(pwr_left, pwr_right);
 
#endif
    #if _DEBUG
    uart_puti(pwr_left);
    uart_puts(";");
    uart_puti(pwr_right);
    uart_puts(";");
    uart_puti(line_diff);
    uart_puts(_CR);
    #endif
 }