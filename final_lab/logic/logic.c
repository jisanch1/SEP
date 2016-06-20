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
		delta_temp = 3;
	}

	// output
	P4DIR |= BIT1 + BIT2;

	// buttons
	P1REN |= BIT1;
	P1OUT |= BIT1;
	P1IES |= BIT1;
	P1IFG &= ~BIT1;
	P1IE |= BIT1;

	P2REN |= BIT1;
	P2OUT |= BIT1;
	P2IES |= BIT1;
	P2IFG &= ~BIT1;
	P2IE |= BIT1;
}

static void output_handler(void) {

	switch (state) {
	case OFF:
		P4OUT &= ~BIT1;
		P4OUT &= ~BIT2;
		break;
	case HEAT:
		P4OUT &= ~BIT2;
		P4OUT |= BIT1;
		break;
	case COOL:
		P4OUT &= ~BIT1;
		P4OUT |= BIT2;
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

int get_set_temp(void) {

	return set_temp;
}

void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void) {

	set_temp++;
	P1IFG &= ~BIT1;
}

void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void) {

	set_temp--;
	P2IFG &= ~BIT1;
}