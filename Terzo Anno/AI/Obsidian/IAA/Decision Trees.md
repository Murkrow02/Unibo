Gli **alberi di decisione** sono una tecnica di apprendimento automatico utilizzata per fare previsioni o classificare i dati. Funzionano creando un modello basato su una serie di regole di decisione, dove ogni nodo dell’albero rappresenta una decisione da prendere e ogni ramo rappresenta una possibile conseguenza di quella decisione.

Per costruire un albero di decisione, si inizia dall’alto verso il basso, selezionando la feature che massimizza l’informazione sulla variabile da prevedere. A ogni passo, si seleziona la feature che fornisce il massimo guadagno di informazione, ovvero quella che meglio separa gli esempi positivi da quelli negativi.Si continua finché non si raggiunge una soglia di purezza desiderata o non ci sono più feature da considerare.

Gli alberi di decisione sono facili da comprendere e da interpretare, ma possono essere sensibili al rumore nei dati e tendono a sovrastimare le prestazioni durante il training. Tuttavia, questi svantaggi possono essere mitigati utilizzando tecniche come il pruning (potatura) degli alberi o l’utilizzo di un insieme di alberi di decisione come nel caso del random forest.
## Train set
Insieme di esempi di allenamento $< x^{(i)} y^{(i)}>$ dove $x^{(i)} \in X \ y^{(i)} \in Y$   
Ad esempio $<piove=true, nevica=false, caldo=false>$
**Problema**: apprendere come mappare x e y
**Y discreto**: (esempio true false): parliamo di classificazione
**Y continuo**: parliamo di regressione
Regressione e classificazione non dipendono quindi dal dominio ma dal codominio della funzione
## ![[Pasted image 20231213174125.png]]

## Entropia
IL SUO VALORE VA DA 0 A $\log_n$ dove $n$ é il numero di features
L'entropia misura la quantità impurità nell'informazione. È la quantità media di informazione prodotta da una sorgente di dati.

Ad esempio, in questo albero, nel primo nodo l'entropia é 1 in quanto il disordine é massimo.
L'entropia é invece 0 dove ci sono solo palle rosse in quanto il disordine é minimo.
La formula (semplice) é questa: 
$$
\sum -p_i \log_2(p_i)
$$
Sostanzialmente dice che l'entropia é pari alla sommatoria della probabilità $p_i$ in uno stato per il suo logaritmo. Il prof la riporta invece come segue
$$
H(X) =-\sum (X=i)log_2(X=i)
$$
L'entropia di una variabile aleatoria $X$ si rappresenta con $H(x)$
## Information gain e teoria dell'informazione
Possiamo definire l'information gain come la "sorpresa" di una determinata informazione.
Di conseguenza, se abbiamo un evento con probabilità = 1, abbiamo IG=0.

Quando costruiamo un albero di decisione, dobbiamo scegliere ad ogni fork la divisione che genererà il massimo guadagno di informazione. Per misurare il guadagno di informazione ad ogni fork seguiamo la seguente formula:
$$
IG = E(parent) - \sum p_i E(child_i)
$$
Quindi sostanzialmente quando facciamo una fork, possiamo calcolare l'informazione ottenuta sottraendo dall'entropia di partenza la sommatoria delle entropie dei nodi generati moltiplicati per la probabilitá.
In parole ancora più semplici, calcoliamo prima l'entropia del nodo padre (facile) poi calcoliamo l'entropia di tutti i nodi figli di quel nodo, moltiplichiamo ognuno per la probabilità di quel

## Il caso continuo (dominio)
Quando gli attributi di X sono continui, creiamo il nostro albero in base a tresholds
![[Pasted image 20231213181842.png]]
Continuiamo comunque a confrontare gli split in base al loro guadagno informativo ma...
Come scegliamo le soglie?

## Overfitting
Fenomeno che si verifica quando il modello allenato si é adattato troppo bene ai dati di training e non performa bene quando gli vengono forniti altri dati dal dataset. Questo avviene quando il modello non ha imparato a generalizzare dal dataset ma anzi, vi si é adattato troppo.

![[Pasted image 20231213183627.png]]
In questo esempio, la linea verde rappresenta un modello in overfitting mentre quella nera un modello che generalizza a sufficienza. A lungo andare il modello nero commetterà meno errori del verde. Questo può essere definito quanto segue:
$$
error_{train}(h) < error_{train}(h')
$$
Ma allo stesso tempo
$$
error_{D}(h) > error_{D}(h')
$$
Dove h' é una nuova ipotesi, train é il set allenato e D é il dataset completo. Sostanzialmente diciamo che l'errore é minore con gli stessi dati ma é maggiore con dei dati nuovi
![[Pasted image 20231213185210.png]]
### Come evitare overfitting
Il problema principale é che il dominio $D$ completo non é ovviamente accessibile, quindi ci limitiamo a dividere i dati in nostro possesso in due insiemi disgiunti:
- Training set (per ipotesi $h$)
- Validation set  (per misurare accuracy e overfitting)
Sono disponibili anche varie tecniche per evitare overfitting negli alberi di decisione:
- Fermarsi con la discesa dell'albero appena il guadagno informativo non é significativo
- Sviluppare l'intero albero e prunarlo all'indietro
	- Finché ogni ulteriore pruning non migliora l'accuratezza
		- Valutare con il **validation set** se la rimozione di un sottoalbero migliora l'accuratezza
		- In modo greedy, rimuovere il sottoalbero che migliora l'accuratezza
## Gini impurity
metti


###  Aspetti positivi
- Facili da capire e visualizzare
- Poco preprocessing
- Costo computazionale non elevatissimo
- Costo predittivo basso
- Sia feature discrete che continue
### Aspetti negativi
- Rischio di overfitting
- Selezione di attributi instabile al variare del dataset
- Facile costruire alberi sbilanciati

## Random forests
Risolvono il problema della mancata generalizzazione all'interno degli alberi di decisione e la loro forte dipendenza dai dati di training forniti.

Le random forests sfruttano il principio di **ensable**, dove si dimostra che un sufficiente numero di modelli sufficientemente scorrelati che operano come un unico comitato, di solito performano meglio rispetto al singolo.

Ad esempio, dallo stesso dataset possiamo prendere dei "sottoinsiemi" di feature e alla fine prendere il "majority voting" dei risultati appresi da ogni albero generato.
![[Pasted image 20231213194308.png]]
