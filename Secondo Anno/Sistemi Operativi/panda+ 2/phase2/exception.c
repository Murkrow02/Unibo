#include <exception.h>
#include <scheduler.h>
#include <utils.h>
#include <interrupt.h>
#include "headers/syscall.h"

void z_breakpoint_exception() {}
void z_breakpoint_exception_panic() {}

void exception_hanlder()
{
    // Disable interrupts
    //setSTATUS(getSTATUS() & DISABLEINTS);

    // Stop execution
    z_breakpoint_exception();

    // Check the cause of the exception
    int ex_cause = extractBits(CPU_CAUSE, 2, 6); // bits 2-6 of the cause register contain the exception cause

    // Handle the exception accordingly
    switch (ex_cause)
    {
    case IOINTERRUPTS: // Interrupt
        interrupt_handler();
        break;
    case 1 ... 3: // TLB Exception
        // tlb_handler();
        break;
    case 4 ... 7: // Trap
    case 9 ... 12:
        pass_up_or_die(GENERALEXCEPT);
        break;
    case 8: // System Call

        // Handle the syscall
        syscall_handler();

        break;
    default:
        z_breakpoint_exception_panic();
        PANIC();
    }
}