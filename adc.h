#ifndef ADC_H_
#define ADC_H_

void SetupAdc();

void ReadAdcTask(void *pvParameters);

void CreateReadAdcTask(char pin, char resultAddr, unsigned int time);

struct AdcTaskInput{
	char pin;
	char resultAddr;
	unsigned int time;
};

#endif