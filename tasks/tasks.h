/*
 * tasks.h
 *
 *  Created on: Mar 4, 2017
 *      Author: jacob
 */

#ifndef TASKS_H_
#define TASKS_H_

#define true 1
#define false 0

struct TASK{
    unsigned int runTime;
    unsigned int currentTime;
    void (*taskFunc)(void*);
    volatile char needsToRun;
    void* params;
};

struct TASK tasks[10];

void AddTask(unsigned int, void*, void(*)(void*));

void RunExpiredTasks();

#endif
