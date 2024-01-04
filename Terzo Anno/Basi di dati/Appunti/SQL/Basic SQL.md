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

#### Referential Triggers
Ogni volta che un determinato constraint non è rispettato si possono programmare delle azioni

Sintassi:
```sql
ON < DELETE | UPDATE > < CASCADE | SET NULL | SET DEFAULT | NO ACTION >
```
