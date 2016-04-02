NAME=hello_msp
CC=msp430-gcc
OBJ=msp430-objcopy
CFLAGS=-Wall -Wextra --std=gnu99 -Os
MCU=msp430f5529

compile:
	$(CC) $(NAME).c $(CFLAGS) -mmcu=$(MCU) -o $(NAME).elf
	$(OBJ) --output-target=elf32-msp430 $(NAME).elf $(NAME).bin

burn: 
	mspdebug tilib -d /dev/ttyACM0 "prog $(NAME).bin"

clean:
	rm $(NAME).elf $(NAME).bin

	
XNAME=extra_msp
extra: 
	$(CC) $(XNAME).c $(CFLAGS) -mmcu=$(MCU) -o $(XNAME).elf
	$(OBJ) --output-target=elf32-msp430 $(XNAME).elf $(XNAME).bin

eburn: 
	mspdebug tilib -d /dev/ttyACM0 "prog $(XNAME).bin"

eclean:
	rm $(XNAME).elf $(XNAME).bin