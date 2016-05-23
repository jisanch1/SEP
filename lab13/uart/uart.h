
#ifndef _UART_H_
#define _UART_H_

#ifndef F_CPU
#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz
#endif /* F_CPU */

typedef enum {OK, ERROR} uart_error_handler_te;

/* UART Configuration Parameters */
typedef enum {NONE, ODD, EVEN} parity_te;
uint8_t uart_set_baudrate(uint16_t baud);
uint8_t uart_set_parity(uint8_t par);
uint8_t uart_set_stopbit(uint8_t stpb);
uint8_t uart_set_databits(uint8_t dbits);
void uart_default_conf(void);

/* UART RX enable Functions */
void uart_enable_rx(void);
void uart_disable_rx(void);
void uart_enable_rx_complete_interrupt(void);
void uart_disable_rx_complete_interrupt(void);
/* UART TX enable Functions */
void uart_enable_tx(void);
void uart_disable_tx(void);
void uart_enable_tx_complete_interrupt(void);
void uart_disable_tx_complete_interrupt(void);
void uart_enable_empty_register_interrupt(void);
void uart_disable_empty_register_interrupt(void);

/* Reading and sending characteres */
char uart_read_char(void);
void uart_send_char(char ch);

#endif // _UART_H_