// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SPI/SPI_implement_me.h"
#include "USART/USART_implement_me.h"
#include "PetitFatFilesystem/PetitFS.h"
#include "display/ST7735_commands.h"
#include "display/graphic_shapes.h"
#include "display/testroutines.h"

// UART configuration
#define BAUD	57600					// serial communication baud rate
#define UBRR_VALUE F_CPU/16/BAUD-1

void exp15_1(void);
void exp15_2(void);
void exp15_3(void);

int main(void)
{
	// Initialises the serial communication interface
	USART_Init(UBRR_VALUE);

	DDRC &= ~_BV(DDC5) & ~_BV(DDC4) & ~_BV(DDC3);
	PCICR |= _BV(PCIE1);
	PCMSK1 |= _BV(PCINT11) | _BV(PCINT12) | _BV(PCINT13);

	USART_Transmit_String("Initialising hardware... ");
	SPI_Master_Init();
	ST7735_init(); 
	sei();
	USART_Transmit_String("success.\r\n");




	




	// Play dead
	while(1);
}

ISR(PCINT1_vect)
{
	if (!(PINC & _BV(PC5)))
	{
		cli();
		exp15_1();
		sei();
	}
	else if (!(PINC & _BV(PC4)))
	{
		cli();
		exp15_2();
		sei();
	}
	else if (!(PINC & _BV(PC3)))
	{
		cli();
		exp15_3();
		sei();
	}
}

void errorHalt(char* msg, uint8_t type) {
	USART_Transmit_String("Error: ");
	USART_Transmit_String(msg);
	USART_Transmit_String(", ");
	USART_Transmit_char(*itoa(type, NULL, 10));
	USART_Transmit_String("\r\n");
	//while(1);
}

void exp15_1(void)
{
	uint8_t err = 1;

	FATFS fs;     		/* File system structure */
	uint8_t buf[32];	/* Buffer for card access */
	UINT nr;			/* Used for various file access functions. */
	
	
	// Welcome message
	USART_Transmit_String("Hello! This is the SD card test.\r\n");
  
	// Initialise SD and file system.
	do
	{
		USART_Transmit_String("Trying to mount the SD card's file system: ");
		if ((err = pf_mount(&fs))) errorHalt("pf_mount", err);
		_delay_ms(100);
	} while(err);
	
	USART_Transmit_String("success.\r\n");
	
	// Open read test file.
	USART_Transmit_String("Trying to open a text file for reading: ");
	if ((err = pf_open("SEPtest.txt"))) errorHalt("pf_open", err);
	USART_Transmit_String("success.\r\n");
	
	// Print test file to the serial interface.
	USART_Transmit_String("Here is the file content:\r\n");
	USART_Transmit_String("\r\n-----------------------------------------------\r\n");
	while (1) {
	  if ((err = pf_read(buf, sizeof(buf), &nr))) errorHalt("pf_read", err);
	  if (nr == 0) break;
	  for(uint8_t i=0; i<nr; i++)
	  {
	      USART_Transmit_char(buf[i]);
	  }
	}
	
	USART_Transmit_String("\r\n-----------------------------------------------\r\n\r\n\r\n");
	
	
	
	// Open write test file.
	USART_Transmit_String("Trying to open a text file for writing: ");
	if ((err = pf_open("writeMe.txt"))) errorHalt("pf_open", err);
	USART_Transmit_String("success.\r\n");
	
	// Set read/write pointer to beginning of file.
	USART_Transmit_String("Going to beginning of file: ");
	if ((err = pf_lseek(0))) errorHalt("pf_lseek", err);
	USART_Transmit_String("success.\r\n");
	
	// Write data and finish the transaction.
	USART_Transmit_String("Writing some data to the file: ");
	char message[] = "If this message does not appear in your text file, you failed to read the PFF documentation. Read about the use of pf_write() there!";
	if ((err = pf_write(message, strlen(message), &nr))) errorHalt("pf_write while writing the file content", err);
	if ((err = pf_write(0, 0, &nr))) errorHalt("pf_write while closing the file.", err);
	USART_Transmit_String("success.\r\n");
	
	
	
	// Open write test file.
	USART_Transmit_String("Trying to open another text file for writing more: ");
	if ((err = pf_open("writeMe2.txt"))) errorHalt("pf_open", err);
	USART_Transmit_String("success.\r\n");
	
	// Set read/write pointer to beginning of file.
	USART_Transmit_String("Going to beginning of file: ");
	if ((err = pf_lseek(0))) errorHalt("pf_lseek", err);
	USART_Transmit_String("success.\r\n");
	
	// Receive a message over USART
	USART_Transmit_String("Please type a short message and press enter. ");
	USART_Receive_String(message, strlen(message));
	
	// Write it to the file and finish the transaction.
	USART_Transmit_String("Writing message to the file: ");
	if ((err = pf_write(message, strlen(message), &nr))) errorHalt("pf_write while writing the file content", err);
	if ((err = pf_write(0, 0, &nr))) errorHalt("pf_write while closing the file.", err);
	USART_Transmit_String("success.\r\n");
	USART_Transmit_String("\r\n\r\n<---- The SD card test is done! ---->\r\n\r\n");
}

