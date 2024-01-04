#### Employee Table

| Code | Name | Age | Wage|
| --- | --- | --- | --- |
| 7309 | Rossi | 34 | 45 |
|5998 | Bianchi | 37 | 38 |
|9553 | Neri | 42 | 35 |
| 5698 | Bruni | 43 | 42 |
|4076 | Mori | 45 | 50 |
| 8123 | Lupi | 46 | 60 |

#### Supervisor Table

| Employee | Chief | 
| --- | -- |
|7309|5698|
|5988|5698|
|9553|4076|
|5698|4076|
|4076|8123|

##### Example 1:
Restituire gli impiegati con uno stipendio superiore a 40

###### Soluzione:
$$\sigma_{Wage > 40}(Employee)$$



##### Example 2:
Return the employees' number, name and age earning more than 40

###### Soluzione:
$$\Pi_{Code,Name,Age}(\sigma_{Wage > 40}(Employee))$$


##### Example 3
Return the employees' chiefs earning more than 40

###### Soluzione:
Utilizzando il Natural Join
$$ \sigma_{Wage > 40}(Employee) \bowtie \rho_{(Code \leftarrow Chief)}(Supervisor)$$

##### Example 4
Return the chief's name and wage having employees earning more than 40

###### Soluzione:
$$\Pi_{Name,Wage}(\sigma(Employee) \bowtie \rho_{(Code \leftarrow Chief)} (\Pi_{Chief}( \sigma_{Wage > 40}(Employee) \bowtie \rho_{(Code \leftarrow Employee)}(Supervisor)))$$

##### Example 5
Return the employees having a wage greater than their chief's, along with number, name and wage of both the employee and his chief

###### Soluzione:
$$\sigma_{Wage > SupWage}(Supervisor \bowtie_{Employee = Code} Employee) \bowtie_{Chief = Code} \rho_{(SupName, SupAge, SupWage \leftarrow Name, Age, Wage)}(Employee)) $$
##### Example 6
Return the chiefs' number having all their employees earning more than 40
###### Soluzione:
$$\Pi_{Chief}(Supervisor) - \Pi_{Chief}(Supervisor \bowtie_{Employee = Code} \sigma_{Wage \le 40}(Employee))$$

##### Example 7
Provide al the Chief's numbers being less than 30 years old.

###### Soluzione:
$$\sigma_{Age < 30}(\Pi_{Chief}(Supervisor) \bowtie_{Chief = Code} Employee)$$