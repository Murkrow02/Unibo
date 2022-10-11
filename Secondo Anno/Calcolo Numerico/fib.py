import math
import numpy as np


def nfib(n):
    x = 1     
    prev = 1
    while(x < n):
        print(x)
        tempx = x
        x = x + prev
        prev = tempx
        
        
        
nfib(20)
        
        
    