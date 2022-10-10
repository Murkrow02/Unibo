"""
Scrivere uno script Python che:
    (a) crea un problema test di dimensione variabile n la cui soluzione esatta sia il vettore x di tutti
    elementi unitari e b il termine noto ottenuto moltiplicando la matrice A per la soluzione x.
    (b) calcola il numero di condizione (o una stima di esso)
    (c) risolve il sistema lineare Ax = b con la fattorizzazione LU con pivoting.
Problemi test
    Una matrice di numeri casuali A generata con la funzione randn di Matlab, (n variabile fra 10 e 1000)
"""

import numpy as np
import scipy
import scipy.linalg
import scipy.linalg.decomp_lu as LUdec 

#Size of the matrix (n*n)
n = 3

#Generate random elements in matrix
A = np.random.randint(10,1000,(n,n))

#A vector of all ones as x
x = np.ones((n, 1))

#The known term, obtained by the matrix multiplication of x and A matrix
b = A@x

#Calculate condition number
cond = np.linalg.cond(A)

#LU factorization to solve linear sysyem
piv, L, U = LUdec.lu(A)

#First step of LU solving (find y)
y = U@x

#Second step of LU solving (find b)
b2 = L@y

#Final step, x is found
x2 = np.linalg.solve(U,y)


"""
Per ogni problema test:
• Disegna il grafico del numero di condizione in funzione della dimensione del sistema
• Disegna il grafico dell’errore in norma 2 in funzione della dimensione del sistema
"""



