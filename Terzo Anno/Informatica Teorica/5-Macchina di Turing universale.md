# Definizione
Una macchina di Turing universale é semplicemente una [[1-Macchina di Turing]] che prende in input non solo dei dati ma anche del codice
- Semplicemente si é scoperto che anche il programma é astraibile come dato della macchina stessa
- La macchina di Turing universale non prende più in input solo $x$ ma una stringa del tipo $$y=Code(M)code(x)$$Dove la funzione $code(-)$ é una codifica, $M$ é una TM e $x$ é una stringa dell'alfabeto di input $\Sigma_I$ di $M$
- Se é così allora UTM simula l'esecuzione di $M$ su $x$

![[Screenshot 2024-03-12 at 19.40.49.png]]
## Simulare M
- Eseguire la UTM su $y=code(M)code(x)$ dovrebbe dare lo stesso risultato che eseguire $M$ su input $x$ ![[Screenshot 2024-03-12 at 20.00.30.png]]
# Costruzione della UTM
Vedi da slide