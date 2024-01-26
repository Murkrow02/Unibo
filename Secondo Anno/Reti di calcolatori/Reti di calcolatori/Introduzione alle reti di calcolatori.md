## Reti a commutazione di circuito (circuit - switched)
Una serie di canali può trasmettere dati anche a lunghe distanze seguendo la commutazione di circuito
![[SCR-20240118-mqio.png]]
Viene riservato un canale di comunicazione privato (linea telefonica) punto a punto su ogni connessione lungo il cammino dal mittente al destinatario in modo da avere un ritardo di comunicazione basso, si paga però il tempo di connessione anche se non si scambiano dati attraverso il canale, che viene sprecato nel momento in cui non si trasmette. Con questo tipo di comunicazione, una volta che viene negoziato il canale riservato, si può procedere a trasmettere i dati in un'unica sequenza di bit, in quanto si ha la certezza che non ci saranno interferenze nella comunicazione.

Es: quando viene effettuata una telefonata si paga il tempo complessivo di utilizzo del canale riservato, anche se durante la chiamata non vengono trasmessi dati (si rimane in silenzio).

## Reti a commutazione di pacchetto

La più utilizzata al giorno d'oggi, si basa sul concetto di suddividere i dati in pacchetti contenenti informazioni fondamentali per la trasmissione tra cui quindi indirizzo del mittente e del destinatario in modo che questi possano transitare su un unico canale broadcast condiviso da più utenti.

Componendo quindi in serie strutture a commutazione di pacchetto, ogni calcolatore può capire se il pacchetto ricevuto appartiene a se e quindi tenerlo, o se appartiene a qualcun altro e quindi fare forward.

Al contrario della commutazione di circuito il canale viene pagato in base alla quantità di dati trasmessi, il che comporta però latenza in quanto il canale può congestionarsi. Un altra problematica che potrebbe sorgere è legata alla perdita o corruzione di pacchetti, insieme anche quindi alla possibilità di ricevere pacchetti in modo disordinato.

### Servizi orientati alla connessione (connection - oriented)
I servizi connection-oriented come le linee telefoniche garantiscono la consegna dei pacchetti in modo ordinato secondo l'ordine di invio, insieme alla ri-trasmissione dei pacchetti perduti.

Per garantire questo tipo di affidabilità i pacchetti vengono quindi numerati in modo da poterli riordinare all'arrivo

### Servizi non orientati alla connessione (connectionless)
I servizi connectionless come quelli di posta ordinaria non garantiscono lo stesso tipo di sicurezza in quanto i pacchetti possono prendere strade diverse ed arrivare in ordine diverso, o non arrivare mai


## Architettura dei protocolli

### Protocollo
Un protocollo consiste in una serie di regole e procedure semantiche di gestione dei processi di comunicazione, insieme anche a dei formati sintattici da rispettare per disambiguare lo scambio di messaggi, di conseguenza garantiscono la compatibilità di sistemi conformi allo stesso standard adottato.

### Architettura
Ogni livello affronta e risolve un problema della comunicazione. I livelli superiori effettuano richieste di servizio al livello inferiore, mentre i livelli inferiori forniscono quindi servizi a quelli superiori.
Ogni livello quindi ha interazioni solo con i livelli a se adiacenti.

![[SCR-20240118-mxnj.png]]

L'architettura standard dei protocolli di rete è suddivisa in 7 livelli di cui ognuno gestisce una classe di problemi relativi alla comunicazione, questa suddivisione segue lo standard **ISO/OSI RM** 
![[SCR-20240118-mzkw.png]]
Il livello applicazione (7) fornisce alle applicazioni in esecuzione sul calcolatore i servizi e le primitive di trasmissione e ricezione dei dati. Il livello presentazione (6) risolve eventuali eterogeneità del formato dei dati tra i nodi della rete. Il livello sessione (5) mantiene e gestisce lo stato attuale del collegamento tra due applicazioni remote. Il livello trasporto (4) si occupa di garantire i servizi di trasmissione dei pacchetti (orientati alla connessione e non) e del controllo della congestione della rete. Il livello rete (3) si occupa di frammentare i dati in pacchetti, scrivere gli indirizzi dei destinatari finali e instradare i pacchetti verso i destinatari intermedi del cammino. Il livello LLC/MAC (2) si occupa di garantire l’affidabilità del mezzo di trasmissione e la gestione dell’accesso al mezzo trasmissivo ad accesso multiplo (evitando le collisioni). Infine, il livello fisico (1) si occupa di definire le tecniche di codifica dei dati, la trasmissione e la ricezione dei dati sul mezzo fisico di trasmissione.

