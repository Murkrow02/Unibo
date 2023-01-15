monitor delay{

    ordered_queue waiting = new ordered_queue(); 

    int wait_tick(int nticks){
        
        //Aggiungi a coda ordinata una nuova condizione
        condition cond = new condition();
        waiting.enqueue(nticks,cond);

        //Aspetta che i ticks scendano a 0
        cond.wait()

        //I ticks sono scesi a 0
        return waiting.size();

    }


    void tick(){

        foreach (item in waiting){
            item.remainingTicks--;
            if(item.remainingTicks == 0){
                waiting.dequeue();
                item.cond.signal();
            }
        }


    }

}
