> HOW:
> Praticamente ti conviene sempre guardare prima le condizioni a cui devi arrivare
> la funzione deve ritornare una macchina da dare in input al secondo linguaggio
## Dimostrare che FL è indecidibile
$$FL:= \{ x \in \Sigma^* | x=code(M) \cap M\text{ ferma su tutti gli input}\}$$
Per verificare che $FL$ è indecidibile dimostriamo che $HALT \le FL$ 
$$HALT := \{\langle y,x \rangle\in\Sigma^* \times \Sigma^*|y=code(M) \cap M \text{ ferma su } x\}$$
Dobbiamo definire la funzione $f$ tale che:
$$\langle y,x \rangle \in HALT \Leftrightarrow f(\langle y,x \rangle) \in FL$$
La funzione viene costruita in questo modo:
1. se $y \ne code(M)$ allora $f(\langle y,x \rangle) \not \in FL$ 
2. se $y=code(M)$ allora $f(\langle y,x \rangle)=code(M_{M,x})$ dove $M_{M,x}$ è costruita come segue:
	1. su qualsiasi input svuoto il nastro e simulo $M$ su $x$

La funzione $f$ è computabile in quanto è sempre possibile decidere se un valore è una codifica di una $TM$, inoltre anche simulare una $TM$ su un input è un problema computabile in quanto si può creare una $TM$ che lo computi.

