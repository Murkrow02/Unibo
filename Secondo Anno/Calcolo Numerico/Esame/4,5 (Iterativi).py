"""
Risoluzione di sistemi lineari con metodo iterativo. Dato un problema test di dimensione
variabile la cui soluzione esatta sia il vettore x di tutti elementi unitari e b il termine noto
ottenuto moltiplicando la matrice A per la soluzione x discutere:
    • la soluzione del sistema lineare Ax=b con i metodi iterativi di Jacobi e gauss Sidel al
    variare del punto iniziale e della tolleranza per il criterio di arresto.
    • Il numero di iterazioni effettuate al variare della dimensione n del sistema (grafico
    del numero di iterazioni al variare di n).
Testare sulla matrice tridiagonale simmetrica e definita positiva positiva avente sulla diagonale
elementi uguali a 9 e quelli sopra e sottodiagonali uguali a -4 (variare n).
"""

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


"""
Discutere la soluzione del sistema lineare Ax=b con i metodi iterativi di Jacobi e gauss Sidel al
variare del punto iniziale e della tolleranza per il criterio di arresto.
"""

#Configurazione problema
matrixSize = 10
maxit = 1000000
tol = 0.00000001
A = generate_tri(matrixSize)
xTrue = np.ones((matrixSize,1))
b = A@xTrue

#Possibili valori del punto iniziale x0
maxValues = 10
x0Range = np.arange(0,maxValues)

#Risultati del test
iterationsGauss = np.arange(0,maxValues)
iterationsJacobi = np.arange(0,maxValues)


for i in x0Range:
    
    #Crea vettore x0 diverso ogni volta
    x0 = np.full((matrixSize,1), i)
    xJacobi, kJacobi, relErrJacobi, errIterJacobi, specJacobi = Jacobi(A,b,x0,maxit,tol,xTrue) 
    xGauss, kGauss, relErrGauss, errIterGauss, specGauss = Gauss(A,b,x0,maxit,tol,xTrue) 
    iterationsJacobi[i] = kJacobi
    iterationsGauss[i] = kGauss
    
    #Create new line on plot showing distance at each iteration
    plt.plot(np.arange(0,relErrJacobi.size),relErrJacobi)
    
#Plotta errore ad ogni iterazione al variare del punto iniziale x0
plt.ylabel("Errore relativo")
plt.xlabel("Iterazioni")
plt.show()
    
#Plotta numero di iterazioni al variare del punto iniziale x0
labels = x0Range
x = np.arange(len(labels))
width = 0.35
fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, iterationsJacobi, width, label='Jacobi')
rects2 = ax.bar(x + width/2, iterationsGauss, width, label='Gauss')
ax.set_ylabel('Iterazioni')
ax.set_xlabel('Vettore iniziale')
ax.set_xticks(x, labels)
ax.legend()
ax.bar_label(rects1, padding=3)
ax.bar_label(rects2, padding=3)
fig.tight_layout()
plt.show()


"""
Discutere la soluzione del sistema lineare Ax=b con i metodi iterativi di Jacobi e gauss Sidel al
variare della dimensione della matrice
"""

#Configurazione problema
maxit = 1000000
tol = 0.00000001

#Possibili valori del punto iniziale x0
maxDim = 12
matrixNRange = np.arange(2,maxDim)

#Risultati del test
iterationsGauss = np.arange(0,maxDim-2)
iterationsJacobi = np.arange(0,maxDim-2)

for i in matrixNRange:
    
    #Create variable size matrix
    A = generate_tri(i)
    xTrue = np.ones((i,1))
    b = A@xTrue
    x0 = np.zeros((i,1))
    
    xJacobi, kJacobi, relErrJacobi, errIterJacobi, specJacobi = Jacobi(A,b,x0,maxit,tol,xTrue) 
    xGauss, kGauss, relErrGauss, errIterGauss, specGauss = Gauss(A,b,x0,maxit,tol,xTrue) 
    iterationsJacobi[i-2] = kJacobi
    iterationsGauss[i-2] = kGauss
    
    
#Plotta numero di iterazioni al variare della soluzione iniziale
x = np.arange(len(labels))
width = 0.35
fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, iterationsJacobi, width, label='Jacobi')
rects2 = ax.bar(x + width/2, iterationsGauss, width, label='Gauss')
ax.set_ylabel('Iterazioni')
ax.set_xlabel('Dimensione matrice')
ax.set_xticks(x, matrixNRange)
ax.legend()
ax.bar_label(rects1, padding=3)
ax.bar_label(rects2, padding=3)
fig.tight_layout()
plt.show()


