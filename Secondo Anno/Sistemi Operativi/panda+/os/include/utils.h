#ifndef PHASE1_FILES_UTILS
#define PHASE1_FILES_UTILS

#include "pandos_types.h"
#include "types.h"
#include "list.h"

//Initialize pcb by cleaning its parameters
pcb_t* initializePcb(pcb_t* pcb);

//Check if given list element pointer is inside list
int list_search_el(list_head* searchElement, list_head* list);

//Sets the namespace ns to the process p, both are expected as non-null
void set_namespace(pcb_t *p, nsd_t *ns);

#endif 
