#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include <pandos_types.h>

void scheduleNext();


void initScheduler();

//Easy way to append a process to the ready queue
void addToReadyQueue(pcb_PTR proc);

//Easy way to remove a process from the ready queue
void removeFromReadyQueue(pcb_PTR proc);

//Easy way to block process by saving its state and inserting it back into the ready queue
void blockRunningAndScheduleNext();

//Increment the program counter of the running process
void incrementProgramCounter();

//Returns the running time in cpu_t of the running process
cpu_t getRunningProcTime();

#endif