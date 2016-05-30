#include <avr/io.h>
#include "exp13.h"

#define PRESS_BLOCK_TIME 	60
#define RELEASE_BLOCK_TIME	20

static uint8_t pressed;
static uint8_t blocked;
static uint8_t num;

void deb_init(void)
{
	DDRD |= _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);
	PORTD = _BV(DDD3);
	blocked = 0;
	pressed = 0;
	num = 0;
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
	if (!num && !pressed)
	{
		deb_shift_right();		
	}
	pressed = 1;
	num = PRESS_BLOCK_TIME;
}

void deb_release(void)
{
	pressed = 0;
	num = RELEASE_BLOCK_TIME;
}

void deb_countdown(void)
{
	if (num > 0)
	{
		num--;
	}
}

