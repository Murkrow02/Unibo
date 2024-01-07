## Operazioni di selezione
L'operatore SELECT serve a selezionare uno o più campi di una tabella o relazione che rispecchino una determinate condizione

```sql
SELECT <Attributelist> FROM <TableList> [ WHERE <Condition> ]
```

### Renaming
È possibile rinominare uno o più campi all'interno della relazione utilizzando l'operatore AS durante la SELECT

```sql
SELECT p.Name AS GivenName, p.Income AS Revenue FROM People AS p WHERE p.Age < 30
```

Output:

| GivenName | Revenue |
| ---- | ---- |
| Jim | 21 |
| James | 15 |
| Phil | 30 |
### Condizioni Composte
È possibile concatenare più condizioni dopo la clausola WHERE utilizzando gli operatori binari AND e OR

```sql
SELECT * FROM People
	WHERE Income>25 AND (Age<30 OR Age>60)
```

### Operatore LIKE
L'operatore like funziona con una sorta di regex, esso applicato sulle stringhe cerca i pattern che combaciano con il suo argomento
```sql
-- Seleziona gli elementi il cui nome inizia con J e la terza lettera è m
SELECT * FROM People WHERE Name LIKE 'J_m%'
```

### Operatore IS NULL
L'operatore is null ritorna true se il valore esaminato è nullo false altrimenti
```sql
SELECT * FROM Employee WHERE Age>40 OR Age IS NULL
```

### Clausola DISTINCT
La clausola Distinct fa si che in output non vengano mostrati mai risultati duplicati

```sql
SELECT Surname, Agency FROM Employee
```

Output:

| Surname | Agency |
| ---- | ---- |
| Neri | Naples |
| Neri | Milan |
| Rossi | Rome |
| Rossi | Rome |

Ma con distinct

```sql
SELECT DISTINCT Surname, Agency FROM Employee
```

Output:

| Surname | Agency |
| ---- | ---- |
| Neri | Naples |
| Neri | Milan |
| Rossi | Rome |

### Cartesian Product
Utilizzando più tabelle dopo l'operatore FROM, possiamo ottenere come risultato un prodotto cartesiano tra queste
```sql
SELECT DISTINCT R1.A1, R2.A4
	FROM R1, R2
	WHERE R1.A2 = R2.A3
```

Potrebbe essere necessario effettuare operazioni di aliasing o renaming quando si lavora con un prodotto cartesiano in quanto le colonne potrebbero avere lo stesso nome

```sql
SELECT X.A1 AS B1, . . .
FROM R1 X, R2 Y, R1 Z 
WHERE X.A2 = Y.A3 AND ...
```

### Expressions on targets
Si possono applicare delle operazioni direttamente sui risultati richiesti dall'interrogazione

```sql
-- Il valore halvedIncome sarà uguale ad Income / 2
SELECT Income/2 AS halvedIncome
FROM People
WHERE Name = 'Louis'
```

### Inner Join
Il join come in algebra relazionale corrisponde ad un prodotto cartesiano che passa per una condizione

Sintassi:
```sql
SELECT ...
FROM LeftTable { ... JOIN RightTable ON joincondition }, ...
[ WHERE otherPredicate ]
```

### Natural Join
Come in algebra relazionale rappresenta il join con la condizione che esistano due colonne con lo stesso nome e lo stesso tipo su cui fare il join

```sql
SELECT mother, child, father
FROM Motherhood NATURAL JOIN Fatherhood
```

### Outer Join
L'outer join include nei risultati anche le tuple che sono state scartate dalla condizione, ma inserisce al posto delle condizioni non rispettate NULL

(Se non capisci vedi la spiegazione di algebra relazionale, è lo stesso concetto)

Sintassi:
```sql
< LEFT | RIGHT | FULL > OUTER JOIN
```

### Recap JOINS

![[SCR-20240106-lrmw.png]]



