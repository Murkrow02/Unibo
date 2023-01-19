//
// Created by Marco Coppola on 19/01/23.
//

#ifndef PHASE1_FILES_ASH_UTILS_H
#define PHASE1_FILES_ASH_UTILS_H

#include "pandos_types.h"

// 14. Viene inserito il PCB puntato da p nella coda dei processi bloccati associata al SEMD con chiave semAdd.
// Se il semaforo corrispondente non è presente nella ASH, alloca un nuovo SEMD dalla lista di quelli liberi (semdFree) e lo inserisce nella ASH,
// settando I campi in maniera opportuna (i.e. key e s_procQ). Se non è possibile allocare un nuovo SEMD perché la lista di quelli liberi è vuota,
// restituisce TRUE. In tutti gli altri casi, restituisce FALSE.
int insertBlocked(int *semAdd, pcb_t *p);

// 15. Ritorna il primo PCB dalla coda dei processi bloccati (s_procq) associata al SEMD della ASH con chiave semAdd. Se tale descrittore non esiste nella ASH, restituisce NULL.
// Altrimenti, restituisce l’elemento rimosso. Se la coda dei processi bloccati per il semaforo diventa vuota, rimuove il descrittore
// corrispondente dalla ASH e lo inserisce nella coda dei descrittori liberi (semdFree_h).
pcb_t* removeBlocked(int *semAdd);

// 16. Rimuove il PCB puntato da p dalla coda del semaforo su cui è bloccato (indicato da p->p_semAdd).
// Se il PCB non compare in tale coda, allora restituisce NULL (condizione di errore). Altrimenti, restituisce p.
// Se la coda dei processi bloccati per il semaforo diventa vuota, rimuove il descrittore corrispondente dalla ASH
// e lo inserisce nella coda dei descrittori liberi
pcb_t* outBlocked(pcb_t *p);

// 17. Restituisce (senza rimuovere) il puntatore al PCB che si trova in testa alla coda dei processi associata al SEMD con chiave semAdd.
// Ritorna NULL se il SEMD non compare nella ASH oppure se compare ma la sua coda dei processi è vuota.
pcb_t* headBlocked(int *semAdd);

// 18. Inizializza la lista dei semdFree in modo da contenere tutti gli elementi della semdTable.
// Questo metodo viene invocato una volta sola durante l’inizializzazione della struttura dati.
void initASH();

#endif //PHASE1_FILES_ASH_UTILS_H
