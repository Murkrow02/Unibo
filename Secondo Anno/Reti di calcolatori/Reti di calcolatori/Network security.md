La network security si basa su 4 principi fondamentali:
- Confidentiality: solo il mittente ed il destinatario devono "percepire" il vero contenuto delle trasmissioni
	- Il mittente cripta i messaggi
	- Il destinatario li decripta
- Authentication: il mittente ed il destinatario vogliono confermarsi l'identità a vicenda
- Message integrity: il mittente ed il destinatario vogliono assicurarsi che il messaggio venga consegnato senza alterazioni
- Access and availability: i servizi devono esser accessibili e disponibili agli utenti

Si parla di sicurezza nella rete quando si prendono in causa due o più figure che fanno parte di una comunicazione, questi possono essere due utenti, un client e un server, host e dns server, ecc...

Purtroppo esistono figure ostili nel mondo dell'internet che possono compromettere questi 4 principi eseguendo degli attacchi mirati classificabili in base all'impatto:
- Eavesdrop: intercettazione dei messaggi
- Inserimento di messaggi all'interno delle connessioni
- Impersonation: falsificare (spoof) indirizzi dei mittenti nei pacchetti
- Hijacking: prendere il controllo della connessione rimuovendo il mittente o il destinatario da questa e inserendo se stesso al suo posto
- DOS (Denial Of Service): impedire l'utilizzo della connessione

## Principi della crittografia
La crittografia è largamente utilizzata per criptare e decriptare pacchetti nel momento giusto, in modo che durante il trasferimento di questi risultino irriconoscibili a coloro che non posseggono le chiavi.

Gli attacchi più semplici alla crittografia sono:
- cipher-text only attack: l'intruder è in possesso dei dati criptati e può analizzarli seguendo:
	- bruteforce: prova tutte le possibili chiavi
	- statistical analysis
- known-plaintext attack: l'intruder è in possesso dei dati criptati e in plain text e può generare nuovi messaggi criptandoli con lo stesso algoritmo.
### Crittografia a chiave simmetrica
In questo tipo di crittografia viene generata una chiave unica, questa è in grado sia di criptare che di decriptare il contenuto di un messaggio
$$m=K_s(K_s(m))$$
#### Substitution cipher
Consiste semplicemente nel sostituire una cosa con un'altra (Caesar Cipher), può essere reso più sofisticato includendo degli specifici caratteri di sostituzione e degli schemi ciclici per la sostituzione, in questo modo la chiave include le informazioni dei sostituti e dei cicli.

#### DES (Data Encryption Standard)
Il DES è uno standard di criptazione degli US, esso include una chiave simmetrica da 56bit che si applica su un input di 64bit.

56bit però sono pochi in quanto è possibile con il bruteforce decriptare i dati in meno di un giorno, per renderlo più sicuro è stato ideato il 3DES, una semplice concatenazione di 3 DES con 3 chiavi differenti

#### AES (Advanced Encryption Standard)
Dal 2001 è stato introdotto un sistema più sicuro di criptazione dei dati che ha rimpiazzato DES, questo metodo processa i dati in blocchi di 128bit, con chiavi di dimensione 128, 192 o 256 bit, in quel momento storico la decriptazione
di DES avrebbe impiegato 1 secondo, mentre quella di AES 149 trilioni di anni


### Crittografia a chiave pubblica

La crittografia a chiave pubblica si basa sul principio di avere due chiavi distinte:
- Una chiave pubblica conosciuta a tutti
- Una chiave privata conosciuta solo al proprietario

Alla base di questa filosofia esistono due regole principali:
- Sono necessarie $K^{+}_{B}$ e $K^-_B$ in modo che $K^-_B(K^+_B(m)) = m$ 
- Data una chiave pubblica $K^+_B$ non è possibile ricavare la chiave privata $K^-_B$ 

La generazione di chiavi comporta quindi la necessità di non essere invertibile, per rendere questo possibile si è pensato di fare uso dell'aritmetica modulare.

#### RSA (Rives, Shamir, Anderson) algorithm
Lo sviluppo dell'algoritmo RSA parte dall'assunzione che un messaggio digitale è semplicemente un pattern di bit, ogni pattern di bit può essere rappresentato da un numero intero, quindi criptare un messaggio è come criptare un numero.

##### Creazione della coppia chiavi pubbliche e private
- 1: Scegli due numeri primi molto grandi $p$ e $q$ (es 1024bit ciascuno)
- 2: Computa $n=p*q$   e   $z=(p-1)*(q-1)$ 
- 3: Scegli $e$ tale che $e<n$ e che $e$ non abbia fattori comuni con $z$ (ciò implica che $e$ e $z$ siano "relativamente primi")
- 4: Scegli $d$ in modo che $ed-1$ sia esattamente divisibile per $z$ (in altre parole: ed mod z = 1)
- 5: La chiave pubblica è (n,e) e la chiave privata è (n,d)

