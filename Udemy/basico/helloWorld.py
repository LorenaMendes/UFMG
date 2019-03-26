# COMANDO USADO CASO O PYTHON NÃO ACEITE ACENTUAÇÃO
# -*- coding: utf-8 -*-

# COMO IMPRIMIR NA TELA
print("Hello world")

# COMO FAZER COMENTÁRIOS NO CÓDIGO
#comentando uma linha
"""comentando
várias
linhas """

# COMO CRIAR VARIÁVEIS BOOLEANAS
var1 = True
var2 = False

# COMO FAZER COMPARAÇÕES LÓGICAS
print(var1 and var2)
print(var1 or var2)
print(not var2)

# COMO USAR ESTRUTURAS DE COMPARAÇÃO
x = 3
y = 5
if x == y : print("Iguais")
elif(x < y): print("x maior")
else: print("y maior")

# COMO USAR ESTRUTURAS DE REPETIÇÃO
while x < 5:
	print(x)
	x += 1

for i in range(10,12):
	print(i)

# COMO LIDAR COM LISTAS
lista1 = [1,2,3,4,5]
lista2 = ["ola","mundo","!"]
lista3 = [0,"ola","biscoito",True]
for item in lista3:
	print(item)

lista3.append("limao") # INSERE AO FINAL
print(lista3)

if 7 in lista2: # CHECA SE UM ITEM ESTÁ NA LISTA
	print("7 está na lista")
else:
	print("7 não está na lista")

del(lista2[1:]) # APAGA ITENS A PARTIR DA POSIÇÃO 1
print(lista2)

# COMO ORDENAR LISTAS
lista = [124,46,3,765,87,5,34]
sorted(lista) # RETORNA A LISTA ORDENADA (NÃO A ALTERA)
lista.sort() # ORDENA A LISTA (A ALTERA)
lista.sort(reverse=True) # ORDEM DECRESCENTE
lista.reverse() # INVERTE A ORDEM ATUAL

# COMO LIDAR COM DICIONÁRIOS
meu_dc = {"A":"AMEIXA", "B":"BOLA", "C":"CACHORRO"}
print(meu_dc["A"])
print(meu_dc)
for chave in meu_dc:
	print(chave)
	print(meu_dc[chave])

for i in meu_dc.items(): # MOSTRA COMO TUPLAS
	print(i)

for i in meu_dc.values(): # MOSTRA OS VALORES
	print(i)

for i in meu_dc.keys(): # MOSTRA AS CHAVES
	print(i)

# COMO CRIAR INPUTS E USÁ-LOS
# nome = input("Digite seu nome: ")
# print("Bem vindo(a), " + nome)
# numero = input("Digite um número:")
# numero = int(numero)
# print("O dobro é:" + str(numero*2))

# COMO CONCATENAR STRINGS
a = "Guilherme "
b = "Renna"
concatena = a + b
print(concatena)

# COMO DESCOBRIR O TAMANHO DE UMA STRING
tamanho = len(concatena)
print(tamanho)

# COMO NAVEGAR PELO ÍNDICE DE UM VETOR, STRING, ETC.
print(a[3])

# COMO USAR UMA PARTE DE UMA STRING
print(concatena[0:5])
print(concatena[2:])
print(concatena[:4])

# USANDO MÉTODOS EM STRINGS
eu = "Lorena Mendes"
print(eu)
print(eu.lower()) # CONVERTE TUDO PARA MINÚSCULO
print(eu.upper()) # CONVERTE TUDO PARA MINÚSCULO
print(eu.strip()) # REMOVE ESPAÇOS ANTES E DEPOIS DA STRING
print(eu.replace("Mendes", "Renna"))

# CONVERTE UMA SEQUÊNCIA EM UMA LISTA
frase = "O rato roeu a roupa do rei de Roma"
# frase = frase.replace("roupa", "raba")
print("Frase: " + frase)
minha_lista = frase.split()
print(minha_lista[4])
busca = frase.find("roupa")
print(frase[busca:]) 

# RETIRA ALGUMA PARTE DA STRING
lista_sem_r = frase.split("r")
print(lista_sem_r)

# LENDO ARQUIVOS
arquivo = open("texto.txt")
linhas = arquivo.readlines() # FAZ UMA LISTA COM AS LINHAS
print(linhas)
arquivo.close()

arquivo = open("texto.txt")
texto_completo = arquivo.read() # LÊ O ARQUIVO COMPLETO
print(texto_completo)
arquivo.close()

# CRIANDO ARQUIVOS
w = open("output.txt", "w") # SOBRESCREVE
w.write("Esse é o meu arquivo\n")
w.close()

w = open("output.txt", "a") # ESCREVE AO FINAL
w.write("Meu nome é Lorena\n")
w.close()

# COMO CRIAR FUNÇÕES
def soma(x, y):
	print(x+y)

# GERAR NÚMEROS ALEATÓRIOS
import random
# random.seed(1) # GERA SEMPRE O MESMO NÚMERO (POUCO ÚTIL)
numero = random.randint(0,10)
print(numero)

lista = [6, 45, 9]
numero = random.choice(lista)
print(numero)

# TRATAMENTO DE EXCEÇÕES
a = 2
b = 0
try:
	print(a/b) # VAI DAR ERRO
except:
	print("Não faço divisão por zero")
