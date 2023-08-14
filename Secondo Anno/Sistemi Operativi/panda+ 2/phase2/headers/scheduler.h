#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include <pandos_types.h>

void scheduleNext();


void initScheduler();

//Easy way to append a process to the ready queue
void addToReadyQueue(pcb_PTR proc);

//Easy way to block process by saving its state and inserting it back into the ready queue
void blockRunningAndScheduleNext();

//Increment the program counter of the running process
void incrementProgramCounter();

#endif