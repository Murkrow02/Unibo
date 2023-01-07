import numpy as np
import matplotlib.pyplot as plt
from skimage import data, metrics
from scipy import signal
from numpy import fft
from scipy.optimize import minimize
np.random.seed(0)



def next_step(x,grad,f): # backtracking procedure for the choice of the steplength

    #We start with alpha = 1 
    alpha=1.1
    
    #Dimezziamo alpha ad ogni iteraione
    rho = 0.5
    
    #
    c1 = 0.25
    
    #Direzione di discesa  
    p=-grad
    
    #Iterazioni
    j=0
    
    #Iterazioni massime
    jmax= 10
    
    while  (f(x + alpha*p) > (f(x) + c1*alpha*grad.T@p) and j <= jmax):
        alpha = rho*alpha
        j = j+1
        #print(alpha)
        
    #Troppe iterazioni
    if (j >= jmax):
        return -1
    else:
        return alpha
        

#x0 appartenente a R2
def minimize(f, df, x0, x_true, MAXITERATION, ABSOLUTE_STOP, fixed_step = -1): 
  
    
    #Iteration index
    k=0
    
    #Last x found (Result)
    x_last_mat = np.copy(x0)
    x_last = np.reshape(x_last_mat, x0.shape[0] * x0.shape[1])
    
    #Salva PSNR e MSE
    PSNR_ite = np.zeros((MAXITERATION))
    MSE_ite  = np.zeros((MAXITERATION))
    

    #Condizioni di arresto
    while (np.linalg.norm(df(x_last))>ABSOLUTE_STOP and k < MAXITERATION -1 ):
        
        #Increment index
        k = k+1
        
        #Direzione di ricerca
        p = -df(x_last)
                
        # backtracking step
        step = next_step(x_last, df(x_last),f) if fixed_step == -1 else fixed_step
        
        # Algoritmo di backtracking non ha trovato uno step adeguato        
        if(step==-1):
            raise Exception("Non converge")
        
        #Calculate new x
        x_last = x_last + step*p
        
        #Salva psnr e mse
        x_last_matrice = np.reshape(x_last, x0.shape)
        PSNR_ite[k] = metrics.peak_signal_noise_ratio(x_true, x_last_matrice)
        MSE_ite [k] = metrics.mean_squared_error(x_true, x_last_matrice)

    return (x_last,k, PSNR_ite[0:k+1], MSE_ite[0:k+1])