##### Criptazione e decriptazione con le chiavi
- Per criptare un messaggio m (<n): $c=m^e$ mod $n$ 
- Per decriptare un messaggio c: $m=c^d$ mod $n$
Quindi $m =(m^e$ mod $n)^d$ mod $n$ 


In sostanza l'RSA funziona in questo modo:
Se io sono Bob e voglio comunicare con Alice, le chiedo la sua chiave pubblica e cripto il mio messaggio con la sua chiave, in modo che nessuno oltre il possessore della chiave privata di Alice possa decriptarlo.

Non è possibile invertire l'algoritmo delle chiavi partendo dalla chiave pubblica in quanto si dovrebbero trovare i fattori comuni di p e q, che rappresentano numeri molto molto grandi.

La criptazione a chiave pubblica è comunque molto intensiva a livello computazionale, quindi si utilizza spesso il metodo di condividere una chiave simmetrica (session key $K_s$) attraverso questo meccanismo per poi proseguire le comunicazioni con quest'ultima.

## Autenticazione
L'obiettivo dell'autenticazione è quello di dimostrare la propria identità al dispositivo con cui si comunica

### Protocollo ap 1.0
Nel protocollo ap 1.0 ci si autentica semplicemente dichiarandosi in una trasmissione (es: "I am Alice"), protocollo molto insicuro in quanto un intruder potrebbe autenticarsi trasmettendo "I am alice" ed impersonarla.
### Protocollo ap 2.0
Nel protocollo ap 2.0 ci si autentica nello stesso modo di ap 1.0, ma questa volta si include nella trasmissione anche il proprio indirizzo IP, ma anche qui l'intruder potrebbe creare un pacchetto usando l'indirizzo IP del vero mittente.
### Protocollo ap 3.0
Nel protocollo ap 3.0 ci si autentica nello stesso modo di ap 2.0, ma questa volta si include la propria password segreta nel pacchetto, qui l'intruder potrebbe effettuare un **playback attack** registrando il pacchetto di autenticazione mandato dal mittente per poi inviarlo più tardi al destinatario
### Protocollo ap 3.1
Identico al protocollo ap 3.0, ma in questo caso la password è criptata, ciò non risolve il problema del playback attack
### Protocollo ap 4.0
Il protocollo ap 4.0 implica il destinatario a ritornare un **nonce**, un numero R che viene utilizzato una sola volta, il mittente per dimostrare la propria identità deve ritornare R criptato con una chiave condivisa tra i due, quindi si utilizzano password concordate sempre diverse per comunicare.
### Protocollo ap 5.0
Il protocollo ap 4.0 utilizza una chiave simmetrica per criptare il nonce, il 5.0 utilizza invece la criptazione a chiave pubblica. Un tipo di attacco possibile a questo protocollo è il **man in the middle** in cui l'intruder si finge il mittente per il destinatario ed il destinatario per il mittente. Questo tipo di attacco è difficile da individuare in quanto gli host non si rendono conto della presenza di un intruder, dato che tutti i pacchetti vengono ritrasmessi dall'intruder.
## Message integrity
Esistono delle tecniche crittografiche utili per identificare il proprietario/creatore di un documento, proprio come una firma, questi metodi vengono chiamati firme digitali, queste sono verificabili e non forgiabili in altro modo.

I messaggi del mittente vengono codificati con la propria chiave privata che simboleggia appunto la firma del documento.

Il messaggio firmato viene quindi spedito come una coppia $m,K^-(m)$ , il destinatario può quindi decifrare il messaggio con la chiave pubblica del mittente e verificare l'integrità del contenuto.
$$K^+(K^-(m)) = m$$
Si è certi a questo punto che solo chi è in possesso della chiave privata del mittente può aver firmato questo messaggio.

### Message digest
Le operazioni di codifica e decodifica a chiave pubblica sono molto costose a livello computazionale quando si lavora con messaggi lunghi, l'obiettivo è quindi quello di creare un'impronta digitale di lunghezza fissa e facile da computare. 
Si applica quindi una funzione di hashing $H(m)$ per ottenere un output di dimensione fissa.

La funzione $H(m)$ ha le seguenti proprietà:
- Many-to-1
- Produce messaggi di dimensione fissa (fingerprint)
- Dato un digest x è impossibile trovare m tale che $x = H(m)$ 

