## Main operators

### Select operator ( $\sigma$ ) 

$$\sigma_{condition}(Relation |Table)$$
L'operatore select seleziona le tuple che soddisfano una determinata condizione, gli operatori possibili per comparare sono i soliti: $$> | < |= |\ge |\le| \ne$$
Mentre invece gli operatori per concatenare più condizioni sono i soliti: $$\land | \lor | \lnot$$

Data questa tabella di istruttori possiamo effettuare diverse operazioni per ottenere i dati desiderati

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |
| 3 | Mark Johnson | Marketing | 65,000 |
| 4 | Emily Davis | Finance | 70,000 | 
| 5 | Alex Brown | Sales | 58,000 |

#### Esempio 1
Selezionare tutti gli istruttori che lavorano nel dipartimento di 'Finance'
$$\sigma_{DeptName = 'Finance'}(Instructor)$$
Output:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 4 | Emily Davis | Finance | 70,000 | 

#### Esempio 2
Selezionare tutti gli istruttori che hanno un salario superiore ai 60,000 euro e lavorano nel dipartimento di 'Marketing'
$$\sigma_{Salary > 60000 \land DeptName='Marketing'}(Instructor)$$
Output:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 3 | Mark Johnson | Marketing | 65,000 |


### Project operator ( $\Pi$ )
$$\Pi_{Attribute1, Attribute2, ...}(Relation|Table)$$
L'operatore project seleziona solo alcuni campi di una determinata relazione o tabella, dopo questa operazione, tutti i duplicati vengono eliminati

Alcuni esempi:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |
| 3 | Mark Johnson | Marketing | 65,000 |
| 4 | Emily Davis | Finance | 70,000 | 
| 5 | Alex Brown | Sales | 58,000 |


#### Esempio 1
Selezionare il nome e il salario di tutti gli istruttori
$$\Pi_{Name,Salary}(Instructor)$$Output:

| Name | Salary | 
|---------------|--------| 
| John Doe | 60,000 |
| Jane Smith | 55,000 |
| Mark Johnson | 65,000 |
| Emily Davis | 70,000 | 
| Alex Brown | 58,000 |

#### Esempio 2
Selezionare il nome di dipartimento degli istruttori con salario superiore ai 60000 euro
$$\Pi_{DeptName}(\sigma_{Salary > 60000}(Instructor))$$
Output:

| DeptName |
|------------|
| Marketing |
| Finance |


### Union operator ( $\bigcup$ )
$$Relation_1 \cup Relation_2$$
L'operatore union seleziona tutti gli elementi che appartengono alla relazione A o alla relazione B, o ad entrambi. Dopo l'operazione, tutti i duplicati vengono eliminati.

Per far si che l'operatore union sia applicabile è necessario che A e B abbiano lo stesso numero di campi e che ogni campo i di A sia dello stesso tipo del campo i di B



| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |
| 3 | Mark Johnson | Marketing | 65,000 |
| 4 | Emily Davis | Finance | 70,000 | 
| 5 | Alex Brown | Sales | 58,000 |

#### Esempio 1
Selezionare i nomi e i nomi di dipartimento in un unica colonna
$$\Pi_{Name}(Instructor) \cup \Pi_{DeptName}(Instructor)$$
Output:

| Output |
|---------------|
| John Doe |
| Jane Smith |
| Mark Johnson | 
| Emily Davis | 
| Alex Brown |
| IT |
| HR |
| Marketing |
| Finance | 
| Sales | 



### Set difference operator ( - )
$$Relation_1 - Relation_2$$
L'operatore differenza serve ad identificare le tuple che sono presenti nell'insieme A ma non nell'insieme B, quest'operazione gode delle stesse proprietà dell'operatore union

#### Esempio: 

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |
| 3 | Mark Johnson | Marketing | 65,000 |
| 4 | Emily Davis | Finance | 70,000 | 
| 5 | Alex Brown | Sales | 58,000 |

Selezionare gli istruttori che hanno un salario superiore ai 60000 euro e sottrarre quelli che lavorano nel dipartimento di finanza

$$\sigma_{Salary>60000}(Instructor) - \sigma_{DeptName = 'Finance'}(Instructor)$$
Output:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 3 | Mark Johnson | Marketing | 65,000 |


### Cartesian product operator ( $\times$ )

$$Relation_1 \times Relation_2$$

Il prodotto cartesiano associa ogni tupla di A con ogni tupla di B

#### Esempio:

Tabella Insegnanti:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |

Tabella Istruttori

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | Emily Davis | Finance | 70,000 | 
| 2 | Alex Brown | Sales | 58,000 |

Effettuando il prodotto cartesiano otteniamo:
$$\sigma(Teachers) \times \sigma(Instructors)$$
Output: 

| Teachers.ID | Teachers.Name | Teachers.DeptName | Teachers.Salary | Instructors.ID | Instructors.Name | Instructors.DeptName | Instructors.Salary |
|----|---------------|------------|--------|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 | 1 | Emily Davis | Finance | 70,000 | 
| 1 | John Doe | IT | 60,000 | 2 | Alex Brown | Sales | 58,000 | 
| 2 | Jane Smith | HR | 55,000 | 1 | Emily Davis | Finance | 70,000 | 
| 2 | Jane Smith | HR | 55,000 | 2 | Alex Brown | Sales | 58,000 | 


### Rename operator ( $\rho$ )
$$\rho_{RelName_{(NewAttrName_1, NewAttrName_2, ...)\leftarrow(AttrName_1, AttrName_2, ...)}}(Relation)$$
Utilizzato per nominare espressioni di algebra relazionale o per disambiguare colonne con lo stesso nome. 

