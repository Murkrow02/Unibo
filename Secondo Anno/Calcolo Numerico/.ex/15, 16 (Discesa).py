import numpy as np
import matplotlib.pyplot as plt
import numdifftools as nd


def next_step(x,grad,f): # backtracking procedure for the choice of the steplength

    #We start with alpha = 1 
    alpha=1.1
    
    #Dimezziamo alpha ad ogni iteraione
    rho = 0.5
    
    #
    c1 = 0.25
    
    #Direzione di discesa  
    p=-grad
    
    #Iterazioni
    j=0
    
    #Iterazioni massime
    jmax= 10
    
    while  (f(x + alpha*p) > (f(x) + c1*alpha*grad.T@p) and j <= jmax):
        alpha = rho*alpha
        j = j+1
        #print(alpha)
        
    #Troppe iterazioni
    if (j >= jmax):
        return -1
    else:
        return alpha
        

#x0 appartenente a R2
def minimize(f, x0,x_true,MAXITERATION,ABSOLUTE_STOP, fixed_step = -1): 
  
    #X found each iteration
    x=np.zeros((2,MAXITERATION))
    
    #Gradient norm at each iteration
    norm_grad_list=np.zeros((1,MAXITERATION)) 
    
    #Z at each iteration
    function_eval_list=np.zeros((1,MAXITERATION))
    
    #Error each iteration
    error_list=np.zeros((1,MAXITERATION)) 
    
    #Iteration index
    k=0
    
    #Last x found
    x_last = np.array([x0[0],x0[1]])
    
    #Set found point k=0
    x[:,k] = x_last
    
    #Calculate initial Z
    function_eval_list[:,k] = abs(f(x0))
    
    #Error at first iteration (absolute)
    error_list[:,k] = np.linalg.norm(x_last-x_true)
    
    #Norm of the gradient at each iteration
    norm_grad_list[:,k]= np.linalg.norm(nd.Gradient(f)(x0))
     
    #Condizioni di arresto
    while (np.linalg.norm(nd.Gradient(f)(x_last))>ABSOLUTE_STOP and k < MAXITERATION -1 ):
        
        #Increment index
        k = k+1
        
        #Direzione di ricerca
        p = -nd.Gradient(f)(x_last)
                
        # backtracking step
        step = next_step(x_last, nd.Gradient(f)(x_last),f) if fixed_step == -1 else fixed_step
        
        # Algoritmo di backtracking non ha trovato uno step adeguato        
        if(step==-1):
            raise Exception("Non converge")
        
        #Calculate new x
        x_last = x_last + step*p
        
        x[:,k] = x_last
        
        function_eval_list[:,k] = abs(f(x_last))
        error_list[:,k] = np.linalg.norm(x_last-x_true)/np.linalg.norm(x_true)
        norm_grad_list[:,k]= np.linalg.norm(nd.Gradient(f)(x_last))

    
    #Truncate at last iteration
    x = x[:,0:k]
    norm_grad_list = norm_grad_list[:,0:k]
    error_list = error_list[:,0:k]
    function_eval_list = function_eval_list[:,0:k]


    return (x_last,norm_grad_list, function_eval_list, error_list, k, x)





'''creazione del problema'''

x_true=np.array([1,2])

def f1(x):
    return 10*((x[0]-1)**2)+((x[1]-2)**2)

def f2(x):
    b = np.ones(x.size) #b sono tutti uno da consegna
    return (np.linalg.norm(x-b,2))**2 + (lambda_f2 *(np.linalg.norm(x,2))**2)


'''problem parameters'''
MAXITERATIONS=1000
ABSOLUTE_STOP=1.e-5
mode='plot_history'

#setta a -1 se vuoi che sia scelto con backtracking
#fixed_step = 0.00001 #Troppo piccolo non converge (non si avvicina nemmeno)
#fixed_step = 0.01 #Converge
#fixed_step = 0.1 #Troppo grande non converge (si blocca su un punto fisso)
fixed_step = -1 #Auto



'''graph parameters'''
v_x0 = np.linspace(-5,5,500)
v_x1 = np.linspace(-5,5,500)
x0v,x1v = np.meshgrid(v_x0, v_x1)

'''f1'''
x0 = np.array((3,-5))
x_last,norm_grad_list, function_eval_list, error_list, k, x = minimize(f1,x0, x_true, MAXITERATIONS, ABSOLUTE_STOP,fixed_step)


'''Superficie'''
z = f1(np.array([x0v,x1v]))
plt.figure()
ax = plt.axes(projection='3d')
ax.plot_surface(x0v,x1v,z, cmap="viridis")
ax.set_title('Superficie f1')
plt.show()


'''contour plots'''
if mode=='plot_history':
    
    contours = plt.contour(x0v,x1v,z, levels = 40)
    plt.plot(x[0,:],x[1,:], marker="o")
    plt.title("Points History")
    plt.show()


'''Grafici di valutazione'''
plt.figure()
plt.plot(np.arange(0,k), error_list[0], label="Errore relativo")
plt.plot(np.arange(0,k), function_eval_list[0], label="Valutazione della funzione")
plt.plot(np.arange(0,k),norm_grad_list[0],label = "Norma del gradiente")
plt.title('f1')
plt.xlabel("Iterazioni")
plt.legend()
plt.show()

#Stop f2
#exit(1)

'''f2'''
x0 = np.array((3,-5))


'''plot f2'''
lambddavalues = np.linspace(0,1,11)
for i in range (lambddavalues.size):
    try:
        #take new lambda
        lambda_f2 = lambddavalues[i]
        
        #ATTENZIONE! IL VALORE f(x)=0 NON È NOTO, PERTANTO NON SONO AFFIDABILI I VETTORI DI ERRORE RELATIVO!!!!!!!
        x_last,norm_grad_list, function_eval_list, error_list, k, x = minimize(f2, x0, x_true, MAXITERATIONS, ABSOLUTE_STOP,fixed_step)
        
        '''Grafici di valutazione per diversi valori di lambda'''
        plt.figure()
        plt.plot(np.arange(0,k), function_eval_list[0], label="Valutazione della funzione")
        plt.plot(np.arange(0,k),norm_grad_list[0],label = "Norma del gradiente")
        plt.title('f2 lambda:{}'.format(lambda_f2))
        plt.xlabel("Iterazioni")
        plt.legend()
        plt.show()

        
    except:
        print("Lambda", lambddavalues[i], "not supported")











