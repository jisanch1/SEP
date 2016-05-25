#include <avr/io.h>
#include "exp13.h"

#define DELAY 	100

static uint8_t press;
static uint8_t num;

void deb_init(void)
{
	DDRD |= _BV(DDD0) | _BV(DDD1) | _BV(DDD2) | _BV(DDD3) | _BV(DDD4);
	press = 0;
	num = 0;
}

void deb_shift_left(void)
{
	PORTD <<= 0x01;
        	
    if (PORTD < 0x01 || PORTD > 0x10)
    	PORTD = 0x01;
}

void deb_shift_right(void)
{
	PORTD >>= 0x01;
        	
    if (PORTD < 0x01 || PORTD > 0x10)
    	PORTD = 0x10;
}

void deb_press(void)
{
	if (!press)
	{
		deb_shift_right();
		press = 1;
	}
	num = DELAY;
}

void deb_release(void)
{
	if (!num)
	{
		press = 0;
	}
}

void deb_countdown(void)
{
	if (num > 0)
	{
		num--;
	}
}

