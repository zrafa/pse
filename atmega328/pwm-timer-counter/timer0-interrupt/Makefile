
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o timer0-contador0.o timer0-contador0.c
	avr-gcc -mmcu=atmega328p timer0-contador0.o main.o -o main.elf
	avr-objcopy -O ihex -R .eeprom main.elf main.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:main.hex:i 



clean:
	rm timer0-contador0.o main.o main.hex main.elf
