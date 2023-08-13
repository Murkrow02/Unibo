#include <exception.h>
#include <scheduler.h>
#include <utils.h>
#include "headers/syscall.h"



void z_breakpoint_exception(){}
void z_breakpoint_exception_panic(){}
void z_breakpoint_interrupt(){}
void z_breakpoint_syscall(){}

void exception_hanlder(){
    
    //Stop execution
    z_breakpoint_exception();

    //Check the cause of the exception
    int ex_cause = extractBits(CPU_CAUSE, 2, 6); // bits 2-6 of the cause register contain the exception cause
    
    //Handle the exception accordingly
    switch (ex_cause)
    {
        case IOINTERRUPTS: // Interrupt
            z_breakpoint_interrupt();
            //interrupt_handler();
            break;
        case 1 ... 3: // TLB Exception
            //tlb_handler();
            break;
        case 4 ... 7: // Trap
        case 9 ... 12:
            //trap_handler();
            break;
        case 8: // System Call
            z_breakpoint_syscall();
            syscall_handler();
            break;
        default:
            z_breakpoint_exception_panic();
            PANIC();
    }

}