#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "relay.h"
#include "options.h"
#include "tasks.h"
#include <stdio.h>

void SetupRelays(){
	DDRC |= _BV(DDC5) + _BV(DDC4) +_BV(DDC3) +_BV(DDC2) +_BV(DDC1) +_BV(DDC0);
	printf("Relays Setup!\n");
}

void CreateRelayTasks()
{
	r0.pin = _BV(PORTC0);
	r0.state = false;
	r0.ioValPos = 10;
	AddTask(100000UI, &r0, SetRelay);

	r1.pin = _BV(PORTC1);
	r1.state = false;
	r1.ioValPos = 11;	
	AddTask(100000UI, &r1, SetRelay);

	r2.pin = _BV(PORTC2);
	r2.state = false;
	r2.ioValPos = 12;	
	AddTask(100000UI, &r2, SetRelay);

	r3.pin = _BV(PORTC3);
	r3.ioValPos = 13;
	r3.state = false;
	AddTask(100000UI, &r3, SetRelay);

	r4.pin = _BV(PORTC4);
	r4.ioValPos = 14;
	r4.state = false;
	AddTask(100000UI, &r4, SetRelay);

	r5.pin = _BV(PORTC5);
	r5.ioValPos = 15;
	r5.state = false;
	AddTask(100000UI, &r5, SetRelay);
}

void SetRelay(void* input)
{
	struct RELAY_Task relayNum = *(struct RELAY_Task*)input;
	if(iobuffer[relayNum.ioValPos])
	{
		relayNum.state = true;
		iobuffer[relayNum.ioValPos] = false;
		PORTC |= relayNum.pin;
	}

	if(relayNum.state)
	{
		relayNum.state = false;
		PORTC &= ~relayNum.pin;
	}
}