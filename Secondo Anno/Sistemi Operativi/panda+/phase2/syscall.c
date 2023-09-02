#include <utils.h>
#include <pandos_const.h>
#include <umps3/umps/libumps.h>
#include "headers/syscall.h"
#include <scheduler.h>
#include <interrupt.h>
#include <pcb.h>
#include <types.h>
#include <ash.h>
#include <ns.h>
#include <listx.h>

#define RECVD 5 // Terminal received a character

typedef unsigned int devregtr;

// PCB table (used to search for a process given its pid)
extern pcb_t pcb_table[MAXPROC];

// Running processes
extern int process_count;

// Blocked processes (waiting for a semaphore)
extern int soft_block_count;

// Processes ready to be executed
extern struct list_head ready_queue;

// Running process
extern pcb_t *running_proc;
extern int running_proc_pid;

// Interval timer semaphore
extern int sem_interval_timer;
extern int is_proc_waiting_for_it; // Set to 1 if a process is waiting for the interval timer

// Terminal semaphores
extern int sem_terminal_in[8];
extern int sem_terminal_out[8];

// DEBUG ONLY
int copied_syscall_code;
void z_breakpoint_syscall() {}
void z_breakpoint_verhogen() {}
void z_breakpoint_passeren() {}
void z_breakpoint_doio() {}
void z_breakpoint_get_cpu_time() {}
void z_breakpoint_wait_for_clock() {}
void z_breakpoint_create_process() {}
void z_breakpoint_terminate() {}
void z_breakpoint_get_process_id() {}

void syscall_handler()
{

    // DEBUG ONLY
    copied_syscall_code = REG_A0_SS;

    switch (REG_A0_SS)
    {

    case CREATEPROCESS:
        z_breakpoint_create_process();
        create_process();
        break;

    case TERMPROCESS:
        z_breakpoint_terminate();
        terminate_process(-1);
        break;

    case PASSEREN:
        passeren(NULL);
        break;

    case VERHOGEN:
        z_breakpoint_verhogen();
        verhogen(NULL);
        break;

    case DOIO:
        z_breakpoint_doio();
        do_io();
        break;

    case GETTIME:
        z_breakpoint_get_cpu_time();
        get_cpu_time();
        break;

    case CLOCKWAIT:
        z_breakpoint_wait_for_clock();
        wait_for_clock();
        break;

    case GETSUPPORTPTR:
        get_support_data();
        break;

    case GETPROCESSID:
        z_breakpoint_get_process_id();
        get_pid();
        break;

    case GETCHILDREN:
        get_children();
        break;

    default:
        pass_up_or_die(GENERALEXCEPT);
        break;
    }

    PC_INCREMENT;
    LDST(CPU_STATE);
}

void killSelfAndProgeny(pcb_PTR proc)
{
    // Iterate over the children of the current process and kill them
    pcb_PTR child;
    while ((child = removeChild(proc)) != NULL)
    {
        killSelfAndProgeny(child);
    }

    killOne(proc);
}

// Internal function used to kill a process
extern int sem_term_mut;
void killOne(pcb_PTR proc)
{

    // Remove the current process from the children of his parent (if any)
    outChild(proc);

    // Remove the process from semaphore queue
    if (proc->p_semAdd != NULL)
    {

        if (isDeviceSem(proc->p_semAdd) == false && headBlocked(proc->p_semAdd) == NULL)
        {
            *(proc->p_semAdd) = 1;
        }
    }
    // adderrbuf("Process is not blocked on semaphore\n");

    outBlocked(proc);

    // Remove the process from the ready queue (if not current process)
    if (proc != running_proc)
        removeFromReadyQueue(proc);
    process_count--;

    freePcb(proc);
}

