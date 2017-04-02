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
	mkdir -p bin/generic
	$(CC) -o bin/generic/out.o $(SRC) $(CFLAGS) $(INCL)
	avr-objcopy -j .text -j .data -O ihex bin/out.o bin/out.hex

all: motormont temperature relay
	mkdir -p bin/generic
	$(CC) -o bin/generic/out.o $(SRC) $(CFLAGS) $(INCL)
	avr-objcopy -j .text -j .data -O ihex bin/generic/out.o bin/generic/out.hex

motormont:
	mkdir -p bin/current
	$(CC) -o bin/current/current.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_MOTORMONT
	avr-objcopy -j .text -j .data -O ihex bin/current/current.o bin/current/current.hex

temperature:
	mkdir -p bin/temperature
	$(CC) -o bin/temperature/temperature.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_TEMPERATURE
	avr-objcopy -j .text -j .data -O ihex bin/temperature/temperature.o bin/temperature/temperature.hex

relay:
	mkdir -p bin/relay
	$(CC) -o bin/relay/relay.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_RELAY
	avr-objcopy -j .text -j .data -O ihex bin/relay/relay.o bin/relay/relay.hex

clean: 
	rm -rf bin