
## Relationships
Stabilire associazioni tra due o più entità, es: residenza (tra persone e città), esame (tra studente e corso). La relazione è anche chiamata associazione o correlazione

### Types of relationships

Relazioni binarie: coppia di istanze di entità, una per ogni entità coinvolta (es: id_utente nella tabella Dipartimenti e id nella cartella utenti)

Relazioni n-arie: tupla di istanze di entità, una per la prima entità e n per la seconda coinvolta (es: id_utente nella cartella ordini e id nella cartella utente)

Non possono esistere ripetizioni di istanze di coppie di tuple all'interno delle relazioni


#### Esempio:
![[SCR-20240107-mnfm.png]]

Il blocco exam in questo caso rappresenta solo la relazione tra studente e corso, vediamo un caso:

![[SCR-20240107-mnot.png]]

Vediamo che c'è la possibilità che uno studente ripeta uno stesso esame, questo renderebbe invalido il nostro sistema di relazione binaria

La soluzione è quella di promuovere Exam da relazione ad entità connessa da una parte a Student e da un'altra a Course
![[SCR-20240107-nygr.png]]


### Cardinalità delle relazioni
Esistono tre principali categorie di relazioni con cardinalità tra entità
- 1 to 1
- 1 to many
- many to many