Si preferisce a questo punto quindi mandare la coppia $m,K^-(H(m))$ in modo che il destinatario possa applicare la funzione di hash sul messaggio integrale e la chiave pubblica del mittente sul digest ricevuto, a questo punto si trova con la coppia $H(m), H(m)$ e può compararla.

![[SCR-20240119-mdig.png]]

### Algoritmi di hashing
I principali algoritmi di hashing utilizzati a livello globale sono **MD5 e SHA1** questi producono rispettivamente digest di dimensioni di 128 e 160 bit rendendo molto difficile trovare due messaggi che criptati forniscono lo stesso output. Lo standard US è SHA-1.



### Certificazione a chiave pubblica
Questi procedimenti non bastano però a verificare l'identità di un host, in quanto si potrebbe comunque firmare un documento con la propria chiave pubblica, ma mentire sul fatto che la firma appartenga a quella persona.

Entra quindi in gioco la certificazione a chiave pubblica che basa tutta la sua affidabilità sulle certification authorities (CA) che collegano le chiavi pubbliche a delle determinate entità. Per potersi identificare su internet è quindi necessario fare richiesta ad una CA di registrarsi fornendo una prova di identità, a questo punto quindi la CA emette un certificato che determina l'associazione di un'entità ad una determinata chiave pubblica.

In questo modo quando si richiede una chiave pubblica, si ottiene il certificato, sul quale applicando la chiave pubblica della CA $K^+_{CA}$ si ottiene la chiave pubblica richiesta.
## Secure e-mail
I principi di autenticazione e di crittografia elencati precedentemente vengono quindi utilizzati per proteggere anche le informazioni di servizi come quello di posta elettronica.

Il mittente genera una chiave simmetrica casuale $K_S$ utilizzata per criptare il messaggio, in seguito manda il messaggio criptato e la chiave simmetrica criptata con la chiave pubblica del destinatario.

In questo modo il destinatario può decriptare la chiave simmetrica con la propria chiave privata e finalmente decodificare il messaggio.

Se il mittente vuole a questo punto fornire nel messaggio anche la propria autenticazione digitale, basta che manda una coppia $m,K^-(H(m))$ dove la prima parte è il messaggio integrale, mentre la seconda rappresenta il messaggio passato per una funzione di hashing e criptato con la propria chiave privata, in modo da inviare sia il messaggio che la firma digitale.

Abbiamo quindi dal lato del mittente l'utilizzo di 3 chiavi per inviare il messaggio, quella simmetrica, quella pubblica del destinatario, e la propria chiave privata.
![[SCR-20240119-mkza.png]]

## SSL (Secure Socket Layer)
Il protocollo di sicurezza SSL è largamente utilizzato e supportato da quasi tutti i browser e server, è il protocollo che utilizza HTTPS per la trasmissione sicura dei dati. 

È un protocollo che fornisce confidenzialità, integrità ed autenticazione, nato per la protezione di transazioni bancarie e processi di autenticazione, ma ora è utilizzato da tutte le comunicazioni TCP.

Il layer SSL si mette esattamente in mezzo tra i livello applicazione e il protocollo TCP del livello trasporto e fornisce API per poter comunicare con esso dal livello applicazione.

### TOY SSL
Toy SSL rappresenta un canale sicuro di comunicazione necessario per la protezione dei dati e per la sicurezza delle trasmissioni, questo tipo di canale divide le comunicazioni in 4 fasi:
- handshake: mittente e destinatario si scambiano i certificati per autenticarsi a vicenda e scambiare il segreto comune
- key derivation: il segreto comune viene utilizzato per generare un set di chiavi
- data transfer: i dati da trasferire vengono spezzati in una serie di record
- connection closure: la connessione viene chiusa in modo sicuro con un messaggio speciale

#### Handshake
L'handshake serve ad iniziare una comunicazione e si divide in tre semplici trasmissioni:
- hello: il mittente manda un messaggio per iniziare una connessione
- certificate: il destinatario risponde con il proprio certificato
- MS (master secret): il mittente a questo punto cripta il MS con la chiave pubblica del destinatario

A questo punto entrambi sono in possesso di un segreto utile per generare le chiavi di comunicazione

#### Key derivation
È considerata buona prassi quella di variare la chiave di criptazione per ogni trasmissione.

Esistono 4 chiavi fondamentali durante una comunicazione, 2 sono per la criptazione e 2 sono codici di autenticazione dei messaggi (MAC):
- $K_C$: Chiave di criptazione inviata dal client al server
- $M_C$: Chiave MAC inviata dal client al server
- $K_S$: Chiave di criptazione inviata dal server al client
- $M_S$: Chiave MAC inviata dal server al client

