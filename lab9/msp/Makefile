#FILES=UART1.c
#FILES=UCS08.c 
FILES=USART_2.c USART/USART_implement_me.c
NAME=usart2
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

	
