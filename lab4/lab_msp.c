/* !!!!!!!!!!!!! Siempre patea el watchdog !!!!!!!!!!!! */

#include <msp430.h> 
#include <stdint.h> 

#define DELAY 	500


int count = 0;

void delay(int wait)
{
    while (wait--)
    {
        WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer, it runs by default. 
        __delay_cycles(1000);
    }
     
}

void chaser(void)
{
	P6OUT = 0x01;
	for(count = 0; count < 3 ; )
	{
		delay(DELAY);

		P6OUT <<= 0x01;
        if (!P6OUT || P6OUT > 0x10)
        {
        	P6OUT = 0x01;
        	count++;
        }
	}
}

void knight(void)
{
	P6OUT = 0x01;
	int dir = 1;
	for(count = 0; count < 3 ; )
	{
        delay(DELAY);

        if (dir)
        	P6OUT <<= 1;
        else
        	P6OUT >>= 1;
        
        if (P6OUT == 0x10 || P6OUT == 0x01)
        	dir = !dir;

        if (P6OUT == 0x01)
        	count++;
	}
	delay(DELAY);
}

void blink(void)
{
	P6OUT = 0x15;
	for(count = 0; count < 20 ; count++)
	{
        delay(DELAY);
        P6OUT ^= 0x1F;
	}
}

 
int main (void) 
{ 
    count = 0;

    P6DIR = 0x1F;        // sets the direction of this pin to output 

    while(1)  
    { 
        WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer, it runs by default. 

        chaser();
    	knight();
    	blink();
    }

    return 0; 
}