Le chiavi sono derivate dalla KDF (Key Derivation Function) che prende in input il MS e crea le chiavi.

#### Data Records
Piuttosto che criptare i dati in uno stream costante che farebbe sorgere il problema dello scegliere dove inserire il MAC si spezzano gli stream in record, di cui ognuno viaggia con un MAC, a questo punto ci si serve di un parametro che specifica la lunghezza del messaggio per distinguerlo dal MAC

#### Sequenze di numeri
Esistono ancora dei problemi però relativi alla sicurezza adottata fin ora, infatti un attacker potrebbe catturare e fare il replay dei record, o magari riordinarli, per questo si inserisce quindi nel MAC anche il numero del record nella sequenza.

A questo punto l'attacker potrebbe semplicemente fare il replay di tutti i record, quindi utilizziamo il meccanismo del nonce per evitare questo problema.

#### Controllo delle informazioni
Un attacker potrebbe performare il **truncation attack**, quindi troncare la connessione prima dell'effettiva richiesta di chiusura da parte dell'host reale, viene quindi aggiunto un valore che rappresenta il tipo di trasmissione che si vuole effettuare: 
- 0 per le trasmissioni standard
- 1 per la chiusura della comunicazione
L'attacker non conoscendo il valore del MS non può criptare un messaggio forgiato contenente il bit di chiusura.

#### Riassunto
![[SCR-20240119-nnnf.png]]

### Real SSL
Fin ora è stato visto lo scopo concettuale basico del protocollo SSL, ma il TOY SSL lascia ancora spazio per dei dubbi:
- quanto sono grandi i messaggi?
- che protocolli di criptazione vengono usati?
- negoziazione dei protocolli?
	- permettere al client e al server di supportare diversi algoritmi
	- permettere al client e al server di scegliere quale usare insieme
#### Suite di cifratura
Esistono varie suite di cifratura che comprendono quindi:
- un algoritmo per la chiave pubblica
- un algoritmo per la chiave simmetrica
- un algoritmo per il MAC

SSL supporta varie suite di cifratura e la scelta di questa è negoziata tra client e server: il client offre al server una serie di suite che conosce e il server ne sceglie una tra queste.

Tra quelle simmetriche sono note:
- DES
- 3DES
- RC2
- RC4

Per quella a chiave pubblica si usa invece RSA
#### Real handshake
Il vero handshake quindi supporta anche questo tipo di negoziazione tra gli algoritmi presenti nelle varie suite di cifratura del protocollo SLL, segue infatti questo ordine
- 1: il client invia una lista di algoritmi supportati, insieme al nonce
- 2: il server sceglie un algoritmo dalla lista e risponde con la scelta + il certificato + il nonce del server
- 3: il client verifica il certificato, estrae la chiave pubblica del server e genera il MS, lo cripta con la chiave pubblica del server e lo invia
- 4: il client e il server possono generare indipendentemente il MAC in quanto conoscono entrambi il MS
- 5: il client invia il MAC dei messaggi di handshake
- 6: il server risponde con il MAC dei messaggi di handshake

Gli ultimi due step servono a prevenire la manomissione dell'handshake, il client offre una serie di possibili algoritmi, di cui alcuni più forti e altri più deboli, un man-in-the-middle potrebbe eliminare gli algoritmi più forti dalla lista, quindi gli ultimi due messaggi vengono criptati e contengono un riepilogo delle comunicazioni svolte per verificarne l'integrità.

#### Protocollo del record
Un record SSL segue quindi una struttura molto precisa per essere compatibile universalmente.
I dati vengono spezzati in frammenti accompagnati dal proprio MAC per poi essere criptati.

Si aggiunge infine un header rappresentante le informazioni del record come il content type, la versione e la lunghezza del record.
Il MAC include le informazioni sul numero di sequenza e il tipo di trasmissione insieme alla chiave M
Il frammento di dati è di dimensione $2^{14}$  byte (16 kbytes)
![[SCR-20240119-nryy.png]]

#### Riassunto
Il vero protocollo SSL comunica quindi in questo modo:
![[SCR-20240119-ntcw.png]]
## Network layer security (IPsec)
La sicurezza a livello rete si basa sulla riservatezza relativa alle connessioni, si introduce quindi il concetto di Virtual Private Network (VPN).

Le istituzioni vogliono spesso mantenere private le loro reti per ragioni di sicurezza separandole da un collegamento diretto con l'internet grazie al VPN che comunica quindi con l'internet nascondendo la provenienza reale dei pacchetti.

