NAME=hello_avr
CC=avr-gcc
CFLAGS=-Wall -Wextra -Wpedantic --std=gnu99 -Os
MCU=atmega328p
PORT=/dev/cu.usbmodemfa122

compile:
	$(CC) $(NAME).c $(CFLAGS) -mmcu=$(MCU) -o $(NAME).elf
	avr-objcopy -j .text -j .data -O ihex $(NAME).elf $(NAME).hex

burn: 
	avrdude -vvvv -p atmega328p -F -c stk500v1 -P $(PORT) -b57600 -D -V -U flash:w:$(NAME).hex:i

clean:
	rm $(NAME).elf $(NAME).hex

	
EMPTY=empty_avr
erase:
	$(CC) $(EMPTY).c $(CFLAGS) -mmcu=$(MCU) -o $(EMPTY).elf
	avr-objcopy -j .text -j .data -O ihex $(EMPTY).elf $(EMPTY).hex
	avrdude -p atmega328p -F -c stk500v1 -P /dev/ttyACM0 -b57600 -D -V -U flash:w:$(EMPTY).hex:i
	rm $(EMPTY).elf $(EMPTY).hex

XNAME=extra_avr
extra: 
	$(CC) $(XNAME).c $(CFLAGS) -mmcu=$(MCU) -o $(XNAME).elf
	avr-objcopy -j .text -j .data -O ihex $(XNAME).elf $(XNAME).hex

eburn: 
	avrdude -v -p atmega328p -F -c stk500v1 -P $(PORT) -b57600 -D -V -U flash:w:$(XNAME).hex:i

eclean:
	rm $(XNAME).elf $(XNAME).hex