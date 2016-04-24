
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_blink.o led_blink.c
	avr-gcc -mmcu=atmega328p led_blink.o -o led_blink.elf
	avr-objcopy -O ihex -R .eeprom led_blink.elf led_blink.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:led_blink.hex:i 


clean:
	rm led_blink.elf led_blink.o led_blink.hex
