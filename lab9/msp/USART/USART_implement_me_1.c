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

#include <msp430.h>

#include "USART_implement_me_1.h"


// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
void USART_Init()
{
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


/*	
	P3DIR |= BIT3;				// Tx as output
	P3SEL |= BIT3 + BIT4;		// Tx y Rx pins connected to peripherials
*/
	P4DIR |= BIT4;				// Tx as output
	P4SEL |= BIT4 + BIT5;		// Tx y Rx pins connected to peripherials

/*
	UCA0CTL1 |= UCSWRST;		// Enable UART configuration
	UCA0CTL1 |= UCSSEL_2;		// Select SMCLK
	UCA0BR0 = 69;				// Prescaler 57600
	UCA0BR1 = 0;				// Prescaler 57600
	UCA0MCTL |= UCBRS_4 + UCBRF_0;
	UCA0CTL0 |= 0x00;			// 8N1
	UCA0CTL1 &= ~UCSWRST;		// Disable UART configuration
*/
	UCA1CTL1 |= UCSWRST;		// Enable UART configuration
	UCA1CTL1 |= UCSSEL_2;		// Select SMCLK
	UCA1BR0 = 69;				// Prescaler 57600
	UCA1BR1 = 0;				// Prescaler 57600
	UCA1MCTL |= UCBRS_4 + UCBRF_0;
	UCA1CTL0 |= 0x00;			// 8N1
	UCA1CTL1 &= ~UCSWRST;		// Disable UART configuration
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while (UCA1STAT & UCBUSY);

	/* Put data into buffer, sends the data */
	UCA1TXBUF = data;

}
