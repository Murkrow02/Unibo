//
// Created by Marco Coppola on 27/01/23.
//

#include "pandos_types.h"
#include "types.h"

//Initialize pcb by cleaning its parameters
pcb_t* initializePcb(pcb_t* pcb){

    //TODO: Init other stuff

    //Initialize the namespaces of this PCB
    for(int i = 0; i < NS_TYPE_MAX; i++){
        pcb->namespaces[i] = NULL; //All NULL
    }

    return pcb;
}

//Check if given list element pointer is inside list
int list_search_el(list_head* searchElement, list_head* list){

    list_head* el;
    list_for_each(el, list){
        if(el == searchElement){

            //We found desired list_head element
            return true;
        }
    }

    //If we landed here we searched the whole list without success
    return false;
}

