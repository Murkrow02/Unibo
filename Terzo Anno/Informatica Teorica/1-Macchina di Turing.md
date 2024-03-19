# Introduzione
- Obiettivo: astrarre il modello di calcolo
- Ottenere un modello il più minimale possibile
- Determinare cosa é calcolabile e cosa non lo é 
- Cosa é davvero essenziale in una computazione?
	- Regole (stati)
	- Simboli (0,1)
	- Supporto (carta, memoria ...)
# La macchina di Turing
- Natro diviso in celle
	-  Infinito nella parte destra
- Ogni cella ha o un simbolo o può essere vuota
- La testina si muove su un nastro ed é sempre in una sola cella
- Configurazione: "istantanea" di un passo di computazione di una macchina 
- Configurazione iniziale
	- Testina nel primo slot
	- Nastro vuoto ad eccezione delle prime celle che corrispondono all'input iniziale![[Screenshot 2024-03-10 at 17.03.37.png]]
## Definizione informale
Come si decide il prossimo stato di computazione?
- Una volta letta la cella la macchina può:
	- Fermarsi
	- Cambiare stato
		- Opzionalmente scrivere un simbolo sulla cella attuale
	- Spostarsi a destra o sinistra
Il tipo di azione é dettato dal programma della macchina

## Definizione formale
Tupla $<\Sigma,Q,q_0,H.\delta>$ 
-  $\Sigma$: Alfabeto in input
-  $Q$: Stati della macchina
-  $q_0$: Stato iniziale
- $H$: Stati finali
- $\delta$: Funzione di transizione definita come
	- $\delta:(Q/Z) \times \Sigma \to Q \times \Sigma \times \{\to , \leftarrow \}$   
	- Da un qualsiasi stato (non finale) e un simbolo dell'alfabeto, andiamo a finire su un nuovo stato, otteniamo un nuovo simbolo da scrivere nella cella e capiamo se spostarci a sinistra o destra
- ![[Screenshot 2024-03-10 at 17.28.00.png]]
## Espressività della macchina di Turing
Non sempre ci ritroviamo ad avere problemi su numeri
- Dato un grafo é strettamente connesso?
- Trovare percorso minimo da punto A a punto B
# Problemi di decisione
In astratto possiamo dividere un qualsiasi problema in due parti
- Istanze positive: dati per cui la risposta é si
	- Esiste un percorso per cui la distanza minima é x?
- Istanze negative: dati per cui la risposta é no
	- Il sistema ha soluzione?
Possiamo svolgere questo con macchine di turing?

# Linguaggi
Ricordiamo dal corso di linguaggi: $L$ é un sottoinsieme di $\Sigma^*$ 
- Una funzione caratteristica di un linguaggio é una funzione $X_L(x)$ con $x \in \Sigma^*$ tale che
$$
\begin{cases} 1 \ se \ x\in L\\ 0  \ altrimenti\end{cases}
$$
- Quindi una funzione che prende in input una stringa dell'alfabeto e ci dice se questa appartiene al linguaggio
## Codifica di linguaggio
- Abbiamo $\alpha$ ovvero i dati del problema di decisione
- Vogliamo codificare $\alpha$ con il linguaggio $L$ quindi su alfabeto $\Sigma^*$
- Otteniamo quindi $code(\alpha) \in \Sigma^*$
$$
L=\{x \in \Sigma^* | x =code(\alpha)  \}
$$
dove $\alpha$ é un [[1-Macchina di Turing#Problemi di decisione|Istanza positiva]] del problema 

### Proprietà per code(-)
- Se $\alpha \not = \beta$ allora $code(\alpha) \not = code(\beta)$
	- Se i dati del problema sono diversi allora il codice sara diverso
- Dovremmo poter calcolare $\alpha$ a partire da $code(\alpha)$
	- Leggendo un programma e conoscendo il linguaggio possiamo risalire al suo funzionamento
- Dovremmo poter verificare se $x \in \Sigma^*$ é $code(\alpha)$ per qualche $\alpha$

## Linguaggi decidibili
Come facciamo a ragionare su un problema di decisione con una macchina di Turing?
- Assumiamo una codifica del problema come un linguaggio $L$ su alfabeto $\Sigma'$
- Vogliamo una TM $M$ con queste proprietà
	- Alfabeto di input/output $\Sigma_I$ é $\Sigma'$
	- L'insieme degli stati finali é $H=\{Y,N\}$
- Diciamo che $M$ accetta un input $x\in \Sigma^*_I$ se la computazione ferma su $Y$, rigetta altrimenti
- $M$ decide $L$ se:
	- Quando $x \in L$ allora $M$ accetta x
	- Quando $x \not \in L$ allora $M$ rigetta x
- Un linguaggio é **decidibile** se c'é una TM che lo decide 
Esempio: stringhe di lunghezza pari
![[Screenshot 2024-03-12 at 18.58.28.png]]
## Linguaggi riconoscibili
Decidibile -> Riconoscibile
È un modo più sottile in cui una TM può essere associata ad un linguaggio
- Assumiamo una codifica del problema come un linguaggio $L$ su alfabeto $\Sigma'$
- Vogliamo una TM con alfabeto di input/output $\Sigma'$
- $M$ riconosce $L$ se:
	- Quando $x \in L$ allora $M$ si ferma (raggiunge qualsiasi stato finale)
	- Quando $x \not \in L$ allora $M$ non si ferma (entra in un ciclo)
- Un lunguaggio é **riconoscibile** se c'é una TM che lo riconosce ![[Screenshot 2024-03-12 at 18.57.58.png]]
  Esempi: alcuni linguaggi sono riconoscibili ma non decidibili
  