// SYS1 VALEX
int create_process()
{
    // Collect the parameters
    state_t *statep = (state_t *)(REG_A1_SS);
    support_t *supportp = (int)(REG_A2_SS);
    nsd_t *ns = (nsd_t *)(REG_A3_SS);

    // Check for legal parameters
    if (statep == NULL)
    {
        pass_up_or_die(GENERALEXCEPT);
    }

    // Allocate a new process
    pcb_t *newProcess = allocPcb();

    // if(newProcess->p_pid == 11){
    //     adderrbuf("Process 11 allocated\n");
    // }

    if (newProcess == NULL)
    {
        // If the process is null, the allocation failed
        // set error code -1 in v0 of the caller
        CPU_STATE->reg_v0 = NOPROC;
        adderrbuf("Cannot allocate new process\n");
    }

    // Copy the state of the process
    copyState(statep, &(newProcess->p_s));

    // copy the support structure
    if (supportp == NULL)
    {
        newProcess->p_supportStruct = NULL;
    }
    else
    {
        newProcess->p_supportStruct = supportp;
    }

    // THE PID IS ALREADY SETTED BY ALLOCPCB()

    // make a child of the current process
    insertChild(running_proc, newProcess);

    // Check if need to add namespace
    if (ns != NULL)
    {
        addNamespace(newProcess, ns);
        if (getNamespace(newProcess, ns->n_type) != ns)
        {
            adderrbuf("COULD NOT ADD PROCESS TO NAMEPSACE \n");
        }
    }

    // Inherit the namespace of the parent (if any)
    else
    {
        if (newProcess->p_parent != NULL && getNamespace(newProcess->p_parent, NS_PID) != NULL)
        {
            addNamespace(newProcess, NS_PID);
        }
    }

    // Insert the new process in the ready queue
    addToReadyQueue(newProcess);
    process_count++;

    // Return the pid of the new process
    CPU_STATE->reg_v0 = newProcess->p_pid;
}

// SYS2 VALEX
int invoked_process_pid = 0;
void terminate_process(int pid)
{

    // Retrieve the pid of the process to kill (from registry or from function param)
    if (pid == -1)
        pid = (int)(REG_A1_SS);

    // Calling process requested to kill itself and all his progeny
    if (pid == 0 || (running_proc != NULL && pid == running_proc->p_pid))
    {

        killSelfAndProgeny(running_proc);
        // killOne(running_proc);
        running_proc = NULL;
        scheduleNext();
    }
    else
    {

        // Search in pcb table process with the given pid
        pcb_t *process = NULL;
        int i;
        for (i = 0; i < MAXPROC; i++)
        {
            if (pcb_table[i].p_pid == pid)
            {
                invoked_process_pid = pid;
                process = &pcb_table[i];
                killSelfAndProgeny(process);
                running_proc = NULL;
                scheduleNext();
            }
        }
    }
}

// SYS3 MURK
void passeren(int *sem)
{

    z_breakpoint_passeren();

    // Retrieve the semaphore (from syscall param or from function param)
    if (sem == NULL)
        sem = (int *)(REG_A1_SS);

    // Check if the semaphore is valid
    if (sem == NULL)
    {
        adderrbuf("Invalid semaphore pointer\n");
        return;
    }

    // Check if need to block the process
    if (*sem == 0)
    {
        // Increment the soft block counter
        soft_block_count++;

        // Insert the process in the semaphore queue
        int result = insertBlocked(sem, running_proc);
        if (result == 1)
        {
            adderrbuf("Cannot insert process in semaphore queue\n");
        }

        // Schedule the next process
        PC_INCREMENT; // NEED TO DO MANUALLY AS NOT DONE AT END OF SYSCALL HANDLER
        scheduleNext();
    }
    else if (*sem > 0) // Sem is more than 0
    {
        // Check if there is a process to unblock (when the semaphore is more than 0 there should be no blocked processes)
        // But a process could have been blocked by a verhogen() call when the semaphore was 1
        pcb_t *unblocked = removeBlocked(sem);
        if (unblocked != NULL)
        {

            // Decrement the soft block counter
            soft_block_count--;

            // Insert the process in the ready queue
            addToReadyQueue(unblocked);

            // Schedule the next process
            // PC_INCREMENT;  //NEED TO DO MANUALLY AS NOT DONE AT END OF SYSCALL HANDLER
            // scheduleNext();
        }

        // Decrement the semaphore
        (*sem)--;
    }
    else
    {
        adderrbuf("Invalid semaphore value\n");
    }

    // TODO
}

