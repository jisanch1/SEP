
 

#if FAMILY == AVR

void init(void)
{
    DDRD |= (1 << DDD6);                        // Enable pin OC0A to output.
    TCCR0A |= (1 << COM0A1);                    // Compare output mode: up at 0x00, down on match with OCR0A.
    TCCR0A |= (1 << WGM01) | (1 << WGM00);      // Waveform generation mode: Fast PWM, count to top.
    TCCR0B |= (1 << CS01) | (1 << CS00);        // Enable timer counter. Prescaler set to clk/64 (250 kHz).
                                                // PWM loop time 1.024 ms. 
}

void delay(void)
{
    _delay_ms(DELAY);
}

#endif