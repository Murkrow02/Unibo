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



static inline const list_head *
list_search(const list_head *element, const list_head *head,
            int (*cmp)(const list_head *, const list_head *))
{
    const list_head *iter;

    for (iter = head->next; iter != head; iter = iter->next)
        if (!cmp(element, iter))
            return iter;
    return NULL;
}
static inline int exact_cmp(const list_head *first, const list_head *second)
{
    return first != second;
}
static inline bool list_contains(const list_head *element,
                                 const list_head *head)
{
    return list_search(element, head, exact_cmp) != NULL;
}
#define LIST_HEAD_NULL(l) ((l)->prev = (l)->next = NULL)
static inline int list_null(const list_head *head)
{
    return head->prev == NULL && head->next == NULL;
}

static inline void list_sdel(list_head *entry)
{
    if (!list_null(entry)) {
        list_del(entry);
        LIST_HEAD_NULL(entry);
    }
}


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

    if (p == NULL || head == NULL)
        return;
    list_sdel(&p->p_list);
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
    list_sdel(&p->p_list);
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

    if (prnt == NULL || p == NULL || p->p_parent != NULL ||
        list_contains(&p->p_sib, &prnt->p_child))
        return;

    p->p_parent = prnt;
    list_add_tail(&p->p_sib, &prnt->p_child);
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
    if (p == NULL || p->p_parent == NULL || list_empty(&p->p_parent->p_child) ||
        !list_contains(&p->p_sib, &p->p_parent->p_child))
        return NULL;

    list_sdel(&p->p_sib);
    p->p_parent = NULL;
    return p;
}
