#include <utils.h>
#include <pandos_const.h>
#include <umps3/umps/libumps.h>
#include "headers/syscall.h"
#include <scheduler.h>
#include <pcb.h>
#include <types.h>

//Running processes
extern int process_count;

//Blocked processes (waiting for a semaphore)
extern int soft_block_count;

//Processes ready to be executed
extern struct list_head ready_queue;

//Running process
extern pcb_t *running_proc;

void syscall_handler(unsigned int syscall_code) {
    switch (syscall_code) {
        case CREATEPROCESS:
            create_process((state_t *)(REG_A1_SS), (int)(REG_A2_SS), (support_t *)(REG_A3_SS));
            break;
        default:
            PANIC();
            break;
    }
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
        newProcess->p_supportStruct = NULL;
    } else {
        newProcess->p_supportStruct = supportp;
    }

    //THE PID IS ALREADY SETTED BY ALLOCPCB()

    //make a child of the current process
    insertChild(running_proc, newProcess);

    // Insert the process in the ready queue
    insertProcQ(&(ready_queue), newProcess);

    // Increment the number of active processes
    process_count++;

    // Return the pid of the new process
    (*statep).reg_v0 = newProcess->p_pid;
}

//SYS8 should be called before calling SYS1 to get the support structure
void get_support_data() {
    //TODO
}