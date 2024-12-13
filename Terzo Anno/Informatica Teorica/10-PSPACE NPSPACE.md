# Complessità di spazio
## Definizione
Sia M una [[1-Macchina di Turing]] che si ferma su tutti gli input. La sua complessità di spazio é definita come la funzione t :N→N, dove $t(n)$ é il massimo numero di celle del nastro che la testina di M visita su arbitrari input di lunghezza n. 
Sostanzialmente facciamo un'analisi simile a quella fatta per il tempo ma analizziamo quante celle sono necessarie su una macchina di Turing per risolvere un determinato problema.
## Classe di complessità di spazio
> $SPACE(t(n))$ é la collezione di tutti i linguaggi decidibili da una TM (deterministica, a un nastro) in spazio $O(t(n))$

> $NSPACE(t(n))$ é la collezione di tutti i linguaggi decidibili da una TM (non-deterministica, a un nastro) in spazio $O(t(n))$

> PSPACE é la classe dei linguaggi decidibili da una TM in spazio **polinomiale**

# Spazio vs Tempo
Possiamo mettere in relazione la complessità di spazio e la complessità del tempo. 
Una conclusione ovvia:
> P é inclusa in PSPACE, ovvero una macchina che va in t(n) non può usare più di s(n) celle. Questo ci dice che lo spazio é più **forte** del tempo sotto un certo punto di vista: anche se volessimo fare un algoritmo che cerca di riempire quante più celle possibili (diciamo n) ci metterà comunque almeno t(n).  $TIME(t(n)) \subseteq SPACE(t(n))$. 

Una considerazione più forte e meno ovvia é invece che NP é anche inclusa in PSPACE. Grazie ai teoremi imparati in precedenza ed in particolare il [[8-Teorema di Rice]] possiamo utilizzare il problema NP-completo SAT, dimostrare che é in PSPACE e di conseguenza dimostrare che NP é in PSPACE.
## NP é in PSPACE
**Teorema**: $NP \subseteq PSPACE$ 
**Prova**: $SAT \in PSPACE$

### Idea
Immagina di dover creare una macchina che prova tutte le possibili formule booleane di lunghezza n per vedere quando una é soddisfacibile, questo può essere fatto semplicemente ad ogni iterazione scrivendo i valori 1 e 0 sul nastro occupando n spazi, all'iterazione successiva sostituisci la precedente.

### Dimostrazione
Con l'osservazione precedente (SAT é in PSPACE) e il Teorema di Cook-Levin ($L\leq_p SAT$)
possiamo concludere che L é in PSPACE, quindi qualsiasi linguaggio é in PSPACE.

# PSPACE-completeness
## Definizione
> Un linguaggio é PSPACE-completo se é in PSPACE e ogni altro linguaggio in PSPACE é poly-riducibile ad esso

## TQBFS
