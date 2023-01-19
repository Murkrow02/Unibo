void snsend(msgtype msg, pid_t dest){

    //Manda il messaggio normalmente
    asend(msg, dest);

    //Aspetta acknowledgement
    ack = arecv(dest);
}

msgtype snrecv(pid_t sender, int n){

    //Coda dei messaggi smistati
    queue<pid_t sender, msgtype msg> smistati;

    int daArrivare = n+1;
    int arrivati = 0;

    //Qua salvo se ho trovato quello che ci serve
    msg quelloBuono;

    do{
        msg, msgsender = arecv(sender); //Attende finche non ne arriva uno
        arrivati++;

        //Questo messaggio non ci serve e dopo lo rimettiamo dove stava
        if(arrivati != daArrivare){
            smistati.add(msgsender, msg);
        }else{

            //Abbiamo trovato quello che ci serve
            quelloBuono = msg;

            //Manda ack
            asend(ack, msgsender);

            //Rimetti i messaggi dove stavano
            while(smistati != empty()){
                asend(<msgsender, msg>, getpid()); //Lo autorimandiamo a noi
            }
        }
    }
    while (arrivati != daArrivare)
    
    return quelloBuono;
}