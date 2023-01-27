//
// Created by Marco Coppola on 19/01/23.
//

#include "pcb.h"
#include "types.h"
#include "utils.c"

struct list_head *pcb_free;

void initPcbs() {

    //Initialize the list of free PCBs
    INIT_LIST_HEAD(pcb_free);

    //TODO: needs more stuff
}

void freePcb(pcb_t *p) {

    //Check if pcb points to null
    if (p == NULL) //TODO: check if already in list
        return;

    //Add element in list of free pcbs
    list_add(&p->p_list, pcb_free);
}

pcb_t *allocPcb() {

    //Returns null if list is empty, otherwise gets first element from list
    pcb_t *required =;

    //Remove from list if element is found
    if (required != NULL) {
        list_del(&required->p_list);
    }

    //Clean pcb before return
    return initializePcb(required);
}

void mkEmptyProcQ(struct list_head *head) {

    //If head is null do nothing
    if (head != NULL)
        INIT_LIST_HEAD(head);
}

int emptyProcQ(struct list_head *head) {

    //If head is null we assume that is empty
    if (head == NULL)
        return 1;
    return list_empty(head);
}

void insertProcQ(struct list_head *head, pcb_t *p) {

    if (head != NULL && p != NULL) {
        list_add(&p->p_list, head);
    }
}

//TODO: attenzione quando si inserisce un processo figlio fare attenzione ad aggiornare i suoi namespace come quelli del padre