L'internet utilizza solo 5 di questi 7 livelli, in ogni trasmissione i livelli ricevono dati dai loro superiori e li incapsulano in delle buste di dati contenenti informazioni aggiuntive ottenute grazie al lavoro svolto su quel livello.
![[SCR-20240118-nasn.png]]


## Livello Fisico e Livello MAC
La trasmissione di dati su un canale richiede la codifica e la decodifica dei dati da parte della scheda di rete. 
I dati in digitale sono bit, quindi sequenze di 0 e 1, questi vengono codificati utilizzando segnali analogici, tutti i segnali viaggiano alla velocità della luce attraverso il canale di trasmissione, difatti la capacità del canale di trasmissione è determinata dal tempo necessario alla codifica e decodifica dei dati

Nella più semplice delle situazioni, quindi in un segmento di rete locale LAN, ogni scheda di rete ha associato uno specifico indirizzo MAC (medium access control), quindi i servizi forniti dal livello 2 (MAC/LLC) ci indicano da quale a quale indirizzo MAC vengono trasmessi i dati in modo che il livello fisico possa smistarli nel modo corretto.
![[SCR-20240118-ness.png]]
Durante questa trasmissione, il pacchetto viene rilevato da tutti i dispositivi connessi al canale, ma viene scartato da tutti quelli che si rendono conto di non essere il destinatario, mentre il destinatario reale lo spacchetta e lo passa al livello superiore.

Inoltre il compito del livello MAC è quello di garantire l'affidabilità del canale di trasmissione applicando una sorta di arbitraggio per decidere chi e quando può comunicare.

Per garantire la trasmissione di tutti i pacchetti viene utilizzato il metodo di acknowledgment, il destinatario quando riceve un pacchetto manda un OK al mittente, mentre se non lo riceve non fa nulla, in modo che il mittente dopo un determinato periodo di tempo possa ritrasmetterlo, ripetendo queste operazioni fino alla conferma di un successo.

Tutti questi procedimenti vengono nascosti ai protocolli di livello superiore, ai quali arriva solo il pacchetto ricevuto correttamente.
### Composizione reti locali
Le principali tecnologie di trasmissione nelle reti locali gestite nei protocolli di livello 2 sono:
- Ethernet: tipo di connessione cablata, trasmette solo se nessun altro sta trasmettendo, se viene rilevata una collisione allora la trasmissione sarà interrotta per essere riprovata più tardi
- IEEE 802.11 (Wi-Fi): è la base delle reti locali senza fili, la scheda ascolta il canale e trasmette solo se nessuno sta trasmettendo, si cerca di prevenire le collisioni dilatando le trasmissioni nel tempo.
- Token Ring: tecnologia utilizzata sulle reti cablate, i dispositivi sono collegati con una topologia di rete ad anello cablato, esiste un token che viene passato come un testimone, chi ha il token può trasmettere, poi deve passare il token.

Per comporre delle reti locali sofisticate ci forniamo di strumenti adatti a risolvere un determinato problema a livello 1 e 2:
- **Repeater**: al livello fisico il repeater si occupa di ritrasmettere i dati indipendentemente da mittente e destinatario, è utilizzato per risolvere il problema della degradazione dei pacchetti dopo lunghe distanze di trasmissione (il limite di ethernet è 100-200 metri) amplificandolo.
- **HUB**: a livello fisico l'hub esegue le stesse mansioni del repeater, ma essendo dotato di molte porte viene utilizzato anche per smistare il segnale nella giusta direzione
- **Bridge**: Il bridge viene utilizzato a livello 2 per connettere segmenti di una rete locale che adottano tecnologie diverse, traduce quindi i frame per trasmetterli nella tecnologia del segmento destinatario.
- **Switch**: utilizzato a livello 2 come un bridge, ma in grado di connettere fino a 12 segmenti, quindi si occupa anche di smistare i dati sul segmento giusto leggendo il relativo indirizzo MAC del pacchetto

## Livello Rete

Le reti locali sono connesse tra di loro attraverso collegamenti organizzati in modo gerarchico, basati su dispositivi rappresentanti delle reti locali (router) a loro volta collegati da da linee di dati veloci o dorsali (backbone).

Il livello rete introduce un protocollo chiamato IP (Internet Protocol), questo protocollo fornisce alla rete locale indirizzi appartenenti ad altre reti locali, si occupa anche di frammentare i dati in pacchetti e di imbustare le informazioni del livello rete.

