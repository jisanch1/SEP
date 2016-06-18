#include <msp430.h>
#include <stdint.h>

void uart_init(void) {

	/* Enable UART receiver and transmitter */
  	P4DIR |= BIT4;				// Tx as output
	P4SEL |= BIT4 + BIT5;		// Tx y Rx pins connected to peripherials

	UCA1CTL1 |= UCSWRST;		// Enable UART configuration
	UCA1CTL1 |= UCSSEL_2;		// Select SMCLK

	/* set baudrate */
	UCA1BR0 = 69;				// Prescaler 57600
	UCA1BR1 = 0;				// Prescaler 57600
	UCA1MCTL |= UCBRS_4 + UCBRF_0;

	UCA1CTL1 &= ~UCSWRST;		// Disable UART configuration
	
	uint8_t i;
	for (i = 0; i < 100; i++)
		__no_operation();            
}

// Transmits a single character
void uart_transmit_char(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while (UCA1STAT & UCBUSY);

	/* Put data into buffer, sends the data */
	UCA1TXBUF = data;
}



// Transmits a given string
void uart_transmit_string(char* string)
{
	while (*string)
		uart_transmit_char((uint8_t)(*string++));
}