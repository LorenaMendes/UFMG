# Crescimento da População Brasileira 1980-2016
# DataSus

import matplotlib.pyplot as plt

dados = open("populacao-brasileira.csv").readlines()

x = [] # ARMAZENA OS ANOS
y = [] # ARMAZENA O TAMANHO DA POPULAÇÃO

for i in range(len(dados)):
	if i != 0:
		linha = dados[i].split(";") # SEPARO POR ;
		x.append(int(linha[0]))
		y.append(int(linha[1]))

plt.plot(x, y, color="k", linestyle="--")
plt.bar(x, y, color="#e4e4e4")
plt.title("Crescimento da População Brasileira 1980-2016")
plt.xlabel("Ano")
plt.ylabel("População x 100.000.000")
# plt.savefig("populacao_brasileira.png", dpi=70)
plt.show()
