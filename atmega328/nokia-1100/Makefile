
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o nokia_1100_lcd.o nokia_1100_lcd.c
	avr-gcc -mmcu=atmega328p nokia_1100_lcd.o -o nokia_1100_lcd.elf
	avr-objcopy -O ihex -R .eeprom nokia_1100_lcd.elf nokia_1100_lcd.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:motor.hex:i 



clean:
	rm nokia_1100_lcd.elf nokia_1100_lcd.o nokia_1100_lcd.hex
