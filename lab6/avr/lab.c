#ifdef AVR
    #define F_CPU   16000000UL                  // clk set to 16MHz 
    #define DELAY   10
    #define TRIG    OCR0A 
    #include <avr/io.h> 
    #include <util/delay.h> 

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

#ifdef MSP430
    #define DELAY   10
    #define TRIG    TA0CCR2 
    #include <msp430.h> 
    #include <stdint.h>

void init(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer, it runs by default. 

    P1DIR |= BIT3;                              // Enable pin TA0.2 (P1.3) to output.
    P1SEL |= BIT3;                              // Set the pin P1.3 to peripherial.

    TA0CCR0 = 0xF0;
    TA0CTL = TASSEL_1;                          // Use the master clock
    //TA0CTL |= ID_3;                             // Prescaler off
    TA0CTL |= MC_1;                             // Mode control: up mode, timer counts to 0xFFFF.
    TA0CTL |= TACLR;                            // Timer clear.
    TA0CCTL2 |= OUTMOD_7;                       // Output mode: Reset/set
 
}

void delay(void)
{
    uint8_t wait = DELAY;
    while (wait--)
    {
        WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer, it runs by default. 
        __delay_cycles(1000);
    }
}

#endif

uint8_t set_bright(uint8_t bright);
 
int main (void) 
{ 
    init();
    TRIG = 0x00;                               // Comparator start on 0x00. Led off.

    while(1)  
    { 
        
        delay();                       
        TRIG = set_bright(TRIG);
      
    } 
} 

uint8_t set_bright(uint8_t bright)
{
    static uint8_t inc = 1;
    if (bright == 0x00)
        inc = 1;
    else if (bright == 0xF0)
        inc = -1;


    return bright + inc*0x05;
}