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
#define _FOSC 8000000		//Hz


void init_uart(void);
void uart_putc(unsigned char data);
void uart_puts (const char *s);


/************************************************************************
* /brief	Übertragen eines ASCII Zeichens (z.B. tab, return etc.)
*			Siehe ASCII Tabelle
*
* /param	data:	ASCII Code (0..255)
*
* /return	none
*
*
************************************************************************/
void uart_puti( uint16_t data );


#endif /* UART_H_ */