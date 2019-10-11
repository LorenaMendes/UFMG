#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import socket
import struct
import numpy
import copy


#função que lê do arquivo e codifica a pl em estrutura de dados
def read_pl(plname):
	pl=[]
	#salva numa lista linha por linha do arquivo de entrada
	with open(plname) as file:
		for line in file:
			pl.append(line)
	
	#retira os /n das linhas
	for i in range(len(pl)):
		pl[i]=pl[i].split("\n")
		pl[i]=pl[i][0]
	
	pl[2]=pl[2].split()
	pl[3]=pl[3].split()

	for i in range(4,len(pl)):
		pl[i]=pl[i].split()

	return pl 
#função que transforma a pl lida no formato fpi
def turn_pl_into_fpi(pl):
	n_variables=int(pl[0])
	n_restrictions=int(pl[1])
	v_state=pl[2]
	max_function=pl[3]
	restrictions=[]

	aux_variables=[]
	aux_index=[]

	for i in range(4,len(pl)): #pegamos em separado as restrições
		restrictions.append(pl[i])

	for i in range(len(v_state)): #pra cada variável olhamos se é livre ou não
		if(float(v_state[i])==0): # se for livre criamos uma variável a mais e guardamos o índice da variável 
			n_variables=float(n_variables)+1
			aux_variables=aux_variables+[1,1]
			aux_index.append(i)

		else:
			aux_variables.append(1)
	v_state=aux_variables # guardamos de volta variável original 


	for i in range(len(aux_index)): #como vamos somar variáveis nas restrições, precisamos atualizar os índices das variáveis
		aux_index[i]=aux_index[i]+i



	m=len(restrictions) #número de linhas
	n=len(restrictions[0]) #numero de colunas

	for i in range(0,m): #adicionamos as variáveis novas nas restrições
		for j in range(len(aux_index)):
			restrictions[i].append(0)

	m=len(restrictions) #número de linhas
	n=len(restrictions[0]) #numero de colunas

	for i in range(0,m): # aqui colocamos as variáveis novas no lugar certo
		for j in range(len(aux_index)):
			for k in range(n-2,aux_index[j],-1):
				restrictions[i][k+1]=restrictions[i][k]
			restrictions[i][aux_index[j]+1]=-float(restrictions[i][aux_index[j]])

	m=len(restrictions) #número de linhas
	n=len(restrictions[0]) #numero de colunas

	for i in range(len(aux_index)):
		max_function.append(0)

	for i in range(len(aux_index)):
		for k in range(n-4,aux_index[i]-1,-1):
			max_function[k+1]=-float(max_function[k])

	aux_index=0
	index1=[]
	n=len(restrictions[0])


	for i in range(0,m): # vê quantas variáveis auxiliares tem que criar
		if(restrictions[i][n-2]!="=="):
			aux_index=aux_index+1
			index1.append(i)

	n_variables=n_variables+aux_index
	for i in range(0,aux_index):
		v_state.append(1)
		max_function.append(0)

	if(aux_index>0):
		for i in range(0,aux_index): #acrescenta espaço pras variáveis auxiliares
			for j in range(0,m):
				restrictions[j].append(0)


		n=len(restrictions[0])
		for i in range(0,m):
			restrictions[i][n-1]=restrictions[i][n-1-aux_index]
			restrictions[i][n-2]=restrictions[i][n-2-aux_index]

		for i in range(0,m):
			for j in range(n-3,n-3-aux_index,-1):
				restrictions[i][j]=0

		for i in range(len(index1)):
			restrictions[index1[i]][n-2-aux_index+i]=1	


		for i in range(len(index1)):
			if(restrictions[index1[i]][n-2]=="<="):
				restrictions[index1[i]][n-2-aux_index+i]=1
			else:
				restrictions[index1[i]][n-2-aux_index+i]=-1

	for i in range(0,m):
		restrictions[i].pop(n-2)
	
	for i in range(len(max_function)):
		max_function[i]=float(max_function[i])

	n=len(restrictions[0])

	for i in range(0,m):
		for j in range(0,n):
			restrictions[i][j]=float(restrictions[i][j])

	tamanho=len(restrictions[0])
	
	for i in range(len(restrictions)):
		if(restrictions[i][tamanho-1]<0.0):
			for j in range(len(restrictions[i])):
				restrictions[i][j]=-restrictions[i][j]

	return [float(n_restrictions),n_variables,max_function,restrictions] 
# função que cria a pl auxiliar
def create_auxpl(plfpi):
	n_lines=round(plfpi[0])
	n_columns=round(plfpi[1])
	max_function=plfpi[2]
	restrictions=plfpi[3]

	for i in range(len(max_function)):
		max_function[i]=0

	i=n_lines
	while(i>0):
		max_function.append(-1.0)
		i=i-1

	for i in range(0,n_lines):
		for j in range(0,n_lines):
			restrictions[i].insert(-1,0.0)

	for i in range(len(restrictions)):
		restrictions[i][n_columns+i]=1.0

	n_columns=len(restrictions[0])-1

	return [n_lines,n_columns,max_function,restrictions] 
