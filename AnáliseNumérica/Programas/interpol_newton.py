import numpy as np
def PolinomioNewton(x, y, z):
    m = len(x)
    Delta = np.zeros((m,m))
    Delta[:,0] = y
    for j in range(1,m):
        for i in range(m-j):
            Delta[i,j] = (Delta[i+1,j-1] - Delta[i,j-1])/(x[i+j]-x[i])
        print(Delta)
    
    res = y[0]
    for j in range(1,m):
        prod = 1
        for k in range(j):
            prod *= z-x[k]
        res += Delta[0,j]*prod
        
    return res

z = np.arange(0.01, 3.15, 0.01)
x = np.array([.0,.2,.3,.4,.7,.9])
y = np.array([3.,2.76,2.655,2.6,3.035,4.125])

res = PolinomioNewton(x,y,z)
print(res)