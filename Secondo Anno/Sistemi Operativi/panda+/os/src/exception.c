#include "exception.h"
#include <umps3/umps/arch.h>
#include "utils.h"
#include <umps3/umps/libumps.h>

// Copy of the exception cause register
int copied_exception_cause;

void exception_hanlder()
{
    //LDST(CPU_STATE);
    
    //Copy the exception cause register
    copied_exception_cause = DECODED_EXCEPTION_CAUSE;

    //Check if the exception is an interrupt
    if (copied_exception_cause == 0)
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
        return;
    }

    addokbuf("Exception handler called \n");
    return;
}

void testRefillHandler()
{
    addokbuf("TLB refill handler called \n");
    return;
}
