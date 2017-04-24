#ifndef DIGITAL_H_
#define DIGITAL_H_

void SetupDigital();

void ReadDigital(void*);

struct Digital_Task{
    unsigned char mask;
	unsigned char loc;
} pd4, pd3;

void CreateDigitalReadTasks();

#endif