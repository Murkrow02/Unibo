import imageio.v3 as imageio
import matplotlib.pyplot as plt
import numpy as np

url="https://drive.google.com/uc?id=1oMwhUwK-tuCaAP-_2aiTyoCrLIcqkDc9"
img = imageio.imread(url)
plt.axis('off')  # Nasconde gli assi

# Show only red
red = img.copy()

# Red
red[:, :, 1] = 0
red[:, :, 2] = 0
plt.imshow(red)

#%%

# Saturate image
saturation_factor = 1.5
saturated_image = img * saturation_factor
# Assicurati che i valori rimangano nel range 0-255, e poi riportali in int
saturated_image = np.clip(saturated_image, 0, 255).astype(np.uint8)

plt.imshow(saturated_image)
plt.axis('off')  # Nasconde gli assi
plt.title('Saturated')
plt.show()