all:
	avr-gcc -c -mmcu=atmega328p silly-crt.S -o startup.o
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_blink.o led_blink.c
	avr-gcc -nostartfiles -mmcu=atmega328p  -Wall  -Os -Wl,-gc-sections -ffunction-sections -fdata-sections -std=gnu99 -DF_CPU=16000000UL -T ldscript.ld     startup.o led_blink.o    -o led_blink.elf
	avr-objcopy -O ihex -R .eeprom led_blink.elf led_blink.hex
	sudo avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:led_blink.hex:i


clean:
	rm led_blink.elf led_blink.o led_blink.hex startup.o


