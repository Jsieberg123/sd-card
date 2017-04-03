INCL = -I .

SRC	= \
main.c \
spi.c \
uart.c \
adc.c \
tasks.c

CC = avr-gcc
CFLAGS = -mmcu=atmega328 -O2 -std=gnu99

default: generic

all: motormont temperature relay generic

generic: 
	mkdir -p bin/generic
	$(CC) -o bin/generic/out.o $(SRC) $(CFLAGS) $(INCL)
	avr-objcopy -j .text -j .data -O ihex bin/generic/out.o bin/generic/out.hex
motormont:
	mkdir -p bin/motormont
	$(CC) -o bin/motormont/out.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_MOTORMONT
	avr-objcopy -j .text -j .data -O ihex bin/motormont/out.o bin/motormont/out.hex

temperature:
	mkdir -p bin/temperature
	$(CC) -o bin/temperature/out.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_TEMPERATURE
	avr-objcopy -j .text -j .data -O ihex bin/temperature/out.o bin/temperature/out.hex

relay:
	mkdir -p bin/relay
	$(CC) -o bin/relay/out.o $(SRC) $(CFLAGS) ${INCL} -D CARD_TYPE=CARD_TYPE_RELAY
	avr-objcopy -j .text -j .data -O ihex bin/relay/out.o bin/relay/out.hex

clean: 
	rm -rf bin