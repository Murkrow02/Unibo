//c.1 2022.02.14

monitor semdata{

    int semVal;
    stack<datatype> dataStack;
    condition ok2go;

    smedata(int initial)
    {
        semVal = initial;
    }

    datatype dP(){

        if(semVal == 0)
            ok2go.wait();

        semVal--;
        return dataStack.pop();
    }

    void dV(datatype data){

        dataStack.push(data);
        semVal++;
        ok2go.signal();
    }

}

//c.2 2021.09.15

void chained_send (T msg, list_of_pids dests){
    
    ssend(<msg, dests.removeHead()>, dests.head());
}

T chained_recv(){

    msg, dests = srecv(ANY);
    chained_send(msg, dests);
}