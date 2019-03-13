import matplotlib.pyplot as pyplot

x = list(range(-100, 3000))
y = list(map(lambda x: x**2, x))
pyplot.plot(x, y)
pyplot.show()
