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


// MCU Clock Speed - needed for baud rate value computation
#define F_CPU	16000000UL
#define BAUD_PRESCALLER (((F_CPU / ( BAUDRATE * 16UL)))-1)

#include <avr/io.h>
#include <string.h>

#include "USART_implement_me.h"


// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.

static uint8_t set_baudrate(uint16_t baud)
{
	if (baud < 1200 || baud > 57600)
		return ERROR;
	uint16_t ubrr = PRESCALER(baud);
	UBRR0H = (unsigned char)(ubrr >> 8);
 	UBRR0L = (unsigned char)(ubrr);
 	return OK;
}

static uint8_t set_parity(uint8_t par)
{
	switch (par)
 	{
 	case ODD:
 		UCSR0C |= (1<<UPM01);
 		break;
 	case EVEN:
 		UCSR0C |= (1<<UPM01)|(1<<UPM00);
 		break;
 	case NONE:
 		break;
 	default:
 		return ERROR;
 		break;
 	}
 	return OK;
}

static uint8_t set_stopbit(uint8_t stpb)
{
 	switch (stpb)
 	{
 	case 1:
 		break;
 	case 2:
 		UCSR0C |= (1<<USBS0);
 		break;
 	default:
 		return ERROR;
 		break;
 	}
 	return OK;
}

static uint8_t set_databits(uint8_t dbits)
{
 	switch (dbits)
 	{
 	case 5:
 		break;
 	case 6:
 		UCSR0C |= (1<<UCSZ00);
 		break;
 	case 7:
 		UCSR0C |= (1<<UCSZ01);
 		break;
 	case 8:
 		UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);
 		break;
 	default:
 		return ERROR;
 		break;
 	}
 	return OK;
}

uint8_t USART_Init(struct USART_configuration config)
{
	// Add your code here. Don't forget that this function is supposed
	// to return an error code if something goes wrong!
 	UCSR0C = 0x00;
	
 	/* Enable UART receiver and transmitter */
  	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/* set baudrate */
  	if (set_baudrate(config.baudrate))
  		goto error;

 	/* Parity */
  	if (set_parity(config.parity))
  		goto error;

 	/* Stop bit */
  	if (set_stopbit(config.stopbits))
  		goto error;

 	/* Number of databits*/
  	if (set_databits(config.databits))
  		goto error;

  	/* No errors in configuration */
  	return OK;

error:
	
	/* Reset; configuration to 8N1, 9600b */
 	UCSR0C = 0x00 | (1<<UCSZ00)|(1<<UCSZ01);
 	uint16_t ubrr = PRESCALER(9600);
	UBRR0H = (unsigned char)(ubrr >> 8);
 	UBRR0L = (unsigned char)(ubrr);

	return ERROR;
}

// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

// Transmits a given string
void USART_Transmit_String(char* string)
{
	while (*string)
		USART_Transmit_char((uint8_t)(*string++));
}



// Receives a single character
char USART_Receive_char(void)
{
	/* Wait for data to be received */ 
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}



// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART_Receive_String(char* buffer, uint8_t bufflen)
{
	int pos = 0;
	
	do 
		buffer[pos] = USART_Receive_char();
	while (buffer[pos] != '\n' && buffer[pos] != '\r' && ++pos < bufflen);

	if (pos >= bufflen)
	{
		buffer[bufflen - 1] = '\0';
		return ERROR;
	}
		
	buffer[pos] = '\0';
	return OK;
}


















