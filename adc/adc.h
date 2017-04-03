#ifndef ADC_H_
#define ADC_H_

void SetupAdc();

unsigned int ReadADC(char ADCchannel);

struct ADC_Task{
    unsigned char channel;
    unsigned int n1;
    unsigned int n2;
	unsigned char minValLoc;
	unsigned char maxValLoc;
	unsigned char ppValLoc;
} adc0, adc1, adc2, adc3, adc4, adc5;

void GetAdcValue(void*);

void CreateAdcTasks();

#endif