#define F_CPU   16000000UL                  // clk set to 16MHz 
#define TRIG    OCR0A 
#include <avr/io.h> 
#include <util/delay.h> 

uint8_t adc_read(void);
uint8_t value;
void set_leds(uint8_t value);

void init(void)
{
    DDRD = 0x7F;                                // Enable first 7 pins to output.
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

    value = 0x00;        
}

void run(void)
{
    value = adc_read();
    TRIG = (value >> 2);
    set_leds(value);
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

void set_leds(uint8_t m)
{
    static uint8_t n = 0;
    if (m != n)
    {
        PORTD &= ~0x3F;
        if (m < 32)
            PORTD |= 0x00 & 0x3F;
        else if (m >= 32 && m < 64)
            PORTD |= 0x01 & 0x3F;
        else if (m >= 64 && m < 3*32)
            PORTD |= 0x03 & 0x3F;
        else if (m >= 3*32 && m < 4*32)
            PORTD |= 0x07 & 0x3F;
        else if (m >= 4*32 && m < 5*32)
            PORTD |= 0x0F & 0x3F;
        else if (m >= 5*32 && m < 6*32)
            PORTD |= 0x1F & 0x3F;
        else if (m >= 6*32)
            PORTD |= 0x3F & 0x3F;
    }
    n = m;
}




