#include <avr/io.h>
#include "exp13.h"

#define PRESS_BLOCK_TIME 	60
#define RELEASE_BLOCK_TIME	20

static uint8_t pressed;
static uint8_t block_time;

void deb_init(void)
{
	DDRD |= _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);
	PORTD = _BV(DDD3);
	pressed = 0;
	block_time = 0;
}

void deb_shift_left(void)
{
	PORTD <<= 0x01;
        	
    if (PORTD < _BV(PORTD3))
    	PORTD = _BV(PORTD3);
}

void deb_shift_right(void)
{
	PORTD >>= 0x01;
        	
    if (PORTD < _BV(PORTD3))
    	PORTD = _BV(PORTD7);
}

void deb_press(void)
{
	if (!block_time && !pressed)
	{
		deb_shift_right();		
	}
	pressed = 1;
	block_time = PRESS_BLOCK_TIME;
}

void deb_release(void)
{
	pressed = 0;
	block_time = RELEASE_BLOCK_TIME;
}

void deb_countdown(void)
{
	if (block_time > 0)
	{
		block_time--;
	}
}

