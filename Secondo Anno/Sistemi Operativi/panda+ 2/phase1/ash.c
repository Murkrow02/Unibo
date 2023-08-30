#ifndef PHASE1_FILES_ASH_H
#define PHASE1_FILES_ASH_H


#include <hashtable.h>
#include <ash.h>
#include <types.h>
#include <utils.h>
#include <listx.h>
#include <pandos_types.h>
#include <stddef.h>


// array di SEMD con dimensione massima di MAX_PROC.
struct semd_t semd_table[MAXPROC];

// Lista dei SEMD liberi o inutilizzati.
struct list_head semdFree_h;

DEFINE_HASHTABLE(semd_h, 10);


//DECLARE_HASHTABLE(sem_hash, 2048);

// 14. Viene inserito il PCB puntato da p nella coda dei processi bloccati associata al SEMD con chiave semAdd.
// Se il semaforo corrispondente non è presente nella ASH, alloca un nuovo SEMD dalla lista di quelli liberi (semdFree) e lo inserisce nella ASH,
// settando I campi in maniera opportuna (i.e. key e s_procQ). Se non è possibile allocare un nuovo SEMD perché la lista di quelli liberi è vuota,
// restituisce TRUE. In tutti gli altri casi, restituisce FALSE.

int insertBlocked(int *semAdd, pcb_t *p) {

    struct semd_t* ASSSEM;
    hash_for_each_possible(semd_h, ASSSEM, s_link, semAdd){
      
      //Controlla se il semd_t e' quello che cerchiamo
      if(ASSSEM != NULL && *ASSSEM->s_key == *semAdd){
      
        //Aggiungo il PCB alla lista dei processi bloccati
        list_add_tail(&p->p_list, &ASSSEM->s_procq);
        
        //Aggiungo al processo il suo semaforo dove e bloccato
        p->p_semAdd = semAdd;

        return FALSE;
      }
    }
    
    //Controlla se ci sono abbastanza semafori liberi
    if(list_empty(&semdFree_h)){
      return TRUE; //Non ce ne sono
    }
    
    //Prendi il primo semaforo libero
    semd_t* firstFreeSem = container_of(semdFree_h.next, semd_t, s_freelink);
    if(firstFreeSem == NULL){
      return TRUE; //Non ce ne sono
    }
    
    //Aggiungo al processo il suo semaforo dove e bloccato
    p->p_semAdd = semAdd;
    
    //Inizializzo la lista dei processi bloccati del nuovo semaforo
    INIT_LIST_HEAD(&firstFreeSem->s_procq);
    
    //Assegno la chiave semAdd al nuovo semaforo
    firstFreeSem->s_key = semAdd;
    
    //Aggiungo il PCB alla lista dei processi bloccati
    list_add(&p->p_list, &firstFreeSem->s_procq);
    
    //Elimino il nuovo semaforo da quelli liberi
    list_del(semdFree_h.next);
        
    //Aggiungo il semaforo alla hashtable
    hash_add(semd_h, &firstFreeSem->s_link, semAdd);//*firstFreeSem->s_key);

    return FALSE;
}

// 15. Ritorna il primo PCB dalla coda dei processi bloccati (s_procq) associata al SEMD della ASH con chiave semAdd. Se tale descrittore non esiste nella ASH, restituisce NULL.
// Altrimenti, restituisce l’elemento rimosso. Se la coda dei processi bloccati per il semaforo diventa vuota, rimuove il descrittore
// corrispondente dalla ASH e lo inserisce nella coda dei descrittori liberi (semdFree_h).
pcb_t* removeBlocked(int *semAdd) {
 
    struct semd_t* ASSSEM;
    hash_for_each_possible(semd_h, ASSSEM, s_link, semAdd){
 
      //Controlla se il semd_t e' quello che cerchiamo
      if(ASSSEM != NULL && *ASSSEM->s_key == *semAdd){
 
        //PCB da ritornare
        pcb_t* tmp = list_first_entry(&ASSSEM->s_procq, pcb_t, p_list);
 
        //Rimuovo il processo dalla lista dei processi bloccati
        list_del(&tmp->p_list);
 
        //Conntrollo se la lista dei processi bloccati è ora vuota
        if (list_empty(&ASSSEM->s_procq) == TRUE) {
            //Rimuovo l'hash del semaforo dagli hash attivi
            hash_del(&ASSSEM->s_link);
 
            //Aggiungo il semaforo tra i semafori liberi
            list_add(&ASSSEM->s_freelink, &semdFree_h);
 
            //TODO secondo te qua bisogna eliminare la lista dei processi bloccati e la chiave?
        }
        return tmp;
      }
 
    }
 
    return NULL;
 
 
}
 
 
 
