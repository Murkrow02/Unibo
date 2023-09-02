//
// Created by Marco Coppola on 19/01/23.
//

#ifndef PHASE1_FILES_NAMESPACE_H
#define PHASE1_FILES_NAMESPACE_H


#include <pandos_types.h>


// 19. Inizializza tutte le liste dei namespace liberi. Questo metodo viene invocato una volta sola durante l’inizializzazione della struttura dati.
void initNamespaces();

// 20. Ritorna il namespace di tipo type associato al processo p (o NULL)
nsd_t* getNamespace(pcb_t *p, int type);

// 21. Associa al processo p e a tutti I suoi figli il namespace ns. Ritorna FALSE in caso di errore, TRUE altrimenti.
int addNamespace(pcb_t *p, nsd_t *ns);

// 22. Alloca un namespace di tipo type dalla lista corretta.
nsd_t *allocNamespace(int type);

// 23. Libera il namespace ns ri-inserendolo nella lista di namespace corretta.
void freeNamespace(nsd_t *ns);

//Checks if the process p is in the default namespace (no namespace)
bool isInDefaultNamespace(pcb_PTR p);

//Sets the namespace ns to the process p, both are expected as non-null
void set_namespace(pcb_t *p, nsd_t *ns);


#endif //PHASE1_FILES_NAMESPACE_H
