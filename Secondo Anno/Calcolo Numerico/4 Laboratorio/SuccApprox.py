import numpy as np
import math
import matplotlib.pyplot as plt
from FunctionRootMethods import succ_app

'''creazione del problema'''
f = lambda x : ((np.e)**x) - (x**2)
df = lambda x : ((np.e)**x) - 2*x

g1 = lambda x: x-f(x)*(np.e**(x/2))
g2 = lambda x: x-f(x)*(np.e**(-x/2))
g3 = lambda x: x-(f(x)/df(x))

xTrue = -0.7034674
fTrue = f(xTrue)
print('fTrue = ', fTrue)

tolx= 10**(-10)
tolf = 10**(-6)
maxit=100
x0= 0

a=-1.0
b=1.0


''' Grafico funzione in [-1, 1]'''

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


'''Calcolo soluzione in g1, g2 e g3'''

xG1, iG1, errG1, vecErrG1, time = succ_app(f, g1, tolf, tolx, maxit, xTrue)
print('Metodo approssimazioni successive g1 \n x =', xG1,'\n iter_new=', iG1)

xG2, iG2, errG2, vecErrG2, time = succ_app(f, g2, tolf, tolx, maxit, xTrue)
print('Metodo approssimazioni successive g2 \n x =', xG2,'\n iter_new=', iG2)

xG3, iG3, errG3, vecErrG3, time = succ_app(f, g3, tolf, tolx, maxit, xTrue)
print('Metodo approssimazioni successive g3 \n x =', xG3,'\n iter_new=', iG3)


''' Grafico Errore vs Iterazioni'''

#Calculate first zero index of the two arrays
firstZero = max(np.where(vecErrG1 == 0)[0][0], np.where(vecErrG3 == 0)[0][0])

#Truncate array at the found position
vecErrG1 = vecErrG1[:firstZero + 1]
vecErrG2 = vecErrG2[:firstZero + 1]
vecErrG3 = vecErrG3[:firstZero + 1]

#Set title
plt.title("Errori assoluti")

# g1
plt.plot(vecErrG1, color="red", label = "g1", marker = 'o')
# g2
plt.plot(vecErrG2, color="blue", label = "g2", marker = 'o')
# g3
plt.plot(vecErrG3, color="brown", label = "g3", marker = 'o')
plt.xlabel('Iterazioni', fontweight ='bold', fontsize = 15)
plt.ylabel('Errore', fontweight ='bold', fontsize = 15)
plt.legend()
plt.show()