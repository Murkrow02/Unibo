import numpy as np
import scipy
import scipy.linalg
import scipy.linalg.decomp_lu as LUdec 
import matplotlib.pyplot as plt

maxDim = 15

"""
Dato un problema test di dimensione variabile la cui soluzione esatta sia il vettore x di tutti elementi unitari e b il termine noto
ottenuto moltiplicando la matrice A per la soluzione x discutere:
    • il numero di condizione (o una stima di esso)
    • la soluzione del sistema lineare Ax=b con la fattorizzazione LU con pivoting.
Testare su una matrice di numeri casuali A generata con la funzione randn di Matlab, (n variabile fra 10 e 1000)
"""

def generateLRProblem(n):
    
    #Generate random elements in matrix
    A = np.random.randint(10,1000,(n,n))
    
    #A vector of all ones as x
    x = np.ones((n, 1))
    
    #The known term, obtained by the matrix multiplication of x and A matrix
    b = A@x
    
    #Calculate condition number
    cond = np.linalg.norm(A)*np.linalg.norm(np.linalg.inv(A))
    
    #LU factorization to solve linear sysyem
    piv, L, R = scipy.linalg.lu(A)
    
    #First step of LU with pivoting (find y) (Ly = Pb -> y=Pb•L^-1)
    y = np.linalg.solve(L,piv@b)
    
    #Second step of LU with pivoting (find x)
    x2 = np.linalg.solve(R,y)
    
    #Find relative error
    relErr = np.linalg.norm(x2-x)/np.linalg.norm(x)
    
    return cond, relErr

"""
Dato un problema test di dimensione variabile la cui soluzione esatta sia il vettore x di tutti elementi unitari e b il
termine noto ottenuto moltiplicando la matrice A per la soluzione x discutere:
    • il numero di condizione (o una stima di esso)
    • la soluzione del sistema lineare Ax=b con la fattorizzazione di Cholesky.
Testare sulla matrice di Hilbert, (n variabile fra 2 e 15).
"""
def generateCholeskyProblem(n):
    
    #Generate hilbert matrix
    AHil = scipy.linalg.hilbert(n)
    
    #Generate tridiagonal matrix
    ATri = generate_tri(n)
    
    #A vector of all ones as x
    x = np.ones((n, 1))
    
    #The known term, obtained by the matrix multiplication of x and A matrix
    bHil = AHil@x
    bTri = ATri@x
    
    #Calculate condition number
    condHil = np.linalg.norm(AHil)*np.linalg.norm(np.linalg.inv(AHil))
    condTri = np.linalg.norm(ATri)*np.linalg.norm(np.linalg.inv(ATri))
    
    #Decompose matrix with cholesky
    try:
        """
        La matrice di Hilbert nonostante sia simmetrica non è sempre definita
        positiva (n minore di 14) (non tutti gli autovalori sono strettamente > 0)
        quindi non si puo sempre scomporre con Cholesky
        """
        canHilbert = True
        CHil = scipy.linalg.cholesky(AHil, lower = True) 
        
    except:
        canHilbert = False
        condHil = -1
        relErrHil = -1
        print("Impossibile scomporre Hilbert con dimensione {} con Cholesky (non positiva)".format(n))
        
        
    #No problems with cholesky on tridiagonal as always positive
    CTri = scipy.linalg.cholesky(ATri, lower = True)
    
    #Transpose cholesky matrix to obtain upper triangular matrix
    if canHilbert:
        CTHil = CHil.T;
    CTTri = CTri.T;
    
    #Proceed like normal LU solve
    if canHilbert:
        yHil = np.linalg.solve(CHil,bHil)
        xHil = np.linalg.solve(CTHil,yHil)
    
    yTri = np.linalg.solve(CTri,bTri)
    xTri = np.linalg.solve(CTTri,yTri)
    
    #Find relative error
    if canHilbert:
        relErrHil = np.linalg.norm(xHil-x)/np.linalg.norm(x)
    relErrTri = np.linalg.norm(xTri-x)/np.linalg.norm(x)
        
    
    return condHil, relErrHil, condTri, relErrTri

#Generates reqeuested tridiagonal matrix
def generate_tri(ndim):
    M = np.zeros((ndim,ndim))
    for i in range(0,np.shape(M)[0]):
        (M[i])[i] = 9
    
        if (i < (np.shape(M)[0])-1):
            (M[i])[i+1] = -4
            (M[i+1])[i] = -4
    return M


#Save condition number and relative errors for each dimension
allCondLU = np.zeros(maxDim-2)
allRelErrLU = np.zeros(maxDim-2)
allCondChHil = np.zeros(maxDim-2)
allRelErrChHil = np.zeros(maxDim-2)
allCondChTri = np.zeros(maxDim-2)
allRelErrChTri = np.zeros(maxDim-2)

#Solve LU and cholesky for each dimension
for i in range(2,maxDim):
    
    #LU
    cond, relErr = generateLRProblem(i)
    allCondLU[i-2] = cond
    allRelErrLU[i-2] = relErr
    
    #Cholesky
    condHil, relErrHil, condTri, relErrTri = generateCholeskyProblem(i)
    allCondChHil[i-2] = condHil
    allRelErrChHil[i-2] = relErrHil
    allCondChTri[i-2] = condTri
    allRelErrChTri[i-2] = relErrTri

#Change to false to display the whole graph
zoomIntoRelErr = True
zoomMargin = 10

#Plot condition number LU
plt.title("Scomposizione LU")
plt.plot(np.arange(2,maxDim), allCondLU, label="Condizionamento")
plt.plot(np.arange(2,maxDim), allRelErrLU,label="Errore relativo")
plt.xticks(np.arange(2, maxDim))
plt.xlabel("Dimensione")
if zoomIntoRelErr:
    plt.ylim(0,(max(allRelErrLU)+zoomMargin))
plt.legend()
plt.show()

#Plot condition number Cholesky
plt.xticks(np.arange(2, maxDim))
plt.subplot(2, 1, 1)
plt.plot(np.arange(2,maxDim), allCondChHil)
plt.ylabel("Condizionamento")

plt.xticks(np.arange(2, maxDim))
plt.subplot(2, 1, 2)
plt.plot(np.arange(2,maxDim), allRelErrChHil)
plt.xlabel("Dimensione")
plt.ylabel("Errore")
plt.suptitle("Hilbert")

plt.subplots_adjust(hspace=0.5)
plt.show()

plt.xticks(np.arange(2, maxDim))
plt.subplot(2, 1, 1)
plt.plot(np.arange(2,maxDim), allCondChTri)
plt.ylabel("Condizionamento")

plt.xticks(np.arange(2, maxDim))
plt.subplot(2, 1, 2)
plt.plot(np.arange(2,maxDim), allRelErrChTri)
plt.xlabel("Dimensione")
plt.ylabel("Errore")
plt.suptitle("Tridiagonale")
plt.subplots_adjust(hspace=0.5)
plt.show()