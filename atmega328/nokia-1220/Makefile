
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o nokia_1220_lcd.o nokia_1220_lcd.c
	avr-gcc -mmcu=atmega328p nokia_1220_lcd.o -o nokia_1220_lcd.elf
	avr-objcopy -O ihex -R .eeprom nokia_1220_lcd.elf nokia_1220_lcd.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:nokia_1220_lcd.hex:i 



clean:
	rm nokia_1220_lcd.elf nokia_1220_lcd.o nokia_1220_lcd.hex
