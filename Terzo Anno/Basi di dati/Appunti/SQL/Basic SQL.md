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