//
// Created by Marco Coppola on 19/01/23.
//

#include <ns.h>
#include <types.h>
#include <utils.h>
#include <pandos_types.h>
#include <listx.h>
#include <stddef.h>

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

nsd_t *getNamespace(pcb_t *p, int type)
{

    // Cycle through all the namespaces of the process
    for (int i = 0; i < NS_TYPE_MAX; i++)
    {

        //Empty namespace
        if (p->namespaces[i] == NULL)
            continue;

        // namespaces[i] is not null, check if is the same type as requested
        if (p->namespaces[i]->n_type == type)
        {
            return p->namespaces[i];
        }
    }
    return NULL;
}

//Check if all namespaces of a process are null ( == default namespace)
bool isInDefaultNamespace(pcb_PTR p){

    // Cycle through all the namespaces of the process
    for (int i = 0; i < NS_TYPE_MAX; i++)
    {

        //Empty namespace
        if (p->namespaces[i] == NULL)
            continue;

        //If found namespace != null then the process is not in the default namespace
        return false;
    }

    return true;
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
            return;
        }
    }
}


void freeNamespace(nsd_t *ns){
    
}
