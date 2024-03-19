# Introduzione
Dalla [[2-Tesi di Church Turing]] abbiamo capito che
- Calcolabile da procedura algoritmica -> calcolabile da TM
Ora dobbiamo dimostrare che:
- Non calcolabile da una TM -> non calcolabile da nessuna procedura algoritmica
	- Non calcolabile né da programma né da qualsiasi computer (quantistico...)
- Ripassa i [[1-Macchina di Turing#Linguaggi decidibili]] e [[1-Macchina di Turing#Linguaggi riconoscibili]]
# Gradi di (in)calcolabilità
![[Screenshot 2024-03-12 at 20.13.27.png]]
# Un problema indecidibile
- Supponiamo che esista una codifica $code(-)$![[Screenshot 2024-03-12 at 20.14.20.png]]
  Ad esempio quello usato per la macchina di Turing universale
## Il problema della fermata
![[Screenshot 2024-03-12 at 20.15.18.png]]
- Halt é formato dalle coppie $x,y$ tali che $y$ é il codice di una macchina che ferma su $x$
- Halt é riconoscibile ma non decidibile
**Teorema**: il problema della fermata é riconoscibile ma non é decidibile
**Dimostrazione**: Dire che é riconoscibile (facile) dire che non é decidibile (difficile), assumendo che sia decidibile e dimostrando la contraddizione
### Dimostrazione di indecidibilità
- Costruiamo una TM ![[Screenshot 2024-03-12 at 20.20.18.png]]
## Il complemento di Halt
Il complemento di halt ci dice semplicemente che: dato un programma e un input, determina se il programma di input **non** terminerà mai l'esecuzione (ovvero entrerà in un loop)
A differenza di Halt, il quale é riconoscibile ma non decidibile, questo non é nemmeno riconoscibile. 

# Ricapitolando
Usando:
- **Teorema**: Se $L$ e $L^-$ sono riconoscibili allora $L$ é decidibile
- **Teorema**: HALT é riconoscibile ma non decidibile
Otteniamo:
- **Corollario**: i linguaggi riconoscibili **non** sono chiusi per complemento
- **Dimostrazione**: HALT é riconoscibile ma il suo complemento non lo é