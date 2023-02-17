//
// Created by Marco Coppola on 27/01/23.
//


#include "pandos_types.h"


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

