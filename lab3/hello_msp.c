#include <msp430.h> 
#include <stdint.h> 
 
int main(void) 
{ 
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer, it runs by default. 
	P1DIR |= 0x01;				// Port1 direction register, Pin0 as output 
 
	while (1)
	// Infinite loop 
	{ 
 
		P1OUT ^= 0x01;
		// Toggle P1.0 (XOR) 
 
		for(volatile uint32_t i=0; i< 20000; i++); // Busy‐wait delay 
	} 
   
	return 0; 
} 