Dalle definizioni precedenti possiamo dimostrare che $HALT \le FL$ in quanto:
$$\langle y,x \rangle\in HALT \Leftrightarrow M \text{ ferma su } x \Leftrightarrow M_{M,x}=code(f(\langle y,x \rangle)) \text{ ferma su qualsiasi input} \Leftrightarrow f(\langle y,x \rangle) \in FL$$
## Dimostrare che EQ è indecidibile
$$EQ := \{ \langle y,x \rangle \in \Sigma^* \times \Sigma^* | x=code(M)\cap y=code(M') \cap M,M' \text{ computano la stessa funzione parziale} \}$$
Per dimostrare l'indecidibilità di $EQ$ dimostriamo che $FL \le EQ$
$$FL:= \{ x \in \Sigma^* | x=code(M) \cap M\text{ ferma su tutti gli input}\}$$
Dobbiamo definire la funzione $f$ tale che:
$$x \in FL \Longleftrightarrow f(x) \in EQ$$
La funzione viene costruita in questo modo:
1. se $x \ne code(M)$ per qualche $M$ allora $f(x) \not \in EQ$ 
2. se $x = code(M)$ allora $f(x)=\langle code(M_1),code(M_2) \rangle$ dove $M_1$ ed $M_2$ sono definite come segue
	1. $M_1$ simula $M$ su tutti gli input e ferma ritornando 1 se $M$ si ferma su tutti, va in loop altrimenti
	2. $M_2$ si ferma sempre e ritorna 1

In questo modo abbiamo una coppia di macchine che calcolano la stessa funzione parziale se e solo se $M$ ferma su tutti gli input, la funzione è computabile per motivi elencati precedentemente e quindi dimostra il nostro teorema con le seguenti implicazioni:
$$x\in FL \Leftrightarrow M \text{ ferma su tutti gli input } \leftrightarrow M_1,M_2 \text{ computano la stessa funzione parziale} \Leftrightarrow f(x) \in EQ$$
## Dimostrare che EQ non è riconoscibile
$$EQ := \{ \langle y,x \rangle \in \Sigma^* \times \Sigma^* | x=code(M)\cap y=code(M') \cap M,M' \text{ computano la stessa funzione parziale} \}$$
Per dimostrare la non riconoscibilità di $EQ$ cerchiamo di ridurre ad esso un problema che sappiamo essere non riconoscibile, come $HALT^-$ 
$$HALT^-:= \{\langle y,x \rangle \in \Sigma^* \times\Sigma^* | y\ne code(M) \cup (y=code(M) \cap M \text{ non ferma su x})\}$$
Dobbiamo quindi verificare che $HALT^- \le EQ$, per farlo possiamo servirci del teorema che enuncia che:
$$L^-\le L' \Leftrightarrow L \le L^{'-}$$
Procediamo quindi a dimostrare che $HALT \le EQ^-$ :
$$HALT:= \{ \langle y,x \rangle \in \Sigma^* \times \Sigma^* | y=code(M) \cap M \text{ ferma su } x \}$$
$$EQ^-:= \{\langle y,x \rangle \in \Sigma^* \times \Sigma^*| x\ne code(M) \cup y \ne code(M') \cup (y=code(M) \cap x=code(M) \cap \newline M,M' \text{ computano due funzioni parziali diverse})\}$$
Dobbiamo quindi definire una funzione di transizione $f$ tale che:
$$\langle y,x \rangle \in HALT \Leftrightarrow f(\langle y,x \rangle) \in EQ^-$$
Costruiamo la funzione di transizione in questo modo:
1. se $y \ne code(M)$ allora $f(\langle y,x \rangle) \not \in EQ^-$ 
2. se $y=code(M)$ allora $f(\langle y,x \rangle) = \langle code(M_{M,x}), code(M_2) \rangle$ dove $M_{M,x}$ ed $M_2$ sono costruite come segue:
	1. $M_{M,x}$ simula $M$ su input $x$ e se ferma ritorna $1$ , altrimenti cicla
	2. $M_2$ ritorna sempre $0$

In questo modo abbiamo definito una coppia di macchine che calcolano due funzioni parziali diverse se e solo se $M$ ferma su $x$, la funzione è computabile per precedenti dimostrazioni e dimostra che $HALT \le EQ^-$ per le seguenti implicazioni:

$\langle y,x \rangle \in HALT \Leftrightarrow M_{M,x} \text { ferma su } x \Leftrightarrow$ $M_{M,x},M_2 \text{ computano due funzioni pariali diverse } \Leftrightarrow f(\langle y,x \rangle) = \langle M_{M,x}, M_2 \rangle \in EQ^-$

## Esercizio esame 2023-05-24
Dimostrare che $L_1 \le L_2$ 
$$L_1:= \{ y \in \{0,1\}^* | y=code(M) \cap M \text{ ferma sulla stringa } \epsilon\}$$
$$L_2 := \{ y \in \{0,1\}^*| y=code(M) \cap M \text{ ferma su } code(M)\}$$
Definiamo la funzione di transizione computabile $f$ tale che:
$$y\in L_1 \Leftrightarrow f(y) \in L_2$$
La funzione $f$ è costruita in questo modo:
1. se $y \ne code(M)$ allora $f(y) \not \in L_2$
2. se $y=code(M)$ allora $f(y)=code(UTM_M)$ dove $UTM_M$ è definita come segue:
	1. se nell'input c'è $code(UTM_M)$ svuoto il nastro e simulo $M$ su $\epsilon$, se $M$ ferma fermo, altrimenti ciclo
	2. ciclo per tutti gli altri input

In questo modo abbiamo una macchina $M'$ che ferma su $code(M')$ se e solo se $M$ ferma su $\epsilon$, la funzione è computabile in quanto definire se un valore rappresenta il codice di una macchina è un problema computabile, proprio come la simulazione di una $TM$, abbiamo verificato quindi che $L_1 \le L_2$ secondo le seguenti implicazioni:
$$y \in L_1 \Leftrightarrow M \text{ ferma su } \epsilon \Leftrightarrow M' \text{ ferma su } code(M') \Leftrightarrow f(y)=code(M') \in L_2$$

## Dimostrare che ETH è indecidibile
$$ETH := \{  x  \in \Sigma^* | x=code(M) \cap M \text{ ferma su } \epsilon \}$$
Per dimostrare che $ETH$ è indecidibile dimostriamo che $HALT \le ETH$
$$HALT := \{\langle y,x \rangle\in\Sigma^* \times \Sigma^*|y=code(M) \cap M \text{ ferma su } x\}$$
Costruiamo una funzione di transizione $f$ tale che:
$$\langle y,x \rangle \in HALT \Leftrightarrow f(\langle y,x \rangle) \in ETH$$
Costruiamo la funzione $f$ in questo modo:
1. se $y \ne code(M)$ allora $f(\langle y,x \rangle) \not \in ETH$ 
2. se $y= code(M)$ allora $f(\langle y,x \rangle)= code(M_{M,x})$
	1. se l'input è vuoto scrivi $x$ e simuli $M$ su $x$
	2. su qualsiasi altro input cicla
$$\langle y,x \rangle \in HALT \Leftrightarrow M \text{ ferma su } x \Leftrightarrow M_{M,x} \text{ ferma su } \epsilon \Leftrightarrow f(\langle y,x \rangle) = code(M_{M,x}) \in ETH$$


## Dimostrare che $ETH^-$ non è riconoscibile
$$ETH^- := \{y \in \{0,1\}^* | y \ne code(M) \cup (y = code(M) \cap M \text{ non ferma su } \epsilon)\}$$
per dimostrare che $ETH^-$ non è riconoscibile ci sono due modi:
### Primo metodo:
Se $ETH^-$ non è riconoscibile allora sarà vero che $HALT^- \le ETH^-$, il che implicherebbe che $HALT \le ETH$, ma siccome lo abbiamo già dimostrato possiamo darlo per vero:
$$HALT \le ETH \Leftrightarrow HALT^- \le ETH^- \Leftrightarrow ETH^- \text{ non è riconoscibile}$$
### Secondo metodo:
#### Teorema:
> $L$ è indecidibile se e solo se $L^-$ non è riconoscibile

#### Dimostrazione:
Poniamo $L$ un linguaggio indecidibile:
$$L \text{ è indecidibile } \Leftrightarrow HALT \le L$$
A questo punto per il teorema dimostrato precedentemente che dice
$$L \le L' \Leftrightarrow L^- \le L^{'-}$$
Possiamo dire che
$$HALT \le L \Leftrightarrow HALT^- \le L^-$$
Il che implica che $L^-$ non è riconoscibile.

