NAME=lab_avr
CC=avr-gcc
CFLAGS=-Wall -Wextra -Wpedantic --std=gnu99 -Os
MCU=atmega328p
PORT=/dev/cu.usbmodemfd1342

compile:
	$(CC) $(NAME).c $(CFLAGS) -mmcu=$(MCU) -o $(NAME).elf
	avr-objcopy -j .text -j .data -O ihex $(NAME).elf $(NAME).hex

burn: 
	avrdude -v -p atmega328p -F -c stk500v1 -P $(PORT) -b57600 -D -V -U flash:w:$(NAME).hex:i

clean:
	rm $(NAME).elf $(NAME).hex

	

XNAME=extra_avr
extra: 
	$(CC) $(XNAME).c $(CFLAGS) -mmcu=$(MCU) -o $(XNAME).elf
	avr-objcopy -j .text -j .data -O ihex $(XNAME).elf $(XNAME).hex

eburn: 
	avrdude -v -p atmega328p -F -c stk500v1 -P $(PORT) -b57600 -D -V -U flash:w:$(XNAME).hex:i

eclean:
	rm $(XNAME).elf $(XNAME).hex
