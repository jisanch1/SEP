#define F_CPU 16000000UL 
#define LED_PIN 5 
 
#include <avr/io.h> 
#include <util/delay.h> 
 
int main (void) 
{ 
    DDRB |= (1 << LED_PIN);          // sets the direction of this pin to output 
   
    while(1)  
    { 
        PORTB ^= (1 << LED_PIN);     // toggles the state of this pin 
        _delay_ms(500);              // busy‐waits the specified time 
    } 
} 