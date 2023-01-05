import numpy as np
import math
import time

''' Metodo di Bisezione'''
def bisezione(a, b, f, tolx, xTrue):
    
    start = time.time()
   
    # numero minimo di iterazioni per avere un errore minore di tolx
    k = math.ceil(np.log2((b-a)/tolx))
    #get machine precision
    eps = np.finfo(float).eps
    
    #init vector of abs errors
    vecErrore = np.zeros((k,1))
  
    #Throw exception if zero is not in range
    if f(a)*f(b)>0:
        raise Exception("Zero is not in range")
  
    #vecErrore[0] = 0.45
    for i in range(1,k):
        print(a,b)
        
        #Get the middle of the range
        c = (a+b) / 2 
        
        #Get the value of the function in c
        fc = f(c)
        
        #save c found at iteration
        if (xTrue != None):
            vecErrore[i-1] = np.abs(c - xTrue)
        
        # se f(c) è molto vicino a 0 
        if (abs(fc) <= eps):   
            print("f(c) molto vicino a 0", fc)                               
            break
        else:
            if (fc > 0):
                b = c
            else:
                a = c

    end = time.time()
    
    return (c, i, k, vecErrore, end-start)

      
''' Metodo di Newton'''

def newton(f, df, tolf, tolx, maxit, xTrue, x0=0):
  
    start = time.time()
    
    err=np.zeros(maxit, dtype=float)
    vecErrore=np.zeros( (maxit,1), dtype=float)
  
    i=0
    err[0]=tolx+1
    vecErrore[0] = np.abs(x0-xTrue)
    x=x0
    oldx = x0
    
    #First iteration fails condition so we check condition at the end
    while (True): 
        
        i = i + 1
        oldx = x
        x = x - (f(x)/df(x))

        err[i] = abs(x-oldx)      
        vecErrore[i] = np.abs(x-xTrue)
        
    
        if ((abs(f(x)) <= tolf and abs(x-oldx) <= tolx) or i >= maxit):
            break
        
    end = time.time()
        
    return (x, i, err, vecErrore, end-start)  

''' Metodo delle approssimazioni successive'''
def succ_app(f, g, tolf, tolx, maxit, xTrue, x0=0):
  
  start = time.time()
    
  err=np.zeros(maxit+1, dtype=np.float64)
  vecErrore=np.zeros(maxit+1, dtype=np.float64)
  
  i= 0
  err[0]=tolx+1
  if (xTrue != None):
      vecErrore[0] = np.abs(x0-xTrue)
  x = x0

  while (True): 
        
        i = i + 1
        oldx = x
        x = g(x)

        err[i] = abs(x-oldx)    
        if (xTrue != None):
            vecErrore[i] = np.abs(x-xTrue)
        
    
        if ((abs(f(x)) <= tolf and abs(x-oldx) <= tolx) or i >= maxit):
            break
        
  end = time.time()
  return (x, i, err, vecErrore, end-start) 