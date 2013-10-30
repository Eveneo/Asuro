/*
 * uart.h
 *
 * Created: 11.10.2013 00:33:23
 *  Author: Dante999
 */ 


#ifndef UART_H_
#define UART_H_

#define _CR "\r\n"
#define _BAUD 2400
#define _FOSC 8000000        //Hz

/************************************************************************
* /brief    Initialisierung UART
*            - Setzen der Baudrate
*            - Aktivieren des Senders (TxD) und Empfängers (RxD)
*            - Festlegen des Formats ( 8data, 1 stop bit)
*
* /param    none
*
* /return   none
*
*
************************************************************************/
void init_uart(void);


/************************************************************************
* /brief    Übertragen eines ASCII Zeichens (z.B. tab, return etc.)
*            Siehe ASCII Tabelle
*
* /param    data:    ASCII Code (0..255)
*
* /return   none
*
*
************************************************************************/
void uart_putc(unsigned char data);


/************************************************************************
* /brief    Übertragen eines Strings über UART
*
* /param    *s    zu übertragenden Text in "" einfügen
*
* /return    none
*
* /example    uart_puts("Test");
*
************************************************************************/
void uart_puts (const char *s);



/************************************************************************
* /brief    Übertragen eines Zahlenwertes (uint16_t)
*
* /param    data:    uint16_t Variable (0..65536)
*
* /return   none
*
* /example  uint16_t i = 2000;
*
*           uart_puti(i);
*
************************************************************************/
void uart_puti( uint16_t data );


#endif /* UART_H_ */