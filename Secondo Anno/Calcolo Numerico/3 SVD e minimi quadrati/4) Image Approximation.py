import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg
from skimage import data


A = data.camera()
#A = data.coins()


print(type(A))
print(A.shape)

# Decompose matrix with SVD
U, S, Vh = np.linalg.svd(A)

# Maximum approximation step
maxP = S.size;

# At which step to stop the approx
target_p = 30


if(target_p > maxP):
    raise Exception("Too big")


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
    
    
A_p = approximate_image(target_p)
plt.imshow(A_p, cmap='gray')
plt.show()


err_rel = calc_relerr(A_p)
c = calc_compression_ratio(target_p)

print('\n')
print('L\'errore relativo della ricostruzione di A è', err_rel)
print('Il fattore di compressione è c=', c)


# Show two images in grid
plt.figure(figsize=(20, 10))

fig1 = plt.subplot(1, 2, 1)
fig1.imshow(A, cmap='gray')
plt.title('True image')

fig2 = plt.subplot(1, 2, 2)
fig2.imshow(A_p, cmap='gray')
plt.title('Reconstructed image with p =' + str(target_p))

plt.show()


# al variare di p
domain = np.arange(1, maxP+1)
error_codomain = []
compression_ratio_codomain = []

for i in domain:
        
    # Compress at i step
    A_p = approximate_image(i)
    
    # Calculate relative error of approximation
    error_codomain.append(calc_relerr(A_p))
    
    # Calculate compression ratio
    compression_ratio_codomain.append(calc_compression_ratio(i))
    
    
# Plot graph
plt.figure(figsize=(20,10))

plt.subplot(1,2,1)
plt.plot(domain,error_codomain, color = "red", label = "Relative error") 
plt.legend()

plt.subplot(1,2,2)
plt.plot(domain,compression_ratio_codomain, color = "blue", label = "Compression ratio")
plt.legend()
plt.show()

    
    


