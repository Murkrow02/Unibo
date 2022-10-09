#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct  7 15:02:17 2022

@author: valeriopiodenicola
"""

import numpy as np
import scipy
# help (scipy)
import scipy.linalg
# help (scipy.linalg)
import scipy.linalg.decomp_lu as LUdec 
import matplotlib.pyplot as plt

# A
n = 5




def generate_tri(M):
    for i in range(0,n):
        (M[i])[i] = 9
    
        if (i < n-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M








A = generate_tri(np.zeros((n,n)))    
#A = scipy.linalg.hilbert(n)
 
    
x = np.ones((n, 1))
b = A@x
    
C = scipy.linalg.cholesky(A, lower = True)
U = np.matrix.transpose(C)


y = U@x

b2 = C@y
    
x2 = np.linalg.solve(A,b2)
    
   


