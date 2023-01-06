import numpy as np
import scipy.linalg
import matplotlib.pyplot as plt
import scipy.linalg.decomp_lu as LUdec 
import time

def generate_tri(ndim):
    M = np.zeros((ndim,ndim))
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M

def SpectralRadius(A):
    eigenValues, eigenVectors = np.linalg.eig(A)
    return np.amax(eigenValues)

"""
A,b: dati del problema
x0: guess iniziale
maxit: numero massimo iteraioni
tol: tolleranza consentita
xTrue: soluzione esatta
"""
def Jacobi(A,b,x0,maxit,tol, xTrue):
    
  # dimensione del vettore x
  n=np.size(x0)     
  
  # siamo alla prima iterazione
  ite=0
  
  x = np.copy(x0)
  
  # la prima volta esageriamo con la norma dell'iterazione (aggiungendo 1) così che almeno una volta il while viene eseguito
  norma_it=1+tol
  
  # Errore relativo rispetto alla xTrue
  relErr=np.zeros((maxit, 1)) 
  
  # Distanza tra un iterato e il precedente 
  errIter=np.zeros((maxit, 1))
  
  # Errore relativo al passo 0 (dal vero valore di x)
  relErr[0]=np.linalg.norm(xTrue-x0)/np.linalg.norm(xTrue)
  
  # Estrai diagonale e crea la matrice D
  diag_A = np.diag(A)
  D = np.diagflat(diag_A)
  
  # Estrai matrici triangolari superiori e inferiori
  F = -np.triu(A,1)
  E = -np.tril(A,-1)
  J = np.linalg.inv(D)@(E+F)
  
  # Trova il raggio spettrale della matrice di iterazione per capire in anticipo se converge o meno
  spec = SpectralRadius(J)
  if(spec >= 1):
      print(spec, J)
      raise Exception("Result does not converge")
  
  # while continua finchè il numero di iterazioni è minore di quelle consentite e
  # la norma calcolata è più grande della tolleranza scelta 
  while (ite < maxit and norma_it > tol):
      
    # salva il valore precedente di x
    x_old=np.copy(x)
    
    # esegue il prodotto tra vettori eseguendo l'iesimo passo dell iterazione di Jacobi
    x = J@x_old+np.linalg.inv(D)@b
      
    # i esimo passo fatto  
    ite=ite+1
    
    # calcola la norma del risultato ottenuto rispetto al precedente
    norma_it = np.linalg.norm(x_old-x)/np.linalg.norm(x_old)
    
    # salva di quanto dista questo risultato rispetto al vero valore di x
    if(ite < maxit):
        relErr[ite] = np.linalg.norm(xTrue-x)/np.linalg.norm(xTrue)
    
    # salva in un vettore
    errIter[ite-1] = norma_it
    
  relErr=relErr[:ite]
  errIter=errIter[:ite]  
  return [x, ite, relErr, errIter, spec]


def Gauss(A,b,x0,maxit,tol, xTrue):
    
  # dimensione del vettore x
  n=np.size(x0)     
  
  # siamo alla prima iterazione
  ite=0
  
  x = np.copy(x0)
  
  # la prima volta esageriamo con la norma dell'iterazione (aggiungendo 1) così che almeno una volta il while viene eseguito
  norma_it=1+tol
  
  # Errore relativo rispetto alla xTrue
  relErr=np.zeros((maxit, 1)) 
  
  # Distanza tra un iterato e il precedente 
  errIter=np.zeros((maxit, 1))
  
  # Errore relativo al passo 0 (dal vero valore di x)
  relErr[0]=np.linalg.norm(xTrue-x0)/np.linalg.norm(xTrue)
  
  # Estrai diagonale e crea la matrice D
  diag_A = np.diag(A)
  D = np.diagflat(diag_A)
  
  # Estrai matrici triangolari superiori e inferiori
  F = -np.triu(A,1)
  E = -np.tril(A,-1)
  T = np.linalg.inv(D-E)
  
  # Trova il raggio spettrale della matrice di iterazione per capire in anticipo se converge o meno
  spec = SpectralRadius(T) 
  if(spec >= 1):
      print(spec, T)
      raise Exception("Result does not converge")

  # while continua finchè il numero di iterazioni è minore di quelle consentite e
  # la norma calcolata è più grande della tolleranza scelta 
  while (ite < maxit and norma_it > tol):
      
    # salva il valore precedente di x
    x_old=np.copy(x)
    
    # esegue il prodotto tra vettori eseguendo l'iesimo passo dell iterazione di Jacobi
    x = T@F@x_old+T@b

    # i esimo passo fatto  
    ite=ite+1
    
    # calcola la norma del risultato ottenuto rispetto al precedente
    norma_it = np.linalg.norm(x_old-x)/np.linalg.norm(x_old)
    
    # salva di quanto dista questo risultato rispetto al vero valore di x
    if(ite < maxit):
        relErr[ite] = np.linalg.norm(xTrue-x)/np.linalg.norm(xTrue)
    
    # salva in un vettore
    errIter[ite-1] = norma_it
    
  relErr=relErr[:ite]
  errIter=errIter[:ite]  
  return [x, ite, relErr, errIter, spec]


