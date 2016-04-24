
CC=avr-gcc
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p -c

.PHONY: clean all

EJECUTABLE = appserial.elf
OBJETOS = serial.o main.o

ARCHIVOHEX = appserial.hex

all: $(EJECUTABLE)
	avr-objcopy -O ihex -R .eeprom $(EJECUTABLE) $(ARCHIVOHEX)
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:$(ARCHIVOHEX):i

$(EJECUTABLE): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm $(EJECUTABLE) $(OBJETOS) $(ARCHIVOHEX)



