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
 * This file has an incomplete struct definition. Add definitions for its
 * members! Check the other files and the lab description to find out which
 * parameters and what ranges are needed.
 *
 ****************************************************/

#ifndef _USART_IMPLEMENT_ME_H_
#define _USART_IMPLEMENT_ME_H_

#include <stdint.h>

#define PRESCALER(B)	(( (F_CPU) / ( (B) * 16UL)) - 1)

struct USART_configuration
{
	uint8_t parity;
	uint8_t stop;
	uint8_t size;
	uint32_t baud;
};

enum {NONE, ODD, EVEN};

// Call once to initialise USART communication
uint8_t USART_Init(struct USART_configuration config);

// Transmits a single character
void USART_Transmit_char(uint8_t data );

// Transmits a given string
void USART_Transmit_String(char* string);


#endif // _USART_IMPLEMENT_ME_H_
