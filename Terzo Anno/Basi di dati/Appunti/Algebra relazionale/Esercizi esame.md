## Esame 2023-05-23

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


#### Esercizio 1:
Scrivere in algebra relazionale un'espressione algebrica che restituisca i nominativi delle persone che hanno acquistato biglietti per concerti pop tenutisi a Berlino.
##### Soluzione:
$$\Pi_{Nome}(\sigma_{Genere = 'pop'}(Artista) \bowtie_{Codice=Artista} \rho_{(CodiceC \leftarrow Codice)}(\sigma_{Città='Berlino'}(Concerti) \bowtie_{Codice=Concerto} \rho_{(CodiceB \leftarrow Codice)}Biglietti))$$
#### Esercizio 2:
Scrivere in algebra relazionale un'espressione algebrica che restituisca i nomi di città che non hanno mai ospitato un concerto rock.
##### Soluzione:
$$\Pi_{Città}(Concerti) - \Pi_{Città}(\sigma_{Genere='Rock'}(Artisti) \bowtie_{Codice = Artista} \rho_{(CodiceC \leftarrow Codice)}Concerti)$$
## Esame 2023-01-09

![[SCR-20240103-mfeh.jpeg]]

### Esercizio 1:
Scrivere in algebra relazionale un'espressione algebrica che restituisca il nome degli atleti Austriaci che tra il 2005 e il 2010 si sono piazzati nelle prime 3 posizioni dello slalom speciale.

#### Soluzione:
$$\Pi_{Nome}(\sigma_{Data \ge 01/01/2005 \land Data \le 31/12/2010 \land Disciplina = 'slalom speciale'}(Gara) \bowtie_{Codice = Gara} \rho_{(CodiceA, DataA \leftarrow Codice, Data)}(\sigma_{Nazione='Austria'}(Atleta) \bowtie_{Codice=Atleta} \sigma_{Piazzamento \le 3}(Partecipazione)))$$

### Esercizio 2:
Scrivere in algebra relazionale un'espressione algebrica che restituisca il luogo di gare che non sono mai state vinte da atleti locali (e.g., della stessa nazione.)

#### Soluzione:
	$$\Pi_{Luogo}(Gara) -  \Pi_{Luogo}(\sigma_{Nazione=Luogo}(Atleta \bowtie_{Atleta.Codice = Atleta} (\sigma_{Piazzamento=1}(Partecipazione) \bowtie_{Partecipazione.Gara = Gara.Codice} Gara)))$$
