import numpy as np
import math
import matplotlib.pyplot as plt
from FunctionRootMethods import bisezione, newton

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
xBisection, iBisection, kBisection, vecErrBisection, time = bisezione(a,b,f,tolx,xTrue)
print('Metodo di bisezione \n x =', xBisection,'\n iter_bise=', iBisection, '\n iter_max=', kBisection)
print('\n')


xNewton, iNewton, errNewton, vecErrNewton, time = newton(f, df, tolf, tolx, maxit, xTrue)
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
plt.xlabel('Iterazioni', fontweight ='bold', fontsize = 15)
plt.ylabel('Errore', fontweight ='bold', fontsize = 15)
plt.show()



