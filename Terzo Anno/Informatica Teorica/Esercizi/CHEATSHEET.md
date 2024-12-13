## Riduzione e Riconoscibilità
- Se $L' \le L$ e $L$ è riconoscibile/decidibile allora $L'$ è riconoscibile/decidibile
- Se $L' \le L$ e $L'$ non è riconoscibile/decidibile allora, $L$ non è riconoscibile/decidibile
- Se $L$ è riconoscibile/decidibile e $L'$ non lo è, allora $L' \not \le L$ 
- Se $L'$ è decidibile allora per ogni $L$ non-triviale $\{L \ne \Sigma^* \text{ e } L \ne \emptyset\}$ $L' \le L$
 ![[PHOTO-2024-05-13-10-53-10.jpg | 300]]



### Relazioni
- La riduzione è riflessiva, quindi  $\forall L$, $L \le L$  
- La riduzione è transitiva, quindi $L \le L'$ e $L \le L^{"}$ implicano $L' \le L^{"}$  
- NON È SIMMETRICA

### Complemento
- $L_1 \le L_2 \Leftrightarrow L_1^- \le L_2^-$  
- $L_1^- \le L_2 \Leftrightarrow L_1 \le L_2^-$
	- Per dimostrare la non riconoscibilità di $L$ dobbiamo ridurre $HALT^-$ ad $L$, per farlo neghiamo la riduzione e quindi dimostriamo che $HALT \le L^-$ 

Non è detto che si possa sempre ridurre un linguaggio al suo complemento
## P e NP

### Classificazione
#### Problemi P
$PATH$: un grafo diretto (con le frecce) con un percorso diretto da s a t
$x-CLIQUE$: con x fisso
#### Problemi in NP
- $k-CLIQUE$: un grafo che contiene un clique di k nodi
##### Problemi NP completi
- $SAT$: una formula booleana soddisfacibile
- $3SAT$: una formula booleana in formato 3-cnf soddisfacibile
	- 3-cnf vuol dire congiunzione di clausole di 3 letterali
	- clausola vuol dire disgiunzione di letterali
	- esempio: $(\bar x \cup y \cup z) \cap (\bar x \cup y \cup \bar z) \ cap (\bar x \cup \bar y \cup z)$
### Teoremi
- Se $L' \le_p L \cap L \in P$ allora $L' \in P$
	- Riuscendo a convertire un problema in tempo polinomiale ad un problema in P allora anche il problema di partenza è in P
- Se $L' \le_p L \cap L' \in NP$ allora $L \in NP$
	- Riuscendo a convertire un problema $NP$ in tempo polinomiale ad un altro allora anche l'altro è in $NP$
- Per $L$ non triviale in $P$, $L^- \le_p L$
- Per $L$ non triviale in $NP$, $L^- \le_p L$
	- $L$ non triviale implica che $L \ne \emptyset$ e $L \ne \Sigma^*$ 
- Se $SAT$ è in $P$ allora $P=NP$

