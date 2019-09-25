
# -*- coding: utf-8 -*-

import sys
import socket
import struct
import signal
from thread import *
import threading
import time
import select

#primeiro modelo de formato de entrada
def distance_of_the_cities(citya,cityb):
	x=float(citya[0])-float(cityb[0])
	y=float(citya[1])-float(cityb[1])
	return (x*x + y*y)**0.5

#outro modelo de entrada
def distance_of_the_cities_att(citya,cityb):
	x=float(citya[0])-float(cityb[0])
	y=float(citya[1])-float(cityb[1])
	return ((x*x + y*y)/10)**0.5


#dada uma cidade e uma lista de cidades, acha a cidade com menor distância da distância dada
def city_with_smaller_distance(city,cities):
	distance=[999999,0]
	for i in range(len(city[2])):
		if(city[2][i]<distance[0] and cities[i][3]==0):
			distance[0]=city[2][i]
			distance[1]=i
	return distance


f= open(sys.argv[1],"r")
cities=f.readlines()

for i in range(len(cities)):
	cities[i]=cities[i].split() #quebra a string por " ", por exemplo "o lobo morreu" vira ["o","lobo","morreu"]

cities.pop(len(cities)-1)
cities.pop(len(cities)-1)

for i in range(len(cities)):
	cities[i].pop(0)
	cities[i].append([])
	cities[i].append(0)

if(sys.argv[2]=="att"):
	for i in range(len(cities)):
		for j in range(len(cities)):
			cities[i][2].append(distance_of_the_cities_att(cities[i],cities[j]))
		cities[i][2][i]=9999999999
else:
	for i in range(len(cities)):
		for j in range(len(cities)):
			cities[i][2].append(distance_of_the_cities(cities[i],cities[j]))
		cities[i][2][i]=9999999999	


current_city=cities[0]
cities[0][+3]=1
soma=[0,1]

while(soma[1]<len(cities)): # dado que começou de uma cidade em específico, vou achando a cada iteração a cidade 
	distance=city_with_smaller_distance(current_city,cities) # com menor distância (guloso)
	soma[0]=soma[0]+distance[0]
	soma[1]=soma[1]+1
	current_city=cities[distance[1]]
	cities[distance[1]][3]=1

soma[0]=soma[0]+current_city[2][0]
print(soma)