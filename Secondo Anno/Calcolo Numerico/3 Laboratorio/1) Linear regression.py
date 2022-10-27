import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg

n = 10# Grado del polinomio approssimante

# Punti da approssimare
x = np.array([1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3])
y = np.array([1.18, 1.26, 1.23, 1.37, 1.37, 1.45, 1.42, 1.46, 1.53, 1.59, 1.5])

# Numero di dati
m = x.size 

# Creazione della matrice del problema
A = np.zeros((m, n+1))

for i in range(0, m):
    row = []
    for j in range(0, n + 1):
        row.append(np.power(x[i], j))
    A[i] = row

''' Risoluzione tramite equazioni normali'''

# calcoliamo la matrice del sistema e il termine noto a parte
ATA = np.transpose(A)@A 
ATy = np.transpose(A)@y

# Risolvi con cholesky 
#L = scipy.linalg.cholesky(ATA, lower = True)
#alpha1 = scipy.linalg.solve(L, ATy)
#alpha_normali = scipy.linalg.solve(L.T, alpha1)

# Per ora risoluzione canonica in quanto Cholesky crasha per matrici troppo grandi
alpha_normali = scipy.linalg.solve(ATA, ATy)

'''Risoluzione tramite SVD'''

# Scomponi matrice con SVD
U, s, Vt = scipy.linalg.svd(A)

# Crea il vettore per i risultati
alpha_svd = np.zeros(s.shape)

# Itera tramite la risoluzione del problema con la moltiplicazione scomposta SVD
for i in range(n+1):
    ui=U[:,i] # Prendi iesima colonna di U
    vi = Vt[i,:] # Prendi iesima riga di v
    alpha_svd = alpha_svd + (np.dot(ui,y)*vi) / s[i]


'''CONFRONTO GRAFICO DEL POLINOMIO'''

# Funzione per valutare il polinomio p, in un punto x, dati i coefficienti alpha (DELLA PROF)
def p(alpha, x):
    m=x.size
    A = np.zeros((m, alpha.size))
    
    for i in range(0, m):
        row = []
        for j in range(0, n + 1):
            row.append(np.power(x[i], j))
        A[i] = row
        
    return A@alpha

# Domain
x_plot = np.linspace(1,3,100)

# Codomains
y_normali = p(alpha_normali, x_plot)
y_svd = p(alpha_svd, x_plot)

# Grafico con equazioni normali
plt.figure(figsize=(20, 10))
plt.subplot(1, 2, 1)
plt.plot(x,y,"o")
plt.plot(x_plot,y_normali)
plt.title('Approssimazione tramite Eq. Normali')

# Grafico con SVD
plt.subplot(1, 2, 2)
plt.plot(x,y,"o")
plt.plot(x_plot,y_svd)
plt.title('Approssimazione tramite SVD')

plt.show()

'''CONFRONTO GRAFICO DEGLI ERRORI'''
eq_norm_error = abs(p(alpha_normali, x) - y) # distanza del puntop calcolato dal polinomio dal punto effettivo
svd_error = abs(p(alpha_svd, x) - y) 

# Istogramma degli errori
plt.figure(figsize=(20, 10))
plt.subplot(1, 2, 1)
plt.bar(x,eq_norm_error,0.1, tick_label=x)
plt.title('Errori tramite Eq. Normali')

# Grafico con SVD
plt.subplot(1, 2, 2)
plt.bar(x,svd_error,0.1, tick_label=x)
plt.title('Errori tramite SVD')

plt.show() 


































































