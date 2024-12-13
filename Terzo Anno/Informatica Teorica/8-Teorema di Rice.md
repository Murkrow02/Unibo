# Prerequisiti
Su una TM non possiamo **mai** decidere se :
- Ferma su un determinato input
- Ferma su input vuoto
- È equivalente a un'atra TM
Allora quali sono i problemi decidibili da una TM?
# Proprietà dei TM-Linguaggi
## Definizione
- Una proprietà di linguaggio é una funzione da un insieme di TM ad un insieme $\{ 0,1 \}$ (vero/falso)
- Questa proprietà deve essere tale che $L_M = L_{M'} \implies P(M)=P(M')$ 
	- Ovvero se il linguaggio é su un altra macchina la proprietà rimane
	- Astrae dall'implementazione della macchina
	- Questo assicura che P dipenda solo dal linguaggio descritto dalla macchina
	- Per esempio: ferma in 42 step non è proprietà del linguaggio.
- **Sostanzialmente, una proprietà di linguaggio ci 'ritorna' un'insieme di macchine**
	- Le macchine che rispettano quella proprietà
## Esempi
![[Screenshot 2024-03-19 at 19.22.09.png]]
## Non trivialità
- La proprietà é detta non triviale se esiste almeno una TM che non la rispetta e una che la rispetta
- Al contrario, se tutte le macchine esistenti la (non)rispettano, allora la proprietà é triviale![[Screenshot 2024-03-19 at 19.22.55.png]]
  Esempio di proprietà triviale, quelle sopra sono invece non triviali
# Teorema di Rice
## Teorema
Se $P$ ha **language property** non triviale, allora il problema `M ha proprietà P` é indecidibile
MANCA DIMOSTRAZIONE

# Cardinalità dei problemi irrisolvibili
Dimostreremo che la maggior parte dei linguaggi non sono riconoscibili (e quindi indecidibili)
- La dimostrazione si basa sul teorema di Cantor e sul dimostrare che esistono molti più linguaggi che TM (cardinalitá di infinito maggiore)
- Un insieme é detto infinito numerabile se esiste una mappatura da quell'insieme ai numeri naturali
	- Intuitivamente, l'insieme ha tanti elementi quanto i numeri naturali
- Possiamo contare tutte le Turing machines
	- Infatti abbiamo visto che é possibile codificare una TM come un insieme di 01
	- L'insieme delle stringe 01 é infinito numerabile![[Screenshot 2024-03-19 at 19.52.57.png]]
  - Di conseguenza anche i linguaggi riconoscibili sono numerabili
	  - Per definizione ogni linguaggio riconoscibile é determinato da una TM che lo riconosce
  - L'insieme dei linguaggi, al contrario, é **non numerabile**
  - Ricordiamo la diagonalizzazione di Cantor
	  - Se esiste una funzione che mappa ogni elemento di un insieme ad un numero naturale allora quell'insieme é infinito numerabile
		  - Ad esempio, i numeri razionali sono associabili ad un numero naturale
	  - Al contrario, se la mappatura non é possibile allora l'insieme é non numerabile
		  - Ad esempio, anche solo l'insieme dei numeri reali tra 0-1, non é un insieme numerabile![[Pasted image 20240405160432.png]]
		  - Questo perchè, prendendo una diagonale qualsiasi della lista che abbiamo creato con essi, il nuovo numero risultante sarà diverso da tutti gli altri, non possiamo elencarli tutti
	- L'insieme $S_{\Sigma}$ é l'insieme di tutti i linguaggi sull'alfabeto finito $\Sigma$ ed é non numerabile
# I linguaggi sono non numerabili
- Sappiamo che un linguaggio L é un sottoinsieme di $\Sigma^*$ 
- $\Sigma^*$ é infinito numerabile
- Possiamo scrivere $\Sigma^*$ come $\set{\sigma_1,\sigma_2,\sigma_3...}$
- Possiamo scrivere un linguaggio, ad esempio $L_1=\set{\sigma_1,\sigma_4}$ come una matrice in base a se un simbolo appare o meno nel linguaggio![[Screenshot 2024-04-05 at 17.05.19.png]]
  In questo caso appare solo $\sigma_1, \sigma_4$
  - Ciascun linguaggio può essere rappresentato in questo modo
  ![[Screenshot 2024-04-05 at 17.06.04.png]]
  - Se osserviamo la diagonale abbiamo un nuovo linguaggio che non appartiene a  $S_{\Sigma}$
  - Quindi  $S_{\Sigma}$ non é numerabile
# Conclusioni
Su un insieme finito $\Sigma$ sappiamo ora che:
- L'insieme di linguaggi riconoscibili da una TM é infinito numerabile
- L'insieme di tutti i linguaggi non é numerabile
- Esistono quindi dei linguaggi che non sono riconoscibili da alcuna TM
	- $HALT^-$
	- EQ
- ![[Screenshot 2024-04-05 at 17.10.36.png]]