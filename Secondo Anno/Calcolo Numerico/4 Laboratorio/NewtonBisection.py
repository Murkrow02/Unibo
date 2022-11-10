import numpy as np
import math
import matplotlib.pyplot as plt
    

''' Metodo di Bisezione'''
def bisezione(a, b, f, tolx, xTrue):
   
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
            return (c, i, k, vecErrore)
        else:
            if (fc > 0):
                b = c
            else:
                a = c

    return (c, i, k, vecErrore)

      
''' Metodo di Newton'''

def newton(f, df, tolf, tolx, maxit, xTrue, x0=0):
  
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
    return (x, i, err, vecErrore)  



'''creazione del problema'''
f = lambda x : ((np.e)**x) - (x**2)
df = lambda x : ((np.e)**x) - 2*x
xTrue = -0.7034674
fTrue = f(xTrue)
print ("fTrue:", fTrue)

a=-1.0
b=1.0
tolx= 10**(-10)
tolf = 10**(-6)
maxit=100
x0= 0


''' Grafico funzione in [a, b]'''
x_plot = np.linspace(a, b, 101)
f_plot = f(x_plot)

#Show grid and axis
plt.grid(True, "both")
plt.axhline(y=0, color="k")
plt.axvline(x=0, color="k")

#Show plot info
plt.title("Original function")

#Plot function
plt.plot(x_plot,f_plot)
plt.show()


''' Calcolo soluzione tramite Bisezione e Newton'''
xBisection, iBisection, kBisection, vecErrBisection = bisezione(a,b,f,tolx,xTrue)
print('Metodo di bisezione \n x =', xBisection,'\n iter_bise=', iBisection, '\n iter_max=', kBisection)
print('\n')


xNewton, iNewton, errNewton, vecErrNewton = newton(f, df, tolf, tolx, maxit, xTrue)
print('Metodo di Newton \n x =', xNewton,'\n iter_new=', iNewton, '\n err_new=', errNewton)
print('\n')


''' Grafico Errore vs Iterazioni'''

#Calculate first zero index of the two arrays
firstZero = min(np.where(vecErrBisection == 0)[0][0], np.where(vecErrNewton == 0)[0][0])

#Truncate newton array at the found position
vecErrNewton = vecErrNewton[:firstZero + 1]

#Get range of ticks
x_plot = np.arange(0, vecErrBisection.size + 1, 2)
plt.xticks(x_plot)

#Set title
plt.title("Errori assoluti")

#Plot Errors
plt.plot(vecErrBisection, color="red", marker='o', label="Bisezione")
plt.plot(vecErrNewton, color="blue", marker='o', label = "Newton")
plt.legend()
plt.show()