#função que cria o tableau
def create_tableau(pl):
	n_lines=round(pl[0])
	n_columns=round(pl[1])
	max_function=pl[2]
	restrictions=pl[3]
	for i in range(0,n_lines):
		max_function.insert(0,0.0)
		for j in range(0,n_lines):
			restrictions[j].insert(0,0.0)

	max_function.append(0.0)
	n_columns=n_columns+1+n_lines
	n_lines=n_lines+1

	for i in range(len(max_function)):
		max_function[i]=-max_function[i]

	restrictions.insert(0,max_function)

	for i in range(1,n_lines):
		restrictions[i][i-1]=1.0

	for i in range(len(restrictions)):
		for j in range(len(restrictions[0])):
			restrictions[i][j]=float(restrictions[i][j])
	return [n_lines,n_columns,restrictions] 
# função que pivoteia (l,c) 
def pivoteia(tableau,l,c):
	mat=tableau[2]
	for i in range(len(mat)):
		if(i==l):
			a=mat[l][c]
			for j in range(len(mat[l])):
				mat[l][j]=mat[l][j]/a
		else:
			a=mat[i][c]/mat[l][c]
			for j in range(len(mat[i])):
				mat[i][j]=mat[i][j]-a*mat[l][j]
	
	for i in range(len(mat)):
		for j in range(len(mat[0])):
			if(mat[i][j]<0.001 and mat[i][j]>0.0):
				mat[i][j]=0.0
	tableau[2]=mat
	return tableau 


#checa se uma coluna no tableau é válida pra pivotear, ou seja, se o índice<0
def search_column_validate(tableau,c): 
	matriz=tableau[2]
	leee=len(matriz[0])
	if(matriz[0][c]<-0.00001):
		return True
	else:
		return False
#calcula quantos positivos tem na coluna c
def number_of_positive_values_in_column(tableau,c):
	matriz=tableau[2]
	sum=0
	leee=len(matriz[0])
	for i in range(1,len(matriz)):
		if(matriz[i][c]>0.001):
			sum+=1
	return sum 
#serve pra calcular qual índice da coluna vai ser pivoteado
def smaller_division_index(tableau,c):
	matriz=tableau[2]
	length=round(tableau[1])-1
	menor=[60000,-1000]
	for i in range(1,len(matriz)):
		if(matriz[i][c]>0.001):
			division=matriz[i][length]/matriz[i][c]
			if(division<menor[0] and division>=0.0):
				menor=[division,i]
	return menor[1] 
#diz se uma coluna não pode ser pivoteada,se indica ilimitância ou se pode ser pivoteada e o índice do pivot
def search_in_column(tableau,c):
	matriz=tableau[2]
	if(not search_column_validate(tableau,c)):
		return ["invalida",0]
	else:
		if(number_of_positive_values_in_column(tableau,c)==0):
			return ["ilimitada",0]
		else:
			return ["valida",smaller_division_index(tableau,c)] 


#diz se uma coluna é base e qual linha dela é 1
def check_column_base(mat,c):
	n_zeros=0
	for i in range(len(mat)):
		if(mat[i][c]<0.001 and mat[i][c]>=0.0):
			n_zeros=n_zeros+1

	if(n_zeros==(len(mat)-1)):
		for i in range(len(mat)):
			if(mat[i][c]<=1.001 and mat[i][c]>=1.0 and i!=0):
				return [True,i]
		return [False,-1]
	else:
		return [False,-1]
#fornce uma lista com as localizações dos pivores
def find_base(tableau):
	n_lines=round(tableau[0])
	n_columns=round(tableau[1])
	mat=tableau[2]
	lists=[]

	for i in range(n_lines-1,n_columns-1):
		aux=check_column_base(mat,i)
		if(aux[0]==True):
			lists.append([aux[1],i])
	
	for i in range(len(lists)):
		k=i-1

		while(k>=0):
			if(lists[i][0]==lists[k][0] or lists[i][1]==lists[k][1]):
				lists[i]=[1307,1307]
				break
			k=k-1
	n_lines-=1

	auxlist=[]
	for i in range(len(lists)):
		if(lists[i][0]!=1307):
			auxlist.append( lists[i])


	return auxlist[0:n_lines]
#simplex em si
def simplex(tableau):
	lines=round(tableau[0])
	n_columns=round(tableau[1])
	i=lines-1
	while(i<n_columns-1):
		aux=search_in_column(tableau,i)
		if(aux[0]=="invalida"): #coluna inválida,não pl 
			next
		else:
			if(aux[0]=="ilimitada"): #pl ilimitada
				certificado=solve_ilimited(tableau,i)
				return[ "ilimitada",certificado,tableau]
			else: #pivoteia a coluna que pode ser pivoteada
				mat=tableau[2]
				#print('\n'.join(str([str(round(mat[k][l], 3)) for l in range(len(mat[k]))]) for k in range(len(mat))))
				tableau=pivoteia(tableau,aux[1],i)
				i=lines-2
		i=i+1

	aux=solve_limited(tableau)
	return ["limitada",aux,tableau]


