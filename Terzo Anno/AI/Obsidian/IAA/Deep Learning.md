### Perché?
Branchia particolare del ML che é particolarmente adatto a risolvere problemi dove il numero di feature é enorme (immagini, audio....)
### Tipi di reti neurali
- Feed forward
	- Se la rete é aciclica
	- ![[Pasted image 20231214153434.png]]
	- Se é presente piú di un layer nascosto allora é una **deep** network, altrimenti **shallow**
- Ricorrente
	- Se la rete ha cicli
### Dense layer
Se ogni nodo di un layer é collegato ad ogni neurone del layer successivo é detto **denso**

### Operazione dei neuroni
Ogni neurone svolge la seguente operazione
$$
O_1 = I_n\cdot W_n + B_1
$$
Ovvero, l'output del neurone é uguale all'input del neurone precedente moltiplicato per il peso dell'input più il bias.

# Perceptron 
Forma di neurone artificiale, visto come pezzo unico di un layer di una rete neurale che imita il funzionamento dei neuroni del cervello umano
![[Pasted image 20231214153232.png]]
Nell'esempio, stiamo usando una funzione di attivazione binaria, ovvero:
![[Pasted image 20231214160240.png]]
L'output é 1 unicamente e la somma di tutti i pesi in input + il bias é maggiore di 0
### Un perceptron é logicamente completo?
Ad esempio, possiamo rappresentare il componente NAND attraverso un singolo perceptron?
![[Pasted image 20231214160713.png]]
Con l'esempio sopra siamo riusciti a rappresentarlo, infatti unicamente se i $x_1,x_2$ sono entrambi accesi, il neurone non si attiva.
![[Pasted image 20231214160819.png]]
Se invece volessimo rappresentare lo XOR la situazione cambia
![[Pasted image 20231214160856.png]]
In questo caso non é presente nessuna linea che divide le palle rosse da quelle verdi.
Quindi, riusciamo a costruire la NAND e sappiamo che questa é logicamente completa, ma non riusciamo a fare lo XOR, arriviamo alla conclusione che il perceptron non é logicamente completo, ma combinandone in più layer otteniamo una rete logicamente completa.

![[Pasted image 20231214161659.png]]
Esempio di XOR con 2 neuroni
### Perché usare reti deep quando le shallow sono logicamente complete
- Con reti deep la stessa funzione puó essere computata con meno neuroni
- Le funzioni di attivazione (che introducono la non-linearità), aumentano l'espressività del modello
# Training
## Current loss
![[Pasted image 20231214184728.png]]
Se abbiamo una rete neurale con vettore di parametri $\theta$ (pesi e bias):
- Gli diamo dei dati in input e passiamo attraverso la rete
	- Forward pass
- Ne calcoliamo l'output
- Prendiamo il **ground truth**, ne confrontiamo la differenza con gli attuali parametri $\theta$
- Cerchiamo di minimizzare la differenza tra il nostro risultato e quello reale tramite un tweak dei parametri di $\theta$
## Parameter updating
![[Pasted image 20231214184712.png]]
- Una volta trovata la loss, vogliamo aggiustare i parametri di $\theta$ in modo tale da minimizzare la current loss.
- Ogni parametro può essere incrementato o decrementato
- Il modello matematico per farlo é ovviamente il gradiente
## Backpropagation
Il gradiente é calcolato all'indietro. 
![[Gradient descent, how neural networks learn Chapter 2, Deep learning.mp4]]
### Problemi della backpropagation
Il neurone a livello $l$ calcola la seguente funzione
$$
a^l=\sigma(w^l + b^l \cdot + a^{l-1})
$$
Dove
- $\sigma$ é la funzione di attivazione
- $w^l$ é l'input pesato a livello $l$
- $b^l$ é il bias a livello $l$
- $a^{l-1}$ é il neurone precedente
Di conseguenza abbiamo che la formula calcolata dalla rete neurale é:
$$
\sigma(b^l + w^l \cdot ...\sigma(b^2+w^2\cdot \sigma(b^1+w^1)))
$$
Per aggiustare i pesi dobbiamo necessariamente trovare la derivata della funzione $\sigma$ (in particolare il gradiente) e sappiamo che se il gradiente é prossimo allo zero, allora l'apprendimento é impossibile. Questo é noto come il problema del **vanishing gradient**.
![[Pasted image 20231215130310.png]]
Possiamo notare che la derivata della sigmoide é quasi sempre sotto 0.25. Per anni questo é stato un problema fino all'introduzione della funzione RELU.
![[Pasted image 20231215130421.png]]
