#### Creazione di un database

``` sql
CREATE DATABASE db_name
```


#### Creazione di uno schema

``` sql
CREATE SCHEMA sc_name
```


#### Definire il possessore di uno schema
Utilizzato dopo il comando di creazione

```sql
AUTHORIZATION 'user_name'
```

#### Definire una nuova istanza e relazione
Specifica i suoi attributi con i relativi tipi e vincoli.

Esempio con Employee

```sql
CREATE TABLE Employee(
	Number CHAR(6) PRIMARY KEY,
	Name CHAR(20) NOT NULL,
	Surname CHAR(20) NOT NULL,
	Dept CHAR(15),
	Wage NUMERIC(9) DEFAULT 0,
	
	FOREIGN KEY(Dept) REFERENCES Department(Dept),
	UNIQUE (Surname, Name)
)
```

#### Constraint
I constraint di sql sono dei vincoli che un determinato campo di una tabella deve rispettare

##### Not Null
```sql
NOT NULL
```

Implica che il campo non può essere NULL, deve necessariamente esserci un valore associato per ogni istanza della tabella

##### Unique
```sql
UNIQUE
```

Implica che nella tabella ogni istanza deve avere un valore diverso di questo campo, non possono coesistere due istanze con lo stesso valore segnalato con UNIQUE

L'attributo può essere utilizzato anche successivamente nella specifica dei vincoli per definire tuple di valori unici
```sql
UNIQUE(Name, Surname)
```

##### Primary Key
```sql
PRIMARY KEY
```

Attributo che specifica che quel campo è la chiave primaria degli elementi, esso implica il constraint (NOT NULL)

##### Check
Il constraint di check viene utilizzato per specificare dei constraint più complessi da applicare sulle tuple, questa possibilità non è però supportata da tutte le implementazioni di SQL
```sql
CHECK (Salary <= (SELECT salary 
				  FROM Employee J
				  WHERE Supervisor = J.Number) )
```
È possibile inserire all'interno del constraint di check anche espressioni aritmetiche con variabili presenti nella tabella che si sta specificando

Si può pensare anche di definire un constraint a livello schema
```sql
CREATE ASSERTION AssertionName CHECK (Predicate)

--Esempio Il numero di elementi della tabella impiegati non può essere inferiore ad 1:
CREATE ASSERTION AtLeastOneEmployee
	CHECK (1 <= ( SELECT COUNT(*) FROM Employee ))
```

 
#### Referential Triggers
Ogni volta che un determinato constraint non è rispettato si possono programmare delle azioni, se questi non vengono definiti si assume che sia per DELETE che UPDATE ci sia NO ACTION. Non definendo i trigger nel momento in cui si elimina o si aggiorna una tupla referenziata, l'azione non verrà performata in quanto si violerebbe l'integrità del db.

Sintassi:
```sql
ON < DELETE | UPDATE > < CASCADE | SET NULL | SET DEFAULT | NO ACTION >
```

##### SET NULL
Setta il valore a NULL, ma se il campo è segnato con il constraint NOT NULL viene sollevata un'eccezione

##### SET DEFAULT
Setta il valore come specificato nel constraint DEFAULT, se però il constraint non è definito viene utilizzato il valore di default di quel dominio, se il database è in "strict mode" invece viene sollevata un'eccezione.

#### Schema change statements

##### ALTER DOMAIN
Permette di modificare domini già esistenti, va utilizzato insieme alle azioni 
```sql
SET DEFAULT | DROP CONSTRAINT | DROP DEFAULT | SET CONSTRAINT
```

Esempio:
```sql
-- Setta il valore default del dominio grade a 30
ALTER DOMAIN Grade SET DEFAULT 30

-- Rimuove il valore di default del dominio grade
ALTER DOMAIN Grade DROP DEFAULT

-- Aggiunge il constraint isValid al dominio grade
ALTER DOMAIN Grade SET CONSTRAINT isValid CHECK (value >=18 AND value <=30)

-- Rimuove il constraint isValid dal dominio grade
ALTER DOMAIN Grade DROP CONSTRAINT isValid
```

##### ALTER TABLE
Permette di modificare tabelle esistenti, va utilizzato insieme alle azioni
```sql
ALTER COLUMN | ADDCOLUMN | DROP COLUMN | DROP CONSTRAINT | ADD CONSTRAINT
```

Esempio:
```sql
-- Setta il constraint not null all colonna number nella tabella employee
ALTER TABLE Employee ALTER COLUMN Number SET NOT NULL

-- Aggiunge la colonna Level alla tabella Employee
ALTER TABLE Employee ADD COLUMN Level CHARACTER(10)

-- Rimuove la colonna Level dalla tabella Employee
-- L'argomento RESTRICT fa si che la colonna venga eliminata solo se non contiene valori
ALTER TABLE Employee DROP COLUMN Level RESTRICT

-- L'argomento CASCADE fa si che oltre alla colonna eliminata vengano eliminati tutti i valori di questa
ALTER TABLE Employee DROP COLUMN Level CASCADE

-- Come al dominio possiamo aggiungere un constraint anche ad una tabella
ALTER TABLE Employee ADD CONSTRAINT validNum CHECK (char_length(Number) = 10)

-- Possiamo anche rimuoverlo
ALTER TABLE Employee DROP CONSTRAINT validNum
```

##### DROP DOMAIN
Rimuove un tipo di dato personalizzato
```sql 
DROP DOMAIN Grade
```

##### DROP TABLE
Rimuove una tabella dal database
```sql 
DROP TABLE Users
```

#### Indices
Gli indici sono un modo di ristrutturare una tabella in modo da indicizzarla in base ad un campo, questo è utile in quanto velocizza di molto le query riguardanti quel campo specifico. Sono definite a livello fisico 

```sql
-- Crea l'indice idx_Surname sulla tabella Officer sul campo Surname
CREATE INDEX idx_Surname ON Officer(Surname)
```
#### Views
Le view di SQL sono un modo di salvare query complesse che necessitano di essere ripetute più volte come se fossero delle tabelle
```sql
-- Sintassi:
CREATE VIEW ViewName [ ( Attlist ) ] AS SelectStatement
[ WITH [ LOCAL | CASCADED ] CHECK OPTION ] 
```

Esempio:
```sql
CREATE VIEW AdminEmployees (Name, Surname, Salary) AS
SELECT Name, Surname, Salary 
FROM Employee
WHERE Dept = 'Administration' AND Salary > 10
```
Una volta creata questa view possiamo interagirci come se fosse una vera e propria tabella
```sql
SELECT * FROM AdminEmployees
```

##### Update della view
È possibile abilitare l'aggiornamento di una view utilizzando determinate keyword 
```sql
CREATE VIEW PoorAdminEmployees AS
SELECT *
FROM AdminEmployees
WHERE Salary < 50
WITH CHECK OPTION
```
CHECK OPTION permette di aggiornare la view ma solo se i nuovi elementi soddisfano le condizioni della view