#include "syscall.h"
#include <pandos_types.h>
#include <umps3/umps/arch.h>
#include <umps3/umps/cp0.h>

int semTerminalDeviceReading[8];
int semTerminalDeviceWriting[8];

void do_IO_device(state_t *excState)
{
    int *cmdAddr = (int *)(*excState).reg_a1;
    int cmdValue = (int)(*excState).reg_a2;

    int *devSemaphore = NULL; // Semaphore address
    devregarea_t *deviceRegs = (devregarea_t *)RAMBASEADDR;

    /* Searching which device is running looking first for terminal then for generic devices */
    for (int i = 0; i < 8; i++)
    {
        if (&(deviceRegs->devreg[4][i].term.transm_command) == (memaddr *)cmdAddr)
        { // Terminal Devices Writing
            devSemaphore = &semTerminalDeviceWriting[i];
            break;
        }
        else if (&(deviceRegs->devreg[4][i].term.recv_command) == (memaddr *)cmdAddr)
        { // Terminal Devices Reading
            devSemaphore = &semTerminalDeviceReading[i];
            break;
        }
    }
    
    *cmdAddr = cmdValue;         // Execute request command
    //P(devSemaphore, excState);   // Call a P on the semaphore found, should be blocking
    //load_or_scheduler(excState); // Just in case
}