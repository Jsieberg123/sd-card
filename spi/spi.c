#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "carddefs.h"
#include "options.h"
#include <stdio.h>

volatile char iobuffer[IOBUFSIZE];
volatile unsigned char slot;

void getSlot()
{
  DDRD &= 0xE0;
  slot = (PIND)>>5;
  printf("Slot: %d\n", slot);
}

void SetupSpi()
{
    SPCR = 0xC0;
    EICRA |= 0x03;
    EIMSK |= 0x01;

    //get slot
    getSlot();
}

volatile char addr;
volatile char state = -1;

ISR(SPI_STC_vect) {
  cli();  
  char c = SPDR;
    if (state == 0x00) {
      if ((c & 0x001F) == slot) {
        DDRB |= _BV(DDB4);
        if (c & 0xE0) {
          state = 0x03; // go to wait address write
        } else {
          state = 0x02; // go to wait address read
        }
      }
      else{
        state = 0xAB;
      }
    } else if (state == 0x02) {
      addr = c;
      state = 0x04;
      SPDR = iobuffer[addr++];
    } else if (state == 0x03) {
      addr = c;
      state = 0x05;
    } else if (state == 0x05) {
      iobuffer[addr++] = c;
    } else if (state == 0x04) {
      SPDR = iobuffer[addr++];
    }

    if(state == 0xAB)
    {
      SPDR = 0x00;
    }
    sei();
}

ISR(INT0_vect) {
  cli();
  //printf("state: %02x val: \n", state & 0x00FF, iobuffer[100] & 0x00FF);
  state = 0;
  DDRB &= !_BV(DDB4);
  sei();
}