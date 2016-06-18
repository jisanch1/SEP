#include <msp430.h>
#include <stdint.h>

void adc_init(void) {

	P6SEL |= BIT0;                      	// P6.0 ADC option select
	ADC12CTL0 = ADC12SHT02 + ADC12ON;       // Sampling time, ADC12 on
	ADC12CTL1 = ADC12SHP;                   // Use sampling timer
	ADC12CTL2 = ADC12RES_0;					// 8bit resolution
	ADC12CTL0 |= ADC12ENC;
}

uint8_t adc_read(void) {

	ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
	while (!(ADC12IFG & BIT0));				// Wait conversion to finish

	return (uint8_t)ADC12MEM0;
}