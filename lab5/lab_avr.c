#define F_CPU 16000000UL 
#define DELAY 	100 
#define PRESS 	!(PINB & 0x80) || !(PINC & 0x01) 
 
#include <avr/io.h> 
#include <util/delay.h> 


void shift(void)
{
	PORTB <<= 1;
        	
    if (PORTB < 0x01 || PORTB > 0x10)
    	PORTB = 0x01;
}

int is_pressed(void)
{
		if (PRESS)
			return 1;
		_delay_ms(10);
		return 0;
}

int isnt_pressed(void)
{
	for (int i = 0; i < DELAY; i++)
	{	
		if (PRESS)
			return 0;
		_delay_ms(1);
	}
	return 1;
}

 
int main (void) 
{ 
    DDRB = 0x7F;    
    DDRD = 0xFF; 
    DDRC = 0x00; 
    PORTC = 0xFF;
    PORTB = 0x81;

   
    while(1)  
    { 
    	while (!is_pressed());
    	shift();
        while (!isnt_pressed());
    } 
} 