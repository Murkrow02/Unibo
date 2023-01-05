"""3. Choleski"""

import numpy as np
import scipy
# help (scipy)
import scipy.linalg
from numpy import linalg as LA
# help (scipy.linalg)
# help (scipy.linalg.cholesky)
# help (scipy.linalg.solve)

# crazione dati e problema test
A = np.array ([ [3,-1, 1,-2], [0, 2, 5, -1], [1, 0, -7, 1], [0, 2, 1, 1]  ], dtype=float)
A = np.matmul(A, np.transpose(A))
x = np.ones((4,1))
b = A@x

condA = LA.cond(A)

print('x: \n', x , '\n')
print('x.shape: ', x.shape, '\n' )
print('b: \n', b , '\n')
print('b.shape: ', b.shape, '\n' )
print('A: \n', A, '\n')
print('A.shape: ', A.shape, '\n' )
print('K(A)=', condA, '\n')

# decomposizione di Choleski
L = scipy.linalg.cholesky(A)
print('L:', L, '\n')

print('L.T*L =',L.T@L)
print('err = ', scipy.linalg.norm(A-np.matmul(L, np.transpose(L)), 'fro'))

scipy.linalg.solve(A,b)

y = ...
my_x = ...
print('my_x = ', my_x)
print('norm =', scipy.linalg.norm(x-my_x, 'fro'))
