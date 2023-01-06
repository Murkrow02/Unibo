import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg
from skimage import data


A = data.camera()
#A = data.coins()

# Decompose matrix with SVD
U, S, Vh = np.linalg.svd(A)


def approximate_image(p):
    # Approximation matrix
    A_p = np.zeros(A.shape)
    for i in range(p):
        A_p += np.outer(U[:,i],(Vh[i,:]))*S[i]
    return A_p

def calc_relerr(A_p):
    return np.linalg.norm(A-A_p)/np.linalg.norm(A)

def calc_compression_ratio(p):
    return (1/p)*(min(A.shape[0], A.shape[1]))-1;

# Maximum approximation step
maxP = S.size #S è un vettore e non una matrice, quando finisce S possiamo fermarci
steps = 10 #Ci vuole troppo a calcolare ogni possibile immagine 
domain = np.arange(1, maxP+1,steps)


# Salva risultati errore e rateo compressione
error_codomain = []
compression_ratio_codomain = []

# Varia P e ottieni immagini dalla piu approssimata alla meno approssimata
for i in domain:
    
    #Plot image
    A_p = approximate_image(i)
    plt.title("P={}".format(i))
    plt.imshow(A_p, cmap='gray')
    plt.show()
        
    # Calculate relative error of approximation
    error_codomain.append(calc_relerr(A_p))
        
    # Calculate compression ratio
    compression_ratio_codomain.append(calc_compression_ratio(i))
        
        

# Plotta grafico dell'errore relativo e della compressione al variare del numero p (diadi utilizzate)
plt.figure(figsize=(20,10))
plt.subplot(1,2,1)
plt.title("Errore relativo")
plt.xlabel("Diadi utilizzate")
plt.ylabel("Errore relativo")
plt.plot(domain,error_codomain, color = "red") 
plt.legend()
plt.subplot(1,2,2)
plt.title("Fattore di compressione")
plt.xlabel("Diadi utilizzate")
plt.ylabel("Fattore di compressione")
plt.plot(domain,compression_ratio_codomain, color = "blue")
plt.legend()
plt.show()

