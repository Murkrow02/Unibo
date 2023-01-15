/*
Una fabbrica usa 16 tipi di componenti (es. ruota telaio scocca sellino catena ....). 
Ogni volta che occorre costruire un prodotto occorre prendere dal magazzino le parti necessarie, 
e.g. per fare un go-kart occorre una scocca e 4 ruote, per fare una bicicletta un telaio, un sellino, 
2 ruote e una catena. Scopo dell'esercizio è di scrivere un monitor storage per la gestione del magazzino (un vettore di 16 interi).
\ Ogni volta che un magazziere riceve un carico di componenti dal formitori chiama la funzione: 
storage.add(components) dove components è un vettore di 16 elementi, indica quanti componenti di ogni tipo vengono aggiunti al magazzino. 
Quando un operaio deve costruire un prodotto chiama: storage.get(components) dove components è un vettore di 16 elementi: 
indica quanti componenti di ogni tipo sono necessari per costruire il prodotto richiesto. 
Ovviamente se manca qualche componente occorre aspettare che i magazzinieri ricevano e mettano nel magazzino le parti mancanti. 
Le richieste degli operali devono essere soddisfatte in ordine FIFO. Ci possono essere casi di Deadlock? e di Starvation? perché?
*/

monitor magazzino{

    int components[16];
    queue<components> requests;
    queue<conditions> waiting;

    magazzino(components iniziali){
        components = iniziali;
    }


    procedure entry add(components newComponents){

        components.add(newComponents);

        
        if(requests != empty){

            bool canBeSatisfied = true;
            for(int i = 0; i < components.size(); i++){
                if(components[i] < requests.first()[i]){
                    canBeSatisfied = false;
                    break;
                }
            }

            if(canBeSatisfied){
                waiting.dequeue().signal()
            }
        }
    }

    procedure entry get(components neededCompoenents){

        for(int i = 0; i < components.size(); i++){


            if(components[i] < neededCompoenents[i]){
                condition a = new condition()
                waiting.push(a)
                requests.push(neededCompoenents)
                break;
            }

        }
    }


}