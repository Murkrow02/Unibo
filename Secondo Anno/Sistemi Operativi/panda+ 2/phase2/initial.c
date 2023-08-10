#include <umps/libumps.h>
#include "../os/pandos_const.h"
#include "../os/pandos_types.h"
#include "../phase1/headers/ash.h"
#include "../phase1/headers/pcb.h"
#include "../phase1/headers/listx.h"
#include "headers/p2test.h"
#include "headers/exception.h"

char a = 'n';
void test2(){
    a = 'y';
    PANIC();
}

void init_pv()
{
    //Get the passupvector from the passupvector area (defined in const.h)
    passupvector_t *pv = (passupvector_t *)PASSUPVECTOR;

    //Initialize and populate the pass up vector
    //pv->tlb_refill_handler = (memaddr) uTLB_RefillHandler;
    pv->tlb_refill_stackPtr = KERNELSTACK;
    //pv->exception_handler = (memaddr) exception_hanlder;
    pv->exception_stackPtr = KERNELSTACK;
}

int main(int argc, int *argv[])
{
    /* Variable initialization */
    initPcbs();

    /* Pass Up Vector */
    init_pv();

    /* Insert first low priority process */
    pcb_PTR firstProc = allocPcb();
    firstProc->p_s.status = ALLOFF | IEPON | IMON | TEBITON;
    firstProc->p_s.pc_epc = firstProc->p_s.reg_t9 = (memaddr)test2;
    RAMTOP(firstProc->p_s.reg_sp); 


    setTIMER(TIMESLICE * (*((cpu_t *)TIMESCALEADDR))); // PLT 5 ms
    LDST(&firstProc->p_s);


    return 0;
}
