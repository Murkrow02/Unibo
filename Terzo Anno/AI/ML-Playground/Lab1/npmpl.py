import math
import numpy as np
import matplotlib.pyplot as plt

# Random matrix 4x4
mat = np.random.randint(0, 10, (4, 4))

# Sine and cosine graph
x = np.linspace(-2, 2)
ysin = np.sin(x)
ycos = np.cos(x)
plt.plot(x,ysin)
plt.plot(x,ycos)
plt.grid()
plt.show()