void exp15_2(void)
{
		USART_Transmit_String("Starting next run of test graphics: ");	
		
		// RGB test
		fillScreen(ST7735_RED);		// Fully red screen.
		_delay_ms(1000);
		fillScreen(ST7735_GREEN);	// Fully green screen.
		_delay_ms(1000);
		fillScreen(ST7735_BLUE);	// Fully blue screen.
		_delay_ms(1000);
		USART_Transmit_String("#");	
		
		
		// Color test: Starts with green at (0,0) and fades to red along the x axis and
		// to blue along the z axis. Gives a good overview of the color capabilities
		// of the display.
		for(uint8_t pixel_y=0; pixel_y<TFT_HEIGHT; pixel_y++)
		{
			for(uint8_t pixel_x=0; pixel_x<TFT_WIDTH; pixel_x++)
			{
				int16_t green = 255-(pixel_x+pixel_y)/2;
				if (green < 0)
					green = 0;
				drawPixelRGB(pixel_x, pixel_y, pixel_x+95, green, pixel_y+127);
			}
		}
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		// Adds a circle to the previous image. This shows the imperfections of the
		// used algorithm very well!
		drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 50, ST7735_RED);
		drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 49, ST7735_RED);
		drawCircle(TFT_WIDTH/2, TFT_HEIGHT/2, 51, ST7735_RED);
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		// Draws a small 2x2 square in each corner and a green pixel in the center.
		// Useful to identify the display rotation.
		fillScreen(ST7735_BLACK);
		testcorners();
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		// Draws rays of yellow lines originating in each of the corners.
		testlines(ST7735_YELLOW);
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		// Draws many boxed triangles.
		testtriangles();
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		// Draws many rectangles.
		testdrawrects(ST7735_GREEN);
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		// Draws many *filled* rectangles.
		testfillrects(ST7735_MAGENTA, ST7735_YELLOW);
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		// Draws discs and circles.
		fillScreen(ST7735_BLACK);
		testfillcircles(10, ST7735_BLUE);
		testdrawcircles(7, ST7735_WHITE);
		_delay_ms(1000);
		USART_Transmit_String("#");
		
		
		USART_Transmit_String(" finished!\r\n");
		
		// Here would be a nice place for drawing a bitmap, wouldn't it?
}

void exp15_3(void)
{
	uint8_t err = 1;
	FATFS fs;     		/* File system structure */
	uint8_t buf[3];		/* Buffer for card access */
	UINT nr = 1;			/* Used for various file access functions. */
	uint8_t x = 0;
	uint8_t y = 0;

	do
	{
		USART_Transmit_String("Trying to mount the SD card's file system: ");
		if ((err = pf_mount(&fs))) errorHalt("pf_mount", err);
		_delay_ms(100);
	} while(err);
	USART_Transmit_String("success.\r\n");

	USART_Transmit_String("Trying to open the bmp: ");
	if ((err = pf_open("rocks.bmp"))) errorHalt("pf_open", err);
	USART_Transmit_String("success.\r\n");

	USART_Transmit_String("Reading bmp: ");
	if ((err = pf_lseek(0x36))) 
		errorHalt("pf_lseek", err);

	while(nr)
	{
		if ((err = pf_read(buf, sizeof(buf), &nr))) 
			errorHalt("pf_read", err);

		//USART_Transmit_char(*itoa(nr, NULL, 10));

		drawPixelRGB(x, y, buf[2], buf[1], buf[0]);

		x++;
		if (x == 160)
		{
			x = 0;
			y++;
		}
		if (y == 128)
		{
			y = 0;
		}
	}
	
	USART_Transmit_String("success.\r\n");






}




























