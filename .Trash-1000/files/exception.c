#include <umps/libumps.h>
#include <umps/arch.h>
#include "umps/cp0.h"
#include "syscall.h"
#include "scheduler.h"



void plt_time_handler(state_t *excState)
{
    setTIMER(-2); // ACK
    copy_state(excState, &currentActiveProc->p_s);
    insert_ready_queue(currentActiveProc->p_prio, currentActiveProc);
    scheduler();
}

// handler IL_TIMER
void intervall_timer_handler(state_t *excState)
{
    return;
    LDIT(100000); // ACK
    pcb_PTR p;
    while ((p = removeBlocked(&semIntervalTimer)) != NULL)
    {
        --blockedProc;
        insert_ready_queue(p->p_prio, p);
    }
    semIntervalTimer = 0;
    load_or_scheduler(excState);
}

/**
 * Obtain the semaphore address of a generic device (NON TERMINAL)
 * Take the device's interrupt line and the device number as input (from 0 to 7)
 * and return semaphore's address
 *
 * @param interruptLine The interrupt line yo recognize.
 * @param devNumber The device index of the semaphore array
 *
 * @return A pointer to the semaphore for the device.
 */
int *getDeviceSemaphore(int interruptLine, int devNumber)
{
    switch (interruptLine)
    {
    case IL_DISK:
        return &semDiskDevice[devNumber];
    case IL_FLASH:
        return &semFlashDevice[devNumber];
    case IL_ETHERNET:
        return &semNetworkDevice[devNumber];
    case IL_PRINTER:
        return &semPrinterDevice[devNumber];
    }
    return NULL;
}

// handler IL_DISK | IL_FLASH | IL_ETHERNET | IL_PRINTER | IL_TERMINAL
void device_handler(int interLine, state_t *excState)
{
    unsigned int statusCode;
    int *devSemaphore = NULL;
    int devNumber = 0;

    devregarea_t *devRegs = (devregarea_t *)RAMBASEADDR;
    unsigned int bitmap = devRegs->interrupt_dev[interLine - 3];
    unsigned int mask = 1;

    for (int i = 0; i < N_DEV_PER_IL; i++)
    {
        if (bitmap & mask)
        {
            devNumber = i;

            if (interLine == IL_TERMINAL)
            {
                termreg_t *devRegAddr = (termreg_t *)DEV_REG_ADDR(interLine, devNumber);

                if (devRegAddr->transm_status != READY && devRegAddr->transm_status != BUSY)
                {
                    statusCode = devRegAddr->transm_status;
                    devRegAddr->transm_command = ACK;
                    devSemaphore = &semTerminalDeviceWriting[devNumber];
                }
                else
                {
                    statusCode = devRegAddr->recv_status;
                    devRegAddr->recv_command = ACK;
                    devSemaphore = &semTerminalDeviceReading[devNumber];
                }
            }
            else
            {
                dtpreg_t *devRegAddr = (dtpreg_t *)DEV_REG_ADDR(interLine, devNumber);
                devSemaphore = getDeviceSemaphore(interLine, devNumber);
                statusCode = devRegAddr->status; // Save status code
                devRegAddr->command = ACK;       // Acknowledge the interrupt
            }
        }
        mask *= 2;
    }

    /* V-Operation */
    pcb_PTR proc = V(devSemaphore, NULL);

    if (proc == NULL || proc == currentActiveProc)
    {
        currentActiveProc->p_s.reg_v0 = statusCode;
        insert_ready_queue(currentActiveProc->p_prio, currentActiveProc);
        scheduler();
    }
    else
    {
        proc->p_s.reg_v0 = statusCode;
        load_or_scheduler(excState);
    }
}

