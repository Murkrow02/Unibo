import numpy as np
import scipy.linalg
import matplotlib.pyplot as plt

"""
A,b: dati del problema
x0: guess iniziale
maxit: numero massimo iteraioni
tol: tolleranza consentita
xTrue: soluzione esatta
"""
def Jacobi(A,b,x0,maxit,tol, xTrue):
    
  #
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
  
  # while continua finchè il numero di iterazioni è minore di quelle consentite e
  # la norma calcolata è più grande della tolleranza scelta 
  while (ite < maxit and norma_it > tol):
      
    # salva il valore precedente di x
    x_old=np.copy(x)
    
    # esegue il prodotto tra vettori eseguendo l'iesimo passo dell iterazione di Jacobi
    for i in range(0,n):
      #x[i]=(b[i]-sum([A[i,j]*x_old[j] for j in range(0,i)])-sum([A[i, j]*x_old[j] for j in range(i+1,n)]))/A[i,i]
      x[i]=(b[i]-np.dot(A[i,0:i],x_old[0:i])-np.dot(A[i,i+1:n],x_old[i+1:n]))/A[i,i]
      
    # i esimo passo fatto  
    ite=ite+1
    
    # calcola la norma del risultato ottenuto rispetto al precedente
    norma_it = np.linalg.norm(x_old-x)/np.linalg.norm(x_old)
    
    # salva di quanto dista questo risultato rispetto al vero valore di x
    relErr[ite] = np.linalg.norm(xTrue-x)/np.linalg.norm(xTrue)
    
    # salva in un vettore
    errIter[ite-1] = norma_it
    
  relErr=relErr[:ite]
  errIter=errIter[:ite]  
  return [x, ite, relErr, errIter]


def generate_tri(ndim):
    M = np.zeros((ndim,ndim))
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M


#creazione del problema test
n = 10
A = generate_tri(n)
xTrue = np.ones((n,1))
b = A@xTrue

print('\n A:\n',A)
print('\n xTrue:\n',xTrue)
print('\n b:\n',b)


#metodi iterativi
x0 = np.zeros((n,1))
maxit = 90000
tol = 0.00000000001

(xJacobi, kJacobi, relErrJacobi, errIterJacobi) = Jacobi(A,b,x0,maxit,tol,xTrue) 

print('\nSoluzione calcolata da Jacobi:' )
for i in range(n):
    print('%0.2f' %xJacobi[i])

# CONFRONTI

# Confronto grafico degli errori di Errore Relativo

rangeJabobi = range (0, kJacobi)

plt.figure()
plt.plot(rangeJabobi, relErrJacobi, label='∂X', color='blue', linewidth=1, marker='o'  )
plt.plot(rangeJabobi, errIterJacobi, label='Errore iterazione', color='red', linewidth=1, marker='o'  )
plt.legend(loc='upper right')
plt.xlabel('iterations')
plt.ylabel('Relative Error')
plt.title('Comparison of the different algorithms')
plt.show()



