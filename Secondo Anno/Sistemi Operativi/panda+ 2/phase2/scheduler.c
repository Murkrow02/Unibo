#include <pcb.h>
#include <p2test.h>
#include <pandos_types.h>
#include <utils.h>
#include <scheduler.h>

//Running processes
int process_count;

//Blocked processes (waiting for a semaphore)
int soft_block_count;

//Processes ready to be executed
struct list_head ready_queue;

//Running process
pcb_t *running_proc;

//Semaphore array
//TODO: check the right number (one foreach device + 1 for the pseudo-clock and count terminal devices twice for I/O)
semd_t semaphores[50]; 


//ONLY FOR DEBUG PURPOSES, REMOVE LATER
int copied_running_status;
memaddr func_addr;

void scheduler_breakpoint(){

}

char watch = 'n';
 void testfunc(){
    watch = 'y';
    PANIC();
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
    func_addr = (memaddr) testfunc;
    root_p->p_s.pc_epc = root_p->p_s.reg_t9 = func_addr;

    //Init the stack pointer of root to RAMTOP
    RAMTOP(root_p->p_s.reg_sp);     

    //Insert root process in ready queue
    insertProcQ(&ready_queue, root_p);
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

        //STATE
        running_proc->p_s = running_proc->p_s;

        //TIME STOPPED
        STCK(running_proc_stop);

        //TIME RUNNING
        running_proc->p_time = running_proc->p_time + (running_proc_stop - running_proc_start);
    }

    //Take first available process from ready queue
    running_proc = removeProcQ(&ready_queue);

    //If there are no processes in the ready queue, panic
    if(running_proc == NULL){
        adderrbuf("Cannot get root proc from ready queue \n");
    }
    
    // PLT 5ms
    setTIMER(TIMESLICE * (*((cpu_t *)TIMESCALEADDR))); 

    //Save start time of the new process
    STCK(running_proc_start); 
    LDST(&running_proc->p_s);
}