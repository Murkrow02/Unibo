Un indice é una struttura dati che supporta un accesso molto efficiente ai dati correlati
- La chiave di ricerca é definita usando degli attributi
	- Le chiavi di ricerca non sono chiavi primario, questo significa che la stessa chiave di ricerca può immagazzinare valori duplicati
- Un indice é una coppia $<chiave, label>$ e supporta un efficiente ricerca di tutte le label aventi una chiave $K$
- La parte di sinistra é detta chiave di ricerca
- La parte di destra é detta index record 
## Labels
Le label possono essere 
- I record di dati
	- ![[Pasted image 20240114170706.png]]
	- Possiamo avere al massimo un indice utilizzando questa rappresentazione
	- La grandezza dell'indice é uguale a quella dei record dati
  - Gli identificatori dei record **RID** con chiave $K$
	- ![[Screenshot 2024-01-14 at 17.07.41.png]]
	  - La stessa chiave puo avere diversi valori
-  Una lista di RID
	  - ![[Screenshot 2024-01-14 at 17.08.17.png]]
	- Soluzione piú compatta ma le label hanno grandezza variabile
## Tipi di indici
- Primario
	- Indice su un set di attributi che include la chiave primaria e i dati ordinati sugli stessi attributi, altrimenti l'indice é detto secondario
- Denso
	- Esiste un record per ogni chiave di ricerca dell'indice
	- Dà accesso immediato a tutti i record del dataset
	- Utile per piccoli set di dati
	- Richiede tanto spazio per grandi set di dati
	- Inserimenti e rimozioni possono essere piu pesanti in quanto l'indice ha bisogno di essere aggiornato piu spesso
- Sparso
	- Non é detto che tutti i record siano puntati da un indice
	- Questo ad esempio puo essere usato per creare indici solo su particolari condizioni
- Clustered
	- L'ordine dei record segue quello delle label
- Unclustered
	- L'ordine dei record non segue quello delle label

## Tabelle hash per indicizzare
- Le tabelle hash sono molto efficienti per l'equity search
	- Riescono in O(1) a darci una corrispondenza
- Sono invece meno efficienti per range search

### Static hasing
- Si usano $N$ buckets e una funzione di hashing che mappa la chiave di ricerca in un range da $0$ a $N-1$
- Se un record ha una chiave $K$ allora lo salviamo nel bucket con numero $H(K)$
- In questo tipo di hashing **non é possibile aggiungere nuovi bucket**, pertanto nell'inserimento di un nuovo record in un determinato bucket, se quest ultimo é pieno allora bisogna aggiungere un nuovo blocco di overflow
- Durante l'eliminazione, se abbiamo tanti blocchi in overflow potremmo dover rispostare tutti questi e quindi avremmo un degradamento delle performance
### Extendible hashing
- Non usa blocchi di overflow
- Ogni volta che non c'é spazio, si raddoppia la lunghezza della directory
- La funzione di hash ritorna i primi $i$ bits dalla search key
- Ogni blocco ha una variabile che indica quanti bit sono usati per indexarlo
- Riusciamo a mantenere l'indice in memoria e a trovare il record associato in un solo accesso al disco
- Splittare i record é lineare
- La directory cresce in maniera esponenziale
#### Inserimento
- Se facendo l hash, otteniamo un blocco con spazio libero lo inseriamo
- Altrimenti
	- Se il blocco é stato indexato con meno bit di quanti sono usati nella directory allora lo dividiamo in 2 
	- Se il blocco ha lo stesso numero allora dobbiamo raddoppiare la directory e aggiungere un bit all'encoding della chiave
### Linear hashing
- Risolve il problema della crescita smisurata della directory dell'extendible hashing
- Risolve il problema di lunghe catene di blocchi di overflow
	- Tuttavia permette la presenza di blocchi di overflow
- Il numero di bucket cresce in maniera lineare e non esponenziale
	- Cresce di 1 ogni volta
- L'indicatore principale é il record-bucket ratio, che rappresenta il fattore di load
	- Dobbiamo scegliere il numero di bucket $n$ tale che non ci sono piú di $1.7*n$ record nel file
### Ricerca 
- Facciamo l'hash della chiave
- Se il bucket risultante esiste (minore del bucket massimo) allora cerchiamo all'interno di quel bucket $m$
- Se il bucket non esiste allora andiamo al bucket $m-2^{i-1}$
### Inserimento
- Contiamo il numero di record $r$ e il numero di buckets $n$
- Se il ratio $r/n$ sorpassa 1.7 allora splittiamo un bucket aggiungendone uno nuovo
- Se il numero di bucket $n$ é uguale a $2^i$ (bit della chiave) allora lo incrementiamo
	- Ancora piú semplice, se la chiave dei bucket non riesce a indexare tutti i bucket allora aggiungiamo un bit
	- 
## Document retrieval e inverted indexes
- Problema: riuscire a trovare il testo che contiene delle parole chiave
- Possiamo utilizzare indici per recuperare i documenti contenenti quel testo
## Achievement
Siamo interessati in:
- Ritornare tutti i documenti che contengono un set di parole chiave ($K_1,... K_n$)
- Ritornare tutti i documenti che contengono una sequenza di parole chiave
	- In quello specifico ordine
- Gli indici invertiti supportano questo tipo di operazioni in quanto invece di creare un indice separato per ogni attributo, rappresentano tutti i documenti in cui appare quella specifica parola
- ![[Screenshot 2024-01-15 at 13.40.03.png]]
  - In questo esempio abbiamo per ogni parola, il documento e la posizione in cui compare![[Screenshot 2024-01-15 at 13.43.31.png]]
    ![[Screenshot 2024-01-15 at 13.43.40.png]]