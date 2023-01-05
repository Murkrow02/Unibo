import numpy as np

def machine_precision(type):
    epsilon = type(1.0)
    mant_dig = 1
    while type(1.0) + epsilon / type(2.0) > type(1.0):
        epsilon /= type(2.0)
        mant_dig += 1
    return epsilon, mant_dig-1
    
print("Float 16 precision:", machine_precision(np.float16)[0])
print("Float 32 precision:", machine_precision(np.float32)[0])
print("Float 64 precision:", machine_precision(np.float64)[0])

print("Float 16 mant size:", machine_precision(np.float16)[1])
print("Float 32 mant size:", machine_precision(np.float32)[1])
print("Float 64 mant size:", machine_precision(np.float64)[1])

