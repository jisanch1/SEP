FILES=USART_1.c USART/USART_implement_me.c
NAME=usart
CC=avr-gcc
CFLAGS=-Wall -Wextra -Wpedantic --std=gnu99 -Os
MCU=atmega328p
MPORT=/dev/cu.usbmodemfd132
PORT=/dev/ttyACM0

compile:
	$(CC) $(FILES) $(CFLAGS) -mmcu=$(MCU) -o $(NAME).elf
	avr-objcopy -j .text -j .data -O ihex $(NAME).elf $(NAME).hex

lburn: 
	avrdude -v -p atmega328p -F -c stk500v1 -P $(PORT) -b57600 -D -V -U flash:w:$(NAME).hex:i

mburn:
	avrdude -v -p atmega328p -F -c stk500v1 -P $(MPORT) -b57600 -D -V -U flash:w:$(NAME).hex:i

clean:
	rm $(NAME).elf $(NAME).hex



