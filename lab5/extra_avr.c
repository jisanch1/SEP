#define F_CPU 16000000UL 
#define LED_PIN 5 
#define DELAY 	1
#define TOT		2*25
 
#include <avr/io.h> 
#include <util/delay.h> 
 
int main (void) 
{ 
    DDRB |= (1 << LED_PIN);          // sets the direction of this pin to output 
	int i, j = 0;
	int inc = 1;

    while(1)  
    { 
        PORTB ^= (1 << LED_PIN);     // toggles the state of this pin 

        for (i = 0; i < j ; i++)
        	_delay_ms(DELAY);              // busy‐waits the specified time

        PORTB ^= (1 << LED_PIN);     // toggles the state of this pin 

        for ( ; i < TOT; i++)
        	_delay_ms(DELAY);              // busy‐waits the specified time

        if (inc) j++;
        else j--;

        if (j == TOT) inc = 0;
        if (j == 0) inc = 1;         
    } 
} 