def LUSolve(A, xTrue):
    
    piv, L, R = scipy.linalg.lu(A)
    y = np.linalg.solve(L,piv@b)
    x2 = np.linalg.solve(R,y)
    relErr = np.linalg.norm(x2-xTrue)/np.linalg.norm(xTrue)
    
    return relErr

#metodi iterativi
maxit = 1000000
tol = 0.1

# Dimensioni su cui iterare
matrix_dims = np.arange(2,80,1)

#Tempo
time_lu = np.zeros(matrix_dims.size)
time_ch = np.zeros(matrix_dims.size)
time_jacobi = np.zeros(matrix_dims.size)
time_gauss = np.zeros(matrix_dims.size)

# Errore
err_lu = np.zeros(matrix_dims.size)
err_ch = np.zeros(matrix_dims.size)
err_jacobi = np.zeros(matrix_dims.size)
err_gauss = np.zeros(matrix_dims.size)

# Iterate matrix_dims times, create different matrixes each time
for i in range(0, matrix_dims.size):

    # Generate problem data
    A = generate_tri(matrix_dims[i])    
    xTrue = np.ones((matrix_dims[i],1))
    b = A@xTrue
    x0 = np.zeros((matrix_dims[i],1))
    x0[0] = 1
    
    # LU
    start = time.time()
    err_lu[i] = LUSolve(A, xTrue)
    end = time.time()
    time_lu[i] = end-start
    
    # Cholesky
    start = time.time()
    C = scipy.linalg.cholesky(A, lower = True)
    U = np.matrix.transpose(C)
    y = U@xTrue
    b2 = C@y
    x2 = np.linalg.solve(A,b2)
    end = time.time()
    err_ch[i] = np.linalg.norm(x2-xTrue)/np.linalg.norm(xTrue)
    time_ch[i] = end-start
    
    # Metodi iterativi
    start = time.time()
    xJacobi, kJacobi, relErrJacobi, errIterJacobi, specJacobi = Jacobi(A,b,x0,maxit,tol,xTrue) 
    end = time.time()
    err_jacobi[i] = relErrJacobi[-1]
    time_jacobi[i] = end-start
    start = time.time()
    xGauss, kGauss, relErrGauss, errIterGauss, specGauss = Gauss(A,b,x0,maxit,tol,xTrue) 
    end = time.time()
    err_gauss[i] = relErrGauss[-1]
    time_gauss[i] = end-start
    

zoom = True    

# Plot time
plt.title("Tempo impiegato da ogni algoritmo")
if zoom:
    plt.ylim(0,(max(time_gauss)))
plt.ylabel("Tempo (sec)")
plt.xlabel("Dimensione matrice")
plt.plot(matrix_dims,time_lu, color = "red", label = "LU") 
plt.plot(matrix_dims,time_ch, color = "blue", label = "Cholesky")
plt.plot(matrix_dims,time_jacobi, color = "green", label = "Jacobi")
plt.plot(matrix_dims,time_gauss, color = "gray", label = "Gauss")
plt.legend()
plt.show()

# Plot relative error
plt.title("Errore relativo finale")
plt.ylabel("Errore")
plt.xlabel("Dimensione matrice")
plt.plot(matrix_dims,err_lu, color = "red", label = "LU") 
plt.plot(matrix_dims,err_ch, color = "blue", label = "Cholesky")
plt.plot(matrix_dims,err_jacobi, color = "green", label = "Jacobi")
plt.plot(matrix_dims,err_gauss, color = "gray", label = "Gauss")
plt.legend()
plt.show()


