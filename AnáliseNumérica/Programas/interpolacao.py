import numpy as np
def InterpolacaoPolinomial(x, y, z):
	m = np.length(x)
	for i in range(m):
		if z==x[i]: 
			return
	G= np.zeros((m,m)) 
	for i in range(m):
		for j in range(m): 
			G[i,j] = x[i] - x[j]
	for i in range(m):
		Gd = Gd * G[i,i]
	Gi = np.zeros(m)
	for i in range(m): 
		for j in range(m):
			Gi = Gi * G[i,j]
	somatorio = 0.0
	for i in range(m):
		somatorio += (y[i] / Gi)
	y_z = Gd*somatorio 
	return y_z

z = np.arange(0.01, 3.15, 0.01)
x = np.array([.0,.2,.3,.4,.7,.9])
y = np.array([3.,2.76,2.655,2.6,3.035,4.125])

res = InterpolacaoPolinomial(x,y,z)
print(res)