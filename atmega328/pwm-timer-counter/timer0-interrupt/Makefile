
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o timer.o timer.c
	avr-gcc -mmcu=atmega328p timer.o -o timer.elf
	avr-objcopy -O ihex -R .eeprom timer.elf timer.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:timer.hex:i 



clean:
	rm timer.elf timer.o timer.hex
