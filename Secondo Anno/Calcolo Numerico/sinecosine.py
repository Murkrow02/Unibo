import matplotlib.pyplot as plt
import numpy as np
import math

precision = 0.01
rangex = 10.1

x_points_sin = np.arange(0.0,rangex, precision)
y_points_sin = np.empty(shape=[x_points_sin.size],dtype=(np.float32))
for i in range(0, x_points_sin.size):
    y_points_sin[i] = math.sin(x_points_sin[i])
    
    
x_points_cosin = np.arange(0.0,rangex, precision)
y_points_cosin = np.empty(shape=[x_points_cosin.size],dtype=(np.float32))
for i in range(0, x_points_cosin.size):
    y_points_cosin[i] = math.cos(x_points_cosin[i])

#print(x_points)

plt.plot(x_points_sin, y_points_sin, label="sine")
plt.plot(x_points_cosin, y_points_cosin, mec="r", label="cosine")
plt.legend(loc="upper left")
plt.title('Seno e coseno')
plt.show()