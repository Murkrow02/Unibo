![[Screenshot 2024-01-15 at 13.45.03.png]]

## Acid
- **Atomicità**: una transazione é un'operazione atomica, o viene eseguita del tutto o non viene eseguita nessuna. In un db non esiste mai uno stato dove una transazione é lasciata a metà
- **Consistenza**: tutte le transazioni devono preservare la consistenza del db, in particolare i constraint e i vincoli delle relazioni
- **Isolation**: ogni transazione deve apparire come eseguita come se non ci fosse nessun altra transazione in esecuzione in quel momento
- **Durability**: una volta che una transazione cambia il db e i cambiamenti sono committati, questi cambiamenti non dovranno mai essere persi per causa di altri fallimenti
## Schedule
- Seriale: per ogni transazione le operazioni sono eseguite tutte insieme, una transazione per volta
- Completa: include commit o abort per ogni transazione
- Serializzabile: l'effetto sul db é garantito essere identico ad una qualsiasi transazione seriale e completa
## Deadlock prevention
Utilizzando i lucchetti possiamo arrivare a possibili deadlock, che bisognano essere evitati o risolti dal DBMS.
- Di solito il DBMS assegna una priorità ad ogni transazione, assegnata da quando é partita quella transazione
- Se una nuova transazione richiede un lucchetto richiesto in precedenza da un altra, possono avvenire due situazioni:
	- **Wait-die**: se la nuova richiedente é piú vecchia allora aspetta, altrimenti é uccisa e ricominciata piu tardi con un delay
	- **Wound-wait**: se la vecchia transazione ha il lucchetto allora la nuova é uccisa e
- Se i deadlock sono rari, un DBMS permette che avvengano e li risolve quando accadono invece di adottare delle pratiche 
	- Ad esempio se una transazione é bloccata da troppo tempo si assume deadlock e la si interrompe
	- Oppure si puo mantenere una struttura chiamata **wait for graph** che identifica i cicli di deadlock, il grafo é analizzato periodicamente e i deadlock sono risolti abortendo qualche transazione

## Crash recovery
Un sistema di crash recovery deve assicurare:
- Atomicità: le operazioni performate da transazioni non-committed devono essere reversate
- Persistenza: le operazioni dopo il commit devono sopravvivere anche a crash del sistema
### ARIES
- Advanced Recovery and Integrated Extraction System 
	- Algoritmo di recupero che gestisce logging e recovery manager
- Usato da IBM DB2, SQL Server...
 - 3 fasi:
	 - Analisi: identifica le pagine sporche dal buffer (non scritte sul disco) e le transazioni attive al momento del crash
	 - Redo: a partire da un checkpoint del file di log, ripete tutte le operazioni e porta il db indietro al momento prima del crash
	 - Undo: cancella le operazioni di transazioni attive durante il crash ma non committate
 - Principi:
	- Write-ahead logging:
		- ogni cambiamento al db va prima nel log e poi nelle tabelle
		- Il file di log deve essere su memoria secondaria 
			- Infine il dato viene modificato
	- Repeating history during redo
		- Al riavvio dopo un crash il sistema é portato indietro allo stato dov'era prima del crash
		- Le operazioni di transazioni attive vengono cancellate
	- Logging changes during undo
		- Anche le operazioni fatte al db durante la recovery sono registrate per assicurare persistenza anche dopo ulteriori crash
## Il file di log
-  Tiene traccia di tutte le azioni fatte al DBMS
- Organizzato in record nella memoria secondaria
- La parte finale (tail) é anche in memoria primaria 
- Viene aggiornato ogni
	- Aggiornamento di pagina: un record deve essere scritto in memoria secondaria dopo che in memoria primaria viene caricata un altra pagina
	- Commit: transazione successo
	- Abort: transazione fallimento
	- End: finalizzazione dopo una transazione
	- Undo: durante un recupero e durante operazione di undo

## Checkpoint
Snapshot dello stato del db. Riducono il tempo di recupero
