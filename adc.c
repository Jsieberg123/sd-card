#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "adc.h"
#include "options.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

unsigned int ReadADC(char ADCchannel);

SemaphoreHandle_t mut;

void SetupAdc()
{	
	mut = xSemaphoreCreateMutex();
	// Select Vref=AVcc
 	ADMUX |= (1<<REFS0);
 	//set prescaller to 128 and enable ADC 
 	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

void ReadAdcTask(void *pvParameters)
{
	struct AdcTaskInput settings = *((struct AdcTaskInput*)pvParameters);

	for(;;)
	{
		unsigned int value = ReadADC(settings.pin);
		iobuffer[settings.resultAddr] = value;
		vTaskDelay(settings.time);
	}
}

unsigned int ReadADC(char ADCchannel)
{
 xSemaphoreTake(mut, portMAX_DELAY);
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 xSemaphoreGive(mut);
 return ADC;
}

void CreateReadAdcTask(char pin, char resultAddr, unsigned int time)
{
	struct AdcTaskInput readInfo;
  	readInfo.pin = pin;
  	readInfo.resultAddr = resultAddr;
  	readInfo.time = time;
  	xTaskCreate(ReadAdcTask, (const portCHAR *)"Read Current Phase 1", 50, (void*)&readInfo, 2, NULL);
}