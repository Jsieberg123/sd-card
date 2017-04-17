// /*
//  * main.c
//  *
//  *  Created on: Mar 4, 2017
//  *      Author: jacob
//  */

#define true 1
#define false 0

#define F_CPU 8000000UL

#include "options.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "spi.h"
#include "uart.h"
#include "adc.h"
#include "tasks.h"
#include "relay.h"
#include "carddefs.h"

//-----------------------------------------------------------

void ToggleLed(void*);
void GetAdcValue(void* param);

int main()
{
    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;

    printf("\nApp Starting!\n");

    DDRD |= _BV(DDD7);

    OCR1A = 800;
    TCCR1B = 0x09;
    TIMSK1 |= (1 << OCIE1A);    

    iobuffer[0] = CARD_TYPE;
    *((unsigned int *) &iobuffer[1]) = CARD_ID;

    SetupSpi();
    sei();

    AddTask(2500, NULL, ToggleLed);

    #if CARD_TYPE == CARD_TYPE_CURRENT
    SetupAdc();    
    CreateAdcTasks();
    #endif

    #if CARD_TYPE == CARD_TYPE_VOLTAGE
    SetupAdc();    
    CreateAdcTasks();
    #endif

    #if CARD_TYPE == CARD_TYPE_RELAY
    SetupRelays();
    CreateRelayTasks();
    #endif

    while (true){
        RunExpiredTasks();
    }

    return 0;
}

char StatusLed = false;

void ToggleLed(void* unused)
{
    printf(".");
}