#include <exception.h>
#include <scheduler.h>
#include <utils.h>
#include <interrupt.h>
#include <umps/cp0.h>
#include "headers/syscall.h"

void z_breakpoint_exception() {}
void z_breakpoint_exception_panic() {}

void exception_hanlder()
{
    // Stop execution
    z_breakpoint_exception();

    // Handle the exception accordingly
    switch (CAUSE_GET_EXCCODE(getCAUSE()))
    {
    case IOINTERRUPTS: // Interrupt
        interrupt_handler();
        break;
    case 1 ... 3: // TLB Exception
        adderrbuf("TLB EXCEPTION \n");
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