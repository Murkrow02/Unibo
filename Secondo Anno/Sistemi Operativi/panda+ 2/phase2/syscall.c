#include <utils.h>
#include <pandos_const.h>
#include <umps3/umps/libumps.h>
#include "headers/syscall.h"
#include <scheduler.h>
#include <pcb.h>
#include <types.h>
#include <ash.h>

//Running processes
extern int process_count;

//Blocked processes (waiting for a semaphore)
extern int soft_block_count;

//Processes ready to be executed
extern struct list_head ready_queue;

//Running process
extern pcb_t *running_proc;

//DEBUG ONLY
int copied_syscall_code;
void z_breakpoint_syscall() {}
void z_breakpoint_verhogen() {}
void z_breakpoint_passeren() {}
void z_breakpoint_doio() {}
void z_breakpoint_create_process() {}

void syscall_handler() {

    //DEBUG ONLY
    copied_syscall_code = REG_A0_SS;
    z_breakpoint_syscall();


    switch (REG_A0_SS) {

        case CREATEPROCESS:
            z_breakpoint_create_process();
            create_process();
            break;

        case PASSEREN:
            z_breakpoint_passeren();
            passeren();
            break;
        case VERHOGEN:
            z_breakpoint_verhogen();
            verhogen();
            break;

        case DOIO:
            z_breakpoint_doio();
            do_io();
            break;
        default:
            PANIC();
            break;
    }
}


///SYS1 VALEX
/// <summary>
/// Creates a new process\n
/// In order to call this function some operations must be done from the calling process:\n
/// set the register a0 to 1
/// set a pointer to the processor state in a1
/// set a pointer to the support structure in a2
/// set a pointer to the PID namespace of the new process in a3
/// THEN YOU CAN CALL SYSCALL
/// \param statep Pointer to the processor state
/// \param supportp Pointer to the support structure
/// \param ns Pointer to the namespace?
/// </summary>
void create_process()
{
    //Collect the parameters
    state_t *statep = (state_t *)(REG_A1_SS);
    support_t *supportp = (int)(REG_A2_SS);
    struct nsd_t *ns = (support_t *)(REG_A3_SS);

    // Allocate a new process
    pcb_t *newProcess = allocPcb();

    if (newProcess == NULL)
    {
        //If the process is null, the allocation failed
        //set error code -1 in v0 of the caller
        CPU_STATE->reg_v0 = NOPROC;
        return;
    }

    // Copy the state of the process
    copyState(statep, &(newProcess->p_s));

    //copy the support structure
    if (supportp == NULL) {
        newProcess->p_supportStruct = NULL;
    } else {
        newProcess->p_supportStruct = supportp;
    }

    //THE PID IS ALREADY SETTED BY ALLOCPCB()

    //make a child of the current process
    insertChild(running_proc, newProcess);

    //Insert the new process in the ready queue
    addToReadyQueue(newProcess);
    process_count++;


    // Return the pid of the new process
    CPU_STATE->reg_v0 = newProcess->p_pid;
}

///SYS3 MURK
void passeren() {

    //Retrieve the semaphore
    int *sem = (int *)(REG_A1_SS);

    //Check if the semaphore is valid
    if (sem == NULL)
    {
        adderrbuf("Invalid semaphore pointer\n");
        return;
    }

    //Check if need to block the process
    if (*sem <= 0)
    {
        //Insert the process in the semaphore queue
        insertBlocked(sem, running_proc);

        //Increment the soft block counter
        soft_block_count++;

        //Schedule the next process
        scheduleNext();
    }
    else
    {
        //Decrement the semaphore
        (*sem)--;
    }

    //TODO
}

///SYS4 MURK
void verhogen() {

    //Retrieve the semaphore
    int *sem = (int *)(REG_A1_SS);

    //Check if the semaphore is valid
    if (sem == NULL)
    {
        adderrbuf("Invalid semaphore pointer\n");
        return;
    }

    //Check if the semaphore is already at its maximum value
    if (*sem == 1)
    {
        addToReadyQueue(running_proc);
        scheduleNext();
        return;
    }

    //Check if there are blocked processes
    if (*sem <= 0)
    {
        //Remove the first process from the semaphore queue
        pcb_t *unblocked = removeBlocked(sem);

        //Decrement the soft block counter
        soft_block_count--;

        //Insert the process in the ready queue
        insertProcQ(&(ready_queue), unblocked);
    }

    //Increment the semaphore
    (*sem)++;
}


///SYS5 MURK
void do_io() {

    //VEDI PERCHE PORCODIO VA NEL REGISTRO 1 INVECE CHE 2
     (*CPU_STATE).reg_v0 = (unsigned int) 23;
    z_breakpoint_doio();
}

//SYS8 should be called before calling SYS1 to get the support structure
void get_support_data() {
    //TODO
}