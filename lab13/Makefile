FILES=exp1.c timer/timer0.c timer/timer2.c uart/uart.c
NAME=lab13
CC=avr-gcc
CFLAGS=-Wall -Wextra -Wpedantic --std=gnu99 -Os
MCU=atmega328p
MPORT=/dev/cu.usbmodemfd142
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



