
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	avr-gcc -mmcu=atmega328p led.o -o led.elf
	avr-objcopy -O ihex -R .eeprom led.elf led.hex
	# avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex
 

clean:
	rm led.elf led.o led.hex
