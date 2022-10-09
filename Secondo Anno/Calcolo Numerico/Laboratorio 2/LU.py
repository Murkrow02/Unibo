#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct  7 13:49:32 2022

@author: valeriopiodenicola
"""

import numpy as np
import scipy
# help (scipy)
import scipy.linalg
# help (scipy.linalg)
import scipy.linalg.decomp_lu as LUdec 

# A
n = 3

A = np.random.rand(n,n)
x = np.ones((n, 1))
b = A@x

# B

cond = np.linalg.cond(A)

piv, L, U = LUdec.lu(A)

y = U@x

b2 = L@y

x2 = np.linalg.solve(U,y)



