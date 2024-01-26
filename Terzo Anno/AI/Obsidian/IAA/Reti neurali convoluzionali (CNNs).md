Le reti neurali convuluzionali, sono particolari reti neurali che comprendono almeno un layer convoluzionale (filtro).
Un filtro non é altro che una matrice (nella grande maggioranza dei casi di dimension 3x3) che viene applicata 
Il risultato della convoluzione viene applicato al pixel centrale
![[What are Convolutional Neural Networks (CNNs) .mp4]]
## Receptive field
A differenza delle reti convoluzionali tradizionali, l'attivazione di un neurone non dipende da ogni neurone del layer precedente ma unicamente da un suo sottoinsieme: il **campo ricettivo**.
Il campo ricettivo é definito unicamente su un neurone **deep, hidden**
Ogni neurone funge da filtro convoluzionale. Ogni neurone applica la stessa trasformazione su parti diverse dell'input. Un neurone non può vedere niente se non il suo campo recettivo.

![[Pasted image 20231215143222.png]]

## Diving deeper
Andando sempre più a fondo nella rete neurale otteniamo filtri sempre più complessi, che ci permettono di riconoscere e mettere insieme più feature semplici in sembianze globali dell'immagine.
![[What are Convolutional Neural Networks (CNNs) (1).mp4]]
## Riconoscere i pattern
![[Pasted image 20231215142610.png]]
![[Pasted image 20231215142628.png]]
 
## Tensori
Le reti neurali convoluzionali lavorano su tensori (array multidimensionali) come le immagini.
Un tipico tensore per le immagini é composto da:
- Size del batch
- Larghezza
- Altezza 
- Canali
#### Come fa il filtro a lavorare sui canali?
Di solito il filtro lavora su tutti i canali in parallelo (filtro 3-dimensionale
![[Pasted image 20231215143708.png]]
## Parametri di una rete convoluzionale
- Kernel size: dimensione del filtro lineare (es. 3x3)
- Stride: movimento del filtro lineare 
	- Con uno stride piccolo (es. unitario) i recettori si overlappano fortemente
	- Con uno stride grande abbiamo meno overlap e l'output diventa piú piccolo
- Padding: Allargamento artificiale dell'input che permette l'applicazione del filtro sui bordi
- Depth: numero di feature maps (messe in stack, i cosiddetti canali) che sono processati in parallelo
	- La depth dell'output layer dipende dal numero di kernel diversi che vogliamo sintetizzare
![[Pasted image 20231215154514.png]]
## Feature map
- Ogni kernel (filtro) produce una singola feature map.
- Feature map prodotte da kernel diversi sono messe in stack sulla dimensione del canale
- Il numero di kernel é uguale alla profondità di canale del layer successivo
- La dimensione spaziale dipende dal numero di kernel che vogliamo sintetizzare
	- Ognuno producente una feature map differente
  
  ## Input-output spatial relation
  fai
  ## Receptive field
  fai
  ## Pooling
  Operazione comune nelle Convolutional Neural Networks (CNNs) utilizzata per ridurre le dimensioni spaziali delle feature map. 
  - In ogni layer di pooling ogni neurone prende ad esempio il **massimo** o la **media** della regione del kernel
  - Hanno un doppio vantaggio
	  - Diminuiscono la dimensione spaziale
	  - Danno tolleranza alle transazioni
  
  ## Residual networks
  Vedi meglio https://www.youtube.com/watch?v=o_3mboe1jYI

### Transfer learning
https://www.youtube.com/watch?v=vmjP6LjGaag
- Allenando un certo modello, siamo riusciti ad astrarre dei pattern all'interno dei dati di test che possiamo generalizzare per altri task di classificazione
- I primi layer delle reti convoluzionali sono molto probabilmente totalmente estranei e indipendenti da quelle immagini che abbiamo dato come input per il training
- **Idea**: possiamo riutilizzare alcuni dei pattern trovati per altri scopi

Quando ha senso riutilizzare le conoscenze da un altro modello?
- Quando i due problemi sono simili
	- E.g. nel mondo reale se hai imparato a portare la bicicletta allora molto probabilmente riuscirai anche a portare la moto
- Quando abbiamo molti piú dati di training per la rete già allenata che per la rete ancora da allenare
- ![[Pasted image 20231215170825.png]]
## Come le CNNs vedono il mondo
Ci viene da pensare, come abbiamo anche dimostrato, che layer più profondi delle reti convoluzionali riescano a riconoscere feature sempre più complesse, ad esempio:
- All'inizio occhi
- Poi faccia
- Poi umano
Ma é davvero così?


### Formula per calcolare parametri di layer convolutivo
$$
Parametri=(\frac{dimensione_{kernelaltezza}}{stride}×\frac{dimensione_{kernellarghezza}}{stride}×inputchannels+1)×outputchannels
$$

$$
w_{new}=\frac{w_{old}-w_{filter}+2\cdot padding}{stride}
$$
$$
h_{new}=\frac{h_{old}-h_{filter}+2\cdot padding}{stride}
$$
$$
depth=numero_{kernel}
$$