#dá um certificado de uma pl ilimitada dado um tableau com coluna problemática
def solve_ilimited(tableau,w):
	base=find_base(tableau)
	mat=tableau[2]
	n_lines=round(tableau[0])-1
	n_columns=round(tableau[1])-1-n_lines
	certificate=numpy.empty(n_columns)
	certificate.fill(0.0)
	certificate[w-n_lines]=1.0
	for i in range(len(base)):
		l=base[i][0]
		c=base[i][1]-n_lines
		certificate[c]=-mat[l][w]
	return certificate

#dá valor obj,solução e certificado de uma pl ok dado um tableau
def solve_limited(tableau):
	n_lines=tableau[0]-1
	n_columns=tableau[1]-1
	mat=tableau[2]
	solution=numpy.empty(n_columns-1)
	solution.fill(0.0)
	base=find_base(tableau)
	objective_value=mat[0][n_columns]
	for i in range(len(base)):
		l=base[i][0]
		c=base[i][1]-n_lines
		solution[c]=mat[l][n_columns]
	certificate=[]
	for i in range(0,n_lines):
		certificate.append(mat[0][i])

	return [objective_value,solution,certificate]
#dado uma coluna nova adicionada na pl auxiliar, retorna o índice do pivot pra deixar ela básica
def index_pivot_aux(tableau,c):
	n_lines=round(tableau[0])-1
	mat=tableau[2]
	for i in range(1,n_lines+1):
		if(mat[i][c]<=1.001 and mat[i][c]>=0.999):
			return i
	else:
		return 0
#faz um pré-pivoteamento na pl auxiliar, pra formar colunas básicas pra poder jogar no simplex
def init_pivot_aux(tableau):
	n_lines=round(tableau[0])-1
	n_columns=round(tableau[1])-1
	mat=tableau[2]
	init=n_columns-n_lines
	final=n_columns
	for i in range(init,final):
		a=index_pivot_aux(tableau,i)
		tableau=pivoteia(tableau,a,i)
	return tableau
	

#converte um tableau da pl auxiliar num tableau normal.
def turn_aux_ordinary(tableau,max_function):
	maxima=max_function
	maxima.append(0.0)
	n_lines=tableau[0]-1
	n_columns=tableau[1]
	matriz=tableau[2]
	for i in range(0,n_lines):
		maxima.insert(0,0.0)
	for i in range(len(maxima)):
		maxima[i]=-maxima[i]

	for i in range(0,n_lines+1):
		for j in range(0,n_lines):
			lena=len(matriz[i])
			matriz[i].pop(lena-2)

	matriz[0]=maxima
	n_columns=n_columns-n_lines
	n_lines=n_lines+1
	return[n_lines,n_columns,matriz]



filee = open(sys.argv[2],"w") 

pl=read_pl(sys.argv[1]) #lê a pl do arquivo
plfpi=turn_pl_into_fpi(pl) #transforma ela em fpi
max_function = copy.deepcopy(plfpi[2]) 
plaux=create_auxpl(plfpi) #cria a pl auxiliar
tableau=create_tableau(plaux) #clia o tableau da pl auxiliar
tableau=init_pivot_aux(tableau) # faz um pré pivoteamento pra achar as bases óbvias da pl auxiliar
# a pl auxiliar sempre é limitada, então não precisei fazer as devidas checagens 
resposta=simplex(tableau) #resolve a auxiliar
tableau=resposta[2] # captura o tableau resultante

plaux_objective_value=resposta[1][0] # valor objetivo
plaux_certificate=resposta[1][2] #certificado de otimalidade da pl aux é de inviabilidade da pl original 


#se o valor objetivo da pl auxiliar for diferente de 0, então a pl original é inviável 
if(not (plaux_objective_value<=0.001 and plaux_objective_value>=-0.001)):
	print("Status: inviavel")
	filee.write("Status: inviavel"+"\n")
	print("Certificado:")
	filee.write("Certificado"+"\n")
	print(plaux_certificate)
	filee.write(str(plaux_certificate))
	exit()

base=find_base(tableau) #acha as bases do tableau da pl auxiliar pra pre pivotear a pl original
#coloca a função máximo no novo tableau
tableau=turn_aux_ordinary(tableau,max_function)

ramb=tableau[2]



#faz o pré-pivoteamento pra poder ir pro simplex
for i in range(len(base)):
	tableau=pivoteia(tableau,base[i][0],base[i][1])




#joga no simplex
resposta=simplex(tableau)
if(resposta[0]=="ilimitada"):
	print("Status: ilimitada")
	filee.write("Status: ilimitada"+"\n")
	print("Certificado:")
	filee.write("Certificado:"+"\n")
	print(resposta[1])
	filee.write(str(resposta[1]))

else:
	print("Status: otimo")
	filee.write("Status: otimo"+"\n")
	print("Objetivo=%s" % (resposta[1][0]))
	filee.write("Objetivo=")
	filee.write(str(resposta[1][0])+"\n")
	print("Solucao:")
	filee.write("Solucao:"+"\n")
	print(resposta[1][1])
	filee.write(str(resposta[1][1])+"\n")
	print("Certificado:")
	filee.write("Certificado:"+"\n")
	print(resposta[1][2])
	filee.write(str(resposta[1][2]))






