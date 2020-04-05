
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o nokia_1100_lcd.o nokia_1100_lcd.c	
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o adc.o adc.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c

	avr-gcc -mmcu=atmega328p adc.o nokia_1100_lcd.o main.o -o adc.elf	
	avr-objcopy -O ihex -R .eeprom adc.elf adc.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:adc.hex:i 



clean:
	rm adc.elf adc.o adc.hex main.o nokia_1100_lcd.o
