#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer0/timer0.h"
#include "uart/uart.h"

#define PRESCALER	64
#define TIMER_MAX	250
#define TIME_MS 	1000
#define BAUDRATE 	57600
#define TX_BUF_SIZE	64

uint16_t count;
uint16_t button_count;
uint8_t press;
char tx_buffer[TX_BUF_SIZE];
char* tx_pos;

int main(void)
{
	count = 0;
	button_count = 0;
	press = 0;
	tx_pos = tx_buffer;

	DDRB |= _BV(DDB5);

	// Button init
	DDRB &= ~_BV(DDB7);
	PORTB |= _BV(PORTB7);
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT7);

	timer0_set_waveform(CTC);
	timer0_enable_clock(PRESCALER);
	timer0_set_compare_register_A(TIMER_MAX);
	timer0_enable_compare_A_interrupt();

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
	if (press)
	{
		button_count++;	
	}
	
}

ISR(PCINT0_vect)
{
	if (PINB & _BV(PB7)) // Suelta boton
	{
		press = 0;
		// Se escribe el buffer
		snprintf(tx_buffer, TX_BUF_SIZE, "Button pressed for %d ms.\r\n", button_count);
		uart_enable_empty_register_interrupt();
	}
	else // Apreta boton
	{
		press = 1;
		button_count = 0;
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
