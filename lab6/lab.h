#if FAMILY == AVR
	#define F_CPU   16000000UL                      // clk set to 16MHz 
	#define DELAY 	62
	#define TRIG    OCR0A 
	#include <avr/io.h> 
	#include <util/delay.h> 
#endif

void init(void);
void delay(void);