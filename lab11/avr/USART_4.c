/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * interrupt functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/


// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL
#define BUFFLEN 128


#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h> 


// Have a look at both the .h and the .c file, there is code missing.
#include "USART/USART_implement_me.h"



/* The main function */
int main(void)
{
	// You already lerned how to configure that button, remember?
	DDRB &= ~_BV(DDB7);
	PORTB |= _BV(PORTB7);
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT7);
	
	// Initialise the serial communication interface. Note that this now also sets up the interrupts!
	struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1};
	USART_Init(config_57600_8N1);
	
	// This time you should also configure and enable(!) some interrupts.
	sei();
	
	// Print a welcome message
	USART_Transmit_String("Please send some characters from your terminal.\r\n");
	
	
	while(1)
	{			
		// Your program will only ask *if* a string was received. If yes, it will display this string.
		// If not, it will just skip and do other stuff until it is time to ask again.
		
		// Show the received string, if any
		char string[BUFFLEN];
		USART_Receive_String(string, BUFFLEN);
		if(strlen(string))
		{
			USART_Transmit_String("I received these characters: ");

			USART_Transmit_String(string);

			USART_Transmit_String("\r\n");


		}

		// Here you could do all kinds of other cool things. Remember, the step above
		// will be skipped in most iterations, so you have plenty of processing time here....
		//_delay_ms(1000); 
	}
}



// Add a ISR for a button here!

ISR(PCINT0_vect)
{
	if (!(PINB & _BV(PB7)))
		USART_Transmit_String("Button pressed.\r\n");
}







