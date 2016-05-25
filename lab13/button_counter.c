#include <avr/io.h>
#include <stdio.h>
#include "uart/uart.h"

#define TX_BUF_SIZE	64

static uint16_t button_count;
static char tx_buffer[TX_BUF_SIZE];
static char* tx_pos;

void cnt_init(void)
{
	button_count = 0;
	tx_pos = tx_buffer;
}

void cnt_increase(void)
{
	button_count++;
}

void cnt_stop(void)
{
	snprintf(tx_buffer, TX_BUF_SIZE, "Button pressed for %d ms.\r\n", button_count);
	uart_enable_empty_register_interrupt();
}

void cnt_start(void)
{
	button_count = 0;
}

void cnt_send_next(void)
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