import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg


n = 2 # Grado del polinomio approssimante

x = np.array([1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3])
y = np.array([1.18, 1.26, 1.23, 1.37, 1.37, 1.45, 1.42, 1.46, 1.53, 1.59, 1.5])

print('Shape of x:', x.shape)
print('Shape of y:', y.shape, "\n")

N = x.size # Numero dei dati

A = np.zeros((N, n+1))

for i in range(0, N):
    row = []
    for j in range(0, n + 1):
        row.append(np.power(x[i], j))
    A[i] = row

print("A = \n", A)



''' Risoluzione tramite equazioni normali'''

# calcoliamo la matrice del sistema e il termine noto a parte
ATA = np.transpose(A)@A 
ATy = np.transpose(A)@y


L = scipy.linalg.cholesky(ATA, lower = True)
alpha1 = scipy.linalg.solve(L, ATy)

alpha_normali = scipy.linalg.solve(L.T, alpha1)

print("alpha_normali = \n", alpha_normali)

xbase = np.arange(1, 3, 0.1)
ybase_lsq = np.zeros((xbase.size,))

for i in range(0, alpha_normali.size):
    ybase_lsq += alpha_normali[i]*np.power(xbase, i)

#plt.scatter(x, y)
#plt.plot(xbase, ybase_lsq, color= "blue", label = "LSQ Regression")
#plt.legend()

'''Risoluzione tramite SVD'''

#help(scipy.linalg.svd)

U, s, Vt = scipy.linalg.svd(A)

print('Shape of U:', U.shape)
print('Shape of s:', s.shape)
print('Shape of V:', Vt.shape)

alpha_svd = np.zeros(s.shape)

for i in range(n+1):
    ui=U[i,:]
    print(ui)
    vi = Vt[i,:]
    print(vi)
    alpha_svd = alpha_svd + (np.dot(ui,y)*vi) / s[i]
    
ybase_svd = np.zeros((xbase.size,))

for i in range(0, alpha_svd.size):
    ybase_svd += alpha_svd[i]*np.power(xbase, i)
    
#plt.plot(xbase, ybase_svd, color= "red", label = "SVD Regression")
#plt.legend()



'''Verifica e confronto delle soluzioni'''

# Funzione per valutare il polinomio p, in un punto x, dati i coefficienti alpha
def p(alpha, x):
    N=x.size
    print(alpha.size)
    A = np.zeros((N, alpha.size))
    
    for i in range(0, N):
        row = []
        for j in range(0, n + 1):
            row.append(np.power(x[i], j))
        A[i] = row
        
    return A@alpha

'''CONFRONTO GRAFICO '''
x_plot = np.linspace(1,3,100)
y_normali = p(alpha_normali, x_plot)
y_svd = p(alpha_svd, x_plot)

plt.figure(figsize=(20, 10))

plt.subplot(1, 2, 1)
plt.plot(x,y,"o")
plt.plot(x_plot,y_normali)
plt.title('Approssimazione tramite Eq. Normali')

plt.subplot(1, 2, 2)
plt.plot(x,y,"o")
plt.plot(x_plot,y_svd)
plt.title('Approssimazione tramite SVD')

plt.show()

'''CONFRONTO ERRORI SUI DATI 
y1 = p(...)
y2 = p(...)

err1 = np.linalg.norm (y-y1, 2) 
err2 = np.linalg.norm (y-y2, 2) 
print ('Errore di approssimazione con Eq. Normali: ', err1)
print ('Errore di approssimazione con SVD: ', err2)





x_plot = ...

y_normali = ...
y_svd = ...


plt.figure(figsize=(20, 10))

plt.subplot(1, 2, 1)
...
plt.title('Approssimazione tramite Eq. Normali')

plt.subplot(1, 2, 2)
...
plt.title('Approssimazione tramite SVD')

plt.show()
'''