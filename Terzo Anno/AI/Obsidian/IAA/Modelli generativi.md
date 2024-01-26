## Categorie
- Compressivi
	- VAEs
	- GANs
- Mantengono la dimensione
	- Normalizing flows
	- Denoising Diffusion Models
## VAEs 
![[Pasted image 20231217140936.png]]
- https://www.youtube.com/watch?v=fcvYpzHmhvA
- Il generatore é accoppiato con un encoder
- È una rete allenata per ricostruire i dati in input tramite una rappresentazione interna
- Con un normale autoencoder non possiamo generare dati dallo spazio latente
	- Non conosciamo la distribuzione delle variabili
	- ![[Pasted image 20231217141317.png]]Autoencoder classico
  - https://www.youtube.com/watch?v=fcvYpzHmhvA
- Con un variational autoencoder invece cerchiamo di ridurre le variabili dello spazio latente ad avere una distruibuzione $P(z)$ 
- A differenza degli autoencoder, i variational autoencoders fanno un lavoro differente:
- ![[Variational Autoencoders - EXPLAINED.mp4]]
## GAN (generative adversarial network)
![[Pasted image 20231216191852.png]]
- Sostanzialmente, due sotto-modelli "avversari" che si battagliano
- All'inizio si allena solo il discriminatore con dei dati veritieri e il generatore sta fermo
- In seguito quando il discriminatore é sufficientemente allenato si procede ad attivare generatore
- Il generatore genera dei campioni a partire dallo spazio latente (inizialmente poco accurati)
- Man mano andando avanti il generatore apprende dal discriminatore
- Man mano il discriminatore ha altri dati su cui allenarsi grazie al generatore
- Inoltre il discriminatore viene informato di quando ha sbagliato e ha dato ragione al fake prodotto dal generatore
- Quando uno dei due sbaglia, solo quello che ha sbagliato viene aggiornato
- ![[Pasted image 20231217150649.png]]
  - Problemi
	  - Il fatto che il discriminatore venga imbrogliato non significa che sicuramente il generatore sia stato allenato bene
	  - **Collasso su un singolo**: il modello riesce a generare perfettamente un tipo molto specifico di fake
## Diffusion models
![[What are Diffusion Models .mp4]]
