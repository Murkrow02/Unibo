#include "syscall.h"
#include <pandos_types.h>
#include <umps3/umps/arch.h>
#include <umps3/umps/cp0.h>
#include <scheduler.h>
#include <pcb.h>
#include <types.h>

int semTerminalDeviceReading[8];
int semTerminalDeviceWriting[8];

void do_IO_device(state_t *excState)
{
    int *cmdAddr = (int *)(*excState).reg_a1;
    int cmdValue = (int)(*excState).reg_a2;

    int *devSemaphore = NULL; // Semaphore address
    devregarea_t *deviceRegs = (devregarea_t *)RAMBASEADDR;

    /* Searching which device is running looking first for terminal then for generic devices */
    for (int i = 0; i < 8; i++)
    {
        if (&(deviceRegs->devreg[4][i].term.transm_command) == (memaddr *)cmdAddr)
        { // Terminal Devices Writing
            devSemaphore = &semTerminalDeviceWriting[i];
            break;
        }
        else if (&(deviceRegs->devreg[4][i].term.recv_command) == (memaddr *)cmdAddr)
        { // Terminal Devices Reading
            devSemaphore = &semTerminalDeviceReading[i];
            break;
        }
    }
    
    *cmdAddr = cmdValue;         // Execute request command
    //P(devSemaphore, excState);   // Call a P on the semaphore found, should be blocking
    //load_or_scheduler(excState); // Just in case
}

//TODO move to helpers
//Copies the state of a process to another
void copy_state(state_t *original, state_t *dest)
{
    dest->entry_hi = original->entry_hi;
    dest->cause = original->cause;
    dest->status = original->status;
    dest->pc_epc = original->pc_epc;
    dest->hi = original->hi;
    dest->lo = original->lo;
    for (int i = 0; i < STATE_GPR_LEN; i++)
    {
        dest->gpr[i] = original->gpr[i];
    }
}

///SYS1
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
void create_process(state_t *statep, support_t *supportp, struct nsd_t *ns)
{
    // Allocate a new process
    pcb_t *newProcess = allocPcb();

    if (newProcess == NULL)
    {
        //If the process is null, the allocation failed
        //set error code -1 in v0 of the caller
        (*statep).reg_v0 = NOPROC;
        return;
    }

    // Copy the state of the process
    copy_state(statep, &(newProcess->p_s));

    //copy the support structure
    if (supportp == NULL) {
        newProcess->p_supportStruct = NULL
    } else {
        newProcess->p_supportStruct = supportp;
    }

    //THE PID IS ALREADY SETTED BY ALLOCPCB()

    //make a child of the current process
    insertChild(running_proc, newProcess);

    // Insert the process in the ready queue
    insertProcQ(&(readyQueue), newProcess);

    // Increment the number of active processes
    processCount++;

    // Return the pid of the new process
    (*statep).reg_v0 = newProcess->p_pid;
}

//SYS8 should be called before calling SYS1 to get the support structure
void get_support_data() {
    //TODO
}