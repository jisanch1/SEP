#include <msp430.h>
#include <stdint.h>
#include "timer.h"

static uint16_t count;
static suscriber rep;

void timer_init(void) {

	count = 0;

	P1DIR |= BIT0;                            	// P1.0 led output
	TA0CTL = TASSEL_2 + MC_1 + ID_2;		  	// SMCLK, upmode, clk/4 (1Mhz)
	TA0CCR0 = 10000;							// count to 10 ms
	TA0CCTL0 = CCIE;                          	// CCR0 interrupt enabled
	TA0CTL |= TACLR;  							// clear TAR

	__no_operation();
}

void timer_suscribe(suscriber sus) {

	rep = sus;
}

void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void) {
	
	count++;

	/* HB */
	if (count == 10)
	{
		P1OUT &= ~BIT0;                         // Toggle P1.0 led
	}
	else if (count == 100)
	{
		P1OUT |= BIT0;							// Toggle P1.0 led
		count = 0;
		rep();
	}

}



