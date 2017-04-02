INCL = -I freeRTOS/include -I $(SOURCE_DIR)/include -I $(SOURCE_DIR)/portable/GCC/ATMega328p -I .

SOURCE_DIR = freeRTOS
PORT_DIR = freeRTOS/portable/GCC/ATMega328p
SRC	= \
main.c \
spi.c \
uart.c \
adc.c \
$(SOURCE_DIR)/croutine.c \
$(SOURCE_DIR)/tasks.c \
$(SOURCE_DIR)/queue.c \
$(SOURCE_DIR)/list.c \
$(SOURCE_DIR)/event_groups.c \
$(SOURCE_DIR)/portable/MemMang/heap_2.c \
$(PORT_DIR)/port.c

CC = avr-gcc
CFLAGS = -mmcu=atmega328 -O2 -std=gnu99

default:
	mkdir -p bin
	$(CC) -o bin/out.o $(SRC) $(CFLAGS) $(INCL)
	avr-objcopy -j .text -j .data -O ihex bin/out.o bin/out.hex

all: current voltage temperature relay
	mkdir -p bin
	$(CC) -o bin/out.o $(SRC) $(CFLAGS) $(INCL)
	avr-objcopy -j .text -j .data -O ihex bin/out.o bin/out.hex

current:
	mkdir -p bin
	$(CC) -o bin/current.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_CURRENT
	avr-objcopy -j .text -j .data -O ihex bin/current.o bin/current.hex

voltage:
	mkdir -p bin
	$(CC) -o bin/voltage.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_VOLTAGE
	avr-objcopy -j .text -j .data -O ihex bin/voltage.o bin/voltage.hex

temperature:
	mkdir -p bin
	$(CC) -o bin/temperature.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_TEMPERATURE
	avr-objcopy -j .text -j .data -O ihex bin/temperature.o bin/temperature.hex

relay:
	mkdir -p bin
	$(CC) -o bin/relay.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_RELAY
	avr-objcopy -j .text -j .data -O ihex bin/relay.o bin/relay.hex

clean: 
	rm -rf bin