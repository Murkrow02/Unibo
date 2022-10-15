import numpy as np
import scipy.linalg
import matplotlib.pyplot as plt


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



def generate_tri(ndim):
    M = np.zeros((ndim,ndim))
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M


#creazione del problema test
n = 50
A = generate_tri(n)
#A = np.random.rand(n, n)
xTrue = np.ones((n,1))
b = A@xTrue

#print('\n A:\n',A)
#print('\n xTrue:\n',xTrue)
#print('\n b:\n',b)


#metodi iterativi
x0 = np.zeros((n,1))
x0[0] = 1
maxit = 1000000
tol = 0.00000001

(xJacobi, kJacobi, relErrJacobi, errIterJacobi, specJacobi) = Jacobi(A,b,x0,maxit,tol,xTrue) 
(xGauss, kGauss, relErrGauss, errIterGauss, specGauss) = Gauss(A,b,x0,maxit,tol,xTrue) 

#print('\nSoluzione calcolata da Jacobi:' )
#for i in range(n):
#    print('%0.2f' %xJacobi[i])
#    
#print('\nSoluzione calcolata da Gauss:' )
#for i in range(n):
#    print('%0.2f' %xGauss[i])

# CONFRONTI

# Confronto grafico degli errori di Errore Relativo

rangeJabobi = range (0, kJacobi)
rangeGauss = range (0, kGauss)

# Errori sul risultato finale ad ogni iterazione
plt.figure()
plt.title('Jacobi')
plt.plot(rangeJabobi, relErrJacobi, label='∂X', color='blue', linewidth=1)
plt.plot(rangeJabobi, errIterJacobi, label='Errore iterazione', color='red', linewidth=1 )
plt.xlabel('Iterations')
plt.ylabel('Relative Error')
plt.legend(loc='upper right')

plt.figure()
plt.title('Gauss')
plt.plot(rangeGauss, relErrGauss, label='∂X', color='blue', linewidth=1)
plt.plot(rangeGauss, errIterGauss, label='Errore iterazione', color='red', linewidth=1 )

plt.legend(loc='upper right')
plt.xlabel('Iterations')
plt.ylabel('Relative Error')


# Errore finale su x al variare della dimensione della matrice

# Dimensioni su cui iterare
matrix_dims = np.arange(2,80,1)

# Codomains
normalized_error_jacobi = np.zeros(matrix_dims.size)
normalized_error_gauss = np.zeros(matrix_dims.size)

iteration_count_jacobi = np.zeros(matrix_dims.size)
iteration_count_gauss = np.zeros(matrix_dims.size)

# Iterate matrix_dims times, create different matrixes each time
for i in range(0, matrix_dims.size):

    # Generate problem data
    A = generate_tri(matrix_dims[i])    
    xTrue = np.ones((matrix_dims[i],1))
    b = A@xTrue
    x0 = np.zeros((matrix_dims[i],1))
    x0[0] = 1
    
    # Calcola il risultato in base alla matrice di dimensione matrix_dims[i]
    (xJacobi, kJacobi, relErrJacobi, errIterJacobi, specJacobi) = Jacobi(A,b,x0,maxit,tol,xTrue) 
    (xGauss, kGauss, relErrGauss, errIterGauss, specGauss) = Gauss(A,b,x0,maxit,tol,xTrue) 
    
    # Fill codomain with errors normalized
    #print(xJacobi[0]==xJacobi[1])
    #print(xJacobi)
    normalized_error_jacobi[i] = (np.linalg.norm(xJacobi-xTrue))/(np.linalg.norm(xTrue))
    normalized_error_gauss[i] = (np.linalg.norm(xGauss-xTrue))/(np.linalg.norm(xTrue))
    
    iteration_count_jacobi[i] = kJacobi
    iteration_count_gauss[i] = kGauss
    

# Plot errors on graph
plt.figure()
plt.plot(matrix_dims,normalized_error_jacobi, color = "red", label = "Error on x Jacobi") 
plt.plot(matrix_dims,normalized_error_gauss, color = "blue", label = "Error on x Gauss")
plt.legend()

# Plot iteration number
plt.figure()
plt.plot(matrix_dims,iteration_count_jacobi, color = "red", label = "Iterations Jacobi") 
plt.plot(matrix_dims,iteration_count_gauss, color = "blue", label = "Iterations Gauss")
plt.legend()


plt.show()



