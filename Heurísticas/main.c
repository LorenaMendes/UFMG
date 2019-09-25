#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_NAME 25
#define MAX_AUX 100

int calcula_distancia_euc(float *coord_x, float *coord_y, int i, int j){
	float xd = coord_x[i] - coord_x[j];
	float yd = coord_y[i] - coord_y[j]; 
	return round(sqrt(xd*xd + yd*yd));
}

int calcula_distancia_pseudo_euc(float *coord_x, float *coord_y, int i, int j){
	float xd = coord_x[i] - coord_x[j];
	float yd = coord_y[i] - coord_y[j]; 
	float rij = sqrt((xd*xd + yd*yd)/10.0);
	return ceil(rij); //ve se ta certin 
}

void vizinho_mais_proximo_pseudo_euc(float *coord_x, float *coord_y, int *visitados, int inicial_total, int inicial_atual, int *custo, int dim){
	int distancia;
	int menor_distancia = 99999999;
	int melhor_indice = -1;

	for(int i = 0; i < dim; i++){
		if(!visitados[i]){
			distancia = calcula_distancia_pseudo_euc(coord_x, coord_y, inicial_atual, i);
			if(distancia < menor_distancia){
				menor_distancia = distancia;
				melhor_indice = i;
			}
		}
	}

	if(melhor_indice == -1){
		*custo += calcula_distancia_pseudo_euc(coord_x, coord_y, inicial_total, inicial_atual);  
	}
	else{
		*custo += menor_distancia;
		visitados[melhor_indice] = 1;
		vizinho_mais_proximo_pseudo_euc(coord_x, coord_y, visitados, inicial_total, melhor_indice, custo, dim);
	}
}

void vizinho_mais_proximo_euc(float *coord_x, float *coord_y, int *visitados, int inicial_total, int inicial_atual, int *custo, int dim){
	int distancia;
	int menor_distancia = 99999999;
	int melhor_indice = -1;

	for(int i = 0; i < dim; i++){
		if(!visitados[i]){
			distancia = calcula_distancia_euc(coord_x, coord_y, inicial_atual, i);
			if(distancia < menor_distancia){
				menor_distancia = distancia;
				melhor_indice = i;
			}
		}
	}

	if(melhor_indice == -1){
		*custo += calcula_distancia_euc(coord_x, coord_y, inicial_total, inicial_atual);
	}
	else{
		*custo += menor_distancia;
		visitados[melhor_indice] = 1;
		vizinho_mais_proximo_euc(coord_x, coord_y, visitados, inicial_total, melhor_indice, custo, dim);
	}
}

int main(){
	char name[MAX_NAME];
	char aux[MAX_AUX];
	int dim;
	char type[MAX_NAME]; 
	int id;

	scanf("%s", aux); // le name
	scanf("%s", name); // le o nome propriamente dito
	scanf("%s", aux); // le type
	scanf("%s", aux); // le tsp
	scanf("%s", aux); //le comment
	scanf("%[^\n]", aux); //le comment
	scanf("%s", aux); //le dimmension
	scanf("%d", &dim); // le o numero q eh o dimension
	scanf("%s", aux); // le o weight type
	scanf("%s", type); // le qual o tipo
	scanf("%s", aux); //le nome coord section

	float *coord_x = malloc(dim*sizeof(float)); 
	float *coord_y = malloc(dim*sizeof(float)); 

	for(int i = 0; i < dim; i++){
		scanf("%d", &id);
		scanf("%f", &coord_x[i]);
		scanf("%f", &coord_y[i]);
	}

	int *visitados = malloc(dim*sizeof(float));
	int melhor_custo = 9999999;

	if(strcmp(type, "EUC_2D") == 0){
		for(int i = 0; i < dim; i++){
			for(int j = 0; j < dim; j++){
				visitados[j] = 0;
			}
			visitados[i] = 1;
			int custo = 0;
			vizinho_mais_proximo_euc(coord_x, coord_y, visitados, i, i, &custo, dim);
			if(custo < melhor_custo) melhor_custo = custo;
		}
	}
	else{
		for(int i = 0; i < dim; i++){
			for(int j = 0; j < dim; j++){
				visitados[j] = 0;
			}
			visitados[i] = 1;
			int custo = 0;
			vizinho_mais_proximo_pseudo_euc(coord_x, coord_y, visitados, i, i, &custo, dim);
			if(custo < melhor_custo) melhor_custo = custo;
		}
	}
	printf("%d\n", melhor_custo);
}