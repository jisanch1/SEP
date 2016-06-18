#ifndef _SENSOR_H_
#define _SENSOR_H_

#define ADC_MIN	7
#define ADC_MAX	240	
#define T_MIN	-40
#define T_MAX	100

typedef struct ntc_val
{
	uint8_t adc_val;
	int temp;
} ntc_val;

void sensor_init(void);
int sensor_read(void);

#endif