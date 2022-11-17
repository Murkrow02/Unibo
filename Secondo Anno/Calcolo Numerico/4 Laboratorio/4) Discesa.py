#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 17 12:51:11 2022

@author: valeriopiodenicola
"""

import numpy as np
import matplotlib.pyplot as plt


def next_step(x,grad): # backtracking procedure for the choice of the steplength
    alpha=1.1
    rho = 0.5
    c1 = 0.25
    p=-grad
    j=0
    jmax= 10
    
    while  (f(x + alpha*p) > (f(x) + c1*alpha*grad.T@p) and j <= jmax):
        print("new z:", f(x + alpha*p))
        print("comparison:", (f(x) + c1*alpha*grad.T@p))
        alpha = rho*alpha
        j = j+1
        #print(alpha)
        
    if (j >= jmax):
        return -1
    else:
        return alpha
        
    
    
      


#x0 appartenente a R2
def minimize(x0,x_true,step,MAXITERATION,ABSOLUTE_STOP): 
  
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
    norm_grad_list[:,k]= np.linalg.norm(grad_f(x0))
     
    while (np.linalg.norm(grad_f(x_last))>ABSOLUTE_STOP and k < MAXITERATION -1 ):
        
        #Increment index
        k = k+1
        
        #Direzione di ricerca
        p = -grad_f(x_last)
                
        # backtracking step
        step = next_step(x_last, grad_f(x_last))
        #print(step)
        
        if(step==-1):
            raise Exception("Non converge")
        
        #Calculate new x
        x_last = x_last + step*p
        
        x[:,k] = x_last
        
        function_eval_list[:,k] = abs(f(x_last))
        error_list[:,k] = np.linalg.norm(x_last-x_true)
        norm_grad_list[:,k]= np.linalg.norm(grad_f(x_last))
    
    print('iterations=',k)
    print('last guess: x=(%f,%f)'%(x[0,k],x[1,k]))
    
    #Truncate at last iteration
    x = x[:,0:k]
    norm_grad_list = norm_grad_list[:,0:k]
    error_list = error_list[:,0:k]
    function_eval_list = function_eval_list[:,0:k]


    
    
 

    return (x_last,norm_grad_list, function_eval_list, error_list, k, x)





'''creazione del problema'''

x_true=np.array([1,2])

def f(x):
    return 10*((x[0]-1)**2)+((x[1]-2)**2)

def grad_f(x):
    dx = 20*x[0]-20
    dy = 2*x[1] - 4
    return np.array([dx, dy])

step=0.1
MAXITERATIONS=1000
ABSOLUTE_STOP=1.e-5
mode='plot_history'
x0 = np.array((3,-5))


result = minimize(x0, x_true, step, MAXITERATIONS, ABSOLUTE_STOP)



v_x0 = np.linspace(-5,5,500)
v_x1 = np.linspace(-5,5,500)
x0v,x1v = np.meshgrid(v_x0, v_x1)
z = f(np.array([x0v,x1v]))
   
'''superficie'''
plt.figure()
ax = plt.axes(projection='3d')
ax.plot_surface(x0v,x1v,z, cmap="viridis")
ax.set_title('Surface plot')
plt.show()

'''contour plots'''
if mode=='plot_history':
    
    contours = plt.contour(x0v,x1v,z, levels = 40)
    plt.plot((result[-1])[0,:],(result[-1])[1,:], marker="o")
    plt.title("Points History")
    plt.show()

'''plots'''

# Iterazioni vs Norma Gradiente
plt.figure()
plt.plot(np.arange(0,result[-2]), (result[1])[0])
plt.title('Iterazioni vs Norma Gradiente')
plt.show()



#Errore vs Iterazioni
plt.figure()
plt.plot(np.arange(0,result[-2]), (result[-3])[0])
plt.title('Errore vs Iterazioni')
plt.show()



#Iterazioni vs Funzione Obiettivo
plt.figure()
plt.plot(np.arange(0,result[-2]), (result[2])[0])
plt.title('Iterazioni vs Funzione Obiettivo')
plt.show()











