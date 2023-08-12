#ifndef PHASE1_FILES_UTILS
#define PHASE1_FILES_UTILS


#define KME_C  0b00000000000000000000000000000010 //KERNEL MODE ENABLE (CURRENT) BIT
#define KMEPON 0b00000000000000000000000000001000 //KERNEL MODE ENABLE (PREVIOUS) BIT

#define CPU_STATE ((state_t *)BIOSDATAPAGE) //Current state of the processor
#define CPU_STATUS CPU_STATE->status //Current status of the processor
#define CPU_CAUSE CPU_STATE->cause //Current cause of the processor

#define PC_INC CPU_STATE->pc_epc += WORDLEN; CPU_STATE->reg_t9 += WORDLEN;

#include "pandos_types.h"
#include "types.h"
#include "list.h"

#define PROCESSOR_SAVED_STATE ((state_t *)BIOSDATAPAGE)
// Macro per reg_a0 in SavedStatus(BIOSDATAPAGE) che contiene il syscallCode.
#define REG_A0_SS PROCESSOR_SAVED_STATE->reg_a0
// Macro per reg_a1 in SavedStatus(BIOSDATAPAGE) che contiene il 1° parametro da passare alla syscall.
#define REG_A1_SS PROCESSOR_SAVED_STATE->reg_a1
// Macro per reg_a2 in SavedStatus(BIOSDATAPAGE) che contiene il 2° parametro da passare alla syscall.
#define REG_A2_SS PROCESSOR_SAVED_STATE->reg_a2
// Macro per reg_a3 in SavedStatus(BIOSDATAPAGE) che contiene il 3° parametro da passare alla syscall.
#define REG_A3_SS PROCESSOR_SAVED_STATE->reg_a3

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
