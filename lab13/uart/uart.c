/* I am Groot */
#include <avr/io.h>
#include "uart.h"

/* UART Configuration Parameters */
static inline uint16_t ubrr_calc(uint16_t baud)
{
	return (( (F_CPU) / (baud * 16UL) ) - 1);
}

uint8_t uart_set_baudrate(uint16_t baud)
{
	if (baud < 1200 || baud > 57600)
		return ERROR;
	uint16_t ubrr = ubrr_calc(baud);
	UBRR0H = (unsigned char)(ubrr >> 8);
 	UBRR0L = (unsigned char)(ubrr);
 	return OK;
}

uint8_t uart_set_parity(uint8_t par)
{
	switch (par)
 	{
 	case EVEN:
 		UCSR0C |= _BV(UPM01);
 		UCSR0C &= ~_BV(UPM00);
 		break;
 	case ODD:
 		UCSR0C |= _BV(UPM01) | _BV(UPM00);
 		break;
 	case NONE:
 		UCSR0C &= ~_BV(UPM01) & ~_BV(UPM00);
 		break;
 	default:
 		return ERROR;
 		break;
 	}
 	return OK;
}

uint8_t uart_set_stopbit(uint8_t stpb)
{
 	switch (stpb)
 	{
 	case 1:
 		UCSR0C &= ~_BV(USBS0);
 		break;
 	case 2:
 		UCSR0C |= _BV(USBS0);
 		break;
 	default:
 		return ERROR;
 		break;
 	}
 	return OK;
}

uint8_t uart_set_databits(uint8_t dbits)
{
 	switch (dbits)
 	{
 	case 5:
 		UCSR0C &= ~_BV(UCSZ01) & ~_BV(UCSZ00);
 		break;
 	case 6:
 		UCSR0C |= _BV(UCSZ00);
 		UCSR0C &= ~_BV(UCSZ01);
 		break;
 	case 7:
 		UCSR0C |= _BV(UCSZ01);
 		UCSR0C &= ~_BV(UCSZ00);
 		break;
 	case 8:
 		UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
 		break;
 	default:
 		return ERROR;
 		break;
 	}
 	return OK;
}

void uart_default_conf(void)
{
	/* Reset; configuration to 8N1, 9600b */
	UCSR0C = 0x00 | (1<<UCSZ00)|(1<<UCSZ01);
 	uint16_t ubrr = ubrr_calc(9600);
	UBRR0H = (unsigned char)(ubrr >> 8);
 	UBRR0L = (unsigned char)(ubrr);
}

/* reading and sending characteres */
inline char uart_read_char(void)
{
	return UCSR0A & _BV(RXC0) ? UDR0 : 0x00;
}

inline void uart_send_char(char ch)
{
	if (UCSR0A & _BV(UDRE0))
		UDR0 = ch;
}


/* UART RX enable Functions */
inline void uart_enable_rx(void)
{
	UCSR0B |= _BV(RXEN0);
}

inline void uart_disable_rx(void)
{
	UCSR0B &= ~_BV(RXEN0);
}

inline void uart_enable_rx_complete_interrupt(void)
{
	UCSR0B |= _BV(RXCIE0);
}

inline void uart_disable_rx_complete_interrupt(void)
{
	UCSR0B &= ~_BV(RXCIE0);
}

/* UART TX enable Functions */
inline void uart_enable_tx(void)
{
	UCSR0B |= _BV(TXEN0);
}

inline void uart_disable_tx(void)
{
	UCSR0B &= ~_BV(TXEN0);
}

inline void uart_enable_tx_complete_interrupt(void)
{
	UCSR0B |= _BV(TXCIE0);
}

inline void uart_disable_tx_complete_interrupt(void)
{
	UCSR0B &= ~_BV(TXCIE0);
}

inline void uart_enable_empty_register_interrupt(void)
{
	UCSR0B |= _BV(UDRIE0);
}

inline void uart_disable_empty_register_interrupt(void)
{
	UCSR0B &= ~_BV(UDRIE0);
}