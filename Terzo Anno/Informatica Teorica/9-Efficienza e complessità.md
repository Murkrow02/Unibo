# Preludio
- Sappiamo che dato un problema questo non sempre é decidibile
- Ora ci concentriamo sui problemi **calcolabili**
- Sappiamo che non tutti i problemi sono decidibili (ad esempio il problema della fermata)
	-  Ponendo però una restrizione di lunghezza di input il problema diventa decidibile
		- Possiamo dimostrare in $n$ passi che il problema sia decidibile?
- Quali problemi sono calcolabili in maniera efficiente?
# Misurare la complessità
## Complessità di tempo
> Sia M una TM che si ferma su ogni input. La sua **complessità** di tempo é definita come la funzione $f: N \to N$ dove $f(n)$ é il massimo numero di passi che M impiega a fermarsi su input di lunghezza **n**

> Attenzione: numero **MASSIMO**, consideriamo quindi sempre il caso **pessimo**

Quanto é robusto questo metodo di misura? Quanto dipende da fattori esterni? Possiamo romperlo?
- Dipende dal modello di calcolo
- Dipende da cosa intendiamo per "passo di compilazione"
- È sensibile a variazioni minime
	- Ad esempio una subroutine che richiede un tempo costante, indipendentemente dall'input
- Dipende dalla codifica dell'input e come misuriamo la sua lunghezza
	- Ad esempio se lavoriamo su un grafo potremmo prendere come n il numero di nodi anche se la concenzione di nodo cade quando parliamo di codifica della macchina
## Notazione Big-O
Per ovviare alla fragilità del metodo precedente, astrae da dettagli poco rilevanti e fornisce solo una stima significativa del suo tempo di esecuzione![[Screenshot 2024-04-15 at 18.19.09.png]]
### Esempi
![[Screenshot 2024-04-15 at 18.23.15.png]] 
## Considerazioni
- L'analisi asintotica tramite Big-O risolve alcune fragilità ma non tutte
	- Rimane il problema della codifica
	- Dipende anche dal modello di calcolo
	- Scegliamo di prendere il caso peggiore ma cosa facciamo se ad esempio l'algoritmo il 99% delle volte é polinomiale e l'1% é fattoriale?
		- In questi casi possiamo prendere in considerazione l'**average-case complexity**
# Classi di complessità
## Classe P
> È la classe di tutti i linguaggi decidibili da una TM (deterministica, ad un nastro) in tempo **polinomiale**

$$
P=\cup_kTIME(n^k)
$$
### Perché P?
- Di solito un algoritmo che lavora in tempo polinomiale viene considerato 'ragionevole'
- Anche se ha un polinomio di grado molto alto, ad esempio $n^{10}$ , di solito esistono delle ottimizzazioni che ci permettono di scendere ad un grado minore
  Es. Moltiplicazione tra matrici nel tempo![[Screenshot 2024-04-15 at 18.34.58.png]]
  - Codifiche: la maggioranza delle codifiche per strutture come grafi, alberi, matrici, automi... come stringhe richiede tempo polinomiale e produce una stringa di output di lunghezza polinomiale rispetto all'input
	  - Un algoritmo che lavora ad esempio su grafi non cambia di classe cambiandone la codifica
- [[2-Tesi di Church Turing]] **rafforzata**
	- Ogni modello di calcolo deterministico fisicamente realizzabile può essere simulato da una TM con overhead al più polinomiale 
		- m passi di computazione del modello possono essere simulati in al più $O(M^c)$
	- Ad esempio una TM con un nastro puo simulare una con k nastri
