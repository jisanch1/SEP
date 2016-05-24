#include <avr/io.h>
#include "timer.h"

void timer2_set_waveform(waveform_mode_te wf)
{
	switch(wf)
	{
	case TIMER_NORMAL:
		TCCR2A &= ~_BV(WGM20) & ~_BV(WGM21);
		TCCR2B &= ~_BV(WGM22);
		break;
	case TIMER_CTC:
		TCCR2A &= ~_BV(WGM20);
		TCCR2A |= _BV(WGM21);
		TCCR2B &= ~_BV(WGM22);
		break;
	case TIMER_FAST_PWM:
		TCCR2A |= _BV(WGM21) | _BV(WGM20);
		TCCR2B &= ~_BV(WGM22);
		break;		
	case TIMER_PHC_PWM:
		TCCR2A &= ~_BV(WGM21);
		TCCR2A |= _BV(WGM20);
		TCCR2B &= ~_BV(WGM22);
		break;
	case TIMER_CTC_FAST_PWM:
		TCCR2A &= ~_BV(WGM21);
		TCCR2A |= _BV(WGM20);
		TCCR2B |= _BV(WGM22);
		break;
	case TIMER_CTC_PHC_PWM:
		TCCR2A |= _BV(WGM21) | _BV(WGM20);
		TCCR2B |= _BV(WGM22);
		break;
	default:
		break;
	}
}

/* Clock and prescaler */
uint8_t timer2_enable_clock(uint16_t prescaler)
{
	switch (prescaler)
	{
	case 1:
		TCCR2B &= ~_BV(CS22) & ~_BV(CS21);
		TCCR2B |= _BV(CS20);
		break;
	case 8:
		TCCR2B &= ~_BV(CS22) & ~_BV(CS20);
		TCCR2B |= _BV(CS21);
		break;
	case 32:
		TCCR2B &= ~_BV(CS22);
		TCCR2B |= _BV(CS21) | _BV(CS20);
		break;
	case 64:
		TCCR2B &= ~_BV(CS21) & ~_BV(CS20);
		TCCR2B |= _BV(CS22);
		break;
	case 128:
		TCCR2B &= ~_BV(CS21);
		TCCR2B |= _BV(CS22) | _BV(CS20);
		break;
	case 256:
		TCCR2B &= ~_BV(CS20);
		TCCR2B |= _BV(CS22) | _BV(CS21);
		break;
	case 1024:
		TCCR2B |= _BV(CS22) | _BV(CS21) | _BV(CS20);
		break;
	default:
		timer2_disable_clock();
		return TIMER_BAD_CLOCK_SET;
		break;
	}
	return TIMER_OK;
}

inline void timer2_disable_clock(void)
{
	TCCR2B &= ~_BV(CS22) & ~_BV(CS21) & ~_BV(CS20);
}

/* Configure compare registers */
inline void timer2_set_compare_register_A(uint8_t value)
{
	OCR2A = value;
}

inline void timer2_set_compare_register_B(uint8_t value)
{
	OCR2B = value;
}

/* Interrupts */
inline void timer2_enable_compare_A_interrupt(void)
{
	TIMSK2 |= _BV(OCIE2A);
} 

inline void timer2_disable_compare_A_interrupt(void)
{
	TIMSK2 &= ~_BV(OCIE2A);
} 

inline void timer2_enable_compare_B_interrupt(void)
{
	TIMSK2 |= _BV(OCIE2B);
} 

inline void timer2_disable_compare_B_interrupt(void)
{
	TIMSK2 &= ~_BV(OCIE2B);
} 

inline void timer2_enable_overflow_interrupt(void)
{
	TIMSK2 |= _BV(TOIE2);
} 

inline void timer2_disable_overflow_interrupt(void)
{
	TIMSK2 &= ~_BV(TOIE2);
} 






