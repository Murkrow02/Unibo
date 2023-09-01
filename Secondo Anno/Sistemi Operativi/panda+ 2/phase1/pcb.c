//
// Created by Marco Coppola on 19/01/23.
//

#include <pcb.h>
#include <listx.h>
#include <pandos_types.h>
#include <stddef.h>
#include <utils.h>
#include <ns.h>

struct list_head pcb_free;
pcb_t pcb_table[MAXPROC];

// Used to assign a unique pid to each process
int lastInsertedPcbPid = 1;

void initPcbs()
{
    // Initialize the list of free PCBs
    INIT_LIST_HEAD(&pcb_free);

    // Copy elements from pcb table to list
    for (int i = 0; i < MAXPROC; i++)
    {
        list_add(&pcb_table[i].p_list, &pcb_free);
    }
}

void freePcb(pcb_t *p)
{
    // Check if pcb points to null
    if (p == NULL) 
        return;

    // Add element in list of free pcbs
    list_add(&p->p_list, &pcb_free);
}

pcb_t *initializePcb(pcb_t *pcb)
{
    if (pcb == NULL)
        return NULL;

    INIT_LIST_HEAD(&pcb->p_list);
    INIT_LIST_HEAD(&pcb->p_child);
    INIT_LIST_HEAD(&pcb->p_sib);

    // Empty list pointers
    pcb->p_list.prev = NULL;
    pcb->p_list.next = NULL;
    pcb->p_sib.prev = NULL;
    pcb->p_sib.next = NULL;

    pcb->p_parent = NULL;
    pcb->p_supportStruct = NULL;
    pcb->p_time = 0;
    pcb->p_semAdd = NULL;
    pcb->p_pid = lastInsertedPcbPid++;
    pcb->p_supportStruct = NULL;


    //Init namespaces
    for (int i = 0; i < NS_TYPE_MAX; i++)
    {
        pcb->namespaces[i] = NULL;
    }

    return pcb;
}

pcb_t *allocPcb()
{
    if (list_empty(&pcb_free))
        return NULL;

    // List is not empty, get first element
    pcb_t *firstElem = container_of(pcb_free.next, pcb_t, p_list);

    // Remove new pcb from free list
    list_del(pcb_free.next);

    // Init pcb before return
    return initializePcb(firstElem);
}

void mkEmptyProcQ(struct list_head *head)
{

    // If head is null do nothing
    if (head != NULL)
        INIT_LIST_HEAD(head);
}

int emptyProcQ(struct list_head *head)
{

    // If head is null we assume that is empty
    if (head == NULL)
        return 1;
    return list_empty(head);
}

void insertProcQ(struct list_head *head, pcb_t *p)
{

    if (p == NULL || head == NULL)
        return;

    //Prevent duplicates adding
    list_safe_del(&p->p_list);

    //Add element to the tail of the list
    list_add_tail(&p->p_list, head);
}

pcb_t *headProcQ(struct list_head *head)
{

    if (head == NULL || list_empty(head))
        return NULL;

    return container_of(head->next, pcb_t, p_list);
}

pcb_t *removeProcQ(struct list_head *head)
{

     if (head == NULL || list_empty(head))
        return NULL;

    /* get the first element of the list */
    list_head *to_remove = list_next(head);
    pcb_t *p = container_of(to_remove, pcb_t, p_list);

    /* return the pcb pointed by the deleted element */
    return outProcQ(head, p);
}


// Like function above but search for p in any position
pcb_t *outProcQ(struct list_head *head, pcb_t *p)
{
     if (head == NULL || p == NULL || list_empty(head) ||
        !list_contains(&p->p_list, head))
        return NULL;

    /* Remove p element from list */
    list_safe_del(&p->p_list);
    return p;
}

/*
 * ALBERI
 * */

int emptyChild(pcb_t *p)
{
    return list_empty(&p->p_child);
}

void insertChild(pcb_t *prnt, pcb_t *p)
{
    // Check if prnt or p are null or if already in child list
    if (prnt == NULL || p == NULL || p->p_parent != NULL ||
        list_contains(&p->p_sib, &prnt->p_child))
        return;

    // Add element to the tail of the list and set parent
    p->p_parent = prnt;
    list_add_tail(&p->p_sib, &prnt->p_child);
}

pcb_t *removeChild(pcb_t *p)
{

    if(list_empty(&p->p_child))
        return NULL;
    pcb_t *firstChild = container_of(p->p_child.next, pcb_t, p_sib);

    list_del(p->p_child.next);          /* Remove p's first child from p_child list and p_sib list */
    INIT_LIST_HEAD(&firstChild->p_sib); /* Initialize firstChild p_sib list as a empty list        */
    firstChild->p_parent = NULL;        /* FirstChild as no parent anymore                         */

    return firstChild;
}

// Like function above but search for p in parent's child list
pcb_t *outChild(pcb_t *p)
{
    if (p == NULL || p->p_parent == NULL || list_empty(&p->p_parent->p_child) ||
        !list_contains(&p->p_sib, &p->p_parent->p_child))
        return NULL;

    list_safe_del(&p->p_sib);
    p->p_parent = NULL;
    return p;
}

//Returns the size of the children list of same namespace of given process
//Adds the found matching processes into pids array
int getChildrenCount(pcb_t *p, nsd_t *ns, int *pids)
{
    //Check if p is null
    if (p == NULL)
        return -1;

    //Save here the number of children found (of same ns)
    int childrenCount = 0;

    // Cycle through all children of process p
    list_head *iterEl;
    list_for_each(iterEl, &p->p_child)
    {
        pcb_t *currentChild = container_of(iterEl, pcb_t, p_sib);
            
        //Requested to check children in default namespace (no namespace)
        if (ns == NULL && isInDefaultNamespace(currentChild))
        {
            //Found children in default namespace

            //Add pid to array if requested
            if (pids != NULL)
                pids[childrenCount] = currentChild->p_pid;
            childrenCount++;
        }
        else
        {
            //Requested to check children in a specific namespace
            if(getNamespace(currentChild, ns->n_type) == NULL)
                continue; //Not the namespace we interested in
 

            //Add pid to array if requested
            if (pids != NULL)
                pids[childrenCount] = currentChild->p_pid;
            childrenCount++;
        }
    }

    return childrenCount;
}
