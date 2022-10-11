


"""4. Choleski con matrice di Hilbert"""

import numpy as np
import scipy
# help (scipy)
import scipy.linalg
# help (scipy.linalg)
# help (scipy.linalg.cholesky)
# help (scipy.linalg.hilbert)

# crazione dati e problema test
n = ...
A = scipy.linalg.hilbert ...
x = ...
b = ...

condA = ...

print('x: \n', x , '\n')
print('x.shape: ', x.shape, '\n' )
print('b: \n', b , '\n')
print('b.shape: ', b.shape, '\n' )
print('A: \n', A, '\n')
print('A.shape: ', A.shape, '\n' )
print('K(A)=', condA, '\n')

# decomposizione di Choleski
L = scipy.linalg.cholesky ...
print('L:', L, '\n')

print('L.T*L =', ...
print('err = ', scipy.linalg.norm(A-np.matmul(L, np.transpose(L)), 'fro'))

y = ...
my_x = ...
print('my_x = \n ', my_x)

print('norm =', scipy.linalg.norm(x-my_x, 'fro'))



"""5. Choleski con matrice di matrice tridiagonale simmetrica e definita positiva """

import numpy as np
import scipy
# help (scipy)
import scipy.linalg
# help (scipy.linalg)
# help (scipy.linalg.cholesky)
# help (np.diag)

# crazione dati e problema test
n = ...
A = np.diag(...) + ...
A = np.matmul(A, np.transpose(A))
x = ...
b = ...

condA = ...

print('x: \n', x , '\n')
print('x.shape: ', x.shape, '\n' )
print('b: \n', b , '\n')
print('b.shape: ', b.shape, '\n' )
print('A: \n', A, '\n')
print('A.shape: ', A.shape, '\n' )
print('K(A)=', condA, '\n')

# decomposizione di Choleski
L = scipy.linalg.cholesky ...
print('L:', L, '\n')

print('L.T*L =', ...
print('err = ', scipy.linalg.norm(A-np.matmul(L, np.transpose(L)), 'fro'))

y = ...
my_x = ...
print('my_x = \n ', my_x)

print('norm =', scipy.linalg.norm(x-my_x, 'fro'))




"""6. plots """


import scipy.linalg.decomp_lu as LUdec 
import matplotlib.pyplot as plt

K_A = np.zeros((20,1))
Err = np.zeros((20,1))

for n in np.arange(10,30):
    # crazione dati e problema test
    A = ...
    x = ...
    b = ...
    
    # numero di condizione 
    K_A[n-10] = ...
    
    # fattorizzazione 
    lu ,piv = ...
    my_x = ...
    
    # errore relativo
    Err[n-10] = ...
  
x = np.arange(10,30)

# grafico del numero di condizione vs dim
plt.plot(...)
plt.title('CONDIZIONAMENTO DI A ')
plt.xlabel('dimensione matrice: n')
plt.ylabel('K(A)')
plt.show()


# grafico errore in norma 2 in funzione della dimensione del sistema
plt.plot(...)
plt.title('Errore relativo')
plt.xlabel('dimensione matrice: n')
plt.ylabel('Err= ||my_x-x||/||x||')
plt.show()









