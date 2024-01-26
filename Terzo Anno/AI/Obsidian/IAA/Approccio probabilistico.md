Invece di calcolare $f:X\to Y$ possiamo calcolare $P(Y|X)$
**PK:**  In questo modo possiamo trovare 
## Ripasso di probabilità
Vedi da goodnotes

## Naïve Bayes

### Bayes vs distribuzione congiunta
- Utilizziamo Naïve Bayes invece che la distribuzione congiunta per un problema di complessità.
- La probabilità congiunta funziona solo se abbiamo a disposizione grandi quantità di dati
	- Bayes funziona anche per stime con pochi dati di training
- 
### Perché naive?
Non considera la dipendenza tra i parametri, ad esempio:
- In un sistema di detection anti-spam, non consideriamo l'ordine delle parole ma solo la loro quantità
![[Pasted image 20231214123444.png]]
- Nel caso in cui la probabilità di un unico evento sia 0, tutta la probabilità viene annullata
![[Pasted image 20231214124252.png]]
### Calcolo di probabilità con naïve Bayes
![[Pasted image 20231214150442.png]]
In parole semplici, la probabilità che l'esito di un certo evento $Y$ sia $y_i$ (ad esempio spam=true) sapendone i parametri in input $X_1,...X_n$ (ad esempio la quantità di quelle parole presenti) é uguale alla probabilità che l'esito sia proprio $y_i$ moltiplicata per tutte le probabilità che i parametri in input siano verificati in $y_i$  e non so perche divide poi.
### Calcolo di quale classe piú probabile con naïve Bayes
![[Pasted image 20231214151100.png]]
Semplicemente svolgiamo il calcolo precedente per ogni possibile classe di $Y$ e prendiamo la probabilità maggiore.
![[Pasted image 20231214151154.png]]

## Accuracy, Precision and Recall
![[Pasted image 20231217175408.png]]