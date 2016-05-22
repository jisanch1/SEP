/***************************************************
 * This is a USART library for the ATMega328P.
 *
 * It can provide basic USART (serial) communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 * 
 * 
 * 
 * FOR STUDENTS:
 * 
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper code
 * and complete these functions.
 * 
 * Hint 1: RTFM! The Atmel device datasheets contain all information necessary.
 * 
 * Hint 2: We do not expect you to write the most performant or exceptionally
 * well-engineered code, but it should work. If in doubt, sacrifice speed for
 * reliability. If you are bored, rewrite the entire library in assembler and
 * squeeze the last microsecond out of it.
 * 
 ****************************************************/


// includes
#define F_CPU	16000000UL		// MCU Clock Speed - needed for baud rate value computation
#define TX_BUFFLEN 30			// Send buffer size
#define RX_BUFFLEN 30			// Receive buffer size
#include <util/delay.h> 

// includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "USART_implement_me.h"
#include "uart328p/uart328p.h"
#include "ringbuffer/ringbuffer.h"

// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.

ringbuffer_t *rx_buf;
ringbuffer_t *tx_buf;

uint8_t USART_Init(struct USART_configuration config)
{
	// Add your code here. Don't forget that this function is supposed
	// to return an error code if something goes wrong!
	
	/* Create Buffers */
	rx_buf = rb_create(RX_BUFFLEN);
	tx_buf = rb_create(TX_BUFFLEN);

 	/* Enable UART receiver and transmitter */
  	uart_enable_rx();
  	uart_enable_tx();

  	/* Enable UART RX Complete Interrupt */
  	uart_enable_rx_complete_interrupt();

	/* set baudrate */
  	if (uart_set_baudrate(config.baudrate))
  		goto error;

 	/* Parity */
  	if (uart_set_parity(config.parity))
  		goto error;

 	/* Stop bit */
  	if (uart_set_stopbit(config.stopbits))
  		goto error;

 	/* Number of databits*/
  	if (uart_set_databits(config.databits))
  		goto error;

  	/* No errors in configuration */
  	return OK;

error:
	
	/* Reset; configuration to 8N1, 9600b */
 	uart_default_conf();
	return ERROR;
}



// Transmits a single character
void USART_Transmit_char()
{
	// A nice hint: With interrupts, you can send bytes whenever the register UDR0
	// is free. And there is an interrupt called USART_UDRE_vect that *tells you*
	// whenever UDR0 is free.
	// This requires you to have some bytes in the buffer that you would like to
	// send, of course. You have a buffer, don't you?

	char ch;
	if (!rb_get_char(tx_buf, &ch))
	{
		uart_send_char(ch);
	}
	else
	{
		uart_disable_empty_register_interrupt();
	}
}



// Transmits a given string
void USART_Transmit_String(char* string)
{
	uint8_t len = strlen(string);
	if (len > rb_get_free_space(tx_buf))
	{
		return;
	}

	rb_put_string(tx_buf, string, len);
	uart_enable_empty_register_interrupt();

	
}



// Receives a single character.
char USART_Receive_char(void)
{
	// A nice hint: With interrupts, your microcontroller can inform you whenever
	// a character comes in. There is an interrupt called USART_RX_vect for that.
	// If such an interrupt would fill a buffer with the received data, this
	// function here could return you one character from this buffer. You would no
	// longer need to 'wait for the byte to arrive', but could just fetch it out
	// of this buffer at any later point. And of course you've got a buffer,
	// right?
	// If the buffer is actually empty, you could maybe return a 0 or so to
	// indicate that to the user?
	char ch;
	ch = uart_read_char();
	rb_put_char(rx_buf, ch);

	return ch;
}



// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
char ret = 0;
uint8_t USART_Receive_String(char* buffer, uint8_t bufflen)
{
	// Your previous code might need little adaptions here. As a nice hint: A
	// string consists of many characters. If a user gives you a buffer to fill
	// for him, and you have a buffer full of already received characters...
	if (ret)
	{
		rb_get_string(rx_buf, buffer, bufflen);
		ret = 0;
		return 0;
	}
	buffer[0] = 0;
	return 0;
} 


/* interrupts */
ISR(USART_RX_vect)
{
	char ch = USART_Receive_char();
	if (ch == '\r')
	{
		ret = 1;
	}
}

ISR(USART_UDRE_vect)
{
	USART_Transmit_char();
}