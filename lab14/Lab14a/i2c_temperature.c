/***************************************************
 * This program reads the temperature from an TMP102
 * I2C temperature sensor. It assumes ADD0 to be on GND,
 * thereby setting the device to address 0x90.
 *
 * This code is based on Atmel Application Note
 * AVR3015 and the according software examples and
 * on the example code published by Sparkfun at
 * https://www.sparkfun.com/products/11931
 * 
 * 
 * FOR STUDENTS:
 * This file is complete and does not require changes.
 * The file I2C_implement_me.c does, though. Compile
 * this file after you have made all the necessary
 * additions and connect with a terminal program
 * to see the temperature readings.
 *
 ****************************************************/


// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL

// read and write addresses; set ADD0 = GND
#define TMP102_READ	 	0x91
#define TMP102_WRITE 	0x90


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>


// Have a look at both the .h and the .c file, there is code missing.
// Reuse the code from previous labs!
#include "USART/USART_implement_me.h"

// Have a look here, too! You are supposed to complete the function
// bodies and enable I2C communication for your application!
#include "I2C/I2C_implement_me.h"





/* Temperature read function */

//Read a tmp102 sensor on a given temp_number or channel
int16_t tmp102Read(void)
{
	
	uint8_t msb, lsb;
	int16_t temp;
	
		
	i2cSendStart();							// send start condition
	i2cWaitForComplete();
	
	i2cSendByte(TMP102_WRITE); 				// send WRITE address of TMP102
	i2cWaitForComplete();
	i2cSendByte(0x00); 						// set TMP102 pointer register to 0 (read temperature)
	i2cWaitForComplete();
	
	i2cSendStart();							// send repeated start condition
	i2cWaitForComplete();
	
	i2cSendByte(TMP102_READ);				// send READ address of TMP102
	i2cWaitForComplete();
	i2cReceiveByte(true);					// receives one byte from the bus and ACKs it
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); 			// reads the MSB (it is a 12 bit value!)
	i2cWaitForComplete();
	i2cReceiveByte(false);					// receives one byte from the bus and NAKs it (last one)
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte();				// reads the LSB
	i2cWaitForComplete();
	
	i2cSendStop();							// send stop condition
	TWCR = 0;								// stop everything
	
	
	// Convert the number to an 8-bit degree Celsius value
	temp = (msb<<8) | lsb;					// combine those two values into one 16 bit value
	temp >>= 4; 							// the values are left justified; fix that by shifting 4 right
	// negative numbers are represented in two's complement, but we just shifted the value and thereby potentially messed it up
	if(temp & (1<<11))						// Hence: if it is a negative number
		temp |= 0xF800;						// restore the uppermost bits
		
	// The 12 bit value has 0.0625°C precision, which is too much for what we want (and the sensor is anyways only about 0.5°C precise)
	// 0.0625 is 1/16 -> Dividing by 16 leaves 1°C precision for the output. Note that shifting >> 4 might go wrong here for negative numbers.
	temp /= 16;
	
	return(temp);
}



/* The main function */
int main(void)
{
	// Pin configurations
	DDRB = 0xff;	// all output; only one heartbeatLED used
	DDRC = 0x00;	// all input; the I2C special pin functions overrule this anyways
	DDRD = 0x00;	// all input
	PORTC = 0x00;	// all pullups off; the breakout board has its own 1k pullups attached
	
	// Initialise the serial communication interface. Note that this now also sets up the interrupts!
	struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1};
	USART_Init(config_57600_8N1);
	
	
	// I2C initialisation
	TWBR = 12;									// 400 kHz at 16MHz crystal and no prescaler
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));		// prescaler 0
	TWDR = 0xFF;								// sending only ones equals an idle high SDA line
	TWCR = (1<<TWEN)|							// Enable TWI-interface and release TWI pins.
			(0<<TWIE)|(0<<TWINT)|				// Disable Interupt.
			(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|	// No Signal requests.
			(0<<TWWC);							//
	
	sei();									// set interrupts (globally enabled)
	
	
	
	USART_Transmit_String("Welcome to the TMP102 I2C temperature sensor test!\r\n");
	
	int16_t temperature = 0;
	char buffer[10];

	while(1)
	{
		temperature = tmp102Read();
		USART_Transmit_String("Temperature: ");
		buffer[0] = '\0';
		itoa(temperature, buffer, 10);
		USART_Transmit_String(buffer);
		USART_Transmit_String(" deg. Celsius\r\n");
		
		PORTB ^= (1 << 5);	// heartbeat LED
		
		_delay_ms(500);
	}
}