### Indirizzamento IPv4
Il protocollo ip fornisce una nuova serie di indirizzi denominati IP, associati ad una sola scheda di rete.
Un indirizzo IPv4 è composto da 4 byte, sequenza di 4 valori decimali separati da dei punti, di cui ogni valore decimale varia tra 0 e 255 (136.128.255.10)
L'indirizzo è composto da due parti: il numero della rete alla quale appartiene la scheda, e il numero dell'host all'interno della rete, da questi possiamo determinare la classe della rete, che può essere A,B o C

#### Classificazioni delle reti
##### Classe A
Le reti di classe A sono le più grandi, in queste il numero della rete occupa solo il primo byte dell'indirizzo IP, tutti gli altri byte sono destinati agli host.

Infatti ogni rete di classe A può avere fino a $255*255*255$ host (oltre 16 milioni).

I numeri di rete delle reti di classe A variano da 1 a 126 quindi avremo tutti indirizzi del tipo
```{1-126}.XXX.XXX.XXX```

##### Classe B
Nelle reti di classe B il numero di rete occupa invece 2 byte, destinando gli altri 2 agli host.

Ogni rete di classe B può avere quindi fino a $255*255$ host (oltre 64 mila).

I numeri di rete nelle reti di classe B variano da 128.0 a 191.255 quindi gli indirizzi saranno
```{128-191}.{0-255}.XXX.XXX```

##### Classe C
Nelle reti di classe C il numero di rete occupa 3 byte su 4, quindi gli host hanno a disposizione solo un byte.

Ogni rete di classe C può avere fino a 254 host e i numeri di rete variano da 192.0.0 a 223.255.255

##### Indirizzi mancanti
Nelle classificazioni si può notare che non sono presenti le reti che iniziano con 127 e le reti che iniziano con numeri che variano da 224 a 255. 
Per quanto riguarda il 127 le reti che iniziano con questo indirizzo sono destinate per scopi di loopback, quindi per ambienti locali, mentre quelle che variano da 224 a 255 sono porte riservate per il futuro e per esperimenti.

#### Sottoreti (subnetwork)
L'indirizzo IP viene spezzato in due componenti logiche mediante una maschera di rete (netmask) che rileva l'indirizzo di sottorete rappresentato dai bit uguali ad 1 nella netmask e il numero dell'host rappresentato dai bit uguali a 0. In questo modo si creano gerarchie di sottoreti, ognuna rappresentata da un router.

Esempio: rete di classe B ```130.136``` con 256 sottoreti: netmask ```255.255.255``` 
	130.136.1 è la sottorete 1, 130.136.2 è la sottorete 2
	130.136.1.22 è l'host 22 della sottorete 1

Informazioni come l'indirizzo IP, il default router e la netmask sono fondamentali per la configurazione di una rete




### Instradamento dei pacchetti (forwarding)
Esempio: host 140.217.2.10 spedisce a 130.136.2.33
	- pacchetto raccolto dal default router della sottorete: 140.217.2.254.
	- destinatario non appartiene alla sottorete -> pacchetto inoltrato al default router del livello superiore (default router): 140.217.0.254.
	- destinatario 130.136, la tabella di forwarding indica di spedire a 190.89.0.254
	- destinatario 130.136, la tabella di forwarding indica di spedire a 130.136.0.254
	- il pacchetto appartiene a questa rete, raccolto dal router
	- pacchetto spedito al router della sottorete 2
	- pacchetto spedito a 130.136.2.33
Il problema del routing consiste quindi nel continuo aggiornamento delle tabelle di forwarding dei router, le modifiche dei cammini della rete sono essenziali al giorno d'oggi in quanto molti dispositivi sono connessi senza cablaggio, sono necessarie quindi delle operazioni da parte dei router per scoprire i nuovi cammini

#### Protocolli di routing
I protocolli di routing si basano sull'invio di richieste del tipo: qualcuno conosce il modo di raggiungere questo destinatario? La risposta sarà essenziale per modificare la tabella di forwarding. Tra i protocolli (algoritmi) più famosi di routing abbiamo
- Routing Information Protocol (RIP)

- Open Shortest Path First (OSPF)
- Border Gateway protocol (BGP)

