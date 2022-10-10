"""
Risoluzione di sistemi lineari con matrice simmetrica e definita positiva.
Scrivere uno script Python che:
    (a) crea un problema test di dimensione variabile n la cui soluzione esatta sia il vettore x di tutti
    elementi unitari e b il termine noto ottenuto moltiplicando la matrice A per la soluzione x.
    (b) calcola il numero di condizione (o una stima di esso)
    (c) risolve il sistema lineare Ax = b con la fattorizzazione di Cholesky..
Problemi test
    • matrice di Hilbert di dimensione n (con n variabile fra 2 e 15)
    • matrice tridiagonale simmetrica e definita positiva avente sulla diagonale elementi uguali a 9 e
    quelli sopra e sottodiagonali uguali a -4.
"""

import numpy as np
import scipy
import scipy.linalg
import scipy.linalg.decomp_lu as LUdec 
import matplotlib.pyplot as plt

#Size of the matrix (n*n)
n = 5

#Generates reqeuested tridiagonal matrix
def generate_tri(ndim):
    M = np.zeros((ndim,ndim))
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M

#Create tridiagonal matrix
A = generate_tri(n)

#Calculate condition number
cond = np.linalg.cond(A)

#Create x vector as requested
x = np.ones((n, 1))

#Find known term
b = A@x
    
#Cholesky decompose
C = scipy.linalg.cholesky(A, lower = True)

#Revert to obtain upper triangular matrix
U = np.matrix.transpose(C)

#Proceed as normal LU decomposition
y = U@x
b2 = C@y
x2 = np.linalg.solve(A,b2)