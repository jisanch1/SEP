#define F_CPU 16000000UL 
#include <avr/io.h> 
#include <util/delay.h> 

#define DELAY 	500

int count = 0;

void chaser(void)
{
	PORTC = 0x01;
	for(count = 0; count < 3 ; )
	{
		_delay_ms(DELAY);

		PORTC <<= 1;
        if (!PORTC || PORTC > 0x10)
        {
        	PORTC = 0x01;
        	count++;
        }
	}
}

void knight(void)
{
	PORTC = 0x01;
	int dir = 1;
	for(count = 0; count < 3 ; )
	{
        _delay_ms(DELAY);

        if (dir)
        	PORTC <<= 1;
        else
        	PORTC >>= 1;
        
        if (PORTC == 0x10 || PORTC == 0x01)
        	dir = !dir;

        if (PORTC == 0x01)
        	count++;
	}
	_delay_ms(DELAY);
}

void blink(void)
{
	PORTC = 0x15;
	for(count = 0; count < 20 ; count++)
	{
        _delay_ms(DELAY);
        PORTC ^= 0x1F;
	}
}

 
int main (void) 
{ 
    DDRC |= 0x1F;        // sets the direction of this pin to output 

    while(1)  
    { 
    	chaser();
    	knight();
    	blink();
    }

    return 0; 
}