// Handler TLB | TRAP
void pass_up_or_die(int pageFault, state_t *excState)
{
    if (currentActiveProc != NULL)
    {
        if (currentActiveProc->p_supportStruct == NULL)
        {
            term_proc(0);
            scheduler();
        }
        else
        {
            copy_state(excState, &currentActiveProc->p_supportStruct->sup_exceptState[pageFault]);
            int stackPtr = currentActiveProc->p_supportStruct->sup_exceptContext[pageFault].stackPtr;
            int status = currentActiveProc->p_supportStruct->sup_exceptContext[pageFault].status;
            int pc = currentActiveProc->p_supportStruct->sup_exceptContext[pageFault].pc;
            LDCXT(stackPtr, status, pc);
        }
    }
}

void exception_handler()
{
    //return;
    state_t *exceptionState = (state_t *)BIOSDATAPAGE;
    int causeCode = CAUSE_GET_EXCCODE(getCAUSE());


    switch (causeCode)
    {
    case IOINTERRUPTS: // Interrupt
        interrupt_handler(exceptionState);
        break;
    case 1 ... 3: // TLB Exception
        tlb_handler(exceptionState);
        break;
    case 4 ... 7: // Trap
    case 9 ... 12:
        trap_handler(exceptionState);
        break;
    case 8: // System Call
        syscall_handler(exceptionState);
        break;
    default:
        PANIC();
    }
}

// case 0 exception_handler()
void interrupt_handler(state_t *excState)
{
    return;
    int cause = getCAUSE(); // Ritorna il registro CAUSE (3.3 pops)

    if CAUSE_IP_GET (cause, IL_CPUTIMER)
        plt_time_handler(excState);
    else if CAUSE_IP_GET (cause, IL_TIMER){
    }
        //intervall_timer_handler(excState);
    else if CAUSE_IP_GET (cause, IL_DISK)
        device_handler(IL_DISK, excState);
    else if CAUSE_IP_GET (cause, IL_FLASH)
        device_handler(IL_FLASH, excState);
    else if CAUSE_IP_GET (cause, IL_ETHERNET)
        device_handler(IL_ETHERNET, excState);
    else if CAUSE_IP_GET (cause, IL_PRINTER)
        device_handler(IL_PRINTER, excState);
    else if CAUSE_IP_GET (cause, IL_TERMINAL)
        device_handler(IL_TERMINAL, excState);

    PANIC();
}

// case 1 ... 3 exception_handler()
void tlb_handler(state_t *excState)
{
    pass_up_or_die(PGFAULTEXCEPT, excState);
}

// case 4 ... 7 | 9 ... 12 exception_handler()
void trap_handler(state_t *excState)
{
    pass_up_or_die(GENERALEXCEPT, excState);
}

// case 8 case exception_handler()
void syscall_handler(state_t *callerProcState)
{
    return;
    int syscode = callerProcState->reg_a0;
    callerProcState->pc_epc += WORDLEN;

    if (syscode <= 0 && ((callerProcState->status << 28) >> 31))
    {
        callerProcState->cause = (callerProcState->cause & !GETEXECCODE) | 0x00000028;
        pass_up_or_die(GENERALEXCEPT, callerProcState);
    }
    else
    {
        switch (syscode)
        {
        case CREATEPROCESS:
            create_process(callerProcState);
            break;
        case TERMPROCESS:
            terminate_process(callerProcState);
            break;
        case PASSEREN:
            passeren(callerProcState);
            break;
        case VERHOGEN:
            verhogen(callerProcState);
            break;
        case DOIO:
            do_IO_device(callerProcState);
            break;
        case GETTIME:
            get_cpu_time(callerProcState);
            break;
        case CLOCKWAIT:
            wait_for_clock(callerProcState);
            break;
        case GETSUPPORTPTR:
            get_support_data(callerProcState);
            break;
        case GETPROCESSID:
            get_ID_process(callerProcState);
            break;
        case YIELD:
            yield(callerProcState);
            break;
        default:
            trap_handler(callerProcState);
            break;
        }
    }
    //load_or_scheduler(callerProcState);
}