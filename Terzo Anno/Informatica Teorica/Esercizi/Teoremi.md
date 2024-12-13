## TM a più nastri
**Teorema**: Le TM e le TM a più nastri sono equivalenti
**Dimostrazione**: Dimostriamo che è possibile simulare una TM a più nastri su una ad un nastro e viceversa

La simulazione di una TM ad un nastro su una TM a più nastri è diretta in quanto basta svolgere tutte le operazioni sul primo nastro

La simulazione di una TM a più nastri su una TM ad un nastro consiste nel codificare tutti i nastri in uno univoco, ad esempio utilizzando dei simboli come `#` per separare i nastri e un ulteriore alfabeto $\Sigma'$ che contiene tutte le lettere di $\Sigma$ con l'aggiunta dei loro corrispettivi tratteggiati $\bar x$.

La funzione di transizione di una TM a più nastri definita come:
$$\delta: (Q \setminus H) \times \Sigma^k \rightarrow Q \times (\Sigma \times \{ \leftarrow, \rightarrow\})^k$$
computa per ogni iterazione i passi svolti su tutti i nastri simultaneamente verrà invece spezzettata in vari passi di computazione che hanno la forma di una normale funzione di transizione.
## Dimostrare che HALT è indecidibile
**Teorema**: HALT è indecidibile
**Dimostrazione**: assumiamo per assurdo che HALT sia decidibile e verifichiamo la presenza di contraddizioni

Ipotesi: Esiste una macchina $H$ che decide HALT, quindi possiamo sapere se un programma si ferma su un determinato input oppure no $H(\langle M, x \rangle)$.

Costruiamo ora una macchina $M'$ che si comporta in questo modo:
1. Prende in input una macchina $M''$ 
2. Simula $H$ sull'input $\langle M'', M'' \rangle$
3. Al termine della computazione di $H$ ritorniamo il risultato negato
	1. Se $H$ rigetta, accettiamo
	2. Se $H$ accetta, andiamo in loop

Se ora proviamo a dare in input ad $H$ la coppia $\langle M', M' \rangle$ possiamo osservare i seguenti possibili comportamenti:
$$H \text{ accetta } \langle M',M'\rangle \iff  M' \text{ non ferma su } M' \iff \langle M', M' \rangle \not \in HALT \iff H \text{ rigetta } \langle M', M' \rangle$$$$H \text{ rigetta } \langle M' M' \rangle \iff M' \text{ ferma su } M' \iff \langle M',M' \rangle \in HALT \iff H \text{ accetta } \langle M', M' \rangle$$
Possiamo notare che in entrambi gli scenari sono presenti delle contraddizioni, l'unica assunzione fatta per la costruzione è che $H$ è una $TM$ decidibile, quindi possiamo dire che $H$ non esiste.
## Dimostrare che $HALT^-$ non è riconoscibile
**Teorema**: $HALT^-$ non è riconoscibile
**Dimostrazione**: assumiamo per assurdo che $HALT^-$ sia riconoscibile e verifichiamo che se lo fosse allora $HALT$ sarebbe decidibile

$$HALT^- := \{ \langle y,x \rangle \in  \Sigma^* \times \Sigma^* | y \ne code(M) \cup (y=code(M) \cap M \text{ ferma su } x)\}$$
Dato che assumiamo che $HALT^-$ è riconoscibile allora possiamo costruire una $TM$ $H^-$ che riconosce $HALT^-$

Possiamo costruire una $TM$ $H$ che decide $HALT$ come una $TM$ a due nastri che simula in parallelo due $TM$ che riconoscono rispettivamente $HALT^-$ ed $HALT$, essendo $HALT$ riconoscibile, possiamo accertarci dell'esistenza di questa macchina.
- se la macchina che si ferma per prima è $HALT^-$ allora vuol dire che non accettiamo l'input
- se la macchina che si ferma per prima è $HALT$ allora vuol dire che accettiamo l'input

Questa macchina si fermerà in ogni caso in quanto una coppia $\langle code(M), x \rangle$ appartiene ad $HALT \iff$ non appartiene ad $HALT^-$ e viceversa.

Abbiamo costruito una $TM$ che decide $HALT$, ma siccome questa macchina non può esistere e abbiamo come assunzione che $HALT^-$ è riconoscibile allora vuol dire che $HALT^-$ non è riconoscibile.
## Se $L' \le L$ ed $L$ è decidibile allora $L'$ è decidibile
Dimostrazione: creiamo una macchina che decide $L'$

Definiamo la funzione di riduzione come segue:
$$f: x \in L' \iff f(x) \in L$$
Siccome sappiamo che $L$ è decidibile allora possiamo costruire una $TM$ $M$ che decide $L$ e costruiamo una $TM$ $M_f$ che computa $f$, possiamo costruire $M_f$ perchè sappiamo che $L' \le L$.

Costruiamo ora una $TM$ $M'$ che decide $L'$:
- simula $M_f$ su input $x$
- successivamente simula $M$ su input $f(x)$
	- se $M$ accetta accettiamo
	- se $M$ rigetta rigettiamo