### Protocollo ICMP (Internet Control Message Protocol)
ICMP è utilizzato da host, router e gateway per scambiare informazioni a livello rete, usando pacchetti definiti con il protocollo IP, lo scopo è quello di notificare la presenza di errori all'interno della rete, tra cui:
- Rete di destinazione non raggiungibile (possibile interruzione di rete?) § Rete di destinazione sconosciuta (indirizzo di rete male specificato?)  
- Host destinazione non raggiungibile (host spento o scollegato?)  
- Host destinazione sconosciuto (indirizzo di host male specificato?)  
- Protocollo richiesto non disponibile (servizi non previsti)
- Ricerca di un cammino alternativo per la destinazione (se esiste)

Tra le applicazioni basate sul protocollo ICMP più famose abbiamo due comandi terminale fondamentali per il discovery delle reti:

#### PING
Ping esegue un test di verifica di connessione tra due host, ovvero tra chi chiama il comando e l'host specificato
```bash
ping <indirizzo IP host 2>
```
L'host1 invia ICMP e l'host2 risponde (eco) se esiste ed è raggiungibile, inoltre viene calcolato il tempo di andata e ritorno delle richieste RTT (Round Trip Time)

#### Traceroute
Traceroute mostra la sequenza di router attraversati da un pacchetto per raggiungere l'host specificato
```bash
traceroute <indirizzo IP host 2>
```
È realizzato inviando ICMP spediti in sequenza verso distanze via via maggiori
### Protocollo ARP e RARP
Quando un router riceve un pacchetto destinato alla sua rete esso deve produrre un frame di livello MAC per poterlo instradare sul mezzo di trasmissione interno alla rete locale, per scoprire l'indirizzo MAC.
#### ARP (Address Resolution Protocol)
Utilizzato se il router non conosce l'indirizzo MAC del destinatario corrispondente all'indirizzo IP specificato sul pacchetto, il router genera un frame spedito a tutti i dispositivi della rete dove si chiede appunto qual'è l'indirizzo MAC del dispositivo con questo IP, se il dispositivo esiste risponde con un frame di livello MAC indirizzato al router, nel quale viene evidenziato il MAC richiesto

#### RARP (Reverse-ARP)
È la versione opposta del protocollo ARP, quindi si chiede quale indirizzo IP corrisponde ad uno specifico indirizzo MAC

### Assegnazione indirizzi IP (DHCP)
L'associazione dei numeri di host appartenenti ad una rete può avvenire in due modi
#### Associazione manuale
Gli indirizzi degli host sono associati manualmente ai dispositivi dall'amministratore di rete, una volta associato l'indirizzo questo rimarrà lo stesso fino a nuova modifica. Questo tipo di associazione è chiamato IP statico.

#### Associazione automatica
Viene effettuata da un server seguendo il protocollo DHCP (Dynamic Host Configuration Protocol) che effettua l'associazione di IP dinamici. 

Questo metodo è utilizzato principalmente nelle reti domestiche e reti wireless, il server DHCP è un host che implementa il servizio di associazione degli IP agli host che ne fanno richiesta. Esso dispone di una serie di indirizzi liberi disponibili per l'associazione con un indirizzo MAC del richiedente. Si chiamano appunto indirizzi dinamici in quanto lo stesso indirizzo MAC può esser di volta in volta associato a diversi indirizzi IP. Il servizio DHCP segue quindi la filosofia del "plug and play" ovvero che basta connettere il dispositivo al medium per poter accedere alla rete


### IPv6 e tunnelling IPv4
L'incremento dei dispositivi connessi ad internet porta il problema di avere troppi dispositivi per un numero limitato di indirizzi IP, l'IPv6 rimanda questo problema estendendo gli indirizzi IP da 4 a 16 byte, portando quindi ad avere una stima di possibili 15 mila indirizzi IP per ogni metro quadro della terra.

Adottare un nuovo protocollo IP comporta quindi anche la necessità di adottare nuove strutture per l'imbustamento dei pacchetti, in quanto la nuova tecnologia non va ancora completamente a sostituire quella vecchia è stato creato un meccanismo di **tunnelling** per spedire pacchetti IPv6 in buste IPv4

![[SCR-20240118-osei.png]]


## Livello Trasporto

A livello trasporto esistono due protocolli di rete essenziali:
- TCP (Trasmission Control Protocol)
- UDP (User Data Protocol)

### Protocollo TCP
Il servizio TCP è un servizio di trasporto affidabile connection-oriented, garantisce il riordinamento basato sulla numerazione dei pacchetti e l'integrità dei pacchetti della trasmissione insieme alla ri-trasmissione dei pacchetti perduti. Inoltre, attraverso il numero d’ordine, la controparte può inviare a sua volta pacchetti di conferma della ricezione (acknowledgment) che sono però diversi da quelli del livello LLC.

