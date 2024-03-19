# Utilità
- Ci permette di dimostrare l'indecidibilità/non-riconoscibilità di un problema
- Consente di ridurre le istanze di un problema a quelle di un altro problema
- Ci rivela che nel confrontare due problemi non é essenziale la decidibiltà/riconoscibilità, piuttosto questa può essere derivata come una conseguenza![[Screenshot 2024-03-12 at 20.38.22.png]]
# Definizione
Siano $L$ e $L'$ due linguaggi sullo stesso alfabeto $\Sigma$, dicamo che $L$ é mapping riducibile a $L$ se esiste una TM che computa la funzione $f:\Sigma^* \to \Sigma^*$ tale che $x \in L' \iff f(x) \in L$ 
In questo caso scriviamo $L' \leq L$ 
- Sostanzialmente convertiamo il problema di appartenenza di L' nel problema di appartenenza per L.
# Proprietà
$$
L'\le L \wedge L \ decidibile \implies L' \  decidibile
$$
Se un linguaggio é decidibile e riduciamo un altro linguaggio a questo allora é decidibile
$$
L'\le L \wedge L \ indecidibile \implies L' \  indecidibile
$$
$$
L \ decidibile \ e \ L' \ no \implies L' \nleq L
$$
# Esempio: il problema della fermata su nastro vuoto
![[Screenshot 2024-03-19 at 18.58.05.png]]
Praticamente identico al problema della fermata, unicamente invece dell'input $x$ abbiamo sempre $\epsilon$ 
- Dobbiamo dimostrare che sia indecidibile
- Basta ridurre HALT al problema in modo tale da dimostrare l'indecidibilità
- Dobbiamo costruire una funzione **computabile** $f$ tale che se $<y,x>$ appartengono ad HALT allora $f(<y,x>)$ appartengono a ETH e viceversa ($\iff$) 
Procediamo per casi
- Se $y \not= code(M)$ per ogni $M$ (y non é codice di alcuna macchina) allora $f(<y,x>)\notin ETH$
	- Semplicemente, possiamo sempre capire se un determinato programma é codice per una macchina M, se non lo é allora sicuramente non appartiene a ETH
- Se $y=code(M)$ (é codice di una qualsiasi macchina), allora possiamo costruire una macchina in modo tale  