### Sorting
È possibile ordinare gli elementi alla fine di una query utilizzando la keyword ORDER BY, l'attributo ASC implica di ordinare in ordine crescente, mentre DESC in ordine decrescente. Il valore di default è DESC quando non viene specificato

```sql
ORDER BY <value> <ASC | DESC>

--Example:
SELECT name, income 
FROM People
WHERE age < 30 
ORDER BY name ASC
```

### UNION
L'operatore union concatena due relazioni purchè queste abbiamo lo stesso numero di campi e purchè il tipo del campo i della relazione 1 corrisponda al tipo del campo j della relazione 2

#### Set Union
Unisce i risultati delle due query escludendo i duplicati
```sql
SELECT child 
FROM Motherhood 
UNION
SELECT child 
FROM Fatherhood
```

#### Multiset Union
Unisce i risultati delle due query includendo i duplicati
```sql
SELECT child 
FROM Motherhood 
UNION ALL
SELECT child 
FROM Fatherhood
```

Quando due tavole hanno uno schema diverso supponiamo di prendere il nome degli elementi del primo operando

ATTENZIONE: L'ordine degli elementi della select è importante in questo tipo di operazioni

### Differenza
La differenza gode delle stesse condizioni di esistenza dell'unione, ma fa l'opposto, rimuove gli elementi di B presenti in A

```sql
SELECT Name 
FROM Employee
EXCEPT
SELECT Surname AS Name 
FROM Employee
```

### Intersezione
L'intersezione sceglie solamente gli elementi che sono presenti sia in A che in B
```sql
SELECT Name
FROM Employee
INTERSECT
SELECT Surname AS Name
FROM Employee
```

Questa query corrisponde a:
```sql
SELECT E.Name
FROM Employee E, Employee F WHERE E.Name = F.Surname
```

### Nested Queries
È possibile incapsulare più query una dentro l'altra rendendo il codice più leggibile. L'unico limite è quello di non poter utilizzare operatori sui set (UNION, EXCEPT, INTERSECT) all'interno delle subquery.

```sql
SELECT Name, Income
FROM People
WHERE Name = ( SELECT Father 
				FROM Fatherhood
				WHERE Child = "Frank" )
```
### Operazioni sulle subquery
Le subqueries possono essere utilizzate insieme a delle operazioni come ALL o ANY e insieme a degli operatori aritmetici di comparazione
```sql
SELECT ...
FROM ...
WHERE Attribute <operator> <NOT |  > < ALL | ANY | IN > ( Subquery )
```

#### ANY
Una tupla della query esterna fa match se soddisfa il predicato con una qualsiasi delle tuple della subquery

#### ALL
Una tupla della query esterna fa match se soddisfa il predicato con tutte le tuple della subquery

#### IN
Una tupla della query esterna fa match se è contenuta negli elementi della subquery

#### NOT
La keyword not può essere utilizzata per negare la condizione successiva

#### Quantificazione esistenziale
Un espressione che ritorna true se una determinata query contiene una o più tuple, false altrimenti
```sql
EXISTS(Expr)

SELECT *
FROM People
WHERE EXISTS (SELECT *
				FROM Fatherhood
				WHERE Father = Name) 
	OR
	EXISTS (SELECT *
				FROM Motherhood
				WHERE Mother = Name)
```

ATTENZIONE:
I nomi dei campi delle tabelle fanno sempre riferimento al FROM più vicino, pertanto è necessario creare alias delle tabelle il quale scope si vuole mantenere all'interno delle subquery

### Funzioni aggregate
Esistono delle funzioni che operano su campi delle tuple basate sul dominio di queste, la keyword distinct viene utilizzata se necessario per evitare di includere i risultati duplicati nel calcolo

Sintassi:
```sql
Aggr([DISTINCT] *)
Aggr([DISTINCT] Attribute)
```

