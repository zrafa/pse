
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial.o serial.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -mmcu=atmega328p serial.o main.o -o appserial.elf
	avr-objcopy -O ihex -R .eeprom appserial.elf appserial.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:appserial.hex:i 

clean:
	rm appserial.elf main.o serial.o appserial.hex

