#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 23 19:17:18 2022

@author: valeriopiodenicola
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy

n = np.array([1,2,3,5,7])








def plot_with_apprx(x, y):
    N = x.size # Numero dei dati
    A = []
    
    for k in range(0, len(n)):
    
        A.append(np.zeros((N, n[k]+1)))

        for i in range(0, N):
            row = []
            for j in range(0, n[k] + 1):   
                row.append(np.power(x[i], j))
            (A[k])[i] = row
                #print("row:",row, N)

        #print("A = \n", A[k])


        ''' Risoluzione tramite equazioni normali'''

        # calcoliamo la matrice del sistema e il termine noto a parte
        ATA = np.transpose(A[k])@A[k]
        ATy = np.transpose(A[k])@y

        # Per ora risoluzione canonica in quanto Cholesky crasha per matrici troppo grandi
        alpha_normali = scipy.linalg.solve(ATA, ATy)
    
        # Funzione per valutare il polinomio p, in un punto x, dati i coefficienti alpha (DELLA PROF)
        def p(alpha, x):
            m=x.size
            A[k] = np.zeros((m, alpha.size))
    
            for l in range(0, m):
                row = []
                for o in range(0, n[k] + 1):
                    row.append(np.power(x[l], o))
                (A[k])[l] = row
        
            return A[k]@alpha
    
        x_plot = np.linspace(-1,1,100)
        y_normali = p(alpha_normali, x_plot)
    
        plt.plot(x_plot,y_normali, label = "Approximation n={}".format(n[k]))


'''CONFRONTO GRAFICO DEL POLINOMIO'''



# Domain


# Codomains

#y_svd = p(alpha_svd, x_plot)



x0 = np.arange(-1, 1, 0.01)
y0 = x0*np.exp(x0)
visiblex = np.arange(-1,1.5, 0.5)
visibley = visiblex*np.exp(visiblex)
plt.plot(visiblex, visibley, "o", label = "Points of reference")
plt.plot(x0, y0, color="red", label ="Function")
plot_with_apprx(x0,y0)
plt.title("f(x) = xexp(x)")
plt.legend()
plt.show()


x1 = np.arange(-1, 1, 0.01)
y1 = 1 / (1+ 25*x1)
visiblex1 = np.arange(-1,1.5, 0.5)
visibley1 =  1 / (1+ 25*visiblex1)
plt.plot(visiblex1, visibley1, "o", label = "Points of reference")
plt.plot(x1, y1, color="red", label ="Function")
plot_with_apprx(x1,y1)
plt.title("f(x) = 1 / 1+25*x")
plt.legend()
plt.show()


x2 = np.arange(1,5,0.01)
y2 = np.sin(5*x2)+3*x2
visiblex2 = np.arange(1,5,0.01)
visibley2 =  np.sin(5*visiblex2)+3*visiblex2
plt.plot(visiblex2, visibley2, "o", label = "Points of reference")
plt.plot(x2, y2, color="red", label ="Function")
plot_with_apprx(x2,y2)
plt.title("f(x) = sin(5x)+3x")
plt.legend()
plt.show()



"""
plt.subplot(2, 2, 2)
plt.plot(x[1], y[1], color="red")

plt.subplot(2, 1, 2)
plt.plot(x[2], y[2], color="red")
"""


