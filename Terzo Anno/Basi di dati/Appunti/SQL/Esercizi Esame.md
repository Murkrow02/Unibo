## 2023-05-23

### Artista
| Codice | Nome | Genere |
| ---- | ---- | ---- |
| ART123 | Maneskin | pop rock |
| RTE543 | Bruce Springsteen | rock |
| DFG398 | Lazza | trap |
### Concerti
| Codice | Artista | Città | Data |
| ---- | ---- | ---- | ---- |
| 987 | RTE543 | Barcellona | 30/04/2023 |
| 765 | ART123 | Roma | 21/07/2023 |
| 432 | OPK687 | Londra | 12/06/2012 |
### Biglietti
| Codice | Concerto | Nome | Posto | Costo |
| ---- | ---- | ---- | ---- | ---- |
| ZXP | 987 | Mario Rossi | pit A | 130 |
| LKJ | 987 | Franco Verdi | unico  | 80 |
| OXZ | 122 | Luca Bianchi | pit B | 110 |
il contenuto delle tabelle è solamente un esempio; non possono trarsi conclusioni sull'assenza o la completezza dei dati. Ad esempio non è detto che non ci siano altri artisti rispetto a quelli elencati.



Scrivere in SQL una query che restituisca il costo medio dei biglietti per genere musicale per concerti tenutisi prima del 2021.

```sql
SELECT AVG(Costo) AS CostoMedio, Artista.Genere
FROM (Biglietti JOIN Concerti ON Biglietti.Concerto = Concerti.Codice)
	JOIN Artisti ON Concerti.Artista = Artisti.Codice
WHERE Concerti.Data < 01.01.2021
GROUP BY Artista.Genere
```

Scrivere in SQL una query che restituisca per ogni artista il nome e la data del concerto in cui ha venduto il maggior numero di biglietti.

```sql
CREATE VIEW X AS
SELECT Artista.Nome AS NA, Artista.Codice AS CA, Concerto.Data AS DC, COUNT(Biglietti.Codice) as CB 
FROM (Biglietti JOIN Concerti ON Concerti.Codice = Biglietti.Concerto) JOIN Artisti ON Concerti.Artista = Artisti.Codice
GROUP BY Artista.Codice, Biglietti.Concerto;


SELECT MAX(CB), NA, DC
FROM X
GROUP BY CA;
```

## 2023-01-09
![[SCR-20240103-mfeh.jpeg]]

### Esercizio 3
Scrivere in SQL una query che restituisca il nome e la data di nascita degli atleti italiani che non hanno mai partecipato a nessuna gara di discesa libera.

```sql
-- MIA SOLUZIONE
SELECT DISTINCT Nome, Data
FROM Atleta
WHERE Nazione = "Italia"
EXCEPT
SELECT DISTINCT Atleta.Nome, Atleta.Data
FROM (Partecipazione JOIN Atleta ON Partecipazione.Atleta = Atleta.Codice) JOIN Gara ON Partecipazione.Gara = Gara.Codice
WHERE Gara.Disciplina = "discesa libera" AND Atleta.Nazione = "Italia"

-- SOLUZIONE PROF
SELECT DISTINCT Atleta.Nome, Atleta.Data
FROM Atleta
WHERE Atleta.Codice NOT IN (
	SELECT Atleta.Codice
	FROM Atleta JOIN Partecipazione ON Atleta.Codice = Partecipazione.Atleta
	JOIN Gara ON Partecipazione.Gara = Gara.Codice
	WHERE Gara.Disciplina = "discesa libera"
) AND Atleta.Nazione = "Italia"
```



### Esercizio 4
Scrivere in SQL una query che restituisca le nazioni per cui concorrono almeno 5 atleti nati dopo il 1996, ciascuno dei quali abbia partecipato ad almeno 10 gare di sci di fondo.
```sql
-- Soluzione Mia
CREATE VIEW X AS
SELECT DISTINCT Atleta.Codice AS CA, Atleta.Nazione AS NA, COUNT(Gara.Codice) AS NG
FROM Atleta JOIN Partecipazione ON Atleta.Codice = Partecipazione.Atleta JOIN Gara ON Partecipazione.Gara = Gara.Codice
WHERE Atleta.Data > 31.12.1996 AND Gara.Disciplina = "sci di fondo"
GROUP BY Atleta.Codice;

CREATE VIEW Y AS
SELECT X.NA AS YNA, COUNT(*) AS NC
FROM X
WHERE X.NG >= 10
GROUP BY X.NA;

SELECT DISTINCT YNA
FROM Y
WHERE NC >= 5;

-- Soluzione PROF
CREATE VIEW V AS
SELECT A.*
FROM Atleta A
JOIN Partecipazione P ON A.Codice = P.Atleta
JOIN Gara G ON P.Gara = G.Codice
WHERE A.Data >= 01/01/1997 AND G.Disciplina = "sci di fondo"
GROUP BY A.Codice
HAVING COUNT(G.Codice) >= 10;

SELECT DISTINCT V.Nazione
FROM V
GROUP BY V.Nazione
HAVING COUNT(V.Codice) >= 5;

```