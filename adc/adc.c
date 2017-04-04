#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "adc.h"
#include "options.h"
#include "tasks.h"
#include <stdio.h>

unsigned int ReadADC(char ADCchannel);

void SetupAdc()
{
    // Select Vref=AVcc
    ADMUX |= (1 << REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
	printf("\nADC setup!\n");
}

unsigned int ReadADC(char ADCchannel)
{
    //select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    //single conversion mode
	ADCSRA |= (1 << ADSC);
    //wait until ADC conversion is complete while (ADCSRA & (1 << ADSC));
    return ADC;
}

void GetAdcValue(void* param)
{
    struct ADC_Task adcNum = *(struct ADC_Task*)param;
    int value = ReadADC(adcNum.channel);
    //printf("%d\n", adcNum.n1);        

    if(adcNum.n1 >= adcNum.n2 && adcNum.n1 >= value)
    {
        //maximum
       *((int *) &iobuffer[adcNum.maxValLoc]) = adcNum.n1;
    }

    if(adcNum.n1 <= adcNum.n2 && adcNum.n1 <= value)
    {
        //minimum
        iobuffer[adcNum.minValLoc] = adcNum.n1;
    }
    iobuffer[adcNum.ppValLoc] = *((int *) &iobuffer[adcNum.maxValLoc]) - *((int *) &iobuffer[adcNum.minValLoc]);
    (*(struct ADC_Task*)param).n2 = adcNum.n1;
    (*(struct ADC_Task*)param).n1 = value;
}

void CreateAdcTasks(){
    adc0.channel = 0;
    adc0.n1 = 0;
    adc0.n2 = 0;
    adc0.maxValLoc = 10;
    adc0.minValLoc = 12;
    adc0.ppValLoc = 14;
    AddTask(10, &adc0, GetAdcValue);

    adc1.channel = 1;
    adc1.n1 = 0;
    adc1.n2 = 0;
    adc1.maxValLoc = 16;
    adc1.minValLoc = 18;
    adc1.ppValLoc = 20;
    AddTask(10, &adc1, GetAdcValue);

    adc2.channel = 2;
    adc2.n1 = 0;
    adc2.n2 = 0;
    adc2.maxValLoc = 22;
    adc2.minValLoc = 24;
    adc2.ppValLoc = 26;
    AddTask(10, &adc2, GetAdcValue);

    adc3.channel = 3;
    adc3.n1 = 0;
    adc3.n2 = 0;
    adc3.maxValLoc = 28;
    adc3.minValLoc = 30;
    adc3.ppValLoc = 32;
    AddTask(10, &adc3, GetAdcValue);

    adc4.channel = 4;
    adc4.n1 = 0;
    adc4.n2 = 0;
    adc4.maxValLoc = 34;
    adc4.minValLoc = 36;
    adc4.ppValLoc = 38;
    AddTask(10, &adc4, GetAdcValue);

    adc5.channel = 0;
    adc5.n1 = 0;
    adc5.n2 = 0;
    adc5.maxValLoc = 40;
    adc5.minValLoc = 42;
    adc5.ppValLoc = 44;
    AddTask(10, &adc5, GetAdcValue);
}