TCP consente lo smistamento dei pacchetti verso le rispettive applicazioni in ascolto su delle "porte".

Per funzionare richiede l'attivazione di una connessione punto a punto tra i due socket (client e server) in modo da mettere in comunicazione le applicazioni in attesa sui socket.
L'host mittente richiede una connessione con un socket, che se è aperto e libero gli risponde con OK, una volta ricevuto l'ok il mittente può iniziare a comunicare. Al termine della connessione vengono rilasciate le porte usate.

![[SCR-20240118-ovll.png]]

Il livello trasporto comunica quindi con il livello applicazione solo attraverso una delle porte disponibili, che combacia con quella specificata nella connessione.

TCP mette in comunicazione anche dispositivi molto distanti tra loro, di conseguenza sorgono dei problemi di alta latenza, inviando un solo pacchetto alla volta e aspettando la ricezione si ottiene una connessione troppo lenta, ma inviando troppi pacchetti insieme si può sfociare in una congestione di rete. Esistono meccanismi come quello del **controllo del flusso**, che consiste nell'inviare pacchetti al massimo ritmo sostenibile dal destinatario finale, oppure il **controllo di congestione** che consiste nell'inviare pacchetti al massimo ritmo sostenibile dal router più lento presente nella strada tra il mittente e il destinatario.
#### Finestra scorrevole (SW sliding-window)
Una finestra scorrevole rappresenta il numero massimo di pacchetti che un mittente può spedire di seguito, in attesa di ricevere conferme, è un valore intero positivo.
- Controllo di flusso: non spedisce più di SW pacchetti, se i primi SW vengono confermati allora si procede all'invio dei prossimi SW, se un pacchetto non viene confermato viene rispedito prima di rispedire i successivi.
- Controllo di congestione: vengono spediti un numero SW variabile di pacchetti, se i pacchetti sono tutti confermati allora si aumenta SW (SW=2-4-8), ma appena un pacchetto non viene confermato si resetta SW al valore minimo, in pratica si cerca sempre di aumentare il ritmo e appena viene scoperta una congestione si rallenta
### Protocollo UDP
In alternativa il protocollo UDP non fa niente di tutto questo, l'aspetto positivo è la sua estrema semplicità e il fatto che non vengono aggiunte delle gestioni pesanti all'invio e alla ricezione dei pacchetti, non garantisce l'affidabilità essendo comunque un servizio connectionless

### Nomi di  dominio e servizio (DNS)
Gli utenti preferiscono accedere alle risorse della rete utilizzando dei nomi piuttosto che degli indirizzi numerici, in quanto i nomi sono mnemonici e gerarchici, i nomi di dominio sono assegnati in modo univoco proprio come i numeri di rete. 

I protocolli di rete preferiscono però utilizzare gli indirizzi IP, qui entra in gioco il servizio DNS (Domain Name Service). Questo è basato su una catena di server DNS organizzati gerarchicamente, quindi ogni host in rete deve conoscere almeno un DNS server e ogni DNS server deve conoscere un DNS server superiore. 

Questi server ricevono richieste attraverso appunto il protocollo DNS e ritornano un indirizzo IP, se il server non conosce l'IP dell'hostname richiesto allora inoltra la domanda al server superiore. I DNS server radice (DNS root server) conoscono tutti i domini e i loro IP, ma sono pochi e molto costosi.

## Livello Applicazione
Il livello applicazione fornisce protocolli per spedire e ricevere dati dalle applicazioni, si appoggia al livello trasporto per fornire servizi tra cui:
- Posta elettronica: basati su protocolli di livello applicazione
	- Simple Mail Transfer Protocol (SMTP): spedizione e trasporto dei messaggi
	- Post Office Protocol (POP3): consegna di messaggi all'utente
	- Internet Mail Access Protocol (ICMP): alternativa a POP3
- World Wide Web (WWW): basato su applicazioni con protocollo HTTP (protocollo per trasferire pagine web)
- DNS: domain name service

Le applicazioni e i servizi su internet possono essere realizzati seguendo due famose metodologie:
- Architettura Client/Server: i client sono host che producono richieste di servizio, mentre i server sono host sui quali sono in esecuzione i servizi che soddisfano le richieste
- Architettura P2P (Peer-To-Peer): tutti gli host sono contemporaneamente sia client che server, ogni host cerca di soddisfare le richieste ricevute se possibile agendo a server, agisce da client quando effettua richieste ad altri host

