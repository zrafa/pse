
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o play.o play.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial.o serial.c
	avr-gcc -mmcu=atmega328p play.o serial.o -o play.elf
	avr-objcopy -O ihex -R .eeprom play.elf play.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:play.hex:i 
flash:
	avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:play.hex:i 



clean:
	rm serial.o play.elf play.o play.hex
