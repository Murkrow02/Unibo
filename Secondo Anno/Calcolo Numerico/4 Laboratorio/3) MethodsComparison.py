from FunctionRootMethods import bisezione, newton, succ_app
import numpy as np
import math
import matplotlib.pyplot as plt

''' creazione del problema '''
a1, b1 = 0, 2
f1 = lambda x : (x**3) + 4*x*np.cos(x) - 2
g1 = lambda x : (2-(x**3))/(4*np.cos(x))
d1 = lambda x : (3*x**2) + 4*(math.cos(x) - x*math.sin(x)) # derivative for newton

a2, b2 = 3, 5
f2 = lambda x : x - (x**(1/3)) - 2
g2 = lambda x : (x**(1/3)) + 2
d2 = lambda x : 1 - 1/(3*(x**(2/3))) # derivative for newton

'''precision parameters'''
tolx = 10**(-6)
tolf = 10**(-6)
maxit=100

#Bisezione
bisectionf1 = bisezione(a1, b1, f1, tolx, None)
bisectionf2 = bisezione(a2, b2, f2, tolx, None)

#Approssimazioni successive (il vettore dell'errore non è giusto in quanto non abbiamo xTrue)
approxf1 = succ_app(f1, g1, tolf, tolx, maxit, 0, a1)
approxf2 = succ_app(f2, g2, tolf, tolx, maxit, 0, a2)

#Newton
newtonf1 = newton(f1, d1, tolf, tolx, maxit, 0, a1)
newtonf2 = newton(f2, d2, tolf, tolx, maxit, 0, a2)

#Prepare data for bar chart (iteration)
methodsNames = ["Bisezione", "Approssimazioni", "Newton"]
methodsIterations_f1 = [bisectionf1[1], approxf1[1], newtonf1[1]]
methodsIterations_f2 = [bisectionf2[1], approxf2[1], newtonf2[1]]
barWidth = 0.25
fig = plt.subplots(figsize =(12, 8))
br1 = np.arange(len(methodsNames)) + barWidth/2
br2 = [x + barWidth for x in br1]

#Display bar chart
plt.bar(br1, methodsIterations_f1, color ='r', width = barWidth, edgecolor ='grey', label ='f1')
plt.bar(br2, methodsIterations_f2, color ='b', width = barWidth, edgecolor ='grey', label ='f2')
plt.xlabel('Metodi', fontweight ='bold', fontsize = 15)
plt.ylabel('Iterazioni', fontweight ='bold', fontsize = 15)
plt.xticks([r + barWidth for r in range(len(methodsNames))],methodsNames)
plt.legend()
plt.show()

#Prepare data for bar chart (time elapsed)
methodsTimes_f1 = [bisectionf1[-1], approxf1[-1], newtonf1[-1]]
methodsTimes_f2 = [bisectionf2[-1], approxf2[-1], newtonf2[-1]]
barWidth = 0.25
fig = plt.subplots(figsize =(12, 8))
br1 = np.arange(len(methodsNames)) + barWidth/2
br2 = [x + barWidth for x in br1]

#Display bar chart
plt.bar(br1, methodsTimes_f1, color ='r', width = barWidth, edgecolor ='grey', label ='f1')
plt.bar(br2, methodsTimes_f2, color ='b', width = barWidth, edgecolor ='grey', label ='f2')
plt.xlabel('Metodi', fontweight ='bold', fontsize = 15)
plt.ylabel('Tempo trascorso', fontweight ='bold', fontsize = 15)
plt.xticks([r + barWidth for r in range(len(methodsNames))],methodsNames)

plt.legend()
plt.show()