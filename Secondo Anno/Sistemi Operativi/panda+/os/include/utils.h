#ifndef PHASE1_FILES_UTILS
#define PHASE1_FILES_UTILS

#define IE_C 0b10000000000000000000000000000000 //INTERRUPTS ENABLE (CURRENT) BIT
#define KME_C 0b01000000000000000000000000100000 //KERNEL MODE ENABLE (CURRENT) BIT

#define IE_P 0b00100000000000000000000000000000 //INTERRUPTS ENABLE (PREVIOUS) BIT
#define KME_P 0b00010000000000000000000000100000 //KERNEL MODE ENABLE (PREVIOUS) BIT

#define IE_ALL 0b00000000000000001111111100000000 //ENABLE ALL INTERRUPTS
#define LTE 0b00000000000000000000000000100000 //ENABLE LOCAL TIMER

#include "pandos_types.h"
#include "types.h"
#include "list.h"

//Initialize pcb by cleaning its parameters
pcb_t* initializePcb(pcb_t* pcb);

//Check if given list element pointer is inside list
int list_search_el(list_head* searchElement, list_head* list);

//Sets the namespace ns to the process p, both are expected as non-null
void set_namespace(pcb_t *p, nsd_t *ns);

void addokbuf(char *strp);
void adderrbuf(char *strp);
void setBitmaskAtIndex(unsigned int* number, int index, int value);

#endif 
