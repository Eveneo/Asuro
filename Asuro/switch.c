/*
 * switch.c
 *
 * Created: 04.11.2013 09:01:28
 *  Author: Dante999
 */ 


 /* Tasterbelegung
 *
 *________________________
 *|      Tasterbelegung  |
 *|______________________|
 *| Taster | ADC  | Wert |
 *|----------------------|
 *| K1     | ADC4 | HIGH |
 *| K2     | ADC4 | LOW  |
 *| K3     | ADC4 | HIGH |
 *| K4     | ADC4 | HIGH |
 *| K5     | ADC5 | HIGH |
 *| K6     | ADC6 | HIGH |
 *|______________________|
 *
 */

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "asuro.h"
 #include "uart.h"

 int switch_press[6];

 /************************************************************************
 * /brief   Initialisierung der Taster K1-K6
 *          - Setzen der IO's
 *          - Konfigurieren des Interrupts (INT1)
 *
 * /param   none
 *
 * /return  none
 *
 *
 ************************************************************************/
 void init_switch(void)
 {
    DDRC &= ~( 1 << PC4);               // PC4 als Eingang definieren (ADC4)
    DDRC &= ~( 1 << PD3);               // PD3 als Eingang definieren (INT1)

    /** ITN1 definieren **/
    MCUCR |=  ( 1 << ISC11);             // Interrupt bei fallender Flanke an INT1
    MCUCR &= ~( 1 << ISC10);

    GICR |= ( 1 << INT1);               // Intterupt INT1 aktivieren

    uart_puts("switch init done...");
    uart_puts(_CR);

 }

  /************************************************************************
 * /brief   ADC Messung der Taster
 *
 * /param   none
 *
 * /return  ADC Wert (uint16_t)
 *
 *
 ************************************************************************/
 uint16_t get_switch_adc(void)
 {

    ADMUX &= ~( 1 << MUX0);
    ADMUX &= ~( 1 << MUX1);
    ADMUX |=  ( 1 << MUX2);
    ADMUX &= ~( 1 << MUX3);

    ADCSRA |= ( 1 << ADSC);                 // Starte ADC Messung
    
    while( ADSC == 1)                       // Warte bis ADC-Messung beendet
    {
        //wait
    }
    
    return ADC;                             // gib ADC Wert zurück
 }

   /************************************************************************
 * /brief   INT0 - Interrupt bei Tastendruck
 *          Diese Funktion wird bei jedem Tastendruck ausgeführt
 * 
 * /param   none
 *
 * /return  none
 *
 *
 ************************************************************************/

 void get_switch( void)
 {
    uint16_t adc = 0;                                   // Zwischenspeicher für ADC Wert
    int i;                                              // Variable für die for-Schleife

    adc = get_switch_adc();                             // Auslesen des ADC

    for ( i=1; i <= 6; i++)                             // Durchlaufen der Taster 1 bis 6
    {                                                   
        switch_press[i] = 0;                            // löschen des Tastenbits -> Taste wurde nicht gedrückt

        switch(i)
        {
            case 1: 
                    switch_press[1] = 0x01 & adc;       // Auswertung Taster 1
                    break;

            case 2: 
                    switch_press[2] = 0x02 & adc;       // Auswertung Taster 2
                    break;

            case 3: 
                    switch_press[3] = 0x04 & adc;       // Auswertung Taster 3
                    break;

            case 4: 
                    switch_press[4] = 0x08 & adc;       // Auswertung Taster 4
                    break;

            case 5: 
                    switch_press[5] = 0x10 & adc;       // Auswertung Taster 5
                    break;

            case 6: 
                    switch_press[6] = 0x20 & adc;       // Auswertung Taster 6
                    break;
        } // switch(i)
    } // for(i..)


 }

 ISR (INT1_vect)
 {
    //get_switch();
    uint16_t buffer2 = 0;

    buffer2 = get_switch_adc();
    uart_puts("switch:");
    uart_puti(buffer2);
    uart_puts(_CR);
 
 }
