#include <avr/io.h>
#include <avr/interrupt.h>

#include "tasks.h"
#include <stdio.h>

unsigned int NumberOfTasks = 0;

ISR(TIMER1_COMPA_vect)
{
    for(int i=0;i<NumberOfTasks;i++)
    {
        tasks[i].currentTime++;
        if(tasks[i].currentTime == tasks[i].runTime)
        {
            tasks[i].needsToRun = true;
            tasks[i].currentTime = 0;
        }
    }
}

void AddTask(unsigned int runTime, void* params, void(*callback)(void*))
{
    tasks[NumberOfTasks].runTime = runTime;
    tasks[NumberOfTasks].currentTime = 0;
    tasks[NumberOfTasks].needsToRun = false;
    tasks[NumberOfTasks].params = params;
    tasks[NumberOfTasks].taskFunc = callback;    
    NumberOfTasks++;
}

void RunExpiredTasks()
{
    for(int i=0;i<NumberOfTasks;i++)
    {
        if(tasks[i].needsToRun)
        {
            (*tasks[i].taskFunc)(tasks[i].params);
            tasks[i].needsToRun = false;
        }
    }
}