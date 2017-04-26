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
    // Select Vref=ARef
    ADMUX = 0;
    //set prescaller to 1 and enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
	printf("\nADC setup!\n");
}

unsigned int ReadADC(char ADCchannel)
{
    //select ADC channel with safety mask
	ADMUX = ADCchannel;
    //single conversion mode
	ADCSRA |= (1 << ADSC);
    //wait until ADC conversion is complete while (ADCSRA & (1 << ADSC));
    while(ADCSRA & (1 << ADSC));
    return ADC;
}

void GetAdcValue(void* param)
{
    //Cast intput as adc_task
    struct ADC_Task *adcTask = (struct ADC_Task*)param;

    //read adc value
    int value = ReadADC((*adcTask).channel);
    
    //Save the latest value in the next position in the buffer
    (*adcTask).pos = ((*adcTask).pos + 1) % 100;
    (*adcTask).oldVals[(*adcTask).pos] = value;

    //Search for the max and min values from last 100 results.
    int minVal = 1024;
    int maxVal = 0;
    for(int i=0;i<100;i++)
    {
        if((*adcTask).oldVals[i] > maxVal)
        {
            maxVal = (*adcTask).oldVals[i];
        }
        if((*adcTask).oldVals[i] < minVal)
        {
            minVal = (*adcTask).oldVals[i];
        }
    }

    //Output results to the iobuffer.
    *((int *) &iobuffer[(*adcTask).maxValLoc]) = maxVal;
    *((int *) &iobuffer[(*adcTask).minValLoc]) = minVal;
    *((int *) &iobuffer[(*adcTask).ppValLoc]) = maxVal - minVal;
}

void CreateAdcTasks(){
    adc0.channel = 0;
    adc0.maxValLoc = 10;
    adc0.minValLoc = 12;
    adc0.ppValLoc = 14;
    AddTask(10, &adc0, GetAdcValue);

    adc1.channel = 1;
    adc1.maxValLoc = 16;
    adc1.minValLoc = 18;
    adc1.ppValLoc = 20;
    AddTask(10, &adc1, GetAdcValue);

    adc2.channel = 2;
    adc2.maxValLoc = 22;
    adc2.minValLoc = 24;
    adc2.ppValLoc = 26;
    AddTask(10, &adc2, GetAdcValue);

    adc3.channel = 3;
    adc3.maxValLoc = 28;
    adc3.minValLoc = 30;
    adc3.ppValLoc = 32;
    AddTask(10, &adc3, GetAdcValue);

    adc4.channel = 4;
    adc4.maxValLoc = 34;
    adc4.minValLoc = 36;
    adc4.ppValLoc = 38;
    AddTask(10, &adc4, GetAdcValue);

    adc5.channel = 5;
    adc5.maxValLoc = 40;
    adc5.minValLoc = 42;
    adc5.ppValLoc = 44;
    AddTask(10, &adc5, GetAdcValue);
}