## La classe EXP
Mentre abbiamo la class P dei linguaggi decidibili in tempo **ragionevole**, ora ci occupiamo di:
$$
EXP=\cup_kTIME(2^{n^k})
$$
Ovvero dei linguaggi decidibili in tempo **irragionevole**. Sono di questo tipo gli algoritmi che lavorano in maniera *bruteforce*, ovvero quegli algoritmi che non vanno verso una direzione giusta ma che hanno bisogno di esplorare tutti i casi.
### Esempio: PATH
- Il prof fa un esempio di un algoritmo di ricerca di percorso da $s$ a $t$ su un grafo. Ovviamente esiste un algoritmo che lo risolve in tempo polimoniale (come quello fatto ad algoritmi che marca i nodi man mano che li visita) che quindi sta in **P**
- Fa notare che non é necessariamente l'unico approccio, infatti un algoritmo che visita tutti i potenziali cammini in un grafo é invece esponenziale
#### Nota sulla codifica
- Il prof fa notare che, per tutte le strutture di dati basilari (alberi, array, grafi...) esiste sempre una codifica che li permette di esprimere in maniera polinomiale. La codifica é importante, ovviamente non possiamo concentrarci unicamente sulla complessità dell'algoritmo quando invece la codifica impiega tropo tempo
- Per fortuna questo non é quasi mai un problema in quanto per la codifica di strutture dati ricadiamo sempre in **P**
## Classe NP
Non é possibile per una macchina di Turing deterministica, simularne una non deterministica in modo efficiente.  ![[Screenshot 2024-04-16 at 18.20.47.png]]
Una macchina non deterministica viene simulata da una deterministica semplicemente esaminando tutti i nodi dell'albero in maniera breadth-first, esplorando tutti i possibili cammini di computazione di M.

 Di conseguenza, possiamo concludere che non é possibile simulare con un algoritmo deterministico uno non-deterministico in tempo ragionevole.

> ATTENZIONE: NP non vuol dire "non polinomiale"
> NP é la classe di tutti i linguaggi decidibili da una TM (non-deterministica, ad un nastro) in tempo **polinomiale**

$$
NP=\cup_kNTIME(n^k)
$$
### Caratterizzazione alternativa di NP (verificatore)
> Un linguaggio é verificabile se esiste una TM M (che termina sempre ed accetta o rigetta) con la proprietà CONTINUA
> Praticamente dice quel fatto che in NP é polinomiale la verifica, ad esempio per il clique é NP trovarlo ma verificarlo é polinomiale, dato un grafo e un k ed un clique, possiamo verificare che quello é un clique in maniera deterministica e polinomiale

È importante quindi il concetto di verificatore, ovvero quel programma che dato in input il problema, i dati e la soluzione, verifica che la soluzione sia corretta. Questo programma in NP agisce sempre in tempo polinomiale

### Teorema: Un linguaggio é in NP se e solo se é verificabile polinomialmente
bordello assurdo

# P vs NP
> P é la classe dei linguaggi per cui la domanda $w \in A$ può essere **risposta** in maniera efficiente

> NP é la classe dei linguaggi per cui la domanda $w \in A$ può essere **verificata** in maniera efficiente

Pensa ad esempio ad una board di sudoku, risolverla é difficile ma verificarne la soluzione é semplice.
![[Screenshot 2024-04-16 at 19.14.12.png]]

## Poly reduction
> Letteralmente, riducibile in tempo polinomiale. Come mapping reduction ma la funzione deve computare in **tempo polinomiale deterministico**

## NP-Completezza
> Un linguaggio é NP-completo se é in NP e ogni altro linguaggio L' in NP é poly-riducibile ad esso

## SAT
### Formula booleana
- Letterali
	- Variabili $x,y,z$
	- Negazioni $\overline{x},\overline{y},\overline{z}$
- Combinazioni di letterali tramite negazioni e disgiunzioni
- Le variabili possono assumere valore 1 o 0
- Esempio: $(\overline{x} \lor y) \land (x\lor z)$  
	- Soddisfacibile con $x=1,y=1,z=0$
- Una formula é detta soddisfacibile se esiste un assegnamento di valori alle sue variabili che diano valore 1
### Clausola
- Una formula booleana é una clausola se é una disguinzione di variabili
- Esempio
	- $\overline{x} \lor y \lor z$
