https://www.youtube.com/watch?v=9zKuYvjFFS8
## Cosa sono?
Particolare tipo di rete neurale che riesce a ricostruire un particolare dato da una rappresentazione interna
![[Pasted image 20231216183837.png]]
La particolarità sta nel fatto che la rappresentazione interna ha una dimensione quasi sempre inferiore rispetto all'immagine in input.
- Questo perché riesce a capire quali sono le feature realmente importanti
- Da quelle riesce in un secondo momento a ricreare l'output
## Ma come?
- Exploitiamo correlazioni tra le feature presenti nei dati
- Se l'input ha molta entropia (dati poco correlati) allora il procedimento non funziona
- La compressione é diversa da quella effettuata sui file in quanto l'output non é mai uguale all'input
## A cosa servono?
- Denoise
- Anomaly detection
- Feature extraction
- Generative models

## Anomaly detection
Il concetto di autoencoder funziona molto bene per l'anomaly detection in quanto il modello ha capito le feature essenziali di un determinato input e riesce a ricostruire alla perfezione solo quello
![[Pasted image 20231216184431.png]]