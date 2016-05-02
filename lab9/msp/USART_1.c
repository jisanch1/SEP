/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * init and send functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
 *
 * Use e.g. 57k6 8N1. This means:
 *    - 57600 Baud/s
 *    - 8 data bits
 *    - No parity bits
 *    - 1 stop bit
 *
 * Note that the ATmega328P Xplained mini developer board
 * allows no higher speeds than this one. The USB to serial
 * translation in the mEDBG chip (ATMega32U4) is not very
 * good. Lower speeds work.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/


// MCU Clock Speed - needed for delay.h
#include <msp430.h>


// Have a look at the .c file, there is code missing.
#include "USART/USART_implement_me_1.h"



/* The main function */
int main(void)
{
	// Initialises the serial communication interface
	USART_Init();


	// Welcome message
	USART_Transmit_char('C');
	// Play dead
	//while(1);
	USART_Transmit_char('o');
	USART_Transmit_char('n');
	USART_Transmit_char('g');
	USART_Transmit_char('r');
	USART_Transmit_char('a');
	USART_Transmit_char('t');
	USART_Transmit_char('u');
	USART_Transmit_char('l');
	USART_Transmit_char('a');
	USART_Transmit_char('t');
	USART_Transmit_char('i');
	USART_Transmit_char('o');
	USART_Transmit_char('n');
	USART_Transmit_char('s');
	USART_Transmit_char('!');
	USART_Transmit_char(' ');
	USART_Transmit_char('Y');
	USART_Transmit_char('o');
	USART_Transmit_char('u');
	USART_Transmit_char(' ');
	USART_Transmit_char('g');
	USART_Transmit_char('o');
	USART_Transmit_char('t');
	USART_Transmit_char(' ');
	USART_Transmit_char('t');
	USART_Transmit_char('h');
	USART_Transmit_char('e');
	USART_Transmit_char(' ');
	USART_Transmit_char('s');
	USART_Transmit_char('e');
	USART_Transmit_char('r');
	USART_Transmit_char('i');
	USART_Transmit_char('a');
	USART_Transmit_char('l');
	USART_Transmit_char(' ');
	USART_Transmit_char('i');
	USART_Transmit_char('n');
	USART_Transmit_char('t');
	USART_Transmit_char('e');
	USART_Transmit_char('r');
	USART_Transmit_char('f');
	USART_Transmit_char('a');
	USART_Transmit_char('c');
	USART_Transmit_char('e');
	USART_Transmit_char(' ');
	USART_Transmit_char('t');
	USART_Transmit_char('o');
	USART_Transmit_char(' ');
	USART_Transmit_char('w');
	USART_Transmit_char('o');
	USART_Transmit_char('r');
	USART_Transmit_char('k');
	USART_Transmit_char('!');
	USART_Transmit_char('\r');
	USART_Transmit_char('\n');


	// Play dead
	while(1);
}


