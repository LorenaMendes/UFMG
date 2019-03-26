lista = [None] * 3
# lista = [2,5,1]
lista[0] = input()
lista[1] = input()
lista[2] = input()

for y in range(2):
	for x in range(2):
		if lista[x] > lista[x+1]:
			lista[x], lista[x+1] = lista[x+1], lista[x]

for x in lista:
	print(x)
