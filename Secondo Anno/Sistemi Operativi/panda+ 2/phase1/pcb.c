//
// Created by Marco Coppola on 19/01/23.
//

#include <pcb.h>
#include <listx.h>
#include <pandos_types.h>
#include <stddef.h>
#include <utils.h>

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
    if (p == NULL) // TODO: check if already in list
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

    if (head != NULL && p != NULL)
    {

        // Add in last position, like a queue
        list_add_tail(&p->p_list, head);
    }
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

    pcb_t *el = container_of(head->next, pcb_t, p_list);
    list_del(&(el->p_list));
    return el;
}

// Like function above but search for p in any position
pcb_t *outProcQ(struct list_head *head, pcb_t *p)
{

    if (head == NULL || p == NULL || list_empty(head))
        return NULL;

    list_head *el;
    list_for_each(el, head)
    {
        // Check if currently pointed element is the same as p
        if (el == &p->p_list)
        {

            // Get container element
            pcb_t *target = container_of(el, pcb_t, p_list);

            // Remove element from list
            list_del(el);


            return target;
        }
    }

    

    // If we landed here then no element was found in the list
    return NULL;
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

    // Check that neither prnt nor p  is null
    if (prnt == NULL || p == NULL)
    {
        return;
    }

    // Copy namespaces from parent (MAYBE NOT REQUIRED)
    //    for(int i = 0; i < MAXPROC; i++){
    //        p->namespaces[i] =
    //    }

    // Add child to parent list
    list_add(&p->p_list, &prnt->p_child);

    // Update child pointer to parent
    p->p_parent = prnt;
}

pcb_t *removeChild(pcb_t *p)
{

    // Check that p is not pointing to NULL
    if (p == NULL)
        return NULL;

    // Check that list is not empty
    if (list_empty(&p->p_child))
        return NULL;

    // List not empty, retreive first child of p
    pcb_t *target = container_of(p->p_child.next, pcb_t, p_child);

    // Remove first child of p
    list_del(p->p_child.next);

    // List not empty, actually return item
    return target;
}

// Like function above but search for p in parent's child list
pcb_t *outChild(pcb_t *p)
{

    // Se il processo non ha padri la funzione termina subito
	if (p->p_parent == NULL)
		return NULL;
	// Lista dei processi attivi, da scorrere
	struct list_head *figlidelpadre = &(p->p_parent->p_child);
	pcb_PTR tmp = NULL;
	list_for_each_entry(tmp, figlidelpadre, p_sib)
	{
		if (p == tmp)
		{
			list_del(&(tmp->p_sib));
			tmp->p_parent = NULL;
			return p;
		}
	}
	return NULL;
    
}
