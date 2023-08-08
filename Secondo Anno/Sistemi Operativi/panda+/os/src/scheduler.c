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
    watch = 'y';
    2/0;
    PANIC();
    return;
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
        PANIC();
    }

    //Create root process
    pcb_t *root_p = allocPcb();
    if(root_p == NULL){
        adderrbuf("Cannot alloc root process \n");
        PANIC();
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
    root_p->p_s.status = ALLOFF | IEPON | KMEPON | IMON | TEBITON;

    //Init the stack pointer of root to RAMTOP
    RAMTOP(root_p->p_s.reg_sp);


    //Init program counter to test function
    func_addr = (memaddr) testfunc;
    root_p->p_s.pc_epc = func_addr;
    root_p->p_s.reg_t9 = func_addr;

    //Insert root process in ready queue
    insertProcQ(&ready_queue, root_p);
    if(headProcQ(&ready_queue) == NULL){
        adderrbuf("Cannot insert root proc to ready queue \n");
        PANIC();
    }
    process_count++;

    //Initialize the interval timer
    LDIT(100000);
}

cpu_t start;
//int a = -1;
void schedule(){
    //a++;

    //Take first available process from ready queue
    running_proc = headProcQ(&ready_queue);
    addokbuf("Running proc from ready queue \n");

    if(running_proc == NULL){
        adderrbuf("Cannot get root proc from ready queue \n");
        PANIC(); //TODO: check what to do on empty procq
    }

    //Start the interval timer
    //STCK(start);

    //Load the state of active process in the processor
    copied_running_status = running_proc->p_s.status;
    
    //running_proc->p_s.pc_epc = func_addr + WORDLEN*a;
    //running_proc->p_s.reg_t9 = func_addr+ WORDLEN*a;


    addokbuf("Loading process to CPU \n");
    scheduler_breakpoint();
    LDST(&(running_proc->p_s));
}