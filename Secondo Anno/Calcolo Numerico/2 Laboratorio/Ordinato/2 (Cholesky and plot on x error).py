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

#Proceed as normal like LU decomposition
y = U@x
b2 = C@y
x2 = np.linalg.solve(A,b2)


"""
Per ogni problema test:
• Disegna il grafico del numero di condizione in funzione della dimensione del sistema
• Disegna il grafico dell’errore in norma 2 in funzione della dimensione del sistema
"""


# A possible dimensions
matrix_dims = np.arange(2,16,1)


# Codomain of function A, shows on y axis the condition number of matrix A
condition_number = np.zeros(matrix_dims.size)

# Codomain of function B, shows on y axis the condition number of matrix A
normalized_error = np.zeros(matrix_dims.size)

# Iterate matrix_dims times, create different matrixes each time
for i in range(0, matrix_dims.size):

    # Choose between hilbert or tridiagonal matrix
    #A = generate_tri(matrix_dims[i])    
    A = scipy.linalg.hilbert(matrix_dims[i])
    
    # Calculate i-exim condition number
    condition_number[i] = np.linalg.cond(A)
    
    # Create x vector
    x = np.ones((matrix_dims[i], 1))
    
    # Find b with matrix multiplication
    b = A@x
    
    """
    La matrice di Hilbert nonostante sia simmetrica non è sempre definita
    positiva (n minore di 14) (non tutti gli autovalori sono strettamente > 0)
    quindi non si puo sempre scomporre con Cholesky
    """
    #C = scipy.linalg.cholesky(A, lower = True)
    #U = np.matrix.transpose(C)
    piv, C, U = LUdec.lu(A)

    # Solve system
    y = U@x
    b2 = C@y
    x2 = np.linalg.solve(A,b2)
    
    # Find error on x by subtracting the known x (we created the vector) with the one found by LU
    normalized_error[i] = (np.linalg.norm(x2-x))/(np.linalg.norm(x))
    
    
# Plot graph
plt.plot(matrix_dims,condition_number, color = "red", label = "Codition number") 
plt.plot(matrix_dims,normalized_error, color = "blue", label = "Error on x")
plt.legend()
plt.show()

