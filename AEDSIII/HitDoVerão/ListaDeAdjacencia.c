/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS
DEPARTAMENTO DE CIÊNCIA DA COMPUTAÇÃO
ALGORITMOS E ESTRUTURAS DE DADOS III
======================================
TP0: HIT DO VERÃO
ALUNA:			Lorena Mendes Peixoto
======================================

Módulo: ListaDeAdjacencia.c
*/

#include "ListaDeAdjacencia.h"
#include <stdio.h>
#include <stdlib.h>

//função para desalocar cada vértice do grafo
void LiberaEspaco (Pessoa *lista, int tam_lista) {
	int i; 
	for (i = 0; i < tam_lista; i++) {
		Pessoa *aux1 = lista[i].prox;
		Pessoa *aux2;
		//filtra o caso em que lista.prox é NULL e que lista.prox não é NULL mas o seguinte é
		while (aux1 && aux1->prox) {
			aux2 = aux1;
			aux1 = aux1->prox;
			//desaloca um nó do grafo
			free(aux2);
		}
	}
}

void ProcuraLista(Pessoa * lista, int tam_lista, int pessoa, int *cont){
	//recebo a pessoa inicial
	if(lista[pessoa].pesquisa == 1) return;

	*cont = *cont + 1;
	lista[pessoa].pesquisa = 1;


	//se a pessoa não tiver relações, retorno 0  
	if(lista[pessoa-1].prox == NULL) return;
	//se a pessoa tiver ao menos uma relação, crio uma variável contendo a célula da primeira pessoa que se relaciona com a pessoa inicial
	Pessoa * tmp;
	tmp = lista[pessoa-1].prox;
	//enquanto ainda houver relação
	while(tmp != NULL){
		//pesquiso nas relações da pessoa apontada por tmp
		ProcuraLista(lista, tam_lista, tmp->id, cont);
		tmp = tmp->prox;
	}
	return;
}

void Imprimir_Lista(Pessoa *lista, int num_pessoas){
	int i;
	Pessoa *tmp;
	for(i=1; i<=num_pessoas; i++){
		tmp = lista[i-1].prox;
		printf("Pessoa %d: ==> ", i);
		while(tmp != NULL){
			printf(" %d (%d anos)", tmp->id, tmp->idade);
			tmp = tmp->prox;
		}
		printf("\n");
	}
}

void Inserir_Relacao(Pessoa *lista, int a, int b, int idade_b){
	Pessoa * ant;
	Pessoa * seg;
	Pessoa * nova;
	
	//cria uma pessoa com as características da que será inserida
	nova = (Pessoa*) malloc((int)sizeof(Pessoa));
	nova->prox = NULL;
	nova->id = b;
	nova->idade = idade_b;
	nova->pesquisa = 0;

	//se não tiver ninguém na lista, adiciona a nova ali
	if(lista[a-1].prox == NULL){
		lista[a-1].prox = nova;
	} else {
		ant = lista[a-1].prox;
		seg = ant->prox;

		if(seg == NULL){
			if(ant->id < b){
				ant->prox = nova;
				return;
			} else {
				seg = ant;
				lista[a-1].prox = nova;
				nova->prox = seg;
				return;
			}
		}
		//percorre a lista até a seguinte ser NULL ou maior que a nova e faz a inserção
		while(seg->prox != NULL && seg->prox->id < b){
			ant = ant->prox;
			seg = seg->prox;
		}
		ant = ant->prox;
		seg = seg->prox;
		ant->prox = nova;
		nova->prox = seg;
	}
}