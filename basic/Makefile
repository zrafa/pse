
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	avr-gcc -mmcu=atmega328p led.o -o led.elf
	avr-objcopy -O ihex -R .eeprom led.elf led.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:led.hex:i 



clean:
	rm led.elf led.o led.hex
