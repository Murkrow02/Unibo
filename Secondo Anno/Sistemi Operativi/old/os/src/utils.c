//
// Created by Marco Coppola on 27/01/23.
//


#include "pandos_types.h"
#include <pandos_const.h>




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


void set_namespace(pcb_t *p, nsd_t *ns){

    //Cycle through all possible spots to find one of the same kind as ns
    for(int i = 0; i < NS_TYPE_MAX; i++){

        //If a namespace of the same type is found, replace this one
        if(p->namespaces[i] != NULL && p->namespaces[i]->n_type == ns->n_type){
            p->namespaces[i] = ns;
            return;
        }
    }

    //Cycle through all possible spots to find a free one
    for(int i = 0; i < NS_TYPE_MAX; i++){

        //If a blank space is found, insert the namespace there
        if(p->namespaces[i] == NULL){
            p->namespaces[i] = ns;
        }
    }
}

//TODO REMOVE THESE LINES

#define MAXPROC 20
#define MAXSEM  MAXPROC
#define MAXNS   MAXPROC

char   okbuf[2048]; /* sequence of progress messages */
char   errbuf[128]; /* contains reason for failing */
char   msgbuf[128]; /* nonrecoverable error message before shut down */
int    sem[MAXSEM];
int    onesem;
pcb_t *procp[MAXPROC], *p, *q, *firstproc, *lastproc, *midproc;
nsd_t *pid_ns, *pid_ns2;
char  *mp = okbuf;


#define TRANSMITTED 5
#define ACK         1
#define PRINTCHR    2
#define CHAROFFSET  8
#define STATUSMASK  0xFF
#define TERM0ADDR   0x10000254

typedef unsigned int devreg;

/* This function returns the terminal transmitter status value given its address */
devreg termstat(memaddr *stataddr) {
    return ((*stataddr) & STATUSMASK);
}

/* This function prints a string on specified terminal and returns TRUE if
 * print was successful, FALSE if not   */
unsigned int termprint(char *str, unsigned int term) {
    memaddr     *statusp;
    memaddr     *commandp;
    devreg       stat;
    devreg       cmd;
    unsigned int error = FALSE;

    if (term < DEVPERINT) {
        /* terminal is correct */
        /* compute device register field addresses */
        statusp  = (devreg *)(TERM0ADDR + (term * DEVREGSIZE) + (TRANSTATUS * DEVREGLEN));
        commandp = (devreg *)(TERM0ADDR + (term * DEVREGSIZE) + (TRANCOMMAND * DEVREGLEN));

        /* test device status */
        stat = termstat(statusp);
        if (stat == READY || stat == TRANSMITTED) {
            /* device is available */

            /* print cycle */
            while (*str != EOS && !error) {
                cmd       = (*str << CHAROFFSET) | PRINTCHR;
                *commandp = cmd;

                /* busy waiting */
                stat = termstat(statusp);
                while (stat == BUSY)
                    stat = termstat(statusp);

                /* end of wait */
                if (stat != TRANSMITTED)
                    error = TRUE;
                else
                    /* move to next char */
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


/* This function placess the specified character string in okbuf and
 *	causes the string to be written out to terminal0 */
void addokbuf(char *strp) {
    char *tstrp = strp;
    while ((*mp++ = *strp++) != '\0')
        ;
    mp--;
    termprint(tstrp, 0);
}


/* This function placess the specified character string in errbuf and
 *	causes the string to be written out to terminal0.  After this is done
 *	the system shuts down with a panic message */
void adderrbuf(char *strp) {
    char *ep    = errbuf;
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

