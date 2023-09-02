#include <umps/libumps.h>
#include <pandos_const.h>
#include <pandos_types.h>
#include <ash.h>
#include <pcb.h>
#include <ns.h>
#include <listx.h>
#include <p2test.h>
#include <exception.h>
#include <scheduler.h>

// void asdasdasdasdasds(){
//     PANIC();
// }

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

int main(int argc, int *argv[])
{
    /* Variable initialization */
    initPcbs();
    initASH();
    initNamespaces();
    initScheduler();
    
    /* Pass Up Vector */
    init_pv();

    /* Start the scheduler */
    scheduleNext();

    /* Should never reach this point */
    addokbuf("Scheduler returned\n");

    return 0;
}