$$x \in L' \iff M' \text{ accetta } x \iff M \text{ accetta } f(x) \iff f(x ) \in L$$
## Se $L' \le L$ ed $L$ è riconoscibile allora $L'$ è riconoscibile
Dimostrazione: creiamo una macchina che riconosce $L'$ 

Definiamo la funzione di riduzione come segue:
$$f: x \in L' \iff f(x) \in L$$
Sappiamo che $L$ è riconoscibile, quindi possiamo costruire una $TM$ $M$ che riconosce $L$
Sappiamo che $f$ è computabile dato che $L' \le L$, quindi possiamo costruire una $TM$ $M_f$ che computa $f$

Costruiamo ora una $TM$ $M'$ che riconosce $L'$:
- simula $M_f$ su input $x$
- successivamente simula $M$ su input $f(x)$
	- se $M$ ferma fermiamo
	- se $M$ non ferma, non fermiamo
$$x \in L' \iff M' \text{ ferma su } x \iff M \text{ ferma su } f(x) \iff f(x ) \in L$$
## Dimostrare che $L_1 \le L_2 \iff L_1^- \le L_2^-$ 

definiamo le funzioni di riduzione:
$$f: x \in L_1 \iff f(x) \in L_2$$
$$f^-: x\in L_1^- \iff f(x) \in L_2^- $$

Dimostriamo il teorema con le seguenti implicazioni
$$x \in L_1 \Rightarrow x \not \in L_1^- \Rightarrow f(x) \not \in L_2^- \Rightarrow f(x) \in L_2$$
$$f(x) \in L_2 \Rightarrow f(x) \not \in L_2^- \Rightarrow x \not \in L_1^- \Rightarrow x \in L_1$$

Per dimostrare il verso opposto possiamo denominare
- $\bar L_1 = L_1^-$
- $\bar L_2 = L_2^-$ 

$\bar L_1 \le \bar L_2 \Rightarrow (\bar L_1)^- \le (\bar L_2)^-$ 

Applichiamo la dimostrazione di sopra e risolviamo le denominazioni come
- $(\bar L_1)^- = L_1$
- $(\bar L_2)^- = L_2$

## Dimostrare che $ABBA$ è indecidibile
Dimostrazione: Dimostriamo che $HALT \le ABBA$
$$ABBA := \{ y \in \{0,1\}^* | y=code(M) \cap M \text{ ferma su } 0110\}$$

Per ridurre $HALT$ ad $ABBA$ definiamo la funzione di riduzione $f$ come segue:
$$f: \langle y,x\rangle \in HALT \iff f(\langle y,x \rangle) \in ABBA$$
Costruiamo la funzione come segue:
1. se $y \ne code(M)$ allora $\langle y,x \rangle \not \in HALT$, quindi $f(\langle y,x \rangle)=y \not \in ABBA$ 
2. se $y=code(M)$ allora ritorniamo $f(\langle y,x \rangle)=code(M_{M,x})$ dove $M_{M,x}$ è definita come segue:
	1. su input $0110$ simulo $M$ su $x$
	2. su tutti gli altri input ciclo

La funzione $f$ è computabile in quanto:
- nello step 1 verifichiamo che $y$ sia il codice di una macchina, il che è risaputo essere un problema computabile
- nello step 2 simuliamo una macchina su un input, il che è computabile

La funzione $f$ soddisfa le seguenti implicazioni:
$$\langle y,x \rangle \in HALT \iff M \text{ ferma su } x \iff M_{M,x} \text{ ferma su } 0110 \iff f(\langle y,x \rangle) \in ABBA$$
## Supponi L sia un linguaggio NP-completo. Dimostra che se L fosse in P, allora avremmo che P = NP.

Sapendo che $L$ è un linguaggio NP-completo allora $\forall L' \in NP, L' \le L$, quindi esisterà sempre una funzione di riduzione computabile in tempo polinomiale $f$ tale che:
$$f:x\in L' \iff f(x) \in L$$

Supponendo che $L$ fosse in $P$, vorrebbe dire che avremo una macchina $M$ deterministica che computa $L$ in tempo polinomiale.

Definiamo $M_f$ come la macchina in grado di trasformare $x$ in $f(x)$ come definito nella funzione di riduzione, questa macchina esiste per definizione e lavora in tempo polinomiale.

Procediamo costruendo una macchina $M'$ che lavora come segue:
- simula $M_f$ su $x$, otteniamo quindi $f(x)$
- successivamente simuliamo $M$ su $f(x)$

In questo modo abbiamo creato una macchina $M'$ che decide $L'$ in tempo polinomiale, in quanto sappiamo per definizione che la computazione di $M_f$ avviene in tempo polinomiale, cos' come la computazione di $M$ su $f(x)$, quindi possiamo dire che il linguaggio generico $L' \in NP$ è computabile in tempo polinomiale da una $TM$ deterministica, il che implica che $L' \in P$, quindi $P=NP$.