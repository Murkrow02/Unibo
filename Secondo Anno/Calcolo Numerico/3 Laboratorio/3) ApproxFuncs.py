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
n3 = np.array([1,5,7])

fnames = ["x•exp(x)", "1 / (1+25x)", "sin(5x) + 3x"]

#Distance between points in ranges
precision = 0.01

def print_relative_error(E, fnumber):
    print("Errore relativo per f(x) =", fnames[fnumber])
    for i in range(len(E)):
        print("n={}:".format(n[i]), E[i])
        
def print_approx_error(E, fnumber):
    print("Errore di approssimazione per f(x) =", fnames[fnumber])
    for i in range(len(E)):
        print("n={}:".format(n3[i]), E[i])
    

#Main func plot_with_apprx(xspace, yspace, [leftmargin, rightmargin])
def plot_with_apprx(x, y, margins, fnumber):    
    N = x.size # Numero dei dati
    A = []
    
    n2errors = []
    approxerrors = []
    
    #cycle for the n grade
    for k in range(0, len(n)):
    
        A.append(np.zeros((N, n[k]+1)))

        for i in range(0, N):
            row = []
            for j in range(0, n[k] + 1):   
                row.append(np.power(x[i], j))
            (A[k])[i] = row
                

        


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
        x_plot = np.arange(margins[0],margins[1],precision)
        # Codomains
        y_normali = p(alpha_normali, x_plot)
        #y_svd = p(alpha_svd, x_plot)
        
        #Calculate norm2 of the relative error
        if (margins[0] < 0 and margins[1] > 0):
            exactval = np.array([x[int(len(x) / 2)], y[int(len(y) / 2)]])
            approxval = np.array([x_plot[int(len(x) / 2)], y_normali[int(len(y) / 2)]])
            
            #ternary if operator prevents division by zero
            relerror = np.Inf if np.linalg.norm(exactval) == 0 else np.linalg.norm(approxval-exactval) / np.linalg.norm(exactval)
            
            #Add error to list of relative errors
            n2errors.append(relerror)
            
        
        if n[k] in n3:
            approxynodes = p(alpha_normali, x)
            approxerror = np.abs(approxynodes - y)
            
            #Add error to list of approximation errors
            approxerrors.append(approxerror)
            
        
        plt.plot(x_plot,y_normali, label = "Approximation n={}".format(n[k]))
    if (margins[0] < 0 and margins[1] > 0):    
        print_relative_error(n2errors, fnumber)
    print_approx_error(approxerrors, fnumber)
        
    plt.legend()
    plt.show()

#Points number where the polinomio is approssimato
Npoints = 7
#Points number of the domain of the original function
SpacePrecision = 41

#Check that the points numbers are odd to have 0 in the middle
Npoints = Npoints + 1 if Npoints % 2 == 0 else Npoints
SpacePrecision = SpacePrecision + 1 if SpacePrecision % 2 == 0 else SpacePrecision

'''PLOT PRIMA FUNZIONE'''

#lambda function
f0 = lambda x: x*np.exp(x)

#Margins
margin0 = [-1, 1]

#Npoints
x0 = np.linspace(margin0[0],margin0[1], Npoints)
y0 = f0(x0)

#Full space
x0space = np.linspace(margin0[0],margin0[1], SpacePrecision)
y0space = f0(x0space)

#Plot
plt.plot(x0, y0, "o", label = "Points of reference")
plt.plot(x0space, y0space, color="red", label ="Function")

#Plot info
plt.title("f(x) =" + fnames[0])

#Approximation with polinomy
plot_with_apprx(x0,y0, margin0, 0)


'''PLOT SECONDA FUNZIONE'''

#lambda function
f1 = lambda x: 1 / (1 + 25*x)

#Margins
margin1 = [-1, 1]

#Npoints
x1 = np.linspace(margin1[0],margin1[1], Npoints)
y1 = f1(x1)

#Full space
x1space = np.linspace(margin1[0],margin1[1],SpacePrecision)
y1space = f1(x1space)

#Plot
plt.plot(x1, y1, "o", label = "Points of reference")
plt.plot(x1space, y1space, color="red", label ="Function")

#Plot info
plt.title("f(x) =" + fnames[1])

#Approximation with polinomy
plot_with_apprx(x1,y1, margin1, 1)


'''PLOT TERZA FUNZIONE'''

#Lambda function
f2 = lambda x: np.sin(5*x)+3*x

#Margins
margin2 = [1, 5]

#Npoints
x2 = np.linspace(margin2[0],margin2[1], Npoints)
y2 = f2(x2)

#Full space
x2space = np.linspace(margin2[0],margin2[1],SpacePrecision)
y2space = f2(x2space)

#Plot
plt.plot(x2space, y2space, color="red", label ="Function")
plt.plot(x2, y2, "o", label = "Points of reference")

#Plot info
plt.title("f(x) =" + fnames[2])

#Approximation with polinomy
plot_with_apprx(x2,y2, margin2, 2)