// SYS4 MURK
void verhogen(int *sem)
{

    // Retrieve the semaphore (from syscall param or from function param)
    if (sem == NULL)
        sem = (int *)(REG_A1_SS);

    // Check if the semaphore is valid
    if (sem == NULL)
    {
        adderrbuf("Invalid semaphore pointer\n");
        return;
    }

    // Check if process is blocked on this semaphore
    pcb_PTR blocked = headBlocked(sem);

    // Check if the semaphore is already at its maximum value
    if (*sem == 1)
    {
        soft_block_count++;
        insertBlocked(sem, running_proc);
        PC_INCREMENT; // NEED TO DO MANUALLY AS NOT DONE AT END OF SYSCALL HANDLER
        scheduleNext();
        return;
    }

    // Semaphore indicates no resource is available
    if (*sem <= 0)
    {

        // Check if there are blocked process on this semaphore
        if (blocked != NULL)
        {
            removeBlocked(sem);

            // Insert the process in the ready queue
            addToReadyQueue(blocked);
            soft_block_count--;
        }
        else
        {

            // Increment the semaphore if no other processes are waiting
            (*sem)++;
        }
    }
}

// SYS5 MURK
int iosem = 0;
int do_io()
{

    // Take the parameters
    int *cmdAddr = (devregtr *)(REG_A1_SS);

    // This is an array of 2 integers, the value of the command is placed inside the first one
    devregtr *value = (devregtr *)(REG_A2_SS);

    // Take the device RAM area
    // devregarea_t *deviceRegs = (devregarea_t *)RAMBASEADDR;

    // Detect if terminal device (by checking the address range of the command)
    devregtr *base = (devregtr *)TERM0ADDR;
    if ((int)cmdAddr <= LAST_TERM_ADDR && (int)cmdAddr >= TERM0ADDR) // Targeting a terminal device
    {
        // Get terminal index (0-7)
        int offset = (devregtr *)cmdAddr - base;
        int termIndex = offset / DEVREGSIZE;
        if (termIndex != 0)
            adderrbuf("Terminal index is not 0\n");

        // Round to nearest terminal index (per difetto)
        cmdAddr = TERM0ADDR + termIndex * DEVREGSIZE;

        // This offset is copied from addokbuf function provided by tests
        memaddr *commandp = (devregtr *)((int)cmdAddr + (TRANCOMMAND * DEVREGLEN));

        // Execute command
        // setSTATUS(getSTATUS() & DISABLEINTS);
        *commandp = value[0] != 0 ? value[0] : value[1];

        // For now only output works, later detect how to handle input
        passeren(&sem_terminal_out[termIndex]);
    }
}

// SYS6 MURK
int get_cpu_time()
{
    CPU_STATE->reg_v0 = getRunningProcTime();
}

void wait_for_clock()
{
    is_proc_waiting_for_it = 1;
    passeren(&sem_interval_timer);
}

// SYS8 VALEX
void get_support_data()
{
    if (running_proc->p_supportStruct == NULL)
    {
        CPU_STATE->reg_v0 = NULL;
    }
    else
    {
        CPU_STATE->reg_v0 = running_proc->p_supportStruct;
    }
}

// SYS9 MURK
void get_pid()
{

    // Get the parameter (parent or current process)
    int parent = (int)(REG_A1_SS);

    if (parent == true)
    {

        // Check if both processes are in the default namespace
        if (isInDefaultNamespace(running_proc) == true && isInDefaultNamespace(running_proc->p_parent) == true)
            CPU_STATE->reg_v0 = (unsigned int)running_proc->p_parent->p_pid;

        // Check if both in PID namespace
        else if (getNamespace(running_proc, NS_PID) != NULL && getNamespace(running_proc->p_parent, NS_PID) != NULL)
            CPU_STATE->reg_v0 = (unsigned int)running_proc->p_parent->p_pid;

        // They are in different namepsaces
        //   From slides:
        //   "Se il parent non e’ nello stesso PID namespace del processo
        //   figlio, questa funzione ritorna 0 (se richiesto il pid del padre)!"
        else
            CPU_STATE->reg_v0 = 0;
    }
    else
    {
        CPU_STATE->reg_v0 = (unsigned int)running_proc->p_pid;
    }
}

// SYS10 VALEX
void get_children()
{
    // Get the parameters
    int *pids = (int *)(REG_A1_SS);
    int size = (int)(REG_A2_SS);

    // Check if the parameters are valid
    if (pids == NULL || size <= 0)
    {
        CPU_STATE->reg_v0 = getChildrenCount(running_proc, NULL, NULL);
        return;
    }

    // Return the number of children and fill the children array
    CPU_STATE->reg_v0 = getChildrenCount(running_proc, running_proc->namespaces[0], pids);
}