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


// includes
#define F_CPU	16000000UL		// MCU Clock Speed - needed for baud rate value computation
#define TX_BUFFLEN 30			// Send buffer size
#define RX_BUFFLEN 30			// Receive buffer size


// includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "USART_implement_me.h"




// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.
uint8_t USART_Init(struct USART_configuration config)
{
	// You can recycle your previous code. But remember, this time you are
	// supposed to configure interrupts! Maybe you]ll have to extend it a little bit?

		// Add your code here. Don't forget that this function is supposed
	// to return an error code if something goes wrong!
	uint16_t ubrr;
	uint8_t error = 1;
 	UCSR0C = 0x00;
	

 	/* Enable UART receiver and transmitter */
  	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/* set baudrate */
	if (config.baud < 1200 || config.baud > 57600)
	{
		goto out;
	}
	ubrr = PRESCALER(config.baud);
	UBRR0H = (unsigned char)(ubrr >> 8);
 	UBRR0L = (unsigned char)(ubrr);

 	/* Parity */
 	switch (config.parity)
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
 		goto out;
 		break;
 	}

 	/* Stop bit */
 	if (config.stop == 2)
 	{
 		UCSR0C |= (1<<USBS0);
 	}
 	else if (config.stop == 1)
 	{

 	}
 	else
 	{
 		goto out;
 	}

 	/* Character size */
 	switch (config.size)
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
 		goto out;
 		break;
 	}

  	/* No errors in configuration */
  	error = 0;

out:
	
	if (error)
	{
		/* Reset; configuration to 8N1, 9600b */
 		UCSR0C = 0x00 | (1<<UCSZ00)|(1<<UCSZ01);
 		ubrr = PRESCALER(9600);
		UBRR0H = (unsigned char)(ubrr >> 8);
 		UBRR0L = (unsigned char)(ubrr);
	}

	return error;
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	// A nice hint: With interrupts, you can send bytes whenever the register UDR0
	// is free. And there is an interrupt called USART_UDRE_vect that *tells you*
	// whenever UDR0 is free.
	// This requires you to have some bytes in the buffer that you would like to
	// send, of course. You have a buffer, don't you?

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



// Receives a single character.
char USART_Receive_char(void)
{
	// A nice hint: With interrupts, your microcontroller can inform you whenever
	// a character comes in. There is an interrupt called USART_RX_vect for that.
	// If such an interrupt would fill a buffer with the received data, this
	// function here could return you one character from this buffer. You would no
	// longer need to 'wait for the byte to arrive', but could just fetch it out
	// of this buffer at any later point. And of course you've got a buffer,
	// right?
	// If the buffer is actually empty, you could maybe return a 0 or so to
	// indicate that to the user?
	return 0;
}



// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART_Receive_String(char* buffer, uint8_t bufflen)
{
	// Your previous code might need little adaptions here. As a nice hint: A
	// string consists of many characters. If a user gives you a buffer to fill
	// for him, and you have a buffer full of already received characters...
	buffer[0] = 0x00;
	return bufflen;
} 