/***************************************************
 * This is a USART library for the ATMega328P.
 *
 * It can provide basic USART (serial) communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 *
 *
 *
 * FOR STUDENTS:
 *
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper code
 * and complete these functions.
 *
 * Hint 1: RTFM! The Atmel device datasheets contain all information necessary.
 *
 * Hint 2: We do not expect you to write the most performant or exceptionally
 * well-engineered code, but it should work. If in doubt, sacrifice speed for
 * reliability. If you are bored, rewrite the entire library in assembler and
 * squeeze the last microsecond out of it.
 *
 ****************************************************/

#include <avr/io.h>
#include <string.h>

#include "USART_implement_me.h"


// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
void USART_Init(uint16_t ubrr)
{
	/* set baudrate */
	UBRR0H = (unsigned char)(ubrr >> 8);
 	UBRR0L = (unsigned char)(ubrr);

 	/* set frame format: 8 data , NP, 1 SB */
 	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));

 	/* Enable UART receiver and transmitter */
  	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );

	/* Put data into buffer, sends the data */
	UDR0 = data;

}
