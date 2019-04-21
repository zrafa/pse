
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o adc.o adc.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial.o serial.c
	avr-gcc -mmcu=atmega328p adc.o serial.o -o adc.elf
	avr-objcopy -O ihex -R .eeprom adc.elf adc.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:motor.hex:i 



clean:
	rm adc.elf adc.o adc.hex serial.o
