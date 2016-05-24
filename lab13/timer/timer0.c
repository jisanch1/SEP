#include <avr/io.h>
#include "timer.h"

void timer0_set_waveform(waveform_mode_te wf)
{
	switch(wf)
	{
	case TIMER_NORMAL:
		TCCR0A &= ~_BV(WGM00) & ~_BV(WGM01);
		TCCR0B &= ~_BV(WGM02);
		break;
	case TIMER_CTC:
		TCCR0A &= ~_BV(WGM00);
		TCCR0A |= _BV(WGM01);
		TCCR0B &= ~_BV(WGM02);
		break;
	case TIMER_FAST_PWM:
		TCCR0A |= _BV(WGM01) | _BV(WGM00);
		TCCR0B &= ~_BV(WGM02);
		break;		
	case TIMER_PHC_PWM:
		TCCR0A &= ~_BV(WGM01);
		TCCR0A |= _BV(WGM00);
		TCCR0B &= ~_BV(WGM02);
		break;
	case TIMER_CTC_FAST_PWM:
		TCCR0A &= ~_BV(WGM01);
		TCCR0A |= _BV(WGM00);
		TCCR0B |= _BV(WGM02);
		break;
	case TIMER_CTC_PHC_PWM:
		TCCR0A |= _BV(WGM01) | _BV(WGM00);
		TCCR0B |= _BV(WGM02);
		break;
	default:
		break;
	}
}

/* Clock and prescaler */
uint8_t timer0_enable_clock(uint16_t prescaler)
{
	switch (prescaler)
	{
	case 1:
		TCCR0B &= ~_BV(CS02) & ~_BV(CS01);
		TCCR0B |= _BV(CS00);
		break;
	case 8:
		TCCR0B &= ~_BV(CS02) & ~_BV(CS00);
		TCCR0B |= _BV(CS01);
		break;
	case 64:
		TCCR0B &= ~_BV(CS02);
		TCCR0B |= _BV(CS01) | _BV(CS00);
		break;
	case 256:
		TCCR0B &= ~_BV(CS01) & ~_BV(CS00);
		TCCR0B |= _BV(CS02);
		break;
	case 1024:
		TCCR0B &= ~_BV(CS01);
		TCCR0B |= _BV(CS02) | _BV(CS00);
		break;
	default:
		timer0_disable_clock();
		return TIMER_BAD_CLOCK_SET;
		break;
	}
	return TIMER_OK;
}

inline void timer0_disable_clock(void)
{
	TCCR0B &= ~_BV(CS02) & ~_BV(CS01) & ~_BV(CS00);
}

/* Configure compare registers */
inline void timer0_set_compare_register_A(uint8_t value)
{
	OCR0A = value;
}

inline void timer0_set_compare_register_B(uint8_t value)
{
	OCR0B = value;
}

/* Interrupts */
inline void timer0_enable_compare_A_interrupt(void)
{
	TIMSK0 |= _BV(OCIE0A);
} 

inline void timer0_disable_compare_A_interrupt(void)
{
	TIMSK0 &= ~_BV(OCIE0A);
} 

inline void timer0_enable_compare_B_interrupt(void)
{
	TIMSK0 |= _BV(OCIE0B);
} 

inline void timer0_disable_compare_B_interrupt(void)
{
	TIMSK0 &= ~_BV(OCIE0B);
} 

inline void timer0_enable_overflow_interrupt(void)
{
	TIMSK0 |= _BV(TOIE0);
} 

inline void timer0_disable_overflow_interrupt(void)
{
	TIMSK0 &= ~_BV(TOIE0);
} 






