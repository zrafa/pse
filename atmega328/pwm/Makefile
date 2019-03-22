
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o servo.o servo.c
	avr-gcc -mmcu=atmega328p servo.o -o servo.elf
	avr-objcopy -O ihex -R .eeprom servo.elf servo.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:servo.hex:i 



clean:
	rm servo.elf servo.o servo.hex
