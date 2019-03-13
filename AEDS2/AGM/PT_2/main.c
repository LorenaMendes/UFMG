#include <stdio.h>
#include <stdlib.h>
#include "grafo.c"

int main(int argc, char const *argv[]){
	
	FILE * entrada = fopen(argv[1], "r");
	FILE * saida = fopen(argv[2], "w");
	
	/*Caso haja algum erro na leitura dos arquivos*/
	if(!entrada || !saida){
		printf("Erro nos arquivos! Certifique-se de que os arquivos existem e foram passador por parâmetro!\n");
		return 0;
	}

	/*Aqui, é feita a leitura do arquivo*/
	int num_vertices, num_arestas, vertice1, vertice2, peso;
	fscanf(entrada, "%d %d", &num_vertices, &num_arestas);
	
	/*Aqui, eu crio um vetor de arestas que vai conter todas as arestas com seus pesos*/
	struct Aresta vetor[num_arestas];
	int cont = 0;
	while(cont < num_arestas){
		fscanf(entrada, "%d %d %d", &vertice1, &vertice2, &peso);
		vetor[cont].vertice1 = vertice1;
		vetor[cont].vertice2 = vertice2;
		vetor[cont].peso = peso;
		cont++;
	}

	/*Aqui, eu ordeno o vetor de arestas pelo peso*/
	qsort(vetor, num_arestas, sizeof(struct Aresta), odenacao);

	struct Vertice lista_adjacencia[num_vertices];
	/*Aqui, será montado o grafo da árvore geradora mínima*/
	for (int i = 0; i < num_vertices; ++i){
		lista_adjacencia[i].filho = NULL;
		lista_adjacencia[i].peso_relativo = 0;
		lista_adjacencia[i].buscado = 0;
		lista_adjacencia[i].valor = i;
	}

	/*############################### PARA TESTAR ######################################*/
	for (int i = 0; i < num_arestas; ++i){
		printf("%d %d %d\n", vetor[i].vertice1, vetor[i].vertice2, vetor[i].peso);
	}
	/*############################### PARA TESTAR ######################################*/

	int insercao = 0;
	/*Primeiro, faço uma busca para ver se dois vértices são filhos do mesmo pai*/
	for (int i = 0; i < num_arestas; ++i){
		int existe = Busca(lista_adjacencia, vetor[i].vertice1, vetor[i].vertice2);
		for (int j = 0; j < num_vertices; ++j) lista_adjacencia[j].buscado = 0;
		if(existe == 0){
			insercao += 1;
			Insere(lista_adjacencia, vetor[i].vertice1, vetor[i].vertice2, vetor[i].peso);
			Insere(lista_adjacencia, vetor[i].vertice2, vetor[i].vertice1, vetor[i].peso);
		}
	}
	
	struct Aresta vetor_saida[insercao];
	for (int i = 0, j = 0; i < num_vertices; ++i){
		struct Vertice * temp1 = lista_adjacencia[i].filho;
		lista_adjacencia[i].buscado = 1;
		while(temp1 != NULL){
			if(lista_adjacencia[temp1->valor].buscado == 0){
				vetor_saida[j].vertice1 = i;
				vetor_saida[j].vertice2 = temp1->valor;
				vetor_saida[j].peso = temp1->peso_relativo;
				j++;
			} temp1 = temp1->filho;
		}
	}

	fprintf(saida, "%d %d\n", num_vertices, insercao);
	for (int i = 0; i < insercao; ++i) fprintf(saida, "%d %d %d\n", vetor_saida[i].vertice1, vetor_saida[i].vertice2, vetor_saida[i].peso);


	/*############################### PARA TESTAR ######################################*/
	ImprimeAdj(lista_adjacencia, num_vertices);
	/*############################### PARA TESTAR ######################################*/

	fclose(entrada);
	fclose(saida);

	return 0;
}