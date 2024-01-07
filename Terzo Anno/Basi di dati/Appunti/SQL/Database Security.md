SQL permette di garantire per ogni utente privilegi specifici di lettura e scrittura, per l'intero database o solo per parte di esso

I privilegi possono essere garantiti a relazioni, attributi, view e domini, e deve esserci almeno un utente admin che abbia tutti i privilegi.

Qualsiasi utente crei una risorsa ha automaticamente tutti i privilegi su di essa

Un privilegio è descritto da:
- Una risorsa specifica
- L'utente che specifica il privilegio
- L'utente che riceve il privilegio
- Un'operazione specifica (Read, Write, ...)
- Se l'utente può propagare il privilegio oppure no

### Privilegi:

```sql
INSERT | UPDATE | DELETE | SELECT | REFERENCES | USAGE
```

### Assegnare privilegi:

```sql
GRANT < Privileges | ALL PRIVILEGES > ON Resource
TO Users
[ WITH GRANT OPTION ]

--Esempio
GRANT SELECT ON Department TO Jack
```
Grant option permette di all'utente di propagare il privilegio ad altri utenti

### Revocare privilegi:
I privilegi possono essere revocati utilizzando la keyword REVOKE, quest'operazione può essere effettuata solo da chi ha garantito quei privilegi

```sql
REVOKE Privileges ON Resource
FROM Users
[ RESTRICT | CASCADE ]
```

RESTRICT (default):  L'operazione non impatta anche gli utenti a cui sono stati assegnati i privilegi da questo utente

CASCADE: Rimuove i privilegi a cascata



L'implementazione di SQL punta a nascondere le parti del database che non sono accessibili all'utente. 

Si può pensare di utilizzare una view per mostrare solo delle tuple specifiche ad un utente, quindi dare all'utente i permessi sulla view

### Autorizzazione
Il sistema di autorizzazione utilizzato in SQL-3 è RBAC (Role Based Access Control), ogni ruolo agisce come un contenitore di privilegi, in ogni momento, ogni utente ha entrambi sia i permessi che gli sono stati garantiti individualmente, sia quelli associati al suo ruolo di RBAC

```sql
-- Creare un ruolo
CREATE ROLE RoleName

-- Assegnare il ruolo all'utente corrente
SET ROLE RoleName
```

Esempio:
Garantire il permesso di creare tabelle ad un utente specifico tramite il ruolo di Employee
```sql
-- Crea il ruolo
CREATE ROLE Employee;
-- Assegna il permesso di creare tabelle a quel ruolo
GRANT CREATE TABLE TO Employee;
-- Assegna il ruolo ad un utente
GRANT Employee TO user1;
-- Rimuovi il permesso dal ruolo
REVOKE CREATE TABLE FROM Employee
```