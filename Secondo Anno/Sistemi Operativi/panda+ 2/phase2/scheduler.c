#include <pcb.h>
#include <p2test.h>
#include <pandos_types.h>
#include <utils.h>
#include <scheduler.h>
#include <umps3/umps/libumps.h>
#include <umps3/umps/arch.h>

//Running processes
int process_count;

//Blocked processes (waiting for a semaphore)
int soft_block_count;

//Processes ready to be executed
struct list_head ready_queue;

//Running process
pcb_t *running_proc;

//Semaphore arrays
int sem_interval_timer;
int sem_terminal_in[8];
int sem_terminal_out[8];


//ONLY FOR DEBUG PURPOSES, REMOVE LATER
int copied_running_status;
memaddr func_addr;

void scheduler_breakpoint(){

}

int watch = 1;
void testfunc()
{
    while (1)
    {
        watch++;
    }

    PANIC();
}

//Easy way to append a process to the ready queue
void addToReadyQueue(pcb_PTR proc){
    insertProcQ(&ready_queue, proc);
}

//Easy way to block process by saving its state and inserting it back into the ready queue
void blockRunningProcess(){

    //Save the state of the running process
    saveStateTo(&running_proc->p_s);

    //Insert the running process in the ready queue
    addToReadyQueue(running_proc);

    //Schedule the next process
    schedule();
}

//Increment the program counter of the running process
void incrementProgramCounter(){
    running_proc->p_s.pc_epc += WORD_SIZE;
    running_proc->p_s.reg_t9 += WORD_SIZE;
}


inline void initScheduler(){

    //Initialize counters
    process_count = 0;
    soft_block_count = 0;
    running_proc = NULL;


    //Initialize the semaphore array TODO:
    

    //Load the pseudo-clock interval in the interval timer
    LDIT(100000);

    //Initialize the ready queue
    mkEmptyProcQ(&ready_queue);
    if(&ready_queue == NULL){
        adderrbuf("Cannot init ready queue \n");
    }

    //Create root process
    pcb_PTR root_p = allocPcb();
    if(root_p == NULL){
        adderrbuf("Cannot alloc root process \n");
    }

    //Clean pcb fields
    //initializePcb(root_p);

    //Initialize the root process with necessary fields (enable interrupts etc.)
     /**
     * ALLOFF = serie di 0
     * IEPON = Interrupt Enable Previous ON
     * IMON = Interrupt Mask ON
     * TEBITON = Time Enable BIT ON
     */
    root_p->p_s.status = ALLOFF | IEPON | IMON | TEBITON;

    //Init program counter to test function
    func_addr = (memaddr) test;
    root_p->p_s.pc_epc = root_p->p_s.reg_t9 = func_addr;

    //Init the stack pointer of root to RAMTOP
    RAMTOP(root_p->p_s.reg_sp);     

    //Insert root process in ready queue
    addToReadyQueue(root_p);
    if(headProcQ(&ready_queue) == NULL){
        adderrbuf("Cannot insert root proc to ready queue \n");
    }

    process_count++;
}

cpu_t running_proc_start;
cpu_t running_proc_stop;
void schedule(){


    //Halt if there are no processes
    if(process_count == 0){
        //TODO: CHECK HOW TO HALT
        //HALT();
    }

    //Save running proc state in its pcb
    if(running_proc != NULL){

        //Save current state of the running process in its pcb
        STST(running_proc->p_s);

        //Stop time of the running process
        STCK(running_proc_stop);

        //Save the time the process has been running
        running_proc->p_time = running_proc->p_time + (running_proc_stop - running_proc_start);
    }

    //Take first available process from ready queue
    running_proc = removeProcQ(&ready_queue);

    //If there are no processes in the ready queue, panic
    if(running_proc == NULL){
        adderrbuf("Cannot get root proc from ready queue \n");
    }
    
    // PLT (Process Local Timer) 5ms (this will give the process a maximum of 5ms to run before being preempted)
    setTIMER(TIMESLICE * (*((cpu_t *)TIMESCALEADDR))); 

    //Save start time of the new process
    STCK(running_proc_start); 
    LDST(&running_proc->p_s);
}