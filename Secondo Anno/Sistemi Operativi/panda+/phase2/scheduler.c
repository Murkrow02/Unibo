#include <pcb.h>
#include <p2test.h>
#include <pandos_types.h>
#include <utils.h>
#include <scheduler.h>
#include <umps3/umps/arch.h>
#include <listx.h>


//Running processes
int process_count;

//Blocked processes (waiting for a semaphore)
int soft_block_count;

//Processes ready to be executed
struct list_head ready_queue;

//Running process
pcb_t *running_proc;

//Semaphore arrays
int is_proc_waiting_for_it=0;
int sem_interval_timer = 0;
int sem_terminal_in[8];
int sem_terminal_out[8];

//Running process pid
int running_proc_pid = 0;

void z_scheduler_breakpoint(){}
void z_scheduler_breakpoint2(){}


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

//Easy way to remove a process from the ready queue
void removeFromReadyQueue(pcb_PTR proc){
    outProcQ(&ready_queue, proc);
}

//Returns the running time in cpu_t of the running process
cpu_t running_proc_start; //This is set in scheduleNext() when a new process is dispatched
cpu_t getRunningProcTime(){
    cpu_t current_time;
    STCK(current_time);
    return running_proc->p_time + (current_time - running_proc_start);
}

inline void initScheduler(){

    //Initialize counters
    process_count = 0;
    soft_block_count = 0;
    running_proc = NULL;    

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

    //Initialize the root process with necessary fields (enable interrupts etc.)
    root_p->p_s.status = ALLOFF | IEPON | IMON | TEBITON;

    //Init program counter to test function
    memaddr func_addr = (memaddr) test;
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

//DEBUG ONLY
int pc = 0;

void scheduleNext(){

    z_scheduler_breakpoint();

    //Save running proc state in its pcb
    if(running_proc != NULL){

        //Save current state of the running process in its pcb
        copyState(CPU_STATE, &running_proc->p_s);

        //Save the time the process has been running
        running_proc->p_time = getRunningProcTime();

    }

    //No more ready processes
    if(headProcQ(&ready_queue) == NULL){
        
        //All processes have terminated
        if(process_count == 0)
            HALT();

        if (process_count > 0 && soft_block_count > 0)
        {
            // Enable interrupts
            running_proc = NULL;

            //Set the plt timer to max to prevent plt interrupts
            setTIMER(4294967295); 
            setSTATUS(IECON | IMON);

            WAIT(); 
        }

        z_scheduler_breakpoint2();

        if (process_count > 0 && soft_block_count == 0)
            adderrbuf("DEADLOCK \n");
    }

    // Take first available process from ready queue
    running_proc = removeProcQ(&ready_queue);
    
    //If there are no processes in the ready queue, panic
    if(running_proc == NULL){
        adderrbuf("NO RUNNING PROC \n");
    }

    //Save the pid of the running process
    running_proc_pid = running_proc->p_pid;
    
    // PLT (Process Local Timer) 5ms (this will give the process a maximum of 5ms to run before being preempted)
    setTIMER(TIMESLICE * (*((cpu_t *)TIMESCALEADDR))); 
    //setTIMER(999999999 * (*((cpu_t *)TIMESCALEADDR))); 

    //Save start time of the new process
    STCK(running_proc_start); 

    //DEBUG
    pc = running_proc->p_s.pc_epc;

    //Load process to CPU
    LDST(&running_proc->p_s);
}