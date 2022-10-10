#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct  7 14:08:16 2022

@author: valeriopiodenicola
"""

import numpy as np
import scipy
import scipy.linalg
import scipy.linalg.decomp_lu as LUdec 
import matplotlib.pyplot as plt

# A
n = np.arange(2,16,1)


def generate_tri(M):
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M





ay = np.zeros(n.size)

ae = np.zeros(n.size)

for i in range(0, n.size):

    #A = generate_tri(np.zeros((n[i],n[i])))    
    A = scipy.linalg.hilbert(n[i])
    
    ay[i] = np.linalg.cond(A)
    
    x = np.ones((n[i], 1))
    b = A@x
    
    #C = scipy.linalg.cholesky(A, lower = True)
    #U = np.matrix.transpose(C)
    piv, C, U = LUdec.lu(A)


    y = U@x

    b2 = C@y
    
    x2 = np.linalg.solve(A,b2)
    
    ae[i] = np.linalg.norm(x-x2)
    
    
    
    
plt.plot(n,ay, color = "red")
plt.plot(n,ae, color = "blue")
plt.show()






"""




cond = np.linalg.cond(A)

C = scipy.linalg.cholesky(A, lower = True)
U = np.matrix.transpose(C)


y = U@x

b2 = C@y

"""




