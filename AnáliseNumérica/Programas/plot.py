# carrega bibliotecas
import numpy as np
import matplotlib.pyplot as plt

# atribui os valores de x e y
x = [2.0, 3.5, 4.0, 5.1, 7.0]
y = [2.2, 2.0, 3.0, 6.0, 5.0]
 
# plota o diagrama de dispersao
plt.scatter(x, y)
# titulo do diagrama
plt.title('Diagrama de Dispersão')
# mostra o diagrama plotado
plt.show()