
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial.o serial.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o modem.o modem.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o motor.o motor.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -mmcu=atmega328p motor.o modem.o serial.o main.o -o appmotor.elf
	avr-objcopy -O ihex -R .eeprom appmotor.elf appmotor.hex
	# sudo avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:appmotor.hex:i 
	# sudo avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:appmotor.hex:i 

clean:
	rm appmotor.elf modem.o main.o motor.o serial.o appmotor.hex
