#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "adc.h"
#include "options.h"
#include <stdio.h>

unsigned int ReadADC(char ADCchannel);

void SetupAdc()
{
    // Select Vref=AVcc
    ADMUX |= (1 << REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
	printf("ADC setup!\n");
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