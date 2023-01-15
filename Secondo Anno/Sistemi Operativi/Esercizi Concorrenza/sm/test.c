#import "semaphore.h"
#import "tlist.h"


queue sempaphores = new queueofsem()
queue sumvalues = new queueofint()

void sumstop(int v){

    semaphore s = semaphore_create(1);
    semaphores.add(s);
    sumvalues.add(s);
    semaphore_P(s);
}

int sumgo(){
    int returnval == 0;

    semaphore currentSem = semaphores.dequeue()
    int currentVal = sumvalues.dequeue()
    while(current != null && currentVal != null)
    {
        semaphore_V(currentSem);
        returnVal += currentVal;
        currentSem = semaphores.dequeue();
        currentVal = sumvalues.dequeue()
    }

    return returnVal;
}