#### COUNT
La funzione count come suggerisce il nome è utilizzata per contare elementi, se uno di questi elementi è NULL, non viene contato nella COUNT
```sql
-- Conta il numero di elementi dell'output
SELECT COUNT( * ) AS NumFrankChildren
FROM Fatherhood
WHERE father = 'Frank'

-- Conta il numero di elementi che hanno il valore Income diverso
SELECT COUNT(DISTINCT Income)
FROM People
```
#### SUM
Somma gli elementi specifici di un campo

#### AVG 
Effettua la media aritmetica degli elementi specifici di un campo, se uno degli elementi è NULL non viene contato nella media aritmetica.



#### MAX
Ritorna il valore massimo degli elementi specifici di un campo

#### MIN
Ritorna il valore minimo degli elementi specifici di un campo


### Grouping
È possibile raggruppare i risultati di una query utilizzando la keyword GROUP BY
```sql
SELECT Father, COUNT(*) AS NumberofChildren 
FROM Fatherhood
GROUP BY Father
```

Per raggruppare gli elementi in modo più preciso è possibile applicare una condizione alla funzione di grouping utilizzando la clausola HAVING
```sql
SELECT Father, AVG(F.Income)
FROM People F JOIN Fatherhood ON F.Name = Child
GROUP BY Father HAVING AVG(F.Income) > 25
```

Durante il grouping tutti gli elementi chiave che hanno come valore NULL sono raggruppati insieme, come se fosse un altro elemento







Riassunto sulla sintassi del SELECT
```sql
SELECT AttList1+Exprs 
FROM TableList+Joins
[ WHERE Condition ]
[ GROUP BY AttList2]
[ HAVING AggrCondition]
[ORDER YB OrderingAttr1]
```
### Funzioni scalari
A livello tupla esistono svariate funzioni che permettono di manipolare i dati secondo domini specifici

#### Funzioni Temporali
```sql
current_date() --Ritorna la data di ora

EXTRACT(<DAY | MONTH | YEAR | HOUR | ...> FROM dateAttribute) --Estrae parte di una data grazie ad una specifica espressione
```
Esempio: ritornare l'anno degli ordini creati oggi
```sql
SELECT EXTRACT(YEAR from OrderDate) AS OrderYear,
FROM Orders
WHERE DATE(OrderDate)=current_date()
```

#### Editing delle stringhe
```sql
char_lenght() --Ritorna la lunghezza della stringa

LOWER --Converte la stringa in lowercase
```

#### Casting
```sql
CAST --Permette il casting di un valore ad un altro dominio
```

#### Condizionali

##### Coalescence
L'espressione coalescence prende in input diverse espressioni e ritorna la prima che non è NULL

```sql
-- Ritorna un numero mobile valido altrimenti un numero di casa valido
SELECT Number, COALESCENCE(Mobile, PhoneHome)
FROM Employee
```

Alternativamente potrebbe essere utilizzato per rimpiazzare i valori null con dei default fissati
```sql
SELECT Name, Surname, COALESCENCE(Dept, "None") 
FROM Employee
```

##### Nullif
L'espressione nullif compara due argomenti, il primo è un attributo di una relazione, mentre l'altro è una costante, l'espressione ritorna NULL se i due valori matchano altrimenti ritorna il valore del primo argomento
```sql
-- Ritorna null se il dipartimento è Unknown
SELECT Surname, NULLIF(Dept, 'Unknown')
FROM Employee
```

##### Case
La funzione di case permette di specificare strutture condizionali di cui i risultati dipendono dalla valutazione delle tabelle del db, in altre parole, fornisce una logica if-then-else al linguaggio SQL
```sql
SELECT PlateNo, 
	(CASE Type
		WHEN 'Car' THEN 2.58 * KWatt
		WHEN 'Moto' THEN (22.00 + 1.00 * KWatt)
		ELSE NULL
	END) AS Tax
FROM Vehicle
WHERE RegistrationYear > 1975
```

## Operazioni di aggiornamento
Le principali operazioni di aggiornamento delle tabelle sono
```sql
INSERT | UPDATE | DELETE
```

