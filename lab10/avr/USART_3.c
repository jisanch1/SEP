/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * receive functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
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
#define BUFFLEN 30


#include <avr/io.h>
#include <util/delay.h>


// Have a look at both the .h and the .c file, there is code missing.
#include "USART/USART_implement_me.h"



/* The main function */
int main(void)
{
	
	
	// Initialise the serial communication interface
	struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1};
	USART_Init(config_57600_8N1);

	
	while(1)
	{
		// Print a welcome message
		USART_Transmit_String("Welcome to the first test. Please send a single character from your terminal.\r\n");
		
		// Show the received character
		char c = USART_Receive_char();
		USART_Transmit_String("I received an ");
		USART_Transmit_char(c);
		USART_Transmit_String(".\r\n\r\n");
		
		
		// Print a welcome message
		USART_Transmit_String("Welcome to the Second test. Please send a properly terminated string.\r\n");
		
		// Show the received string
		char string[BUFFLEN];
		USART_Receive_String(string, BUFFLEN);
		USART_Transmit_String("I received this line: ");
		USART_Transmit_String(string);
		USART_Transmit_String(".\r\n\r\n");
	}
}


