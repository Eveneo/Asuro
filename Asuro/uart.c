/*
 * uart.c
 *
 * Created: 11.10.2013 00:10:08
 *  Author: Dante999
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

/************************************************************************
* /brief	Initialisierung UART
*			- Setzen der Baudrate
*			- Aktivieren des Senders (TxD) und Empfängers (RxD)
*			- Festlegen des Formats ( 8data, 1 stop bit)
*
* /param	none
*
* /return	none
*
*
************************************************************************/
void init_uart(void)
{
		uint8_t ubrr;
		ubrr = _FOSC/16/_BAUD-1;
		/* Set baud rate */
		UBRRH = (unsigned char)(ubrr>>8);
		UBRRL = (unsigned char)ubrr;
		/* Enable receiver and transmitter */
		UCSRB |= (1<<TXEN);
		/* Set frame format: 8data, 1stop bit */
		UCSRC = (1<<URSEL) |(3<<UCSZ0);
		
		uart_puts("uart init done..." _CR);
}

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
void uart_putc(unsigned char data) 
{	
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

/************************************************************************
* /brief	Übertragen eines Strings über UART
*
* /param	*s	zu übertragenden Text in "" einfügen
*
* /return	none
*
* /example	uart_puts("Test Text");
*
************************************************************************/
void uart_puts (const char *s)
{
	do
	{
		uart_putc (*s);
	}
	while (*s++);
}

/************************************************************************
* /brief	Übertragen eines Zahlenwertes (uint16_t)
*
* /param	data:	Zahl oder Variable (0..65536)
*
* /return	none
*
* /example	uint16_t i = 2000;
*
*			uart_puti(i);
*
************************************************************************/
void uart_puti( uint16_t data )
{
	char buffer[6];
	itoa(data, buffer, 10);
	uart_puts(buffer);
}


