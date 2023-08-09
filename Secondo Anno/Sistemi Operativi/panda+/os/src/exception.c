#include "exception.h"
#include <umps3/umps/arch.h>
#include "utils.h"
#include "pandos_const.h"
#include <umps3/umps/libumps.h>

#define CAUSE_IP_GET(cause, il_no) ((cause) & (1 << ((il_no) + 8))) // performs a bit shift based on the parameters

// Copy of the exception cause register
int copied_exception_cause;



void exception_hanlder()
{    
    state_t *exceptionState = (state_t *)BIOSDATAPAGE;
    int causeCode = CAUSE_GET_EXCCODE(getCAUSE());


    switch (causeCode)
    {
    case IOINTERRUPTS: // Interrupt
        //interrupt_handler(exceptionState);
        break;
    case 1 ... 3: // TLB Exception
        //tlb_handler(exceptionState);
        break;
    case 4 ... 7: // Trap
    case 9 ... 12:
        //trap_handler(exceptionState);
        break;
    case 8: // System Call
        //syscall_handler(exceptionState);
        break;
    default:
        PANIC();
    }
}