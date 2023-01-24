//
// Created by Marco Coppola on 19/01/23.
//

#include "pcb.h"


static struct list_head *pcb_free;

void initPcbs(){

    //Initialize the list of free PCBs
    INIT_LIST_HEAD(pcb_free);

    //TODO: needs more stuff
}

void freePcb(pcb_t * p){

    //Check if pcb points to null
    if(p == NULL) //TODO: check if already in list
        return;

    //Add element in list of free pcbs
    list_add(&p->p_list, pcb_free);
}

pcb_t *allocPcb(){

    //Returns null if list is empty, otherwhise gets first element from list
    pcb_t* required = list_first_entry_or_null(pcb_free, pcb_t, p_list);

    //Remove from list if element is found
    if(required != NULL){
        list_del(&required->p_list);
    }

    return required; //TODO: check if needs cleaining before return
}
