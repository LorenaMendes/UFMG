#include "ListaDeAdjacencia.hpp"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0


int main(int argc, char const *argv[]){
	int vertices, arestas, i;

	const char* entrada = argv[1];
	const char* saida = argv[2];

	ifstream file;
	file.open(entrada);
	file >> vertices >> arestas;

	Vertice * vertice;
	vertice = (Vertice *) malloc(vertices * sizeof(Vertice));

	for (int i = 0; i < vertices; ++i){
		vertice[0].pesquisa = 0;
	}

	int * vetor_vertices, lixo;
	vetor_vertices = (int *) malloc (vertices * sizeof(int)); 

	int vertice1, vertice2;
	for (int i = 0; i < arestas; ++i){
		file >> vertice1 >> vertice2;

		Inserir_Relacao(vertice, vertice1, vertice2, vetor_vertices[vertice2-1]);
		Inserir_Relacao(vertice, vertice2, vertice1, vetor_vertices[vertice1-1]);
	}

	if(DEBUG) Imprimir_Lista(vertice, vertices);

	// int primeira;
	// scanf(" %d", &primeira);

	// int cont = 0;
	// ProcuraLista(vertice, vertices, primeira, &cont);
	// printf("%d\n", cont);

	// LiberaEspaco(vertice, vertices);
	
	// free(vertice);
	// free(vetor_vertices);

	return 0;
}