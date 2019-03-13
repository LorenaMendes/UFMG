#include <stdlib.h>
#include <stdio.h>
#include "Grafo.h"

void Ordena(struct GrafoAresta * vetor_de_arestas, int numero_a){
 	if (!numero_a) return;
 	int w;
 	struct GrafoAresta temp;
 	for (int i = 1; i < numero_a; i++){
 		temp = vetor_de_arestas[i];
 		for (w = i - 1; w >= 0 && temp.valor < vetor_de_arestas[w].valor; w--) vetor_de_arestas[w + 1] = vetor_de_arestas[w];
 		vetor_de_arestas[w + 1] = temp;
 	}
}

int main(int argc, char const *argv[]){
	const char * arquivo1 = argv[1];
	const char * arquivo2 = argv[2];
	//abre o arquivo de leitura
	FILE * leitura = fopen(arquivo1, "r");

	int numero_v;
	int numero_a;

	//lê a primeira linha do arquivo com num de arestas e de vértices]
	fscanf(leitura, "%d %d", &numero_v, &numero_a);

	//lê cada linha seguinte com os componentes de cada aresta
	struct GrafoAresta vetor_de_arestas[numero_a];
	for (int i = 0; i < numero_a; i++){
		fscanf(leitura, "%d ", &vetor_de_arestas[i].vertice_a);
		fscanf(leitura, "%d ", &vetor_de_arestas[i].vertice_b);
		fscanf(leitura, "%d ", &vetor_de_arestas[i].valor);
	}

	//ordena as arestas por seu valor
	Ordena(vetor_de_arestas, numero_a);

	//cria uma lista de adjacências
	struct GrafoVertice lista_de_adjacencias[numero_v];
	for (int i = 0; i < numero_v; i++) {
		lista_de_adjacencias[i].id = i;
		lista_de_adjacencias[i].seg = NULL;
	}

	for (int i = 0; i < numero_a; ++i) printf("%d %d %d\n", vetor_de_arestas[i].vertice_a, vetor_de_arestas[i].vertice_b, vetor_de_arestas[i].valor);

	for (int i = 0, cont = 0; i < numero_a; i++) if(AdicionaNaLista(vetor_de_arestas[i], numero_a, lista_de_adjacencias, numero_v)) cont++;

	fclose(leitura);
	return 0;
}