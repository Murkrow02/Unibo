import numpy as np
import math
import matplotlib.pyplot as plt
from FunctionRootMethods import bisezione, newton, succ_app

# Configuration
a=-1.0
b=1.0
tolx = 10**(-6)
tolf = 10**(-6)
maxit=100
x0= 0
zoom = False
     
def findFunctionRoot(f, xTrue, df, fname, gFuncs, x0=0):
    
   
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
    
    
    ''' Calcolo soluzione Bisezione'''
    xBisection, iBisection, kBisection, vecErrBisection, time = bisezione(a,b,f,tolx,xTrue)
    
    ''' Calcolo soluzione Newton'''
    xNewton, iNewton, errNewton, vecErrNewton, time = newton(f, df, tolf, tolx, maxit, xTrue,x0)
    
    ''' Calcolo soluzione approssimazione successive'''
    xApps = []
    iApps = []
    errApps = []
    vecErrApps = []
    timeApps = []
    for g in gFuncs:
        xApp, iApp, errApp, vecErrApp, timeApp = succ_app(f, g, tolf, tolx, maxit, xTrue)
        xApps.append(xApp)
        iApps.append(iApp)
        errApps.append(errApp)
        vecErrApps.append(vecErrApp)
        timeApps.append(timeApp)
    
    
    ''' Grafico Errore vs Iterazioni'''    
    #Get range of ticks
    x_plot = np.arange(0, max(vecErrBisection.size,(vecErrNewton.size), max([len(i) for i in vecErrApps])) + 1, 2)
    #plt.xticks(x_plot)
    
    #Set title
    plt.title("Errori assoluti \n {}".format(fname))
    
    #Plot Errors
    for error in vecErrApps:
        plt.plot(error, label = "Punto fisso g")
    
    plt.plot(vecErrBisection, color="red", label="Bisezione")
    plt.plot(vecErrNewton, color="blue", label = "Newton")
    plt.legend()
    if zoom:
        plt.xlim(0,np.trim_zeros(errNewton).size + 5)
    plt.xlabel('Iterazioni', fontweight ='bold', fontsize = 15)
    plt.ylabel('Errore', fontweight ='bold', fontsize = 15)
    plt.show()
    
    
    
'''Prima funzione'''
f = lambda x : ((np.e)**x) - (x**2)
df = lambda x : ((np.e)**x) - 2*x
xTrue = -0.7034674
fTrue = f(xTrue)
g1 = lambda x: x-f(x)*(np.e**(x/2))
g2 = lambda x: x-f(x)*(np.e**(-x/2))
g3 = lambda x: x-(f(x)/df(x))
findFunctionRoot(f, xTrue, df, "f(x)=exp(x) x^2 ", [g1,g2,g3])


'''Seconda funzione'''
f = lambda x : (x**3) + 4*x*np.cos(x) - 2
xTrue = 0.536839
g1 = lambda x : (2-(x**3))/(4*np.cos(x))
df = lambda x : (3*x**2) + 4*(math.cos(x) - x*math.sin(x)) # derivative for newton
findFunctionRoot(f, xTrue, df, "f(x)=x^3+4xcos(x)-2", [g1])

'''Terza funzione'''
f = lambda x : x - (x**(1/3)) - 2
g1 = lambda x : (x**(1/3)) + 2
df = lambda x : 1 - 1/(3*(x**(2/3))) # derivative for newton
xTrue = 3.52138
findFunctionRoot(f, xTrue, df, "f(x)=x-(x^1/3)-2 ", [g1], 3) #IMPORTANTE IL 3 SENNO DERIVATA NON FUNZIONA

