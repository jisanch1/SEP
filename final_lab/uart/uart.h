#ifndef _UART_H_
#define _UART_H_

void uart_init(void);
void uart_transmit_char(uint8_t data);
void uart_transmit_string(char* string);

#endif