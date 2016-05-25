#include <avr/io.h>

#define TIME_MS 	1000

static uint16_t count;

void led_init(void)
{
	DDRB |= _BV(DDB5);
	count = 0;
}

void led_toggle(void)
{
	count++;
	if (count >= TIME_MS)
	{
		PORTB ^= _BV(PORTB5);
		count = 0;
	}
}