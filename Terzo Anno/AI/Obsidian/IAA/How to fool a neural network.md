Sappiamo che le reti neurali non riconoscono immagini come il cervello umano, cercano dei pattern specifici all'interno di esse.
Una ricerca ha dimostrato che, aggiungendo ad un immagine una piccola perturbazione, impercettibile all'occhio umano, riusciamo ad imbrogliare la rete.![[Pasted image 20231216120127.png]]
Questa tecnica ha però bisogno di conoscere il funzionamento della rete per poter funzionare.

Ci sono altri tipi di attacchi che però sfruttano la rete come **blackbox**, riuscendo ad imbrogliarla non solo con delle immagini distorte, ma anche con pattern ben definiti.
![[Pasted image 20231216120316.png]]
Questa tecnica viene chiamata **evolutionary approach**
- Inizia con un immagine a caso
- In modo alternato, muta l'immagine e mantieni la modifica che ha prodotto la confidence più alta dalla rete neurale

## Perché possiamo imbrogliare le reti
Il fatto é semplice:
- Le immagini che hanno veramente senso sono infinitamente meno di quelle senza senso
- Se prendiamo un immagine composta di pixel casuali, sicuramente questa non avrà significato
	- Possiamo quindi ridurre la dimensione dei dati in input per riconoscere determinati pattern
	- Questo concetto é alla base degli [[Autoencoders]]