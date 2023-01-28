//
// Created by Marco Coppola on 19/01/23.
//

#include "namespace.h"
#include "types.h"
#include "utils.h"

//
nsd_t pid_nsTable[MAXPROC];

//Free or non-used namespaces
static list_head pid_nsFree_h;

//Active namespaces
static list_head pid_nsList_h;

//TODO: when a new namespace is added, make sure to duplicate lists above

void initNamespaces(){

    //Initialize lists
    INIT_LIST_HEAD(&pid_nsFree_h);
    INIT_LIST_HEAD(&pid_nsList_h);

    //Add elements from table to non-used namespaces
    for (int i = 0; i < NS_TYPE_MAX; i++) {
        list_add(&pid_nsTable[i].n_link, &pid_nsFree_h);
    }
}

nsd_t* getNamespace(pcb_t *p, int type){

    switch (type) {

        //TODO: generalize when more namespaces are added
        case NS_PID:

            //Cycle through all the namespaces of the process
            for(int i = 0; i < NS_TYPE_MAX; i++){

                //Assume that the array is always full, but when a cell is empty (without namespace), a NULL pointer is placed instead
                if(p->namespaces[i] == NULL)
                    continue; //Check the next one, this one is free

                //namespaces[i] is not null, check if is the same type as requested
                if(p->namespaces[i]->n_type == type){

                    //Namespace of the process is as the same type as requested, check if the namespace is active
                   // int activeNamespace = list_search_el(&pid_nsList_h, &p->namespaces[i]->n_link);

                    //The namespace linked to the process is still valid
                    //if(activeNamespace){
                        return p->namespaces[i];
                   // }else{

                        //The namespace linked to the process is no longer valid
                   //     p->namespaces[i] = NULL; //We can safely
                    //}

                }

                //If we landed here then the namespace found is not as the same type as requested
            }
            break;

        default:

            //Namespace type not recognized
            return NULL;
    }

    //If we landed here, no namespace of requested type was found
    return NULL;
}

int addNamespace(pcb_t *p, nsd_t *ns){

    //Check if params are null
    if(p == NULL || ns == NULL){
        return false;
    }

    //Detect namespace type
    switch (ns->n_type) {


        case NS_PID:

            //Set namespace to himself
            set_namespace(p,ns);

            //Set namespace to all children
            if(!list_empty(&p->p_child)){
                
                //Cycle through all children
                list_head* iterEl;
                list_for_each(iterEl, &p->p_child){
                    pcb_t *currentChild = container_of(iterEl, pcb_t, p_list);
                    set_namespace(currentChild,ns);
                }
            }

            //Set namespace to parent
            if(p->p_parent != NULL){
                set_namespace(p->p_parent,ns);
            }
            
            return true;
        break;

        default:
            return false;
    }

    //If we reached this point then probably the process had not available space for a new namespace
    return false;
}

nsd_t *allocNamespace(int type){

    switch (type) {
        case NS_PID:

            //Check if there are available namespaces to alloc
            if(list_empty(&pid_nsFree_h))
            {
                //No more available namespaces
                return NULL;
            }

            //List is not empty, we can take the first element of the list
            list_head* firstFreeElem = pid_nsFree_h.next;

            //Add new element to allocated namespaces list (this should automatically remove the element from the free list)
            list_add(firstFreeElem, &pid_nsList_h);

            //Return namespace
            return container_of(firstFreeElem, nsd_t, n_link);

            break;

        default:
            return NULL;
    }
}

void freeNamespace(nsd_t *ns){
    //TODO: implement this function even if not called by the phase1 test
}
