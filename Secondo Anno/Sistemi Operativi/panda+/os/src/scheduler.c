#include "pcb.h"
#include "../../phase2/include/test.h"
#include "utils.h"

int process_count;
int soft_block_count;
struct list_head ready_queue;
pcb_t *running_proc;

void constructRootProc(pcb_t *root_p)
{
    //Enable interrupts for process (previous)
    root_p->p_s.status |= IE_P;

    //Enable all interrupts in mask for process (bits 15-8)
    root_p->p_s.status |= IE_ALL;

    //Enable local timer (bit 27)
    root_p->p_s.status |= LTE;

    //Set kernel mode (previous)
    root_p->p_s.status |= KME_P;

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

    //TODO: implement interval timer

    //Create root process
    pcb_t *root_p = allocPcb();
    if(root_p == NULL){
        adderrbuf("Cannot alloc root process \n");
        PANIC();
    }

    //Clean pcb fields
    initializePcb(root_p);

    //Initialize the root process with necessary fields (enable interrupts etc.)
    constructRootProc(root_p);

    //Insert root process in ready queue
    insertProcQ(&ready_queue, root_p);
    if(headProcQ(&ready_queue) == NULL){
        adderrbuf("Cannot insert root proc to ready queue \n");
        PANIC();
    }
    process_count++;

    //Init the stack pointer of root to RAMTOP
    RAMTOP(root_p->p_s.reg_sp);

    //Init program counter to test function
    root_p->p_s.pc_epc = (memaddr) test;
    root_p->p_s.reg_t9 = (memaddr) test;


}

void schedule(){

    //Take first available process from ready queue
    running_proc = removeProcQ(&ready_queue);
    if(running_proc == NULL){
        adderrbuf("Cannot get root proc from ready queue \n");
        PANIC(); //TODO: check what to do on empty procq
    }

    //Load the state of active process in the processor
    adderrbuf("DSA \n");
    LDST(&running_proc->p_s);
    adderrbuf("ASD \n");

}