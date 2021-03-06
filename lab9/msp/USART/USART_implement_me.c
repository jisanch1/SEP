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
#ifdef AVR
#define F_CPU	16000000UL
#include <avr/io.h>
#include <string.h>
#endif

#ifdef MSP430
#include <msp430.h>
#endif

#include "USART_implement_me.h"


// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.
uint8_t USART_Init(struct USART_configuration config)
{
#ifdef AVR	
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

#endif

#ifdef MSP430
	uint8_t error = 1;
 	//UCSR0C = 0x00;
	

 	/* Enable UART receiver and transmitter */
  	P4DIR |= BIT4;				// Tx as output
	P4SEL |= BIT4 + BIT5;		// Tx y Rx pins connected to peripherials

	UCA1CTL1 |= UCSWRST;		// Enable UART configuration
	UCA1CTL1 |= UCSSEL_2;		// Select SMCLK

	/* set baudrate */
	if (config.baud < 1200 || config.baud > 57600)
	{
		goto out;
	}
	switch (config.baud)
	{
	case 9600:
		UCA1BR0 = 160;				// Prescaler 9600
		UCA1BR1 = 1;				// Prescaler 9600
		UCA1MCTL |= UCBRS_6 + UCBRF_0;
		break;
	case 19200:
		UCA1BR0 = 208;				// Prescaler 19200
		UCA1BR1 = 0;				// Prescaler 19200
		UCA1MCTL |= UCBRS_3 + UCBRF_0;
		break;
	case 57600:
		UCA1BR0 = 69;				// Prescaler 57600
		UCA1BR1 = 0;				// Prescaler 57600
		UCA1MCTL |= UCBRS_4 + UCBRF_0;
		break;
	}

	UCA1CTL0 = 0x00;			// 8N1, Reset

 	/* Parity */
 	switch (config.parity)
 	{
 	case ODD:
 		UCA1CTL0 |= UCPEN;	
 		break;
 	case EVEN:
 		UCA1CTL0 |= UCPEN + UCPAR;
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
 		UCA1CTL0 |= UCSPB;
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
 	case 7:
 		UCA1CTL0 |= UC7BIT;
 		break;
 	case 8:
 		break;
 	default:
 		goto out;
 		break;
 	}

 	UCA1CTL1 &= ~UCSWRST;		// Disable UART configuration
  	/* No errors in configuration */
  	error = 0;

out:
	
	if (error)
	{
		/* Reset; configuration to 8N1, 57600b */
		UCA1BR0 = 69;				// Prescaler 57600
		UCA1BR1 = 0;				// Prescaler 57600
		UCA1MCTL |= UCBRS_4 + UCBRF_0;
		UCA1CTL0 = 0x00;			// 8N1
		UCA1CTL1 &= ~UCSWRST;		// Disable UART configuration
	}

	return error;

#endif

}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
#ifdef AVR
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );

	/* Put data into buffer, sends the data */
	UDR0 = data;
#endif

#ifdef MSP430
	/* Wait for empty transmit buffer */
	while (UCA1STAT & UCBUSY);

	/* Put data into buffer, sends the data */
	UCA1TXBUF = data;
#endif	
}



// Transmits a given string
void USART_Transmit_String(char* string)
{
	while (*string)
		USART_Transmit_char((uint8_t)(*string++));
}


