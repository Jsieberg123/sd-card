#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "digital.h"
#include "options.h"
#include "tasks.h"
#include <stdio.h>

void SetupDigital()
{
    DDRD &= 0x0F;
	printf("\nDigital setup!\n");
}

void ReadDigital(void* param)
{
    struct Digital_Task digital = *(struct Digital_Task*)param;
    printf("%d\n", PIND);
    if(PIND & digital.mask)
    {
        iobuffer[digital.loc] = 0x7F;
    }
    else{
        iobuffer[digital.loc] = 0x00;
    }
}

void CreateDigitalReadTasks(){
    pd4.mask = _BV(PORTD4);
    pd4.loc = 34;
    AddTask(100, &pd4, ReadDigital);

    pd3.mask = _BV(PORTD3);
    pd3.loc = 40;
    AddTask(100, &pd3, ReadDigital);
}