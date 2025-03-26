CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
TTY = /dev/ttyUSB0

# INCLUDES = -I. -I../FreeRTOS/Source/portable/GCC/ATMega1284p -I../FreeRTOS/Source/include
INCLUDES = -I. -I../FreeRTOS/Source/portable/GCC/ATMega328 -I../FreeRTOS/Source/include
SOURCES =	../FreeRTOS/Source/list.o \
			../FreeRTOS/Source/queue.o \
			../FreeRTOS/Source/tasks.o \
			../FreeRTOS/Source/portable/MemMang/heap_1.o \
			../FreeRTOS/Source/portable/GCC/ATMega328/port.o \
			adc.o \
			nokia_1100_lcd.o \
			$(MAIN).o

MMCU = atmega328
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU) 
HFLAGS = -O ihex -R .eeprom

MAIN = main

all: $(SOURCES) link hex

clean:
	-rm *.o *.hex $(MAIN) \
		../FreeRTOS/Source/*.o \
		../FreeRTOS/Source/portable/MemMang/heap_1.o \
		../FreeRTOS/Source/portable/GCC/ATMega328/port.o 

link: 
	$(CC) -mmcu=$(MMCU) -o $(MAIN) $(SOURCES)

hex:
	$(OBJCOPY) $(HFLAGS) $(MAIN) $(MAIN).hex

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

.cpp.o:
	$(CXX) -c $(CFLAGS) $(INCLUDES) -fno-exceptions $< -o $@

flash:
	avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:$(MAIN) 




