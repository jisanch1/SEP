#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer/timer.h"
#include "uart/uart.h"

#define PRESCALER	64
#define TIMER_MAX	250
#define TIME_MS 	1000
#define BAUDRATE 	57600
#define SW0_RELEASE (PINB & _BV(PB7))
#define TX_BUF_SIZE	64


uint16_t count;
uint16_t button_count;
char tx_buffer[TX_BUF_SIZE];
char* tx_pos;

void shift_left(void);
void shift_right(void);

int main(void)
{
	count = 0;
	button_count = 0;
	tx_pos = tx_buffer;

	DDRB |= _BV(DDB5);

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
	count++;
	if (count >= TIME_MS)
	{
		PORTB ^= _BV(PORTB5);
		count = 0;
	}

	// button
	if ( !SW0_RELEASE )
	{
		button_count++;	
	}
	
}

ISR(TIMER2_COMPA_vect)
{

}

ISR(PCINT0_vect)
{
	if (SW0_RELEASE) // Suelta boton
	{
		// Se escribe el buffer
		snprintf(tx_buffer, TX_BUF_SIZE, "Button pressed for %d ms.\r\n", button_count);
		uart_enable_empty_register_interrupt();
	}
	else // Apreta boton
	{
		button_count = 0;
		//shift_left();
	}
}

ISR(PCINT1_vect)
{
	if (PINC & _BV(PB0)) // Suelta boton
	{

	}
	else // Apreta boton
	{

	}
}

ISR(USART_UDRE_vect)
{
	if (*tx_pos)	// si hay algo por mandar
	{
		uart_send_char(*tx_pos++);
	}
	else
	{
		// Se limpia el buffer
		tx_buffer[0] = '\0';
		tx_pos = tx_buffer;
		uart_disable_empty_register_interrupt();
	}
}

void shift_left(void)
{
	PORTD <<= 0x01;
        	
    if (PORTD < 0x01 || PORTD > 0x10)
    	PORTD = 0x01;
}

void shift_right(void)
{
	PORTD >>= 0x01;
        	
    if (PORTD < 0x01 || PORTD > 0x10)
    	PORTD = 0x10;
}