# Crea un kernel Gaussiano di dimensione kernlen e deviazione standard sigma
def gaussian_kernel(kernlen, sigma):
    x = np.linspace(- (kernlen // 2), kernlen // 2, kernlen)    
    # Kernel gaussiano unidmensionale
    kern1d = np.exp(- 0.5 * (x**2 / sigma))
    # Kernel gaussiano bidimensionale
    kern2d = np.outer(kern1d, kern1d)
    # Normalizzazione
    return kern2d / kern2d.sum()

# Esegui l'fft del kernel K di dimensione d agggiungendo gli zeri necessari 
# ad arrivare a dimensione shape
def psf_fft(K, shape):
    
    #Get kernel dimension
    d = K.shape[0]
    
    # Aggiungi zeri
    K_p = np.zeros(shape)
    K_p[:d, :d] = K

    # Sposta elementi
    p = d // 2
    K_pr = np.roll(np.roll(K_p, -p, 0), -p, 1)

    # Esegui FFT
    K_otf = fft.fft2(K_pr)
    return K_otf

# Moltiplicazione per A
def A(x, K):
  x = fft.fft2(x)
  return np.real(fft.ifft2(K * x))

# Moltiplicazione per A trasposta
def AT(x, K):
  x = fft.fft2(x)
  return np.real(fft.ifft2(np.conj(K) * x))

def convert_255_to_1(A):
    return A/255

def img_to_fourier(img):
    return fft.fft2(img)

def deblur(original, corrotta, blurFilter, maxit, lambda_=0):
  

    def f(x):
        
        xmat = x.reshape((512,512))
        
        #Se lambda_ == 0 non utilizziamo la regolarizzazione di Tikhonov ma la naive
        if lambda_ == 0:
            return (0.5)*( np.sum( np.square( (A(xmat, blurFilter) -corrotta ) )))
        else:
            return (0.5)*( np.sum( np.square( (A(xmat, blurFilter) -corrotta ) ))) + (0.5)* lambda_ * np.sum(np.square(xmat))

    def df(x):
        xmat = x.reshape((512,512))
        if lambda_ == 0:
            res = AT(A(xmat, blurFilter), blurFilter) -AT(corrotta, blurFilter)
            res = np.reshape(res, 512*512)
            return res
        else:
            res = AT(A(xmat, blurFilter), blurFilter) -AT(corrotta, blurFilter) + lambda_ * xmat
            res = np.reshape(res, 512*512)
            return res
    

    ABSOLUTE_STOP=1.e-6
    (x_last, k, iter_PSNR, iter_MSE) = minimize(f, df, corrotta, original, maxit, ABSOLUTE_STOP)        
    
    deblurred_img = np.reshape(x_last, (512, 512))
    
    PSNR = metrics.peak_signal_noise_ratio(original, deblurred_img)    
    MSE = metrics.mean_squared_error(original, deblurred_img)    
    
    
    return (deblurred_img, iter_PSNR, iter_MSE, k)


def plotImgData(iteraz, PSNR, MSE, title):
    
    
    iterazioni = np.linspace(1, iteraz+1, iteraz+1)
    
    plt.figure()
    plt.suptitle(title)
    ax1 = plt.subplot(1, 2, 1)
    ax1.plot(iterazioni, PSNR, color='blue', label='PSNR')
    ax2 = plt.subplot(1, 2, 2)
    ax2.plot(iterazioni, MSE, color='red', label='MSE')
    plt.legend()
    plt.show()

# Rumore
deviazione_standard = 0.05

#Get image from library
img = convert_255_to_1(data.camera())

#Show image (without blur)
plt.imshow(img, cmap='gray')
plt.title("Immagine originale")
plt.show()

#Create blurred image
ker = gaussian_kernel(24, 3)
psf = psf_fft(ker, img.shape)
blurred = A(img, psf)

#Add noise to image
noise = np.random.normal(loc = 0, scale = deviazione_standard, size = ((512,512)))
noisedBlurred = A(img, psf) + noise
plt.imshow(noisedBlurred, cmap='gray')
plt.title("Noise+Blur")
plt.show()

#Calculate PSNR
psnr = metrics.peak_signal_noise_ratio(img, noisedBlurred)
mse = metrics.mean_squared_error(img, noisedBlurred)


#Naive revert
x0 = blurred
max_it = 100
deblur_img, PSNR, MSE, k = deblur(img, noisedBlurred, psf, max_it, 0)
plt.title("Naive")
plt.imshow(deblur_img, cmap='gray')
plt.show()

#Grafico PSNR e MSE
plotImgData(k, PSNR, MSE, "Naive")

#Different lambdas
lambdas = [0.02, 0.05, 0.1]
x0 = blurred
max_it = 100
images = []
images.append(img)
for i in lambdas:
    
    deblur_img, PSNR, MSE, k = deblur(img, noisedBlurred, psf, max_it, i)    
    images.append(deblur_img)
    
    #Grafico PSNR e MSE
    title = "Tikhonov, lambda: {}".format(i)
    plotImgData(k, PSNR, MSE, title)
    
    #Show whole image    
    plt.title(title)
    plt.imshow(deblur_img, cmap='gray')
    plt.show()

    
# Confronto tutte 
fig = plt.figure()
plt.axis("off")

plt.subplot(2, 2, 1)
fig = plt.imshow(images[0], cmap='gray')
fig.axes.get_xaxis().set_visible(False)
fig.axes.get_yaxis().set_visible(False)
plt.title("Original")

plt.subplot(2, 2, 2)
fig = plt.imshow(images[1], cmap='gray')
fig.axes.get_xaxis().set_visible(False)
fig.axes.get_yaxis().set_visible(False)
plt.title("Lambda: {}".format(lambdas[0]))

plt.subplot(2, 2, 3)
fig = plt.imshow(images[2], cmap='gray')
fig.axes.get_xaxis().set_visible(False)
fig.axes.get_yaxis().set_visible(False)
plt.title("Lambda: {}".format(lambdas[1]))

plt.subplot(2, 2, 4)
fig = plt.imshow(images[3], cmap='gray')
fig.axes.get_xaxis().set_visible(False)
fig.axes.get_yaxis().set_visible(False)
plt.title("Lambda: {}".format(lambdas[2]))

plt.show()
    