In questo modo abbiamo provato entrambe le direzioni del teorema in quanto:
$$L \text { è indecidibile } \Leftrightarrow HALT \le L \Leftrightarrow HALT^- \le L^- \Leftrightarrow L^- \text{ non è riconoscibile}$$
#### Applicazione
Possiamo quindi dire che:
$$ETH \text{ è indecidibile } \Leftrightarrow ETH^- \text{ non è riconoscibile}$$
## Dimostrare che PP non è riconoscibile
$$PP:= \{ y \in \{0,1\}^* | y=code(M) \cap M \text{ ferma su tutte le stringhe di lunghezza pari}\}$$
Per dimostrare che $PP$ non è riconoscibile dobbiamo dimostrare che $HALT^- \le PP$, il che è possibile dimostrando che $HALT \le PP^-$ 
$$HALT := \{\langle y,x \rangle\in\Sigma^* \times \Sigma^*|y=code(M) \cap M \text{ ferma su } x\}$$
$$PP^- := \{ y \in \{0,1\}^* | y \ne code(M) \cup (y=code(M) \cap M \text{ non ferma su almeno una stringa pari})\}$$
Definiamo la funzione computabile $f$ tale che:
$$\langle y,x \rangle \in HALT \Leftrightarrow f(\langle y,x \rangle) \in PP^-$$
La funzione viene costruita come segue:
1. se $y \ne code(M) \Rightarrow \langle y,x \rangle \not \in HALT$ allora definiamo $f(\langle y,x \rangle)=code(M')$ dove $M'$ ferma su tutti gli input
2. se $y=code(M)$ allora definiamo $f(\langle y,x \rangle)=code(M_{M,x})$  dove $M_{M,x}$ è definita come segue:
	1. su input dispari ferma sempre
	2. su input pari di lunghezza $n$ simula $M$ su $x$
		1. se dopo $n$ passi $M$ si è fermata allora $M_{M,x}$ va in loop
		2. altrimenti se dopo $n$ pass non si è fermata $M_{M,x}$ ferma

In questo modo costruiamo una $TM$ $M_{M,x}$ che sottoposta agli input del linguaggio $PP^-$ che la testerà con tutte le stringhe di lunghezza pari, prima o poi arriverà una stringa di lunghezza $n$ che è uguale o maggiore al tempo di computazione di $M$ su $x$, ma solo se effettivamente $M$ può fermare su $x$

La funzione $f$ è computabile in quanto la verifica che un valore rappresenti il codice di una macchina è provato essere computabile (passo 1) e la costruzione di una macchina in grado di simulare altre macchine è computabile (passo 2)

Abbiamo quindi dimostrato che $HALT \le PP^-$ 
$$\langle y,x \rangle \in HALT \Leftrightarrow M \text{ ferma su x } \Leftrightarrow M_{M,x} \text{ non ferma su 00 (stringa pari)} \Leftrightarrow f(\langle y,x \rangle) \in PP^-$$
Quindi $HALT^- \le PP$ e $PP$ non è riconoscibile
## Dimostrare FL non riconoscibile
$$FL:= \{ y \in \{0,1\}^* | y=code(M) \cap M \text{ ferma su tutti gli input}\}$$
Per dimostrare che $FL$ non è riconoscibile dimostriamo che $HALT^- \le FL$ il che significa dimostrare che $HALT \le FL^-$.
$$HALT := \{\langle y,x \rangle\in\Sigma^* \times \Sigma^*|y=code(M) \cap M \text{ ferma su } x\}$$
$$FL^- := \{ y \in \{0,1\}^*| y \ne code(M) \cup (y = code(M) \cap M \text{ non ferma su almeno un input})\}$$
Definiamo la funzione di transizione $f$ computabile tale che:
$$\langle y,x \rangle \in HALT. \Leftrightarrow f(\langle y,x \rangle ) \in FL^-$$
Costruiamo $f$ come segue:
1. se $y \ne code(M)$ allora $f(\langle y,x \rangle) = code(M')$ dove $M'$ si comporta come segue:
	1. su qualsiasi input svuota il nastro e ferma
2. se $y = code(M)$ allora $f(\langle y,x \rangle) = code(M_{M,x})$ dove $M_{M,x}$ si comporta come segue
	1. CONTINUAA
	$$\langle y,x \rangle \in HALT \Leftrightarrow M \text{ ferma su } x \Leftrightarrow M_{M,x} \text{ non ferma su input a } \Leftrightarrow f(\langle y,x \rangle)=code(M_{M,x}) \in FL^-$$
## Dimostrare che AP è indecidibile ma riconoscibile
$$AP := \{ x \in \{0,1\}^* | x= code(M) \cap M \text{ ferma su almeno una stringa di lunghezza pari}\}$$
Per dimostrare che $AP$ è indecidibile ma riconoscibile la riduciamo ad $ETH$, quindi dimostriamo che $AP \le ETH$
$$ETH := \{  x  \in \Sigma^* | x=code(M) \cap M \text{ ferma su } \epsilon \}$$
Costruiamo la funzione computabile biettiva $f$ tale che:
$$x \in AP \Leftrightarrow f(x) \in ETH $$
Costruiamo la funzione in questo modo:
1. se $x \ne code(M)$ allora $x \in AP$ quindi definiamo $f(x) = x \not \in ETH$ 
2. se $x = code(M)$ allora $f(x) = code(M')$ dove $M'$ è definita come segue:
	1. su input $\epsilon$ simulo $M$ sulle stringhe pari 
	2. su tutti gli altri input fermo

Ho dimostrato le seguenti affermazioni
$$x \in AP \Leftrightarrow M \text{ ferma su una stringa pari } \Leftrightarrow M' \text{ ferma su } \epsilon \Leftrightarrow f(x) \in ETH$$
