#include "pcb.h"
#include "../../phase2/include/test.h"
#include "utils.h"

//Running processes
int process_count;

//Blocked processes (waiting for a semaphore)
int soft_block_count;

//Processes ready to be executed
struct list_head ready_queue;

//Running process
pcb_t *running_proc;

//ONLY FOR DEBUG PURPOSES, REMOVE LATER
int copied_running_status;
memaddr func_addr;

void scheduler_breakpoint(){

}

char watch = 'n';
void testfunc(){
    PANIC();
    watch = 'y';
}



void initScheduler(){

    //Initialize counters
    process_count = 0;
    soft_block_count = 0;
    running_proc = NULL;

    //Initialize the ready queue
    mkEmptyProcQ(&ready_queue);
    if(&ready_queue == NULL){
        adderrbuf("Cannot init ready queue \n");
    }

    //Create root process
    pcb_t *root_p = allocPcb();
    if(root_p == NULL){
        adderrbuf("Cannot alloc root process \n");
    }

    //breakpoint();
    //LDST(&(root_p->p_s));
    //adderrbuf("TEST2 \n");

    //Clean pcb fields
    initializePcb(root_p);

    //Initialize the root process with necessary fields (enable interrupts etc.)
     /**
     * Imposto lo state_t su kernel mode, interrupt abilitati e Processor Local Time abilitato.
     * Uso l'or | per sommare i bit del registro e accenderli dove serve con le macro da pandos_const.h
     * ALLOFF = serie di 0
     * IEPON = Interrupt Enable Previous ON
     * IMON = Interrupt Mask ON
     * TEBITON = Time Enable BIT ON
     * KMEPON = Kernel Mode Enable Proevious BIT ON (custom)
     * Bisogna usare i Previous bit invece dei current quando si inizializza
     * un nuovo processor state
     */
    root_p->p_s.status = ALLOFF | IEPON | IMON | TEBITON;//IEPON | KMEPON | IMON | TEBITON;

    //Init the stack pointer of root to RAMTOP
    RAMTOP(root_p->p_s.reg_sp);


    //Init program counter to test function
    func_addr = (memaddr) test;
    root_p->p_s.pc_epc = func_addr;
    root_p->p_s.reg_t9 = func_addr;

    //Insert root process in ready queue
    insertProcQ(&ready_queue, root_p);
    if(headProcQ(&ready_queue) == NULL){
        adderrbuf("Cannot insert root proc to ready queue \n");
    }
    process_count++;

}

cpu_t start;
void schedule(){

    //Take first available process from ready queue
    //running_proc = headProcQ(&ready_queue);
    //addokbuf("Running proc from ready queue \n");

    //if(running_proc == NULL){
    //    adderrbuf("Cannot get root proc from ready queue \n");
    //    PANIC(); //TODO: check what to do on empty procq
    //}

    //Start the interval timer
    

    //Load the state of active process in the processor
    //copied_running_status = running_proc->p_s.status;

    //addokbuf("Loading process to CPU \n");


    //Creating ONLY FOR DEBUG THE PROCESS HERE
    pcb_PTR firstProc = allocPcb();
    firstProc->p_s.status = ALLOFF | IEPON | IMON | TEBITON;
    firstProc->p_s.pc_epc = firstProc->p_s.reg_t9 = (memaddr)testfunc;
    RAMTOP(firstProc->p_s.reg_sp);

    addokbuf("Starting \n");

    STCK(start); // start timer
    LDST(&(firstProc->p_s));
}