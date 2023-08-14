#include <interrupt.h>
#include <umps/libumps.h>
#include <umps/arch.h>
#include "umps/cp0.h"
#include <utils.h>
#include <pandos_const.h>
#include <scheduler.h>
#include <pcb.h>

//Running process
extern pcb_t *running_proc;

//Processes ready to be executed
extern struct list_head ready_queue;

void z_breakpoint_interrupt(){}
void z_breakpoint_plt_handler(){}
void z_breakpoint_intervall_timer_handler(){}
void z_breakpoint_interrupt_panic(){}


void plt_handler()
{
    //setTIMER(-2); // ACK (WTF?)
    addToReadyQueue(running_proc);
    scheduleNext();
}

void interrupt_handler(){

    //DEBUG ONLY
    z_breakpoint_interrupt();

    //Get the cause register
    int cause = CPU_CAUSE;

    //Check the cause of the interrupt
    if CAUSE_IP_GET (cause, IL_CPUTIMER)

        z_breakpoint_plt_handler();

        //Process local timer interrupt (this indicates that the time slice of the current process has expired)
        plt_handler();
    //else if CAUSE_IP_GET (cause, IL_TIMER)
    //     intervall_timer_handler(excState);
    // else if CAUSE_IP_GET (cause, IL_DISK)
    //     device_handler(IL_DISK, excState);
    // else if CAUSE_IP_GET (cause, IL_FLASH)
    //     device_handler(IL_FLASH, excState);
    // else if CAUSE_IP_GET (cause, IL_ETHERNET)
    //     device_handler(IL_ETHERNET, excState);
    // else if CAUSE_IP_GET (cause, IL_PRINTER)
    //     device_handler(IL_PRINTER, excState);
    // else if CAUSE_IP_GET (cause, IL_TERMINAL)
    //     device_handler(IL_TERMINAL, excState);


    //If we landed here, the interrupt is not supported
    z_breakpoint_interrupt_panic();
    PANIC();


    
}


