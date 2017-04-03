#ifndef RELAY_H_
#define RELAY_H_

void SetupRelays();

struct RELAY_Task{
	unsigned char pin;
	unsigned char state;
	unsigned char ioValPos;
} r0, r1, r2, r3, r4, r5;

void CreateRelayTasks();

void SetRelay(void* input);

#endif