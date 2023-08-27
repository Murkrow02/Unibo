#include <utils.h>
#include <pandos_const.h>
#include <umps3/umps/libumps.h>
#include "headers/syscall.h"
#include <scheduler.h>
#include <interrupt.h>
#include <pcb.h>
#include <types.h>
#include <ash.h>

#define RECVD    5 //Terminal received a character

typedef unsigned int devregtr;

//PCB table (used to search for a process given its pid)
extern pcb_t pcb_table[MAXPROC];

//Running processes
extern int process_count;

//Blocked processes (waiting for a semaphore)
extern int soft_block_count;

//Processes ready to be executed
extern struct list_head ready_queue;

//Running process
extern pcb_t *running_proc;
extern int running_proc_pid;

//Interval timer semaphore
extern int sem_interval_timer;
extern int is_proc_waiting_for_it; //Set to 1 if a process is waiting for the interval timer

//Terminal semaphores
extern int sem_terminal_in[8];
extern int sem_terminal_out[8];

//DEBUG ONLY
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

void syscall_handler() {


    //DEBUG ONLY
    copied_syscall_code = REG_A0_SS;


    switch (REG_A0_SS) {

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
            verhogen();
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

        case GETPROCESSID:
            z_breakpoint_get_process_id();
            get_pid();
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
     
    //Iterate over the children of the current process and kill them
    pcb_PTR child;
    while (child = removeChild(proc) != NULL)
    {
        
        killOne(child);
    }

    killOne(proc);
}

//Internal function used to kill a process
void killOne(pcb_PTR proc){


    //Remove the current process from the children of his parent (if any)
    //outChild(proc); //TODO:


    //TODO: remove the process from the semaphore queue (if any)


    //Remove the process from semaphore queue
    outBlocked(proc);

    //Remove the process from the ready queue (if not current process)
    if(proc != running_proc)
        removeFromReadyQueue(proc);
    process_count--;

    //initializePcb(proc);
}



//SYS1 VALEX
int create_process()
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
        adderrbuf("Cannot allocate new process\n");
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


//SYS2 VALEX
void terminate_process(int pid) {

    //Retrieve the pid of the process to kill (from registry or from function param)
    if(pid == -1)
        pid = (int)(REG_A1_SS);
  

    //Calling process requested to kill itself and all his progeny
    if (pid == 0 || (running_proc != NULL && pid == running_proc->p_pid)) {

        killSelfAndProgeny(running_proc);
        running_proc = NULL;
        scheduleNext();

    } else {


        //Search in pcb table process with the given pid
        pcb_t *process = NULL;
        int i;
        for (i = 0; i < MAXPROC; i++) {
            if (pcb_table[i].p_pid == pid) {
                process = &pcb_table[i];
                killSelfAndProgeny(process);
                break;
            }
        }
    }
}

//Debug 
int blocked_on_terminal = 0;
extern int sem_term_mut;

//SYS3 MURK
void passeren(int *sem) {

    

    z_breakpoint_passeren();

    //Retrieve the semaphore (from syscall param or from function param)
    if(sem == NULL)
        sem = (int *)(REG_A1_SS);


    //Check if the semaphore is valid
    if (sem == NULL)
    {
        adderrbuf("Invalid semaphore pointer\n");
        return;
    }

    //Check if need to block the process
    if (*sem <= 0)
    {

        //Increment the soft block counter
        soft_block_count++;

        //Insert the process in the semaphore queue
        int result = insertBlocked(sem, running_proc);
        if(result == TRUE){
            adderrbuf("Cannot insert process in semaphore queue\n");
        }

        //Schedule the next process
        PC_INCREMENT; //NEED TO DO MANUALLY AS NOT DONE AT END OF SYSCALL HANDLER
        scheduleNext();
    }
    else //Sem is more than 0
    {


        //Check if there is a process to unblock (when the semaphore is more than 0 there should be no blocked processes)
        //But a process could have been blocked by a verhogen() call when the semaphore was 1
        pcb_t *unblocked = removeBlocked(sem);
        if (unblocked != NULL)
        {

            // Decrement the soft block counter
            soft_block_count--;

            // Insert the process in the ready queue
            addToReadyQueue(unblocked);

            //Schedule the next process
            //PC_INCREMENT;  //NEED TO DO MANUALLY AS NOT DONE AT END OF SYSCALL HANDLER
            //scheduleNext();
        }
        

        //Decrement the semaphore
        (*sem)--;
    }

    //TODO
}


//SYS4 MURK
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


        soft_block_count++;
        insertBlocked(sem, running_proc);
        PC_INCREMENT; //NEED TO DO MANUALLY AS NOT DONE AT END OF SYSCALL HANDLER
        scheduleNext();
        return;
    }

    //Semaphore indicates no resource is available
    if (*sem <= 0)
    {
      

        //Remove the first process from the semaphore queue
        pcb_t *unblocked = removeBlocked(sem);

        //Decrement the soft block counter
        if (unblocked != NULL)
        {

            // Insert the process in the ready queue
            addToReadyQueue(unblocked);
            soft_block_count--;
        }
        else
        {
             
            // Increment the semaphore if no other processes are waiting
            (*sem)++;
        }
    }
}

