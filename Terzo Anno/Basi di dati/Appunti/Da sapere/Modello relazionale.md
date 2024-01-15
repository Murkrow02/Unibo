## Metodi logici
- Gerarchico
	- Usa puntatori esplicitamente
- Rete
	- Usa puntatori esplicitamente
- Relazionale
	- Value based
	- I riferimenti tra dati delle relazioni sono immagazzinati tramite valori 
	- Le relazioni sono rappresentate tra le tabelle
	- L'utente e il programmatore vedono gli stessi dati

## Tuple constraints
- Esprimono regole sui valori di ogni tupla, indipendentemente da altre tuple
	- Esempio: domain constraints
		- Esprimono constraint su un singolo attributo
	- Esempio: (grade >= 18) AND (grade <= 30)

## Chiave
Set di attributi che identifica univocamente tuple in una relazione
### Superchiave
Set $K$ di attributi su $r$ tali che:
-  Non ci sono due diverse tuple $t_1$ $t_2$ in $r$ tali che $t_1[K]=t_2[K]$ 
- Ovvero, se due tuple diverse hanno la stessa superchiave $K$ allora le due tuple sono distinte
### Chiave minimale
Se eliminiamo un qualsiasi attributo dal set $K$ allora non identifica piú univocamente una tupla

## Chiave primaria
- Non ammettono valori nulli
- Sono sottolineate 

## Constraints
Corrispondono alle proprietà del mondo reale, modellate all'interno del database
Sono modellate sullo schema della tabella e quindi si applicano a tutte le tuple
### Referential integrity constraint
Questo particolare tipo di constraint ci assicura che se una tabella X ha riferimenti verso una tabella Y utilizzando la sua chiave primaria, questi saranno sempre coerenti.


