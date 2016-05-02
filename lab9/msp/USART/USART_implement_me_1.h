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
 * This file is complete, but the according .c file will be given to you in an
 * 'empty' state. See there for further information.
 * 
 ****************************************************/

#ifndef _USART_IMPLEMENT_ME_H_
#define _USART_IMPLEMENT_ME_H_

#include <stdint.h>


// Call once to initialise USART communication
void USART_Init();

// Transmits a single character
void USART_Transmit_char(uint8_t data );


#endif // _USART_IMPLEMENT_ME_H_