### INSERT
L'operazione insert applicata su una tabella serve ad aggiungere un nuovo record a questa
```sql 
INSERT INTO Table [(AttList)] VALUES(vals)

--oppure

INSERT INTO Table [(AttList)]
SELECT ...
```

Esempi:
```sql
INSERT INTO People VALUES ('John',25,52)

INSERT INTO People(Name, Age, Income) VALUES ('Jack', 25,52)

INSERT INTO People(Name, Income) VALUES ( 'Robert' , 55 )

INSERT INTO People( Name ) 
SELECT Father
FROM Fatherhood
WHERE Father NOT IN (SELECT Name FROM People)
```

ATTENZIONE:
L'ordine degli attributi è rilevante nell'insert ed entrambe le liste devono avere lo stesso numero di valori. Se la lista degli attributi è omessa, si assume che si voglia specificare un record con tutti i suoi valori, questi vanno tutti specificati. Mentre se decidiamo di aggiungere solo alcuni valori di un record, i valori non specificati verranno segnalati come NULL oppure otterranno il loro valore di DEFAULT

### DELETE
L'operazione di delete come suggerisce il nome serve ad eliminare delle tuple da una tabella
```sql
DELETE FROM Table 
[WHERE condition]
```

Esempi:
```sql
DELETE FROM People WHERE Age < 35

DELETE FROM Fatherhood
WHERE Child NOT IN ( SELECT Name
						FROM People ) 
						
DELETE FROM Fatherhood
```

ATTENZIONE:
La rimozione di tuple potrebbe comportare automaticamente la rimozione di tuple che sono in relazione con queste se esistono dei constraint definiti come CASCADE sulla ON DELETE.

Se nessuna condizione è specificata, tutti i record della tabella in input verranno eliminati
### UPDATE
L'operazione UPDATE permette di andare a manipolare i dati di tuple già esistenti
```sql
UPDATE TableName
SET Attribute = < Expr | SELECT ... | NULL | DEFAULT >
[WHERE condition]
```

##### Esempi
| Name | Age | Income |
| ---- | ---- | ---- |
| Jim | 27 | 30 |
| James | 25 | 15 |
| Bob | 55 | 36 |
Operazioni:
```sql
UPDATE People 
SET Income = 45
WHERE Name = Bob
```

|Name|Age|Income|
|---|---|---|
|Jim|27|30|
|James|25|15|
|Bob|55|45 |


```sql
UPDATE People 
SET Income = Income * 1.1
WHERE Age < 30
```

|Name|Age|Income|
|---|---|---|
|Jim|27|33 |
|James|25|16.5 |
|Bob|55|45 |


```sql
UPDATE People 
SET Income = NULL
WHERE Age < 30
```

|Name|Age|Income|
|---|---|---|
|Jim|27|NULL |
|James|25|NULL |
|Bob|55|45 |

### Transactions
SQL supporta l'utilizzo di transazioni: operazioni end-to-end che permettono di scambiare dati come bilanci in denaro con operazioni atomiche.

Il database durante queste operazioni utilizza una formula di stati per preservare l'integrità: prima di effettuare una transazione il DB salva il suo stato come consistente, al termine della transazione se non c'è stato alcun tipo di alterazione o violazione esegue un COMMIT del lavoro svolto, entrando in un nuovo stato consistente. Se invece durante l'operazione abbiamo delle violazioni allora il Database esegue un ROLLBACK per tornare allo stato precedente consistente.

Per garantire la sicurezza di queste operazioni è necessario quindi che non vengano interferite da altre, anche se più transazioni vengono eseguite concorrentemente è necessario che queste non influiscano sulle altre, onde evitare problemi e attacchi come quelli che sfruttano le "Race Condition".

Esempio:
Trasferire 10€ dall'account con id 42177 a quello con id 12202
```sql
START TRANSACTION
	UPDATE BanckAccount
	SET Balance = Balance - 10
	WHERE AccountNumber = 42177;

	UPDATE BankAccount
	SET Balance = Balance + 10
	WHERE AccountNumber = 12202;
COMMIT WORK
```