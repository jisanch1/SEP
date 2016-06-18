FILES=main.c uart/uart.c clock/clock.c timer/timer.c util/util.c sensor/sensor.c sensor/adc/adc.c logic/logic.c
NAME=peltier
CC=msp430-gcc
OBJ=msp430-objcopy
CFLAGS=-Wall -Wextra --std=gnu99 -Os
MCU=msp430f5529
PORT=/dev/ttyACM0

compile:
	$(CC) $(FILES) $(CFLAGS) -mmcu=$(MCU) -o $(NAME).elf
	$(OBJ) --output-target=elf32-msp430 $(NAME).elf $(NAME).bin

burn: 
	mspdebug tilib -d $(PORT) "prog $(NAME).bin"

clean:
	rm $(NAME).elf $(NAME).bin

	
