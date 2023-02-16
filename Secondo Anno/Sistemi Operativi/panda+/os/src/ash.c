//
// Created by Marco Coppola on 19/01/23.
//

#ifndef PHASE1_FILES_ASH_H
#define PHASE1_FILES_ASH_H

#include "pandos_types.h"
#include "ash.h"
#include "hashtable.h"
#include "list.h"

// array di SEMD con dimensione massima di MAX_PROC.
struct semd_t semd_table[MAXPROC];
// Lista dei SEMD liberi o inutilizzati.
struct list_head semdFree_h;
// Hash dei semafori attivi
struct hlist_head semd_h;

DEFINE_HASHTABLE(sem_hash, 10);
//DECLARE_HASHTABLE(sem_hash, 2048);

// 14. Viene inserito il PCB puntato da p nella coda dei processi bloccati associata al SEMD con chiave semAdd.
// Se il semaforo corrispondente non è presente nella ASH, alloca un nuovo SEMD dalla lista di quelli liberi (semdFree) e lo inserisce nella ASH,
// settando I campi in maniera opportuna (i.e. key e s_procQ). Se non è possibile allocare un nuovo SEMD perché la lista di quelli liberi è vuota,
// restituisce TRUE. In tutti gli altri casi, restituisce FALSE.
int insertBlocked(int *semAdd, pcb_t *p) {

    //Semaforo associato alla chiave semAdd
    semd_t ASSSEM = semd_table[*semAdd];

    //Controllo se la tabella di hash non contiene il semaforo
    if(!hash_hashed(&ASSSEM.s_link))
    {
        //Controllo se la lista dei semafori liberi è vuota
        if (list_empty(&semdFree_h) == 1)
        {
            return TRUE;
        }

        //Alloco un nuovo semd dalla lista di quelli liberi //TODO CONTROLLA NON SO SE VA BENE
        list_del(&ASSSEM.s_freelink);

        //Aggiungo il semaforo alla hashtable
        hash_add(sem_hash, &ASSSEM.s_link, *ASSSEM.s_key);
    }

    //Aggiungo il PCB alla lista dei processi bloccati
    list_add_tail(&p->p_list, &ASSSEM.s_procq);

    return FALSE;
}

// 15. Ritorna il primo PCB dalla coda dei processi bloccati (s_procq) associata al SEMD della ASH con chiave semAdd. Se tale descrittore non esiste nella ASH, restituisce NULL.
// Altrimenti, restituisce l’elemento rimosso. Se la coda dei processi bloccati per il semaforo diventa vuota, rimuove il descrittore
// corrispondente dalla ASH e lo inserisce nella coda dei descrittori liberi (semdFree_h).
pcb_t* removeBlocked(int *semAdd) {
    //Semaforo associato alla chiave
    semd_t ASSSEM = semd_table[*semAdd];

    //Controllo se la tabella di hash non contiene il semaforo
    if(!hash_hashed(&ASSSEM.s_link))
    {
        return NULL;
    }

    //Salvo il PCB da ritornare
    pcb_t* returnPCB = container_of(&ASSSEM.s_procq, pcb_t, p_list);

    //Rimuovo il PCB in testa alla lista
    list_del(&ASSSEM.s_procq);

    //Controllo se la lista dei processi bloccati è vuota
    if (list_empty(&ASSSEM.s_procq) == 1) {

        //Rimuovo l'hash del semaforo dagli hash attivi
        hash_del(&ASSSEM.s_link);

        //Aggiungo il semaforo tra i semafori liberi
        list_add_tail(&ASSSEM.s_freelink, &semdFree_h);
    }

    return returnPCB;

}

// 16. Rimuove il PCB puntato da p dalla coda del semaforo su cui è bloccato (indicato da p->p_semAdd).
// Se il PCB non compare in tale coda, allora restituisce NULL (condizione di errore). Altrimenti, restituisce p.
// Se la coda dei processi bloccati per il semaforo diventa vuota, rimuove il descrittore corrispondente dalla ASH
// e lo inserisce nella coda dei descrittori liberi
pcb_t* outBlocked(pcb_t *p) {

    //Semaforo associato al pcb p
    semd_t ASSSEM = semd_table[*p->p_semAdd];

    //Prendo primo elemento della lista
    struct list_head* headBlocked = &ASSSEM.s_procq;

    //inizializzo la head mobile
    struct list_head* head = headBlocked;

    //Scorro la lista e controllo di non essere arrivato alla fine
    while(list_is_last(head, headBlocked) == 0) {

        //Controllo che il processo da sbloccare sia p
        if (head == &p->p_list) {

            //Rimuovo p dalla lista dei processi bloccati
            list_del(head);

            //Controllo se la lista dei bloccati ora è vuota
            if (list_empty(headBlocked) == 1) {

                //Rimuovo l'hash del semaforo dagli hash attivi
                hash_del(&ASSSEM.s_link);

                //Aggiungo il semaforo tra i semafori liberi
                list_add_tail(&ASSSEM.s_freelink, &semdFree_h);
            }
            return p;
        }

        //Il processo in analisi non è p quindi scorro
        head = list_next(head);
    }

    //Se p non è nella coda dei bloccati ritorno null -> ERRORE
    return NULL;
}

// 17. Restituisce (senza rimuovere) il puntatore al PCB che si trova in testa alla coda dei processi associata al SEMD con chiave semAdd.
// Ritorna NULL se il SEMD non compare nella ASH oppure se compare ma la sua coda dei processi è vuota.
pcb_t* headBlocked(int *semAdd) {

    //Semaforo associato a semAdd
    semd_t ASSSEM = semd_table[*semAdd];

    //Controllo se la tabella di hash non contiene il semaforo
    if(!hash_hashed(&ASSSEM.s_link)) {
        return NULL;
    }
    //Controllo se la coda di processi bloccati è vuota
    if (list_empty(&ASSSEM.s_procq) == 1) {
        return NULL;
    }

    return (container_of(&ASSSEM.s_procq, pcb_t, p_list));
}

// 18. Inizializza la lista dei semdFree in modo da contenere tutti gli elementi della semdTable.
// Questo metodo viene invocato una volta sola durante l’inizializzazione della struttura dati.
void initASH() {

    //DEFINE_HASHTABLE(sem_hash, 10);
    
    //hash_init(semd_h);

    //Prendo il primo semaforo da maxproc per inizializzare una testa
    semdFree_h = semd_table[0].s_freelink;

    //Inizializziamo una nuova lista con la list-head che abbiamo preso dalla tabella
    INIT_LIST_HEAD(&semdFree_h);

    //Aggiungiamo in coda alla lista dei semafori liberi tutti i semafori restanti nella tabella
    for (int i = 1; i < MAXPROC; ++i) {
        list_add_tail(&semd_table[i].s_freelink, &semdFree_h);
    }
}

#endif //PHASE1_FILES_ASH_H
