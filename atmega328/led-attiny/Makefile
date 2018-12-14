
all:
	# avr-gcc -Os -Wall -DF_CPU=1000000 -mmcu=attiny2313 -c -o led.o led.c
	avr-gcc -Os -Wall -DF_CPU=1000000 -mmcu=attiny2313 -c -o led.o led.c
	avr-gcc -DF_CPU=1000000 -mmcu=attiny2313 led.o -o led.elf
	avr-objcopy -j .text -j .data -O ihex led.elf led.hex
	avr-gcc -Os -Wall -DF_CPU=1000000 -mmcu=attiny2313 -c -o led-button.o led-button.c
	avr-gcc -DF_CPU=1000000 -mmcu=attiny2313 led-button.o -o led-button.elf
	avr-objcopy -j .text -j .data -O ihex led-button.elf led-button.hex
	# avrdude -v -v -v -v -p t4313 -c arduino -P /dev/ttyACM0 -b19200   -U flash:w:led.hex
	# VIEJO avrdude -v -v -v -v -p t4313 -c arduino -P /dev/ttyACM0 -b 19200 -D -U flash:w:led.hex:i



clean:
	rm led.elf led.o led.hex
	rm led-button.elf led-button.o led-button.hex