#### Esempio:

Tabella Insegnanti:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |

Tabella Istruttori

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | Emily Davis | Finance | 70,000 | 
| 2 | Alex Brown | Sales | 58,000 |

Effettuando il prodotto cartesiano e rinominiamo le colonne di Instructors:
$$\sigma(Teachers) \times \rho_{(InsId, InsName, InsDeptName, InsSalary)\leftarrow(ID, Name, DeptName, Salary)}(\sigma(Instructors))$$
Output: 

| ID | Name | DeptName | Salary | InsID | InsName | InsDeptName | InsSalary |
|----|---------------|------------|--------|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 | 1 | Emily Davis | Finance | 70,000 | 
| 1 | John Doe | IT | 60,000 | 2 | Alex Brown | Sales | 58,000 | 
| 2 | Jane Smith | HR | 55,000 | 1 | Emily Davis | Finance | 70,000 | 
| 2 | Jane Smith | HR | 55,000 | 2 | Alex Brown | Sales | 58,000 | 






## Additional operators

### Intersection operator
$$Relation_1 \cap Relation_2$$
Seleziona gli elementi che sono presenti sia in A che in B, per far si che si possa applicare questo tipo di operazione è necessario che siano soddisfatte le stesse condizioni dell'operatore Union

#### Esempio:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 2 | Jane Smith | HR | 55,000 |
| 3 | Mark Johnson | Marketing | 65,000 |
| 4 | Emily Davis | Finance | 70,000 | 
| 5 | Alex Brown | Sales | 58,000 |

Selezionare tutti gli istruttori che hanno un salario maggiore uguale di 60000 euro per poi scegliere solo quelli che lo hanno inferiore ai 70000

$$\sigma_{Salary \ge 60000}(Instructor) \cap \sigma_{Salary < 70000}(Instructor)$$
Output:

| ID | Name | DeptName | Salary | 
|----|---------------|------------|--------| 
| 1 | John Doe | IT | 60,000 |
| 3 | Mark Johnson | Marketing | 65,000 |





### JOIN 

#### Inner Join ( $\bowtie$ )
L'inner Join è essenzialmente un prodotto cartesiano, ma che seleziona solo gli elementi che soddisfano determinate condizioni. Gli elementi che non soddisfano la condizione vengono tagliati fuori dalla relazione finale.

##### Theta Join
$$Relation_1 \bowtie_{condition} Relation_2$$
Il theta join è il caso generico dell'inner join

##### Equi Join
$$Relation_1 \bowtie_{col_1 = col_2} Relation_2$$
Viene chiamato in questo modo quando il theta join utilizza solo un operatore di uguaglianza

##### Natural Join
$$Relation_1 \bowtie Relation_2$$
Il natural join può essere effettuato solo se è presente una colonna comune tra le relazioni, il nome e il tipo della colonna devono essere gli stessi, lo si può considerare un sottotipo dell'equi join in cui l'uguaglianza viene effettuata tra i dati della colonna in comune.

Esempio:

Considerando le seguenti tabelle C e D

| Num | Square | 
| --- | ---|
| 2 | 4 |
| 3 | 9 |

| Num | Cube | 
| --- | ---|
| 2 | 8 |
| 3 | 27 |

Effettuando il Natural Join otteniamo:
$$C \bowtie D$$

| Num | Square | Cube |
| -- | --| -- |
| 2 | 4 | 8 |
| 3 | 9 | 27 |



#### Outer Join ( $⟗$ )
L'outer join differisce dall'inner join in quanto inserisce NULL al posto degli elementi che non soddisfano la condizione di join

##### Left outer join ( $⟕$ )
Mantiene tutte le tuple del primo operando, se queste non soddisfano le condizioni viene inserito NULL al posto del loro valore.

###### Esempio:

Tabella Employee

| Employee | Dept |
| ------ | --|
|Rossi|A|
|Neri|B|
|Bianchi|B|

Tabella Department

| Department | Chief |
| --| -----|
|B | Mori|
|C | Bruni|

$$Employee ⟕ Department$$

Output:

|Employee|Dept|Chief|
|----|-|-|
|Neri|B |Mori|
|Bianchi|B|Mori|
|Rossi|A|NULL|

##### Right outer join ( ⟖ )
Inverso del left outer join, vengono mantenuti tutti i valori del secondo operando

###### Esempio:

Tabella Employee

| Employee | Dept |
| ------ | --|
|Rossi|A|
|Neri|B|
|Bianchi|B|

Tabella Department

| Department | Chief |
| --| -----|
|B | Mori|
|C | Bruni|

$$Employee ⟖ Department$$

Output:

|Employee|Dept|Chief|
|----|-|-|
|Neri|B |Mori|
|Bianchi|B|Mori|
|NULL|C|Bruni|

##### Full outer join ( ⟗ )
È l'unione del left outer join ed il right outer join, quindi gli operandi che non rispettano le condizioni da entrambi i lati vengono mantenuti e viene inserito null nei campi non combacianti

###### Esempio:

Tabella Employee

| Employee | Dept |
| ------ | --|
|Rossi|A|
|Neri|B|
|Bianchi|B|

Tabella Department

| Department | Chief |
| --| -----|
|B | Mori|
|C | Bruni|

$$Employee ⟗ Department$$

Output:

|Employee|Dept|Chief|
|----|-|-|
|Neri|B |Mori|
|Bianchi|B|Mori|
|Rossi|A|NULL|
|NULL|C|Bruni|
