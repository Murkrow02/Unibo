# Pandos+

##Compilazione
Lanciare all'interno della cartella principale (panda+) il seguente comando:
> make

<b>Nota</b>: il makefile é stato generato attraverso CMake, se si incontrano problemi durante la compilazione é necessario eseguire il comando
> cmake .

Per generare un nuovo makefile.


## Fase 1
### PCB (Process Control Block)
I PCB identificano i processi e le relative strutture dati ad essi associati all'interno del sistema operativo. I PCB sono organizzati in maniera gerarchica, ogni processo puó infatti creare piú sottoprocessi. Questi ultimi sono collegati al processo padre attraverso il puntatore `p_parent` e ai propri 'fratelli' attraverso il puntatore `p_sib`, creandone una lista concatenata.

Non ci sono notevoli scelte implementative da documentare in quanto in questa prima fase si chiedeva semplicemente di gestire le liste e alberi di PCB, quindi di inserire, rimuovere elementi all'interno di liste ed alberi.

### ASH (Active Semaphore Hash)
L'implementazione dei servizi dei semafori è data dalla necessità di mettere in pausa e poter riprendere l'esecuzione dei processi per permettere una corretta concorrenza di questi. Quando un processo viene bloccato da un semaforo esso viene inserito nella propria lista dei processi bloccati `s_procq`.

È stato necessario per il corretto funzionamento dei semafori implementare una tabella di hash che permette di accedere in modo rapido ai semafori attivi di cui abbiamo bisogno indicizzando questi ultimi con una chiave numerica `s_key`.

In generale i semafori all'avvio del sistema vengono trasferiti tutti dall'array `semd_table` contentente tutti i semafori alla lista `semdFree_h` contentente i semafori liberi. Quindi quando è richiesto l'utilizzo di un semaforo da un processo esso viene rimosso dai semafori liberi e aggiunto alla tabella di hash con una chiave identificativa.

A differenza dei dizionari, nelle tabelle hash non é possibile avere la certezza che ad una chiave corrisponda un unico oggetto, pertanto é stato necessario l'utilizzo della funzione di libreria `hash_for_each_possible` per controllare tutte le corrispondenze di una chiave e vedere quale fosse effettivamente il semaforo desiderato. Essendo questo controllo ricorrente ogni volta che abbiamo bisogno di accedere ad un semaforo specifico é in programma la generalizzazione di questo controllo per ritornare direttamente il semaforo desiderato attraverso la sua chiave.

###Namespace
Un namespace é un meccanismo che permette di organizzare diversi elementi all'interno del sistema operativo in modo da evitare conflitti tra di essi. 

In questa prima fase abbiamo un unico tipo di namespace, ovvero l' `NS_PID`, pertanto le funzioni implementate effettuano un semplice `switch` sul tipo di namespace richiesto per controllare se sia effettivamente `NS_PID` prima di effettuare le varie operazioni. In futuro, quando ci saranno piú tipi di namespace, é in programma di generalizzare queste implementazioni in modo tale da evitare codice ridondante.



