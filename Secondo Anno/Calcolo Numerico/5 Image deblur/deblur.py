import numpy as np
import matplotlib.pyplot as plt
from skimage import data, metrics
from scipy import signal
from numpy import fft
from scipy.optimize import minimize

np.random.seed(0)

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

#Get image from library
img = convert_255_to_1(data.camera())

#Show image (without blur)
plt.imshow(img, cmap='gray')
plt.show()

#Create blurred image
ker = gaussian_kernel(24, 3)
psf = psf_fft(ker, img.shape)
blurred = A(img, psf)

#Show blurred image
plt.imshow(blurred, cmap='gray')
plt.show()

#Add noise to image
noised = blurred + np.random.normal(scale=0.02, size=(blurred.shape[0], blurred.shape[1]))
plt.imshow(noised, cmap='gray')
plt.show()

#Calculate PSNR
psnr = metrics.peak_signal_noise_ratio(img, noised)
mse = metrics.mean_squared_error(img, noised)

def f(x):
    xmat = x.reshape((512,512))
    return (0.5)*( np.sum( np.square( (A(xmat, psf) -blurred ) )))

def df(x):
    x_r = x.reshape((512,512))
    res = AT(A(x_r, psf), psf) -AT(blurred, psf)
    res = np.reshape(res, 512*512)
    return res

#Naive revert
x0 = blurred
max_it = 100
res = minimize(f, x0, method='CG', jac=df, options={'maxiter':max_it, 'return_all':True})
deblur_img = np.reshape(res.x, (512, 512))


plt.imshow(deblur_img, cmap='gray')
plt.show()



