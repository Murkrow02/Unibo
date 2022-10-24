#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 23 19:17:18 2022

@author: valeriopiodenicola
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg

#Define grades of the polinomy
n = np.array([1,2,3,5,7])

#Main func plot_with_apprx(xspace, yspace, [leftmargin, rightmargin])
def plot_with_apprx(x, y, margins):
    N = x.size # Numero dei dati
    A = []
    
    #cycle for the n grade
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
        
        
        
        '''CONFRONTO GRAFICO DEL POLINOMIO'''
    
        # Domain
        x_plot = np.arange(margins[0],margins[1],0.01)
        # Codomains
        y_normali = p(alpha_normali, x_plot)
        #y_svd = p(alpha_svd, x_plot)
        
        #Calculate norm2 of the relative error
        if (margins[0] < 0 and margins[1] > 0):
            exactval = np.array([x[100], y[100]])
            approxval = np.array([x_plot[100], y_normali[100]])
            relerror = np.linalg.norm(approxval-exactval) / np.linalg.norm(approxval)
            print("Norm 2 error for n={}:".format(n[k]), relerror)     
        
        plt.plot(x_plot,y_normali, label = "Approximation n={}".format(n[k]))




'''PLOT PRIMA FUNZIONE'''

#Calculated function plot
x0 = np.arange(-1, 1, 0.01)
y0 = x0*np.exp(x0)
plt.plot(x0, y0, color="red", label ="Function")

#Points of reference
visiblex0 = np.arange(-1,1.5, 0.5)
visibley0 = visiblex0*np.exp(visiblex0)
plt.plot(visiblex0, visibley0, "o", label = "Points of reference")

#Approximation with polinomy
plot_with_apprx(x0,y0, [-1, 1])

#Plot info
plt.title("f(x) = x•exp(x)")
plt.legend()
plt.show()


'''PLOT SECONDA FUNZIONE'''

#Calculated function plot
x1 = np.arange(-1, 1, 0.01)
y1 = 1 / (1+ 25*x1)
#Limit to the y axis because the function is an hyperbole
plt.ylim(-(10**12), 10**12)
plt.plot(x1, y1, color="red", label ="Function")

#Points of reference
visiblex1 = np.arange(-1,1.5, 0.5)
visibley1 =  1 / (1+ 25*visiblex1)
plt.plot(visiblex1, visibley1, "o", label = "Points of reference")

#Approximation with polinomy
plot_with_apprx(x1,y1, [-1, 1])

#Plot info
plt.title("f(x) = 1 / (1+25•x)")
plt.legend()
plt.show()


'''PLOT TERZA FUNZIONE'''

#Calculated function plot
x2 = np.arange(1,5,0.01)
y2 = np.sin(5*x2)+3*x2
plt.plot(x2, y2, color="red", label ="Function")

#Points of reference
visiblex2 = np.arange(1,5,0.5)
visibley2 =  np.sin(5*visiblex2)+3*visiblex2
plt.plot(visiblex2, visibley2, "o", label = "Points of reference")

#Approximation with polinomy
plot_with_apprx(x2,y2, [1, 5])

#Plot info
plt.title("f(x) = sin(5x)+3x")
plt.legend()
plt.show()




