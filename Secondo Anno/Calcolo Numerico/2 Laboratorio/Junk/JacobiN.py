#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 13 13:12:23 2022

@author: valeriopiodenicola
"""

""" ** METODI ITERATIVI ** """

import numpy as np
import scipy.linalg
import matplotlib.pyplot as plt


def Jacobi(A,b,x0,maxit,tol, xTrue):
  n=np.size(x0)     
  ite=0
  x = np.copy(x0)
  norma_it=1+tol
  relErr=np.zeros((maxit, 1))
  errIter=np.zeros((maxit, 1))
  relErr[0]=np.linalg.norm(xTrue-x0)/np.linalg.norm(xTrue)
  while (ite<maxit and norma_it>tol):
    x_old=np.copy(x)
    for i in range(0,n):
      #x[i]=(b[i]-sum([A[i,j]*x_old[j] for j in range(0,i)])-sum([A[i, j]*x_old[j] for j in range(i+1,n)]))/A[i,i]
      x[i]=(b[i]-np.dot(A[i,0:i],x_old[0:i])-np.dot(A[i,i+1:n],x_old[i+1:n]))/A[i,i]
    ite=ite+1
    norma_it = np.linalg.norm(x_old-x)/np.linalg.norm(x_old)
    relErr[ite] = np.linalg.norm(xTrue-x)/np.linalg.norm(xTrue)
    errIter[ite-1] = norma_it
  relErr=relErr[:ite]
  errIter=errIter[:ite]  
  return [x, ite, relErr, errIter]



"""
def GaussSeidel(A,b,x0,maxit,tol, xTrue):
    
  ...
  ...
  
  return [x, ite, relErr, errIter]
"""

""" **  matrice tridiagonale nxn ** """
# help(np.diag)
# help (np.eye)
# n=5
# c = np.eye(n)
# s = np.diag(np.ones(n-1)*2,k=1)
# i = ...
# print('\n c:\n',c)
# print('\n s:\n',s)
# print('\n i:\n',i)
# print('\n c+i:\n',c+i+s)


#creazione del problema test

def generate_tri(ndim):
    M = np.zeros((ndim,ndim))
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M

#comportamento al variare di N

dim = np.arange(5,101,1)

ErrRelF_J = np.zeros((np.size(dim), 1))
#ErrRelF_GS = ...

ite_J = np.zeros((np.size(dim), 1))
#ite_GS = ...

i = 0


maxit = 1000
tol = 0.0000001

for k in dim:
    
    #creazione del problema test
    A = generate_tri(k)    
    xTrue = np.ones((k,1))
    b = A@xTrue
    x0 = np.zeros((k,1))
    x0[0] = 1
    
    #metodi iterativi
    (xJacobi, kJacobi, relErrJacobi, errIterJacobi) = Jacobi(A, b, x0, maxit, tol, xTrue)
    
    #errore relativo finale
    ErrRelF_J[i] = relErrJacobi[-1]
    #ErrRelF_GS[i] = ...
    
    #iterazioni
    ite_J[i] = kJacobi
    #ite_GS[i]= ...

    i = i+1
    

# errore relativo finale dei metodi al variare della dimensione N
plt.figure()
plt.plot(dim, ErrRelF_J, color = "red", label = "Err")
#plt.plot(count,...
plt.legend()
plt.xlabel("Dimensione")
plt.ylabel("Errore relativo")
plt.title("Errore relativo al variare della dimensione")
plt.show()

#numero di iterazioni di entrambi i metodi al variare di N
plt.figure()
...



