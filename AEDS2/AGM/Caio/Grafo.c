#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int AdicionaNaLista(struct GrafoAresta aresta, int numero_a, struct GrafoVertice * lista_de_adjacencias, int numero_v){
	int pesquisa = FazBuscaEmProfundidade(lista_de_adjacencias, aresta.vertice_a, aresta.vertice_b);
	if(pesquisa){
		Insere(lista_de_adjacencias, aresta.vertice_a, aresta.vertice_b, aresta.valor);
		Insere(lista_de_adjacencias, aresta.vertice_b, aresta.vertice_a, aresta.valor);
		return 1;
	} else return 0;
}

// int FazBuscaEmProfundidade(struct GrafoVertice * lista_de_adjacencias, int vertice_a, int vertice_b){
// 	if(lista_de_adjacencias[vertice_a].seg == NULL)
// 	else printf("não nulo\n");
// 	return 0;
// }

void Insere(lista_de_adjacencias, int vertice_a, int vertice_b, int valor){
	struct GrafoVertice * inserido = malloc(sizeof(struct GrafoVertice));
	inserido->id = vertice_b;
	inserido->valor = valor;
	inserido->seg = NULL;

	if(lista_de_adjacencias[vertice_a].seg == NULL)
}