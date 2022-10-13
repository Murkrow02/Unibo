import numpy as np
from numpy import linalg as LA

#help(np.linalg) # View source
#help (np.linalg.norm)
#help (np.linalg.cond)

n = 2
A = np.array([[1, 2], [0.499, 1.001]])

print ('Norme di A:')
norm1 = LA.norm(A,1)
norm2 = norm1 = LA.norm(A,2)
normfro = norm1 = LA.norm(A,"fro")
norminf = LA.norm(A, np.inf)

print('Norma1 = ', norm1, '\n')
print('Norma2 = ', norm2, '\n')
print('Normafro = ', normfro, '\n')
print('Norma infinito = ', norminf, '\n')

cond1 = LA.cond(A)
cond2 = LA.cond(A, 2)
condfro = LA.cond(A, "fro")
condinf = LA.cond(A, np.inf)

print ('K(A)_1 = ', cond1, '\n')
print ('K(A)_2 = ', cond2, '\n')
print ('K(A)_fro =', condfro, '\n')
print ('K(A)_inf =', condinf, '\n')

x = np.ones((2,1))
b = np.dot(A,x)

btilde = np.array([[3], [1.4985]])
xtilde = np.array([[2, 0.5]]).T

# Verificare che xtilde è soluzione di A xtilde = btilde
# A * xtilde = btilde
print ('A*xtilde = ', A@xtilde)

deltax = xtilde-x "Forse va fatta la norma"
deltab = btilde-b

print ('delta x = ', deltax)
print ('delta b = ', deltab)