- Una formula booleana é in **forma normale congiunta** CNF se é una congiunzione di clausole
- Esempio
	-  $(\overline{x} \lor y \lor z) \land ( \overline{z} \lor x \lor y)$
- Una formula é 3CNF se é in CNF e ogni clausola contiene esattamente 3 letterali

> $SAT=\{ <F> | F \ \text{é una formula booleana soddisfacibile}\}$   
> $3SAT=\{ <F> | F \ \text{é una formula booleana 3CNF soddisfacibile}\}$ 

Numerosi problemi in informatica possono essere formulati come istanze di 3SAT/SAT
### Esempio 3-SAT e CLIQUE
Vogliamo dimostrare che $3SAT \leq_p CLIQUE$  
- L'idea é tradurre le formule di SAT in un grafo
- Nodi
	- Il grafo ha 3K nodi, suddivisi in k gruppi chiamati **triple** 
	- Ogni tripla corrisponde ad una clausola di F
	- Etichettiamo ogni nodo del grafo con il letterale in F
- Archi
	- Gli archi di G collegano tutte le coppie di nodi tra loro eccetto:
		- se 2 nodi sono nella stessa tripla
		- se un nodo ha etichetta $x$ e l'altro ha etichetta $\overline{x}$
![[Screenshot 2024-04-17 at 18.01.08.png]]
Boh

## Il teorema di Cook-Levin
Introduce un problema, **SAT**, il quale é uno speciale tra P e NP
### Teorema
> SAT é NP-completo

Manca dimostrazione
### Corollario
> Se $SAT \in P$  allora $P=NP$

 In sostanza, se riuscissimo a dimostrare che SAT é in P allora tutti gli altri problemi in NP sarebbero riducibili a P. Diremo che SAT é **NP-COMPLETO**

# Riassuntone classi
![[Screenshot 2024-04-18 at 12.08.19.png]]
> **Classe P**: tutti i problemi che possono essere risolti in tempo polinomiale da una macchina di Turing deterministica. Deterministica perché questi algoritmi a differenza di NP, procedono in una direzione ben precisa (ad esempio ordinare un array), senza andare di bruteforce. La crescita della complessità temporale cresce in maniera polinomiale rispetto alla dimensione dell'input

> **Classe NP**: tutti i problemi per i quali una soluzione può essere verificata in tempo polinomiale nonostante la risoluzione a tali problemi sia (per quanto ne sappiamo) molto più difficile da trovare. Questi algoritmi sono di solito di tipo bruteforce e si applicano a problemi di alcuni giochi come sudoku o più in generale a problemi dove dobbiamo per forza andare a tentativi. Non é noto se la crescita della complessità temporale cresca in maniera polinomiale o meno.

> **NP Completi**: sono tutti i problemi più "difficili" in NP. Sono detti *completi*  in quanto ogni altro problema in **NP** può essere ricondotto ad uno di questi (in tempo polinomiale! Poly-reduction). Se risolvi un problema NP-completo in tempo polinomiale allora hai risolto anche tutti gli altri problemi in NP. Un classico esempio di problema NP-completo é **SAT** o **3-SAT*

> **NP-Hard**: sono quei problemi che non necessariamente rientrano in NP, quindi anche la loro verifica potrebbe richiedere tempo non-polinomiale. Sono almeno difficili quanto ogni problema in NP. Un classico problema di questo tipo potrebbe essere l'halting problem, del quale nemmeno la verifica é possibile calcolare in tempo polinomiale.

> **EXP**: Sono quei problemi che sappiamo essere **sicuramente** al di fuori di P e di NP. Fanno parte di questa categoria ad esempio gli scacchi oppure Go, quei problemi che sostanzialmente non sono solo difficili da risolvere ma anche difficili da verificare (data una posizione su una scacchiera non sappiamo se una mossa scelta é effettivamente giusta)