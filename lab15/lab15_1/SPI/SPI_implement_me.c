/***************************************************
 * This is a SPI library for the ATMega328P.
 *
 * It can provide basic SPI master functionality for any application, but is
 * directly targeted at the Adafruit 1.8" SPI display and its SD card socket.
 * 
 * It is based on example codes from the Atmel device datasheet. The code is
 * kept simple, but is not always efficient. It is an easy-to-understand example
 * for studies and not intended for productive use.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 * 
 * 
 * 
 * FOR STUDENTS:
 * 
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper setup
 * code and complete these functions.
 * 
 * Hint 1: RTFM! The Atmel device datasheets contain all information necessary.
 * 
 ****************************************************/

#include <avr/io.h>

#include "SPI_implement_me.h"


// The initialisation function. Call it once from your main() program before
// issuing any SPI commands with the functions below!
//
// Hint: It shoud activate the according SPI module in the microcontroller and
// probably set some register values. SPI has many options to configure! Read
// about them and find out, which ones are to be used here. Understanding the
// datasheets will be much faster than a simple try and error approach.
//
// Also note that <avr/io.h> and other files provide convenient macros for most
// registers and their bits. Stuff like
//    EXPL = (1<<POS)|(1<<FOO);
// is much nicer to read than
//    EXPL = 0b10010;
// This is not a requirement, but it will make life easier for you and your
// supervisors.
void SPI_Master_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB2)|(1<<DDB3)|(1<<DDB5);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


// This function transmits a single byte over the SPI bus.
//
// It does *not* control the CS line.
void SPI_Master_transmit_char(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */ 
	while(!(SPSR & (1<<SPIF)))
		;
}


// This function receives a single byte over the SPI bus.
//
// This is very easy and short if you understood how SPI works.
// Hint: It is a *full duplex* bus!
char SPI_Master_receive_char(void)
{
	SPI_Master_transmit_char(0xFF);

	return SPDR;
}