//SYS5 MURK

int iosem = 0;

int do_io() {

    //Take the parameters
    int * cmdAddr = (devregtr *)(REG_A1_SS);

    //This is an array of 2 integers, the value of the command is placed inside the first one
    devregtr * value = (devregtr *)(REG_A2_SS);

    //Take the device RAM area
    //devregarea_t *deviceRegs = (devregarea_t *)RAMBASEADDR;


    //Detect if terminal device (by checking the address range of the command)
    if((int)cmdAddr <= LAST_TERM_ADDR && (int)cmdAddr >= TERM0ADDR) //Targeting a terminal device
    {
        //Get terminal index (0-7)
        int termIndex = ((int)cmdAddr-TERM0ADDR)/DEVREGSIZE;

        //This offset is copied from addokbuf function provided by tests
        memaddr *commandp = (devregtr *)((int)cmdAddr + (TRANCOMMAND * DEVREGLEN));         

        //Execute command
        //setSTATUS(getSTATUS() & DISABLEINTS);
        *commandp = value[0];

        //For now only output works, later detect how to handle input
        passeren(&sem_terminal_out[termIndex]);
    }
}

//SYS6 MURK
int get_cpu_time() {
    CPU_STATE->reg_v0 = getRunningProcTime();
}

void wait_for_clock(){
    is_proc_waiting_for_it = 1;
    passeren(&sem_interval_timer);
}

//SYS8 VALEX
void get_support_data() {
    if (running_proc->p_supportStruct == NULL) {
        CPU_STATE->reg_v0 = NULL;
    } else {
        CPU_STATE->reg_v0 = running_proc->p_supportStruct;
    }
}

//SYS9 MURK TODO: METTI I NAMESPACES

void get_pid() {

    //Get the parameter (parent or current process)
    int parent = (int)(REG_A1_SS);

    if (parent == true) {
        CPU_STATE->reg_v0 = (unsigned int) running_proc->p_parent->p_pid;
    } else {
        CPU_STATE->reg_v0 = (unsigned int) running_proc->p_pid;
    }
}


///SYS10 VALEX
///<summary>
///This service returns the pids of the calling process' children belonging to the same namespace
///the sys10 call is made with the following parameters:
///a1 is an array of integers, each of which is a pid of a child process
///a2 is the size of the array
///the return value is the number of children of the calling process that could have been
///inserted in the array
///</summary>
void get_children() {
    
        //Get the parameters
        int *pids = (int *)(REG_A1_SS);
        int size = (int)(REG_A2_SS);
    
        //Check if the parameters are valid
        if (pids == NULL || size <= 0) {
            CPU_STATE->reg_v0 = -1;
            return;
        }
    
        //Iterate over the children of the current process and copy their pid in the array
        pcb_PTR child;
        //get the list of children
        struct list_head *children = &(running_proc->p_child);
        int i = 0;
        while (headProcQ(children) != NULL && i < size)
        {
            pids[i] = child->p_pid;
            i++;
            //go to next child
            children = children->next;
        }
    
        //Return the number of children
        CPU_STATE->reg_v0 = i;
}