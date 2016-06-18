#include <msp430.h>
#include <stdint.h>
#include "logic.h"

static stm_state state = OFF;
static int set_temp;
static uint8_t delta_temp;

void stm_init(int set, uint8_t delta) {

	if (set < LOGIC_T_MAX && set > LOGIC_T_MIN) {
		set_temp = set;
	}
	else {
		set_temp = 20;
	}

	if (delta < DELTA_MAX) {
		delta_temp = delta;
	}
	else {
		delta_temp = 5;
	}

	// output
	P8DIR |= BIT1 + BIT2;
}

static void output_handler(void) {

	switch (state) {
	case OFF:
		P8OUT &= ~BIT1;
		P8OUT &= ~BIT2;
		break;
	case HEAT:
		P8OUT &= ~BIT2;
		P8OUT |= BIT1;
		break;
	case COOL:
		P8OUT &= ~BIT1;
		P8OUT |= BIT2;
		break;
	}
}

stm_state stm_handler(int temp) {

	switch (state) {
	case OFF:
		if (temp < set_temp - delta_temp) {state = HEAT;}
		else if (temp > set_temp + delta_temp) {state = COOL;}
		break;
	case HEAT:
		if (temp >= set_temp) {state = OFF;}
		break;
	case COOL:
		if (temp <= set_temp) {state = OFF;}
		break;
	}

	// handle output
	output_handler();

	return state;
}

