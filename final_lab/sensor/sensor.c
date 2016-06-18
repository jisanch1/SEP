#include <msp430.h>
#include <stdint.h>
#include "sensor.h"
#include "adc/adc.h"

const ntc_val ntc_conv[] = {
	{0,		-100},
	{7,	 	-40},
	{10,	-35},
	{14,	-30},
	{18,	-25},
	{24,	-20},
	{31,	-15},
	{39,	-10},
	{49,	-5},
	{60,	0},
	{72,	5},
	{85,	10},
	{99,	15},
	{113, 	20},
	{128, 	25},
	{141, 	30},
	{154, 	35},
	{166, 	40},
	{178, 	45},
	{188, 	50},
	{196, 	55},
	{204, 	60},
	{211, 	65},
	{217, 	70},
	{222, 	75},
	{227, 	80},
	{230, 	85},
	{234, 	90},
	{236, 	95},
	{239, 	100},
	{241, 	105},
};


void sensor_init(void) {

	adc_init();
}

int sensor_read(void) {

	uint8_t adc_val = adc_read();
	uint8_t pos;
	int temp;

	if (adc_val < ADC_MIN) return -100;
	else if (adc_val > ADC_MAX) return 200;

	for (pos = 0; ntc_conv[pos].adc_val <= adc_val ; pos++);
		
	temp = 5*(adc_val - ntc_conv[pos].adc_val);
	temp /= ntc_conv[pos+1].adc_val - ntc_conv[pos].adc_val; 
	temp += ntc_conv[pos].temp;


	return temp;
}