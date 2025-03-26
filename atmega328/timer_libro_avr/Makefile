CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy

INCLUDES = 
SOURCES = blink_v01.o led.o timer_v01.o

MMCU = atmega8
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU)
HFLAGS = -O ihex -R .eeprom

MAIN = blink_v01

all: $(SOURCES) link hex

clean:
	-rm *.o *.hex $(MAIN)

link: 
	$(CC) -mmcu=$(MMCU) -o $(MAIN) $(SOURCES)

hex:
	$(OBJCOPY) $(HFLAGS) $(MAIN) $(MAIN).hex

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
.cpp.o:
	$(CXX) -c $(CFLAGS) -fno-exceptions $(INCLUDES) $< -o $@

