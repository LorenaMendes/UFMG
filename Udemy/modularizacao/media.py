'''
média = somo todos e divido pelo tamanho
mediana = ordeno e pego o elemento central (ou média dos dois centrais)
moda = valor que mais se repete na lista
'''

forma_facil = 1

if forma_facil: from statistics import *

def media(lista):
	if forma_facil: media = mean(lista)
	else:
		media = sum(lista)/float(len(lista))
	return media

def mediana(lista):
	if forma_facil: mediana = median(lista)
	else:
		lista_ordenada = sorted(lista)
		tam = len(lista_ordenada)
		if tam % 2 == 0:
			mediana = (lista_ordenada[int(tam/2-1)] + lista_ordenada[int(tam/2)])/2
		else:
			mediana = lista_ordenada[int(tam/2)]
	return mediana

def moda(lista):
	if forma_facil: moda = mode(lista)
	else:
		lista_dic = {}
		for l in lista:
			if l not in lista_dic:
				lista_dic[l] = 1
			else:
				lista_dic[l] += 1
		maior_repeticao = max(lista_dic.values())

		for i in lista_dic:
			if lista_dic[i] == maior_repeticao:
				moda = i
	return moda