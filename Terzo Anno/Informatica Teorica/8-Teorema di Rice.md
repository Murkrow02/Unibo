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
	- Questo assicura che P dipenda solo dal linguaggio descritto dalla macchina. Per esempio: ferma in 42 step non è proprietà del linguaggio.
- Sostanzialmente, una proprietà di linguaggio ci 'ritorna' un'insieme di macchine
	- Le macchine che rispettano quella proprietà
## Esempi
![[Screenshot 2024-03-19 at 19.22.09.png]]
## Non trivialità
- La proprietà é detta non triviale se esiste almeno una TM che non la rispetta e una che la rispetta
- Al contrario, se tutte le macchine la (non)rispettano, allora la proprietà é triviale![[Screenshot 2024-03-19 at 19.22.55.png]]
  Esempio di proprietà triviale, quelle sopra sono invece non triviali
# Teorema di Rice
## Teorema
Se $P$ ha **language property** non triviale, allora il problema `M ha proprietà P` é indecidibile
MANCA DIMOSTRAZIONE

# Cardinalità dei problemi irrisolvibili
Dimostreremo che la maggior parte dei linguaggi non sono riconoscibili (e quindi indecidibili)
- La dimostrazione si basa sul teorema di Cantor e sul dimostrare che esistono molti più linguaggi che TM (cardinalitá di infinito maggiore)
- Un insieme é detto infinito numerabile se esiste una mappatura da quell'insieme ai numeri naturali
- Possiamo contare tutte le Turing machines
	- Infatti abbiamo visto che é possibile codificare una TM come un insieme di 01
	- L'insieme delle stringe 01 é infinito numerabile![[Screenshot 2024-03-19 at 19.52.57.png]]
  - Di conseguenza anche i linguaggi riconoscibili sono numerabili
	  - Per definizione ogni linguaggio riconoscibile é determinato da una TM che lo riconosce
  - L'insieme dei linguaggi, al contrario, é **non numerabile**
  - DIMOSTRAZIONE MANCA
  - Osserviamo quindi che ci sono alcuni linguaggi che non possono essere associati ad alcuna TM
	  - Halt, EQ, 