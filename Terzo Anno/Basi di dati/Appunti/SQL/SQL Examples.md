#### People Table
| Name | Age | Income |
| ---- | ---- | ---- |
| Jim | 27 | 21 |
| James | 25 | 15 |
| Alice | 55 | 42 |
| Jesse | 50 | 35 |
| Phil | 26 | 30 |
| Louis | 50 | 40 |
| Frank | 60 | 20 |
| Olga | 30 | 41 |
| Steve | 85 | 35 |
| Abby | 75 | 87 |
#### Motherhood Table
| Mother | Child |
| ---- | ---- |
| Abby | Alice |
| Abby | Louis |
| Jesse | Olga |
| Jesse | Phil |
| Alice | Jim |
| Alice | James |
#### Fatherhood Table
| Father | Child |
| ---- | ---- |
| Steve | Frank |
| Louis | Olga |
| Louis | Phil |
| Frank | Jim |
| Frank | James |
### Example 1
I nomi dei padri delle persone che guadagnano più di 20
#### Soluzione:
```sql
SELECT DISTINCT Father
FROM People, Fatherhood
WHERE Child = Name AND Income > 40
```

### Example 2
Return the people's name, income and their father's income, where such people earn more than their fathers.
#### Soluzione:
```sql
SELECT P1.Name, P1.Income, P2.Income
FROM People P1, Fatherhood, People P2
WHERE Child = P1.Name AND Father = P2.Name AND P1.Income > P2.Income
```

#### Soluzione con JOIN
```sql
SELECT P1.Name, P1.Income, P2.Income
FROM (People P1 JOIN Fatherhood ON P1.Name = Child) JOIN People P2 ON P2.Name = Father
WHERE P1.Income > P2.Income
```



### Example 3 (Nested queries)
Provide the name and the income of Frank's father

#### Soluzione con JOIN:
```sql
SELECT Name, Income
FROM Fatherhood JOIN People ON Name = Father
WHERE Child = "Frank"
```

#### Soluzione con subquery
```sql
SELECT Name, Income
FROM People
WHERE Name = ( SELECT Father 
				FROM Fatherhood
				WHERE Child = "Frank")
```

### Example 4
Provide name and income of the fathers' having child earning more than 20

#### Soluzione:
```sql
SELECT Name, Income
FROM People
WHERE Name = IN (SELECT Father 
				 FROM Fatherhood 
				 WHERE Child = ANY (SELECT Name 
								  FROM People 
								  WHERE Income > 20))
```

#### Soluzione con 2 query
```sql
SELECT Name, Income 
FROM People
WHERE Name IN (SELECT Father
				FROM Fatherhood, People
				WHERE Child = Name AND Income > 20 )
```

#### Soluzione con quantificazione esistenziale
```sql
SELECT Name, Income
FROM Fatherhood F1
WHERE NOT EXISTS (SELECT * 
				  FROM Fatherhood F2, People
				  WHERE F2.Father = F1.Father 
					  AND F2.Child = Name 
					  AND Income < 20 )
```

### Example 5 (Quantificazione esistenziale)
People having at least one child

#### Soluzione:
```sql
SELECT * 
FROM People
WHERE EXISTS (SELECT * 
			  FROM FatherHood
			  WHERE Father = Name)
	  OR
	  EXISTS (SELECT * 
			  FROM Motherhood
			  WHERE Mother = Name)
```

