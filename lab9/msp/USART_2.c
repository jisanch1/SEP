/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * init and send functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
 *
 * Note that you will have to reconfigure it several times
 * to see the output with all the different parameters.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/


// MCU Clock Speed - needed for delay.h
#ifdef AVR
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#endif

#ifdef MSP430
#include <msp430.h>
#endif

// Have a look at both the .h and the .c file, there is code missing.
#include "USART/USART_implement_me.h"



/* The main function */
int main(void)
{

#ifdef MSP430
	// Ajustes de reloj
	WDTCTL = WDTPW + WDTHOLD;		// Stop Watchdog

	P2DIR |= BIT2;                            // SMCLK set out to pins
	P2SEL |= BIT2;                            
	P7DIR |= BIT7;                            // MCLK set out to pins
	P7SEL |= BIT7;
	
	P5SEL |= BIT2+BIT3;                       // Port select XT2

 	UCSCTL6 &= ~XT2OFF;                       // Enable XT2 
 	UCSCTL3 |= SELREF_2;                      // FLLref = REFO
 	                                          // Since LFXT1 is not used,
 	                                          // sourcing FLL with LFXT1 can cause
 	                                          // XT1OFFG flag to set
 	UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO
	
	 // Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
	                                          // Clear XT2,XT1,DCO fault flags
	  	SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	} while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
	
 	UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                           // expected frequency
	UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2
#endif
// Fuente: Ejemplos de MSP439F55xx de la documantacion de texas instruments

	struct USART_configuration config_57600_8N1 = {NONE, 1, 8, 57600};
	struct USART_configuration config_9600_8N2 = {NONE, 2, 8, 9600};
	struct USART_configuration config_19200_7N1 = {NONE, 1, 7, 19200};
	struct USART_configuration config_19200_7E2 = {EVEN, 2, 7, 19200};

	// Initialise the serial communication interface and print a test string
	USART_Init(config_57600_8N1);
	USART_Transmit_String("Congratulations! You are now sending test messages at 57600 8N1.\r\n");

	// Initialise the serial communication interface and print a test string
	USART_Init(config_9600_8N2);
	USART_Transmit_String("Change your terminal settings and reset the MCU to see 9600 8N2.\r\n");

	// Initialise the serial communication interface and print a test string
	USART_Init(config_19200_7N1);
	USART_Transmit_String("With the wrong settings, you will see nothing but gibberish at 19200 7N1.\r\n");

	// Initialise the serial communication interface and print a test string
	USART_Init(config_19200_7E2);
	USART_Transmit_String("Even parity and two stop bits have limited use. But 19200 7E2 is great for annoying students.\r\n");


	// Play dead
	while(1);
}


