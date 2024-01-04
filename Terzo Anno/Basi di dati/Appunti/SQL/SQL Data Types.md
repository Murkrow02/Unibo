## Tipi di dato testuali

### Stringhe di lunghezza fissa

```sql
-- Stringa di lunghezza fissa (può contenere lettere, numeri e caratteri speciali). Il parametro size specifica la lunghezza del valore in caratteri e può variare tra 0 e 255 il default è 1

CHAR(size)
```

```sql
-- Stringa di lunghezza variabile (può contenere lettere, numeri e caratteri speciali). Il parametro size specifica la lunghezza massima della stringa e può variare tra 0 e 65535

VARCHAR(size)
```

### Binary di lunghezza fissa

```sql
-- Uguale a CHAR, ma memorizza stringhe binarie, il parametro size specigicha la lunghezza del valore in byte

BINARY(size)
```

```sql
-- Uguale a VARCHAR, ma memorizza stringhe binarie, il parametro size specigicha la lunghezz massima del valore in byte

VARBINARY(size)
```


### Stringhe di lunghezza variabile

```sql
-- Stringa con lunghezza massima di 255 caratteri

TINYTEXT
```

```sql
-- Stringa con lunghezza massima di 65.535 byte

TEXT
```

```sql
-- Stringa con lunghezza massima di 16.777.215 caratteri

MEDIUMTEXT
```

```sql
-- Stringa con lunghezza massima di 4,294,967,295 caratteri

LONGTEXT
```

###  BLOBs di lunghezza variabile

```sql
-- Per i BLOBs (Binary Large Objects), Lunghezza massima 255 bytes

TINYBLOB
```

```sql
-- BLOB con lunghezza massima di 65535 bytes di dati

BLOB
```

```sql
-- BLOB con lunghezza massima di 16.777.215 bytes di dati

MEDIUMBLOB
```

```sql
-- BLOB con lunghezza massima di 4,294,967,295 bytes di dati

LONGBLOB
```

### Stringhe di valore specifico

```sql
-- Una stringa che può avere un valore tra quelli definiti nella dichiarazione dello schema, si possono avere fino a 65535 valori all'interno dell'ENUM. Se il valore inserito non si trova all'interno della lista, il campo verrà contrassegnato come vuoto. I valori sono ordinati nel modo in cui vengono definiti

ENUM(val1, val2, val3, ...)
```

```sql
-- Una stringa che può avere 0 o più valori, scelti da una lista di possibili valori, si possono avere fino a 64 valori all'interno di un SET

SET(val1, val2, val3, ...)
```



## Tipi di dato numerici

### Binari

```sql
-- Tipo di dato binario, il numero di bit può variare tra 1 e 64, di default il valore è 1

BIT(size)
```


### Numeri interi

```sql
-- Valore intero molto piccolo, il valore con segno può variare tra -128 a 127, mentre il valore senza segno varia tra 0 e 255

UNSIGNED TINYINT
SIGNED TINYINT
```

```sql
-- Valore intero piccolo, il valore con segno può variare tra -32768 a 32767, mentre il valore senza segno varia tra 0 e 65535

UNSIGNED SMALLINT
SIGNED SMALLINT
```

```sql
-- Valore intero medio, il valore con segno può variare tra -8388608 a 8388607, mentre il valore senza segno varia tra 0 e 16777215

UNSIGNED MEDIUMINT
SIGNED MEDIUMINT
```

```sql
-- Valore intero medio, il valore con segno può variare tra -2147483648 a 2147483647, mentre il valore senza segno varia tra 0 e 4294967295

UNSIGNED INT
SIGNED INT
UNSIGNED INTEGER
SIGNED INTEGER
```

```sql
-- Valore intero medio, il valore con segno può variare tra -9223372036854775808 a 9223372036854775807, mentre il valore senza segno varia tra 0 e 18446744073709551615

UNSIGNED BIGINT
SIGNED BIGINT
```

### Numeri decimali

```sql
-- Numero di tipo float. Il numero totale di cifre è specificato con il parametro size, mentre il numero di cifre dopo la virgola è specificato con il parametro d

FLOAT(size, d)
```

```sql
-- Numero di tipo float con doppia precisione. Il numero totale di cifre è specificato con il parametro size, mentre il numero di cifre dopo la virgola è specificato con il parametro d

DOUBLE(size, d)
```

```sql
-- Numero di tipo float. Il parametro p è utilizzato non solo per specificare la precisione del numero di cifre dopo la virgola, ma anche per dire al DATBASE che tipo di dato utilizzare: se p è tra 0 e 24 allora verrà utilizzato il tipo FLOAT. Se invece p è tra 25 e 53 allora il dato sarà di tipo DOUBLE

FLOAT(p)
```

```sql
-- Numero con la virgola esatto: il numero di cifre prima della virgola è specificato in size, mentre il numero di cifre dopo la virgola è specificato nel parametro d, il valore massimo per size è 65, mentre il valore massimo per d è 30

DECIMAL(size, d)
DEC(size, d)
```

### Booleani

```sql
-- 0 è considerato come FALSO, mentre 1 è considerato come VERO

BOOL
BOOLEAN
```



## Tipi di dato temporali

```sql
-- Una data con formato YYYY-MM-DD. Il range supportato è da '1000-01-01' a '9999-12-31'

DATE
```

```sql
-- Una combinazione di data e ora con formato YYYY-MM-DD hh:mm:ss. Il range supportato va da '1000-01-01 00:00:00' a '9999-12-31 23:59:59'. L'aggiunta della direttiva DEFAULT e ON UPDATE inizializzano la data e l'ora con quella attuale, utile per i parametri di data di creazione e modifica. Il parametro fsp indica la precisione delle frazioni di secondo, es: se fsp=3 allora la colonna accetterà valori tipo '2002-12-12 12:13:22.222' con 3 numeri dopo la virgola dei secondi

DATETIME(fsp)
```

```sql
-- I valori di tipo timestamp sono memorizzati come il numero di secondi dall'EPOCH ('1970-01-01 00:00:00' UTC) in formato YYYY-MM-DD hh:mm:ss. Il range va da '1970-01-01 00:00:01' UTC a '2038-01-09 03:14:07' UTC. L'aggiunta delle direttive DEFAULT CURRENT_TIMESTAMP e ON UPDATE CURRENT_TIMESTAMP sincronizzano la data e l'ora attuali nel momento dell'evento.

TIMESTAMP(fsp)
```

```sql
-- Tempo in formato hh:mm:ss, il range di valori va da '-838:59:59' a '838:59:59'


TIME(fsp)
```

```sql
-- Anno in formato di 4 cifre, il range di valori va da 1901 a 2155 e include anche il valore di 0000

YEAR
```

## Tipi di dato personalizzati

È possibile creare dei tipi di dato personalizzati partendo da quelli base e inserendo a questi dei vincoli

```sql
-- Valore numerico che va da 10 a 30 (inclusi)

CREATE DOMAIN Grade
	AS SMALLINT DEFAULT NULL
	CHECK (value >= 10 AND value <= 30)
```

```sql 
-- Valore di tipo codice postale che fa match on un'espressione regolare

CREATE DOMAIN Cap
	AS CHAR(5) DEFAULT '00000'
	CHECK VALUE SIMILAR TO '[0-9]{5}'
```
