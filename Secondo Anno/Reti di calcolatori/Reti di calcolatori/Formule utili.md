### Lunghezza d'onda
Utile quando si vuole cercare la differenza di fase tra due onde
$$
wavelen_{m}=\frac{e_{m/s}}{freq_{Hz}}=\frac{300.000.000}{freq_{Hz}}
$$
Una volta trovata, se abbiamo la distanza percorsa dalle 2 onde (d1 e d2) possiamo fare
d1-d2 per trovare la differenza. Una volta ottenuta la possiamo dividere per la lunghezza d'onda, se troviamo un valore x.5 allora le onde sono in opposizione di fase
### Throughput
$$Percentuale_{Accesso}*N_{hostTrasmittenti}*N_{richiesteAlSecondo}*Dimensione_{Richieste}<Capacità_{medium}$$
Ad esempio la percentuale di accesso può essere la percentuale di cache hit di un web proxy

## Logaritmi
$$x = log_ab$$ $$a^x=b$$
### mW e db e dbm

![[SCR-20240124-qxzg.png]]
![[SCR-20240124-qycp.png]]

#### Converting mW to dBm
$$P_{dBm} = 10*log(P_{mW})$$
#### Converting dBm to mW
$$P_{mW} = 10^{P_{dBm} / 10}$$
#### Perdita di segnale (sulla terra)
$$
db_{loss}= 36.6 + (20 * log_{10}(freq_{MHz})) + (20 * log_{10}(dist_{miles}))
$$
#### 6db rule
Ogni qual volta la distanza tra 2 antenne raddoppia, perdiamo 6 decibel di segnale
Di conseguenza ogni qual volta la distanza si dimezza, guadagnamo 6 decibel

#### Raggio fresnel zone 
Il calcolo del raggio dipende dalla percentuale cercata, il 100% si calcola come segue
$$
72.2 * \sqrt{\frac{d_{miles}}{4*f_{GhZ}}}
$$
La costante puó essere cambiata per rispecchiare la percentuale del raggio cercato, ad esempio se vogliamo il 60% del raggio possiamo fare 
$$
43.3 * \sqrt{\frac{d_{miles}}{4*f_{GhZ}}}
$$
### OFDM

#### Definizioni
- **Symbol rate** = quanti simboli é possibile trasmettere su ogni canale
- **Bits coded per phase transition** = quanti bit riusciamo a trasmettere per ogni simbolo
	- Sostanzialmente abbiamo i bit per secondo moltiplicando symbol rate per il numero di sub-carriers per bit codificati per phase transition
- 
#### Prestazione canale
Ovvero quanti simboli al secondo totali possono essere trasmessi
$$P_c=n_{subcarr}*symbolrate$$
Questi simboli rappresentano gli effettivi "bit" o "bit multipli" (in caso di QPSK) riusciamo a trasmettere ogni secondo sul canale
#### Tabella
![[Pasted image 20240126110331.png]]

### DECIMAL TO HEX
Step-1: First, divide the given number by 16.

Step-2: The remainder left here, will produce the hex value.

Step-3: Take the quotient from above and repeat steps 1-3 till quotient becomes 0.

Step-4: Write all the remainders in reverse order. This will be the Hexadecimal converted value.