int countBlocked(int *semAdd) {
 
    struct semd_t* ASSSEM;
    hash_for_each_possible(semd_h, ASSSEM, s_link, semAdd){
 
      //Controlla se il semd_t e' quello che cerchiamo
      if(ASSSEM != NULL && *ASSSEM->s_key == *semAdd){
 
        pcb_t* tmp = NULL;
        int count = 0;
        list_for_each_entry(tmp, &ASSSEM->s_procq, p_list)
        {
            count++;
        }
        return count;
      }
 
    }
 
    return 0;
}

// 16. Rimuove il PCB puntato da p dalla coda del semaforo su cui è bloccato (indicato da p->p_semAdd).
// Se il PCB non compare in tale coda, allora restituisce NULL (condizione di errore). Altrimenti, restituisce p.
// Se la coda dei processi bloccati per il semaforo diventa vuota, rimuove il descrittore corrispondente dalla ASH
// e lo inserisce nella coda dei descrittori liberi
pcb_t* outBlocked(pcb_t *p) {

    //Semaforo associato al pcb p
    struct semd_t* ASSSEM;
    hash_for_each_possible(semd_h, ASSSEM, s_link, p->p_semAdd){
    
        //Controlla se il semd_t e' quello che cerchiamo

        if(ASSSEM != NULL && *ASSSEM->s_key == *p->p_semAdd){

            list_head* el;
            //Cerco il pcb p nella lista dei bloccati
            list_for_each(el, &ASSSEM->s_procq) {
            

                //Check if currently pointed element is the same as p
                if(el == &p->p_list){
                
                    //Rimuovo p dalla lista dei processi bloccati
                    list_del(el);

                    //Conntrollo se la lista dei processi bloccati è ora vuota
                    if (list_empty(&ASSSEM->s_procq) == TRUE) {
                        //Rimuovo l'hash del semaforo dagli hash attivi
                        hash_del(&ASSSEM->s_link);

                        //Aggiungo il semaforo tra i semafori liberi
                        list_add(&ASSSEM->s_freelink, &semdFree_h);

                        //TODO secondo te qua bisogna eliminare la lista dei processi bloccati e la chiave?
                    }
                    return p;
                }
            }
        }
    }

    //Se il processo non viene trovato tra i bloccati -> ERRORE

    return NULL;
}

// 17. Restituisce (senza rimuovere) il puntatore al PCB che si trova in testa alla coda dei processi associata al SEMD con chiave semAdd.
// Ritorna NULL se il SEMD non compare nella ASH oppure se compare ma la sua coda dei processi è vuota.
pcb_t* headBlocked(int *semAdd) {

    struct semd_t* ASSSEM;
    hash_for_each_possible(semd_h, ASSSEM, s_link, semAdd){
      
      //Controlla se il semd_t e' quello che cerchiamo
      if(ASSSEM != NULL && *ASSSEM->s_key == *semAdd){
      
        if (list_empty(&ASSSEM->s_procq))
        {
            return NULL;
        }
      
        //PCB da ritornare
        return list_first_entry(&ASSSEM->s_procq, pcb_t, p_list);
      }
      
    }
    

    return NULL;
}

// 18. Inizializza la lista dei semdFree in modo da contenere tutti gli elementi della semdTable.
// Questo metodo viene invocato una volta sola durante l’inizializzazione della struttura dati.
void initASH() {

    //Inizializziamo una nuova lista con la list-head che abbiamo preso dalla tabella
    INIT_LIST_HEAD(&semdFree_h);
  
    //Move elements from semd table to list
    for (int i = 0; i < MAXPROC; i++) {
        list_add(&semd_table[i].s_freelink, &semdFree_h);
    }
}

#endif //PHASE1_FILES_ASH_H
