#ifndef PHASE1_FILES_UTILS
#define PHASE1_FILES_UTILS


#define KME_C  0b00000000000000000000000000000010 //KERNEL MODE ENABLE (CURRENT) BIT
#define KMEPON 0b00000000000000000000000000001000 //KERNEL MODE ENABLE (PREVIOUS) BIT

#define CPU_STATE ((state_t *)BIOSDATAPAGE) //Current state of the processor
#define CPU_STATUS CPU_STATE->status //Current status of the processor
#define CPU_CAUSE CPU_STATE->cause //Current cause of the processor
#define PC_INCREMENT CPU_STATE->pc_epc +=WORDLEN; //Increment the program counter of the running process

// Macro per reg_a0 in SavedStatus(BIOSDATAPAGE) che contiene il syscallCode.
#define REG_A0_SS CPU_STATE->reg_a0
// Macro per reg_a1 in SavedStatus(BIOSDATAPAGE) che contiene il 1° parametro da passare alla syscall.
#define REG_A1_SS CPU_STATE->reg_a1
// Macro per reg_a2 in SavedStatus(BIOSDATAPAGE) che contiene il 2° parametro da passare alla syscall.
#define REG_A2_SS CPU_STATE->reg_a2
// Macro per reg_a3 in SavedStatus(BIOSDATAPAGE) che contiene il 3° parametro da passare alla syscall.
#define REG_A3_SS CPU_STATE->reg_a3


#define MAX_TERM_DEV 8 //Max number of terminal devices
#define TERM0ADDR   0x10000254
#define LAST_TERM_ADDR (TERM0ADDR + (MAX_TERM_DEV * DEVREGSIZE))-1

#include <listx.h>
#include <types.h>
#include <pandos_types.h>

//Copies the state of the running process to another state_t
void saveStateTo(state_t *dest);

//Copies the state of a process to another
void copyState(state_t *original, state_t *dest);

// Function to extract only the desired bits from an integer
int extractBits(int num, int start, int end);

//Copies a string from src to dest
void strcopy(char *dest, char *src, int len);

//Check if given list element pointer is inside list
int list_search_el(list_head* searchElement, list_head* list);

int isDeviceSem(int *sem);


void addokbuf(char *strp);
void adderrbuf(char *strp);
void setBitmaskAtIndex(unsigned int* number, int index, int value);


#define CAUSE_GET_EXCCODE(x)   (((x) & CAUSE_EXCCODE_MASK) >> CAUSE_EXCCODE_BIT)                                                                                                                                    ;if(p5MemLocation == KUSEG){exCode = 3;p5MemLocation = NULL;}



#endif 
