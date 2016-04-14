#define F_CPU   16000000UL                  // clk set to 16MHz 
#define DELAY   10
#define TRIG    OCR0A 
#include <avr/io.h> 
#include <util/delay.h> 

uint8_t adc_read(void);
void delay(void);

void init(void)
{
    DDRD |= (1 << DDD6);                        // Enable pin OC0A to output. (PD6)
    TCCR0A |= (1 << COM0A1);                    // Compare output mode: up at 0x00, down on match with OCR0A.
    TCCR0A |= (1 << WGM01) | (1 << WGM00);      // Waveform generation mode: Fast PWM, count to top.
    TCCR0B |= (1 << CS01) | (1 << CS00);        // Enable timer counter. Prescaler set to clk/64 (250 kHz).PWM loop time 1.024 ms. 
    TRIG = 0x00;                                // Comparator start on 0x00. Led off.

    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);                        // ADC prescaler ser to clk/128 (125 kHz).
    ADCSRA |= _BV(ADEN);                        // Enable ADC.
    ADMUX = 0x00;                               // ADC0 as input. (PC0)
    ADMUX |= _BV(REFS0);                        // AVcc at Vmax.
    ADMUX |= _BV(ADLAR);                        // Use the ADC High byte.        
}

void run(void)
{
    TRIG = adc_read();
}
 
int main (void) 
{ 
    init();
    while(1)
    {
        run(); 
    }
} 

#define ADC_IS_WORKING  ADCSRA & (1 << ADSC)
uint8_t adc_read(void)
{
    ADCSRA |= _BV(ADSC);                        // Strat adc conversion

    while(ADC_IS_WORKING);

    return ADCH;                                // Read most significative pins.
}