#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "exp13.h"
#include "timer/timer.h"
#include "uart/uart.h"

#define PRESCALER	64
#define TIMER_MAX	250
#define BAUDRATE 	57600
#define SW0_RELEASE (PINB & _BV(PB7))
#define SW0_PRESS	!SW0_RELEASE



int main(void)
{
	led_init();
	cnt_init();
	deb_init();

	// Button init
	DDRB &= ~_BV(DDB7);
	PORTB |= _BV(PORTB7);
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT7);

	DDRC &= ~_BV(DDC0);
	PORTC |= _BV(PORTC0);
	PCICR |= _BV(PCIE1);
	PCMSK1 |= _BV(PCINT8);

	timer0_set_waveform(TIMER_CTC);
	timer0_enable_clock(PRESCALER);
	timer0_set_compare_register_A(TIMER_MAX);
	timer0_enable_compare_A_interrupt();

	timer2_set_waveform(TIMER_CTC);
	timer2_enable_clock(PRESCALER);
	timer2_set_compare_register_A(TIMER_MAX);
	timer2_enable_compare_A_interrupt();

	uart_set_baudrate(BAUDRATE);
	uart_set_parity(NONE);
	uart_set_stopbit(1);
	uart_set_databits(8);
	uart_enable_tx();

	sei();

	while(1);

}

ISR(TIMER0_COMPA_vect)
{
	// Led
	led_toggle();

	// button sw0
	if (SW0_PRESS)
	{
		cnt_increase();
	}

	// debouncer
	deb_countdown();
	
}

ISR(TIMER2_COMPA_vect)
{

}

ISR(PCINT0_vect)
{
	if (SW0_RELEASE) // Suelta boton
	{
		cnt_stop();
	}
	else // Apreta boton
	{
		cnt_start();
		deb_shift_left();
	}
}

ISR(PCINT1_vect)
{
	if (PINC & _BV(PINC0)) // Suelta boton
	{
		deb_release();
	}
	else // Apreta boton
	{
		deb_press();
	}
}

ISR(USART_UDRE_vect)
{
	cnt_send_next();

}


