# Chiusure
- Reminder: i linguaggi sono insiemi, possiamo ragionare su operazioni come unione, intersezione e complemento sullo stesso alfabeto $\Sigma$
- Su un insieme $X$ di linguaggi:
	- Unione
		- Dimostrazione $X$ chiuso per unione: $L_1 \in X \land L_2 \in X$ implica $L_1 \cup L_2 \in X$
	- Il complemento $L^-$ di un linguaggio su $\Sigma$ é $\Sigma^* - L$ 
		- Dimostrazione $X$ chiuso per unione: $L \in X$ implica $L^- \in X$ 
	- Concatenazione $L_1L_2=\set{yz | y \in L_1 \land z \in L_2}$ 
		- Dimostrare chiusura 
## Chiusura dei [[1-Macchina di Turing#Linguaggi decidibili|linguaggi decidibili]]
- Chiusi per complemento
	- Scambia Y e N
- Chiusi per unione ![[Screenshot 2024-03-12 at 19.34.21.png]]
- Chiusi per intersezione
- Chiusi per concatenazione ![[Screenshot 2024-03-12 at 19.34.03.png]]
## Chiusura dei [[1-Macchina di Turing#Linguaggi riconoscibili|linguaggi riconoscibili]]
  - Chiusi per concatenazione![[Screenshot 2024-03-12 at 19.36.02.png]]
- Chiusi per intersezione
- Chiusi per unione![[Screenshot 2024-03-12 at 19.36.43.png]]
- NON sono chiusi per intersezione a differenza di quelli decidibili
![[Screenshot 2024-03-12 at 19.38.03.png]]