#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/*Função para inserir o vértice 2 na lista do vértice 1*/
void Insere(struct Vertice * lista_adjacencia, int vertice1, int vertice2, int peso){
	// printf("Inserindo %d e %d\n", vertice1, vertice2);
	
	/*Crio um novo vértice com os valores do que será inserido*/
	struct Vertice * novo = malloc(sizeof(struct Vertice));
	novo->filho = NULL;
	novo->pai = NULL;
	novo->peso_relativo = peso;
	novo->buscado = 0;
	novo->valor = vertice2;

	/*Se o vértice não tiver filhos, adiciono o novo lá*/
	if(lista_adjacencia[vertice1].filho == NULL){
		lista_adjacencia[vertice1].filho = novo;
		novo->pai = &lista_adjacencia[vertice1];
	}
	/*Se ele tiver, procuro entre seus filhos*/
	else {
		/*Crio vértices temporários para ajudar na inserção*/
		struct Vertice * temp1 = lista_adjacencia[vertice1].filho;
		struct Vertice * temp2 = &lista_adjacencia[vertice1];
		/*Insiro os novos vértices de maneira ordenada na lista de filhos*/
		while(temp1 != NULL){
			if(temp1->valor > novo->valor){
				/*Insiro o novo no lugar do temp1*/
				temp1->pai->filho = novo;
				novo->pai = temp1->pai;
				novo->filho = temp1;
				temp1->pai = novo;
				return;
			} else {
				temp1 = temp1->filho;
				temp2 = temp2->filho;
			}
		}
		temp2->filho = novo;
		novo->pai = temp2;
		return;
	}
}

/*############################### PARA TESTAR ######################################*/
//imprime uma lista de adjacências
void ImprimeAdj(struct Vertice * ajd, int vertices){
	/*cria um vértice temporário para ajudar a imprimir*/
	struct Vertice * temp1;
	for(int i=0; i<vertices; i++){
		temp1 = ajd[i].filho;
		printf("Vértice %d: ==> ", i);
		while(temp1 != NULL){
			printf(" %d", temp1->valor);
			temp1 = temp1->filho;
		}
		printf("\n");
	}
}
/*############################### PARA TESTAR ######################################*/

/*Função recursiva para descobrir se dois vértices pertencem à mesma árvore*/
int Busca(struct Vertice * lista_adjacencia, int vertice1, int vertice2){
	
	/*Retorna 0 se uma busca já tiver sido feita naquele vértice*/
	if(lista_adjacencia[vertice1].buscado == 1) return 0;
	/*caso contrário, marca o vértice como buscado e faz a busca*/
	else lista_adjacencia[vertice1].buscado = 1;
	
	int retorno = 0;

	/*Cria vértices temporários para ajudar na busca*/
	struct Vertice * temp1 = lista_adjacencia[vertice1].filho;
	struct Vertice * temp2 = lista_adjacencia[vertice1].filho;

	if(temp1 == NULL) return retorno;
	else{
		/*Percorre cada filho daquele vértice para ver se algum deles tem o mesmo id do procurado*/
		while(temp1 != NULL){
			//retorna 1 se encontrar e olha pro próximo se não encontrar
			if(temp1->valor == vertice2) return 1;
			temp1 = temp1->filho;
		}
		/*crio um temp2 para recomeçar a busca*/
		while(temp2 != NULL){
			/*chama a função recursivamente para cada filho daquele vértice*/
			int recursao = Busca(lista_adjacencia, temp2->valor, vertice2);
			/*se encontrar, retorna 1. Senão, pesquisa no próximo*/
			if(recursao) return recursao;
			else temp2 = temp2->filho;
		}
		return retorno;
	}
}

/*Esta função é usada pelo qsort para ordenar um vetor de struct pelo peso das arestas*/
int odenacao(const void *a, const void *b){
    int valor1 = ((struct Aresta *)a)->peso;
    int valor2 = ((struct Aresta *)b)->peso;
    return (valor1 - valor2); 
}