#define F_CPU 16000000UL 

#define DELAY 	500
#define PRESS1  (!(PINC & 0x01)) 
#define PRESS2  (!(PINC & 0x02)) 
 
#include <avr/io.h> 
#include <util/delay.h> 

unsigned char DigitTo7SegEncoder(unsigned char digit, unsigned char common); 
unsigned char digit;

int is_pressed(int num)
{
        if (PRESS1 && num == 1)
            return 1;
        else if (PRESS2 && num == 2)
            return 1;
        return 0;
}

void init(void)
{
    DDRB = 0x7F;    
    DDRD = 0xFF; 
    DDRC = 0x00; 
    PORTC = 0x00;

    digit = 0;
    PORTD = DigitTo7SegEncoder(digit, 1);
}

void run(void)
{
    while(1)  
    { 
        if (PRESS1 && PRESS2);
        else if (PRESS1 || PRESS2)
        {
            
            if (PRESS1)     digit++;
            else if (digit == 0) digit = 9;     // parche
            else            digit--;
            digit %= 10;
            PORTD = DigitTo7SegEncoder(digit, 1);
            _delay_ms(DELAY);
        }

       _delay_ms(10);
    } 
}

int main (void) 
{ 
    init();
    run();
} 






/*
* Author: AVR Tutorials
* AVR-Tutorials.com
*
* Compiler: AVR GNU C Compiler (GCC) 
*
* Function Description:
* Encode a Decimal Digit 0-9 to its Seven Segment Equivalent.
*
* Function Arguments:
* digit - Decimal Digit to be Encoded
* common - Common Anode (0), Common Cathode(1)
* SegVal - Encoded Seven Segment Value 
*
* Connections:
* Encoded SegVal is return in the other G-F-E-D-C-B-A that is A is the least
* significant bit (bit 0) and G bit 6.
*/
unsigned char DigitTo7SegEncoder(unsigned char digit, unsigned char common)
{
    unsigned char SegVal;
 
    switch(digit)   
    {   
        case 0: if(common == 1) SegVal = 0b00111111;
                else            SegVal = ~0b00111111;
                break;
        case 1: if(common == 1) SegVal = 0b00000110;
                else            SegVal = ~0b00000110;
                break;
        case 2: if(common == 1) SegVal = 0b01011011;
                else            SegVal = ~0b01011011;
                break;
        case 3: if(common == 1) SegVal = 0b01001111;
                else            SegVal = ~0b01001111;
                break;
        case 4: if(common == 1) SegVal = 0b01100110;
                else            SegVal = ~0b01100110;
                break;
        case 5: if(common == 1) SegVal = 0b01101101;
                else            SegVal = ~0b01101101;
                break;
        case 6: if(common == 1) SegVal = 0b01111101;
                else            SegVal = ~0b01111101;
                break;
        case 7: if(common == 1) SegVal = 0b00000111;
                else            SegVal = ~0b00000111;
                break;
        case 8: if(common == 1) SegVal = 0b01111111;
                else            SegVal = ~0b01111111;
                break;
        case 9: if(common == 1) SegVal = 0b01101111;
                else            SegVal = ~0b01101111;       
    }       
    return SegVal;
}