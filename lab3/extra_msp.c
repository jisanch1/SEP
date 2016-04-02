#include <msp430.h> 
#include <stdint.h> 
#define DELAY 	1
#define TOT		1*25

inline void delay(int count)
{
	uint32_t wait = 30*count;
	for(volatile uint32_t i=0; i< wait; i++); // Busy‐wait delay
}



int main(void) 
{ 
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer, it runs by default. 
	P1DIR |= 0x01;				// Port1 direction register, Pin0 as output 
	//P4DIR |= 0x80;
 
	int i, j = 0;
	int inc = 1;



	while (1)
	// Infinite loop 
	{ 
 
		P1OUT ^= 0x01;
		//P4OUT ^= 0X80;

        for (i = 0; i < j ; i++)
        	delay(DELAY);              // busy‐waits the specified time

        P1OUT ^= 0x01;
        //P4OUT ^= 0X80;

        for ( ; i < TOT; i++)
        	delay(DELAY);              // busy‐waits the specified time

        if (inc) j++;
        else j--;

        if (j == TOT) inc = 0;
        if (j == 0) inc = 1;     
	} 
   
	return 0; 
} 