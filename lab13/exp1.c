#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

#include "timer0/timer0.h"
#include "uart/uart.h"

#define PRESCALER	64
#define TIMER_MAX	250

uint16_t count;

int main(void)
{
	count = 0;

	DDRB |= _BV(DDB5);
	DDRB &= ~_BV(DDB7);

	timer0_set_waveform(CTC);
	timer0_enable_clock(PRESCALER);
	timer0_set_compare_register_A(TIMER_MAX);
	timer0_enable_compare_A_interrupt();
	sei();

	while(1);

}

ISR(TIMER0_COMPA_vect)
{
	count++;
	if (count >= 1000)
		{
			PORTB ^= _BV(PORTB5);
			count = 0;
		}
}