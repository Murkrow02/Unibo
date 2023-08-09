#include "pcb.h"
#include "types.h"
#include "utils.h"
#include "list.h"
#include <stddef.h>
#include <pandos_const.h>
#include <pandos_types.h>
#include <umps3/umps/libumps.h>
#include "ash.h"
#include "ns.h"
#include "scheduler.h"
#include "exception.h"
#include "test.h"

static pcount = 0;


//The pass up vector is where the addresses of the common core stuff is located
void init_pv()
{
    //Get the passupvector from the passupvector area (defined in const.h)
    passupvector_t *pv = (passupvector_t *)PASSUPVECTOR;

    //Initialize and populate the pass up vector
    pv->tlb_refill_handler = (memaddr) uTLB_RefillHandler;
    pv->tlb_refill_stackPtr = KERNELSTACK;
    pv->exception_handler = (memaddr) exception_hanlder;
    pv->exception_stackPtr = KERNELSTACK;
}

void test2() {
    PANIC();
    return;
}
int main(void) {

    //Fill the free pcb list
    initPcbs();

    //Initialize the active semaphore ash table
    initASH();

    initNamespaces();

    //Initialize the scheduler
    //initScheduler();

    //Initialize the pass up vector
    init_pv();

    addokbuf("Init OK \n");

    //Initialize the interval timer
    //LDIT(100000);


     /* Insert first low priority process */
    pcb_PTR firstProc = allocPcb();

    //++activeProc;
    //insert_ready_queue(PROCESS_PRIO_LOW, firstProc);
    firstProc->p_s.status = ALLOFF | IEPON | IMON | TEBITON;
    firstProc->p_s.pc_epc = firstProc->p_s.reg_t9 = (memaddr)test2;
    RAMTOP(firstProc->p_s.reg_sp);


    setTIMER(TIMESLICE * (*((cpu_t *)TIMESCALEADDR))); // PLT 5 ms
    //STCK(startTime);
    LDST(&firstProc->p_s);

    //Start the scheduler
    //schedule();

    addokbuf("FINISHED   \n");

    return 1;
}