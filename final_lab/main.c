#include <msp430.h>
#include <stdint.h>
#include "clock/clock.h"
#include "uart/uart.h"
#include "timer/timer.h"
#include "util/util.h"
#include "sensor/sensor.h"
#include "logic/logic.h"

void repeat(void);
void write(int temp, stm_state state);

int main(void) {

	WDTCTL = WDTPW + WDTHOLD;		// Stop Watchdog

	clock_init();
	uart_init();
	sensor_init();
	stm_init(22, 3);
	timer_init();
	

	uart_transmit_string("Iniciando...                       \r\n\r\n\r\n");

	timer_suscribe(repeat);

	__enable_interrupt();
	
	while(1);
}

/* This funcion excecutes every second */
void repeat(void) {
	
	int val = sensor_read();
	stm_state state = stm_handler(val);
	write(val, state);
}

void write(int temp, stm_state state) {

	if (temp > T_MAX) {
		uart_transmit_string(" \tTemp too high...             \r");
		return;
	}
	else if (temp < T_MIN) {
		uart_transmit_string(" \tTemp too low...              \r");
		return;
	}
	char buf[5];
	int set_temp = get_set_temp();

	uart_transmit_string(" \tSet = ");
	itoa(set_temp,buf,10);
	uart_transmit_string(buf);

	uart_transmit_string(",     Temp = ");
	itoa(temp,buf,10);
	uart_transmit_string(buf);

	if (state == HEAT) {
		uart_transmit_string("    Heating...");
	}
	else if (state == COOL) {
		uart_transmit_string("    Cooling...");
	}



	uart_transmit_string("                \r");
}