#include <interrupt.h>
#include <umps/libumps.h>
#include <umps/arch.h>
#include "umps/cp0.h"
#include <utils.h>
#include <pandos_const.h>
#include <scheduler.h>
#include <pcb.h>
#include <ash.h>
#include <syscall.h>    

#define RECVD    5 //Terminal received a character

//Running process
extern pcb_t *running_proc;
extern int process_count;

//Processes ready to be executed
extern struct list_head ready_queue;

void z_breakpoint_interrupt(){}
void z_breakpoint_plt_handler(){}
void z_breakpoint_il_time_handler(){}
void z_breakpoint_interrupt_panic(){}
void z_breakpoint_terminal_handler(){}

//Interval timer semaphore
extern int sem_interval_timer;
extern int is_proc_waiting_for_it; //Set to 0 if interval timer is called
extern int soft_block_count;

//Terminal semaphores
extern int sem_terminal_in[8];
extern int sem_terminal_out[8];

//Used to detect which device called for an interrupt (by providing the interrupt line)
int getDeviceNumber(int line){

    unsigned int statusCode;
    int *devSemaphore = NULL;
    int devNumber = 0;

    devregarea_t *devRegs = (devregarea_t *)RAMBASEADDR;
    unsigned int bitmap = devRegs->interrupt_dev[line - 3];
    unsigned int mask = 1;

    for (int i = 0; i < N_DEV_PER_IL; i++)
    {
        if (bitmap & mask)
            return i;
        mask *= 2;
    }

    return -1;
}

void plt_handler()
{
    addToReadyQueue(running_proc);
    scheduleNext();
    return;
}

void terminal_handler(){

    z_breakpoint_terminal_handler();

    //Get device number
    int deviceNumber = getDeviceNumber(IL_TERMINAL);

    //Get the terminal address
    termreg_t *termAddr = (termreg_t *)DEV_REG_ADDR(IL_TERMINAL, deviceNumber);

    //Find the terminal device that raised the interrupt
    pcb_PTR blockedP = removeBlocked(&sem_terminal_out[deviceNumber]);

    //BlockedP could be NULL if waiting process has been killed
    if(blockedP == NULL){
        return;
    }

    soft_block_count--;

    //Restore the process into ready queue
    addToReadyQueue(blockedP);

    //Acknowledge the interrupt
    termAddr->transm_command = ACK;

    //Save return status into PCB
    blockedP->p_s.reg_v0 = 0;
    ((int*)blockedP->p_s.reg_a2)[0] = RECVD;

    if(running_proc == NULL)
        scheduleNext();
    else
        LDST(CPU_STATE);
        //LDST(&blockedP->p_s);
}

//This function is called when the interval timer interrupt occurs 
//The interval timer interrupt occurs every 100ms and is used by the process to wait for this time
void il_time_handler()
{

    LDIT(100000); // Set interval timer to 100ms
    pcb_t *p;    

    //Check whether a process is waiting for the interval timer and stuck in the wait_for_clock syscall
    while((p = removeBlocked(&sem_interval_timer)) != NULL)
    {
        addToReadyQueue(p);
        soft_block_count--;
        sem_interval_timer = 0;
    }

    is_proc_waiting_for_it = 0;

    //Dispatch next process if no ready processes are available
    if(running_proc == NULL)
        scheduleNext();
    else
        LDST(CPU_STATE);
}

void interrupt_handler(){

    //DEBUG ONLY
    z_breakpoint_interrupt();

    //Get the cause register
    int cause = CPU_CAUSE;

    //Check the cause of the interrupt
    if CAUSE_IP_GET (cause, IL_CPUTIMER){
        z_breakpoint_plt_handler();
        //Process local timer interrupt (this indicates that the time slice of the current process has expired)
        plt_handler();
    }

        
    else if CAUSE_IP_GET (cause, IL_TIMER){
        z_breakpoint_il_time_handler();
        il_time_handler();
}
    // else if CAUSE_IP_GET (cause, IL_DISK)
    //     device_handler(IL_DISK, excState);
    // else if CAUSE_IP_GET (cause, IL_FLASH)
    //     device_handler(IL_FLASH, excState);
    // else if CAUSE_IP_GET (cause, IL_ETHERNET)
    //     device_handler(IL_ETHERNET, excState);
    // else if CAUSE_IP_GET (cause, IL_PRINTER)
    //     device_handler(IL_PRINTER, excState);
    else if CAUSE_IP_GET (cause, IL_TERMINAL) // Terminal device raised an interrupt (I/O completed?)
        terminal_handler();


    else{
        //If we landed here, the interrupt is not supported
        //z_breakpoint_interrupt_panic();
        PANIC();
    }
}

//This is called when an unhandled exception occurs like a bad syscall number or a bad memory address
void pass_up_or_die(int code){

    //If no support struct is present, terminate the process
    if(running_proc->p_supportStruct == NULL){

        terminate_process(0); // 0: current process
        //Scheduler has control here
    }

    //Copy cpu state into the support struct exception state
    copyState(CPU_STATE, &running_proc->p_supportStruct->sup_exceptState[code]);

    //Load new processor state
    int stackPtr = running_proc->p_supportStruct->sup_exceptContext[code].stackPtr;
    int status = running_proc->p_supportStruct->sup_exceptContext[code].status;
    int pc = running_proc->p_supportStruct->sup_exceptContext[code].pc;

    
    LDCXT(stackPtr, status, pc);
}


