extern int nServers;
process dispatcher{

    bool serverBusy[nServers];
    Dictionary<pid, pid> inoltraRisposta; //Manda riposta da server "key" a client "value"


    while(true){

        msg, mittente = arecv(ANY);

        //Detecta se é un server oppure client
        if(isServer(mittente)){
            
            //Un server ha finito di elaborare la richiesta, rispediscila al mittente
            destinatario = inoltraRisposta.get(mittente); //Vedi a chi era destinata la risposta originariamente
            inoltraRisposta.remove(mittente); //Ritorna al client la risposta
            serverBusy[getServerIndex(mittente)] = false; //Salva che il server non é piú occupato
            asend(destinatario, msg);
        }

        //Client
        else{

            //Continua finché non si libera un server
            while(true){

                //Controlla tutti i server
                for(i in [0,n-1]){
                    if(!serverBusy[i]){

                        //trovato server libero
                        inoltraRisposta.add(getPid(i), mittente); //capisci dopo a chi reinoltrare la risposta
                        asend(getPid(i), msg); //Inoltra la richiesta al server libero
                        serverBusy[i] = true; //Salva che il server é occupato
                    }
                }

            }

        }

       
        


    }

        


}