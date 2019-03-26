# Comparando genomas

entrada = open("16s_bacteria.fasta").read()
saida = open("bacteria.html","w")
entrada = entrada.replace("\n", "")
cont = {}

for i in ['A', 'T', 'C', 'G']:
	for j in ['A', 'T', 'C', 'G']:
		cont[i+j] = 0

for k in range(len(entrada)-1):
	cont[entrada[k] + entrada[k+1]] += 1

print(cont)