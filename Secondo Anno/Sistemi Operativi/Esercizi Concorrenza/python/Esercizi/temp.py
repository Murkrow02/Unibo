from semaphore import semaphore
from Queue import Queue

mutex = semaphore(1)
semaphores = Queue()
sum_ = 0

def sumstop(val):
    global sum_ 


    sem = semaphore(0)
    mutex.P()
    sum_ = sum_ + val
    semaphores.put(sem)
    mutex.V()
    sem.P()
    #free(sem)
    
    
def sumgo():
    
    mutex.P()
    
    
    while(semaphores.empty() == False):
        sem = semaphores.get()
        sem.V()
    
    mutex.V()
    
    sum_ = 0
    return sum_