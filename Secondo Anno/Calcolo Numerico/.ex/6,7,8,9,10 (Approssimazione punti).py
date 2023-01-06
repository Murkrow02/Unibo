import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg
import pandas as pd

#Distance between points in ranges
precision = 0.01

# Funzione per valutare il polinomio p, in un punto x, dati i coefficienti alpha (DELLA PROF)
def p(alpha, x, n):
    m=x.size
    A = np.zeros((m, alpha.size))
    
    for i in range(0, m):
        row = []
        for j in range(0, n + 1):
            row.append(np.power(x[i], j))
        A[i] = row
        
    return A@alpha
 
def approx(x,y,n, title, nograph=False):
    
    
    ''' Risoluzione tramite equazioni normali'''
    
    # Numero di dati
    m = x.size 

    # Creazione della matrice del problema
    A = np.zeros((m, n+1))

    for i in range(0, m):
        row = []
        for j in range(0, n + 1):
            row.append(np.power(x[i], j))
        A[i] = row

   

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
        
 
    # Domain
    x_plot = np.linspace(1, max(x),100)

    # Codomains
    y_normali = p(alpha_normali, x_plot,n)
    y_svd = p(alpha_svd, x_plot,n)
   
    
    '''CONFRONTO GRAFICO DEL POLINOMIO'''    

    if nograph == False:
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
    
        plt.suptitle(title)
        plt.show()
    
    '''CONFRONTO GRAFICO DEGLI ERRORI'''
    eq_norm_error = abs(p(alpha_normali, x, n) - y) # distanza dei punti calcolati a quelli effettivi
    svd_error = abs(p(alpha_svd, x, n) - y) 

    if nograph == False:
        # Istogramma degli errori
        plt.figure(figsize=(20, 10))
        plt.subplot(1, 2, 1)
        plt.bar(x,eq_norm_error,0.1, tick_label=x)
        plt.title('Errori tramite Eq. Normali \n Errore norma 2: {}'.format(np.linalg.norm(eq_norm_error)))
    
        # Grafico con SVD
        plt.subplot(1, 2, 2)
        plt.bar(x,svd_error,0.1, tick_label=x)
        plt.title('Errori tramite SVD \n Errore norma 2: {}'.format(np.linalg.norm(svd_error)))
    
        plt.suptitle(title)
        plt.show() 
    
    return alpha_normali, alpha_svd, eq_norm_error, svd_error
    
    

# Punti da approssimare
x = np.array([1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3])
y = np.array([1.18, 1.26, 1.23, 1.37, 1.37, 1.45, 1.42, 1.46, 1.53, 1.59, 1.5])

#Lettura dataset da file csv
dataset = pd.read_csv('HeightVsWeight.csv')  

#Lettura delle colonne convertire in serie
ages = dataset.iloc[:,0]
weights = dataset.iloc[:,1]


#Approssima punti e dataset
for i in range(1, 7):
    
    #Set di punti
    approx(x,y,i, "Set di punti grado {}".format(i))
    
    #Dataset
    approx(ages,weights,i, "Dataset grado {}".format(i))
    
    
    
    
    
#Approssimazione di funzioni
fnames = ["x•exp(x)", "1 / (1+25x)", "sin(5x) + 3x"]
Npoints = 10
SpacePrecision = 41

fspacesX = np.zeros((3,SpacePrecision))
fspacesY = np.zeros((3,SpacePrecision))
fpointsX = np.zeros((3,Npoints))
fpointsY = np.zeros((3,Npoints))

fmargins = np.zeros((3,2))

#f0
f0 = lambda x: x*np.exp(x)
fmargins[0] = [-1, 1]

#Punti
fpointsX[0] = np.linspace(fmargins[0][0],fmargins[0][1], Npoints)
fpointsY[0] = f0(fpointsX[0])

#Funzione completa
fspacesX[0] = np.linspace(fmargins[0][0],fmargins[0][1], SpacePrecision)
fspacesY[0] = f0(fspacesX[0])


#f1
f1 = lambda x: 1 / (1 + 25*x)
fmargins[1] = [-1, 1]

#Punti
fpointsX[1] = np.linspace(fmargins[1][0],fmargins[1][1], Npoints)
fpointsY[1] = f1(fpointsX[1])

#Funzione completa
fspacesX[1] = np.linspace(fmargins[1][0],fmargins[1][1], SpacePrecision)
fspacesY[1] = f1(fspacesX[1])

#f2
f2 = lambda x: np.sin(5*x)+3*x
fmargins[2] = [1, 5]

#Punti
fpointsX[2] = np.linspace(fmargins[2][0],fmargins[2][1], Npoints)
fpointsY[2] = f2(fpointsX[2])

#Funzione completa
fspacesX[2] = np.linspace(fmargins[2][0],fmargins[2][1], SpacePrecision)
fspacesY[2] = f2(fspacesX[2])


def approxFuncs(method):
    
    print(method)


    #Cicla per ogni funzione
    for i in range(0,3):
        
        #Plot punti
        plt.plot(fpointsX[i], fpointsY[i], "o", label = "Points of reference")
        
        #Plot funzione originale
        plt.plot(fspacesX[i], fspacesY[i], color="red", label ="Function")
        
        #Cicla per ogni dimensione
        for j in range(1, 8, 2):
            
            
            #Calcola codominio con SVD e equazioni normali
            alpha_norm, alpha_svd, err_norm, err_svd = approx(fpointsX[i], fpointsY[i],j, fnames[i], True)
            
            # Domain
            x_plot = np.arange(fmargins[i][0],fmargins[i][1],precision)
            
            
            #Plot approssimazione
            if method == "SVD":
                y_svd = p(alpha_svd, x_plot,j)
                plt.plot(x_plot, y_svd, label="Grado polinomio {}".format(j))
                print("Errore norma 2 per approssimazione grado {} della funzione {}: {}".format(j, fnames[i],np.linalg.norm(err_norm) ))
            if method == "Equazioni normali":
                y_normali = p(alpha_norm, x_plot,j)
                plt.plot(x_plot, y_normali, label="Grado polinomio {}".format(j))
                print("Errore norma 2 per approssimazione grado {} della funzione {}: {}".format(j, fnames[i],np.linalg.norm(err_svd) ))

            
        
        #Plot info
        plt.legend()
        plt.title("f(x) = {}\n {}".format(fnames[i],method))
        plt.show()
        
        
approxFuncs("SVD")
approxFuncs("Equazioni normali")





























