I protocolli di IPsec creano quindi un ulteriore tunnel crittografato che incapsula il messaggio con un ulteriore livello di sicurezza che fa in modo che enti esterni non possano risalire alla reale provenienza del pacchetto (es nasconde IP).

I servizi di IPsec vogliono garantire l'integrità dei dati, prevenire gli attacchi di replay e la riservatezza. Si introducono due protocolli principali:
- AH (Authentication Header): fornisce autenticazione della sorgente e integrità dei dati, ma non la riservatezza
- ESP (Encapsulation Security Protocol): fornisce autenticazione, integrità e riservatezza.

### Security associations (SAs)
Prima di inviare i dati un'SA è stabilita tra il mittente e il destinatario, questa è unidirezionale, quindi in una comunicazione bidirezionale esisteranno due SAs. Le entità riceventi e mittenti mantengono lo stato delle SAs, queste infatti contengono informazioni di sicurezza relative agli algoritmi di crittografia, in modo da permettere la ripresa della comunicazione senza la necessita di un nuovo handshake, a questo punto siamo passati da un protocollo connectionless come IP ad uno connection-oriented come IPsec.

Ad esempio un router che supporta IPsec conserve in una SA vari dettagli:
- SPI (Security Parameter Index): Codice identificativo di 32bit dell'SA
- Indirizzo IP di origine
- Indirizzo IP di destinazione
- Tipi di criptazione utilizzati
- Chiave di criptazione
- Tipo di meccanismo per la verifica dell'integrità utilizzato
- Chiave di autenticazione

Gli endpoint mantengono lo stato di ogni SA in un SAD (Security Association Database), quando si invia un datagramma IPsec il router accede al SAD per capire come processarlo, mentre il ricevitore lo identifica tramite il SPI nel SAD e lo processa analogamente.

Il nuovo datagramma nuovamente incapsulato ora sarà strutturato in questo modo seguendo il protocollo ESP:
![[SCR-20240119-octo.png]]

Il mittente aggiunge un trailer (ESP trailer) al payload originale, che include i dati dell'header originario, questo valore viene criptato seguendo i valori salvati nell'SA. 
Viene aggiunto ora all'inizio un ulteriore header (ESP header) creando quindi l'**enchilada**.
Viene ora creato il MAC di autenticazione di tutta l'enchilada e aggiunto alla fine del blocco, creando il payload completo. Viene aggiunto ora un nuovo IP header uguale nella sua forma a quello di default e messo prima del payload.

Sorge però il problema di dover riconoscere se l'entità mittente sta usando IPsec oppure no, vengono salvate quindi delle informazioni nell'SPD (Security Policy Database), contenenti informazioni riguardanti l'host, come l'indirizzo IP. 

Quindi a questo punto si usa l'SPD per capire cosa fare con un payload e l'SAD per capire come lavorarci.

### IKE (Internet Key Exchange)
La scrittura manuale di chiavi nel SAD è un'operazione poco pratica, si pensi a VPN con centinaia di endpoint, a risolvere questo problema ci pensa l'IKE.

Si basa principalmente su un'autenticazione che può essere svolta in due modi possibili:
- PSK (Pre-Shared Secret Key): entrambe le parti iniziano con un segreto e fanno partire IKE per autenticarsi a vicenda e generare la SA (una per direzione)
- PKI (Public/Private Keys Identification): Simile ad un handshake in SSL, ci si autentica con le chiavi pubbliche e private e si genera la SA.

IKE ha due fasi principali:
- 1: stabilire la chiave IKE-SA bidirezionale, anche chiamata ISAKMP che si differisce dalla SA di IPsec
- 2: ISAKMP è utilizzata per negoziare in modo sicuro la coppia di SAs

## Securing Wireless LANs
Dopo aver appurato il livello di sicurezza funzionale sul livello trasporto, sorge la necessità di introdurre un livello di sicurezza a livello IP locale, è stato quindi disegnato un sistema denominato WEP che si focalizza principalmente su:
- cifratura a chiave simmetrica
- self-sync: ogni pacchetto è criptato separatamente, ma con un pacchetto e una chiave si può continuare a decriptare pacchetti anche se uno dei pacchetti è stato perso.

Si utilizza quindi un generatore di keystream che data una chiave e del plain text li combina per ottenere il testo cifrato seguendo questa logica:
- m(i): unità i-esima del messaggio
- ks(i): unità i-esima del keystream
- c(i): unità i-esima del messaggio cifrato: $c(i) = ks(i)$ XOR $m(i)$
- m(i): $m(i) = ks(i)$ XOR $c(i)$

FRA NON CAPISCO UNA SEGA DEVI CONTINUARLO

