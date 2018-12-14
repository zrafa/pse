
all:
	avr-gcc -Os -Wall -DF_CPU=1000000 -mmcu=attiny2313 -c -o led.o led.c
	avr-gcc -DF_CPU=1000000 -mmcu=attiny2313 led.o -o led.elf
	avr-objcopy -j .text -j .data -O ihex led.elf led.hex
	# avrdude -v -v -v -v -p t4313 -c arduino -P /dev/ttyACM0 -b19200   -U flash:w:led.hex


clean:
	rm led.elf led.o led.hex
