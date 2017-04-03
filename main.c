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
#include "carddefs.h"

//-----------------------------------------------------------

void ToggleLed(void*);
void GetAdcValue(void* param);

int main()
{
    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;

    printf("App Starting!\n");

    DDRD |= _BV(DDD7);

    OCR1A = 8000;
    TCCR1B = 0x09;
    TIMSK1 |= (1 << OCIE1A);    

    iobuffer[0] = CARD_TYPE;

    SetupSpi();

    SetupAdc();

    sei();

    AddTask(1000, NULL, ToggleLed);
    int adc0 = 0;
    AddTask(1000, &adc0, GetAdcValue);

    while (true){
        RunExpiredTasks();
    }

    return 0;
}

char StatusLed = false;

void ToggleLed(void* unused)
{
    if (StatusLed)
    {
        PORTD |= _BV(PORTD7);
        printf("ON\n");
        StatusLed = false;
    }
    else
    {
        PORTD &= ~_BV(PORTD7);
        printf("OFF\n");
        StatusLed = true;
    }
}

void GetAdcValue(void* param)
{
    int adcNum = *(int*)param;
    int value = ReadADC(adcNum);
}