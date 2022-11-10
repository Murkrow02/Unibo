from NewtonBisection import bisezione, newton, tolx
from SuccApprox import succ_app
import numpy as np
import math
import matplotlib.pyplot as plt

''' creazione del problema '''

a1, b1 = 0, 2
f1 = lambda x : (x**3) + 4*x*np.cos(x) - 2
g1 = lambda x : (2-(x**3))/(4*np.cos(x))

a2, b2 = 3, 5
f2 = lambda x : x - (x**(1/3)) - 2
g2 = lambda x : (x**(1/3)) + 2

bisectionf1 = bisezione(a1, b1, f1, tolx, None)

