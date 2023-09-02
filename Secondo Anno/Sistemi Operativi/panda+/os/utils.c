#include <pandos_types.h>
#include <utils.h>

//Copies the state of the running process to another state_t
void saveStateTo(state_t *dest){
    copyState(CPU_STATE, dest);
}

//Copies the state of a process to another
void copyState(state_t *original, state_t *dest)
{
    dest->entry_hi = original->entry_hi;
    dest->cause = original->cause;
    dest->status = original->status;
    dest->pc_epc = original->pc_epc;
    dest->hi = original->hi;
    dest->lo = original->lo;
    for (int i = 0; i < STATE_GPR_LEN; i++)
    {
        dest->gpr[i] = original->gpr[i];
    }
}

int extractBits(int num, int start, int end) {

    // Calculate the number of bits to extract
    int numBits = end - start + 1;
    
    // Create a mask with the desired bits set to 1
    int mask = (1 << numBits) - 1;
    
    // Shift the mask to the desired position
    mask <<= start;
    
    // Extract the desired bits using bitwise AND
    int extractedBits = (num & mask) >> start;
    
    return extractedBits;
}

//Copies a string from src to dest
void strcopy(char *dest, char *src, int len) {
    int i;
    for (i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int list_search_el(list_head* searchElement, list_head* list){

    list_head* el;
    list_for_each(el, list){
        if(el == searchElement){

            //We found desired list_head element
            return 1;
        }
    }

    //If we landed here we searched the whole list without success
    return 0;
}

extern int sem_terminal_in[8];
extern int sem_terminal_out[8];
bool isDeviceSem(int *sem)
{
    for (int i = 0; i < DEVPERINT; i++)
    {
        if (sem == &sem_terminal_in[i] || sem == &sem_terminal_out[i])
        {
            return true;
        }
    }

    return false;
}




//TODO REMOVE THESE LINES

#define MAXSEM  MAXPROC
#define TRANSMITTED 5
#define PRINTCHR    2
#define CHAROFFSET  8
#define STATUSMASK  0xFF
char   okbuf[2048]; /* sequence of progress messages */
char   errbuf[128]; /* contains reason for failing */
char  *mp = okbuf;
typedef unsigned int devreg;

/* This function returns the terminal transmitter status value given its address */
devreg termstat(memaddr *stataddr) {
    return ((*stataddr) & STATUSMASK);
}

/* This function prints a string on the specified terminal and returns TRUE if
 * print was successful, FALSE if not   */
unsigned int termprint(char *str, unsigned int term) {
    memaddr *statusp;
    memaddr *commandp;
    devreg stat;
    devreg cmd;
    unsigned int error = FALSE;

    if (term < DEVPERINT) {
        /* terminal is correct */
        /* compute device register field addresses */
        statusp = (devreg *)(TERM0ADDR + (term * DEVREGSIZE) + (TRANSTATUS * DEVREGLEN));
        commandp = (devreg *)(TERM0ADDR + (term * DEVREGSIZE) + (TRANCOMMAND * DEVREGLEN));

        /* test device status */
        stat = termstat(statusp);
        if (stat == READY || stat == TRANSMITTED) {
            /* device is available */

            /* print cycle */
            while (*str != EOS && !error) {
                cmd = (*str << CHAROFFSET) | PRINTCHR;
                *commandp = cmd;

                /* busy waiting */
                stat = termstat(statusp);
                while (stat == BUSY)
                    stat = termstat(statusp);

                /* end of wait */
                if (stat != TRANSMITTED)
                    error = TRUE;
                else
                    /* move to the next char */
                    str++;
            }
        } else
            /* device is not available */
            error = TRUE;
    } else
        /* wrong terminal device number */
        error = TRUE;

    return (!error);
}

/* This function places the specified character string in okbuf and
 * causes the string to be written out to terminal0 */
void addokbuf(char *strp) {
    char *tstrp = strp;
    while ((*mp++ = *strp++) != '\0')
        ;
    mp--;
    termprint(tstrp, 0);
}

/* This function places the specified character string in errbuf and
 * causes the string to be written out to terminal0. After this is done,
 * the system shuts down with a panic message */
void adderrbuf(char *strp) {
    char *ep = errbuf;
    char *tstrp = strp;

    while ((*ep++ = *strp++) != '\0')
        ;

    termprint(tstrp, 0);

    PANIC();
}



// Function to set a 32-bit integer value at index i as a bitmask
void setBitmaskAtIndex(unsigned int* number, int index, int value) {

    if (index < 0 || index >= 32) {
        return;
    }

    unsigned int mask = 1 << index;

    if (value) {
        *number |= mask;  // Set the bit at the given index to 1
    } else {
        *number &= ~mask; // Set the bit at the given index to 0
    }
}


