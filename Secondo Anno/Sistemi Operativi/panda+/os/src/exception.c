#include "exception.h"
#include <umps3/umps/arch.h>
#include "utils.h"
#include <umps3/umps/libumps.h>

// Copy of the exception cause register
int copied_exception_cause;

void interrupt_handler()
{
    //Check which interrupt line is active
    for (int line = 1; line < N_INTERRUPT_LINES; line++)
    {
        if ((CPU_STATE->cause) & CAUSE_IP(line))
        {
            //Check if the interrupt line is the timer
            if (line == 1)
            {
                addokbuf("TIMER INTERRUPT \n");
                //schedule();
                break;
            }
        }
    }
}

void syscall_handler()
{
    addokbuf("SYSCALL \n");
}

void exception_hanlder()
{
    //Determine the cause of the exception
    int exception_cause = DECODED_EXCEPTION_CAUSE;

    switch (exception_cause)
    {
    case 0: //Interrupt
        interrupt_handler();
        break;
    case 1 ... 3: //TLB Exception
        //tlb_handler();
        break;
    case 4 ... 7: //Trap
    case 9 ... 12:
        //trap_handler();
        break;
    case 8: //Syscall
        syscall_handler();
        break;
    default:
        PANIC();
    }
}