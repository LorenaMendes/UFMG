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
#define DEBUG 1

void ProcuraLista(Relacao * lista, int tam_lista, Pessoa pessoa, int *cont){
	// if(DEBUG == 1) printf("Visitando a lista da pessoa %d\n", pessoa.id);
	//recebo a pessoa inicial
	if(pessoa.pesquisa == 1){
		//se eu já tiver pesquisado nessa pessoa, retorno 0
		// if(DEBUG == 1) printf("A pesquisa já foi feita aqui\n");
		return;
	}

	*cont = *cont + 1;
	//essa pessoa passa ser uma já pesquisada
	int i;
	Relacao * aux;
	//em cada item da lista, procuro por essa pessoa e a marco como pesquisada
	for(i=1; i<=tam_lista; i++){
		aux = lista[i].prox;
		while(aux != NULL){
			if(aux->fulano.id == pessoa.id){
				aux->fulano.pesquisa = 1;
				break;
			}
			// printf("%d não é a pessoa que quero marcar\n", aux->fulano.id);
			aux = aux->prox;
		}
		// printf("Acabei de pesquisar nessa lista\n");
	}

	//se a pessoa não tiver relações, retorno 0  
	if(lista[pessoa.id].tot_relacoes == 0){
		// if(DEBUG == 1) printf("A pessoa %d não tem relações\n", pessoa.id);
		return;
	}
	//se a pessoa tiver ao menos uma relação
	else{
		//crio uma variável contendo a célula da primeira pessoa que se relaciona com a pessoa inicial
		Relacao * tmp;
		tmp = lista[pessoa.id].prox;
		//enquanto ainda houver relação
		while(tmp != NULL){
			//pesquiso nas relações da pessoa apontada por tmp
			if(tmp->fulano.idade < 35)
				ProcuraLista(lista, tam_lista, tmp->fulano, cont);// printf("a pesquisa de %d é %d\n", tmp->fulano.id, tmp->fulano.pesquisa);
			tmp = tmp->prox;
		}
	}
}

void Imprimir_Lista(Relacao *lista, int num_pessoas){
	int i;
	Relacao *tmp;
	for(i=1; i<num_pessoas; i++){
		tmp = lista[i].prox;
		// if(DEBUG == 1) printf("Pessoa %d: (%d relações) ==> ", i, lista[i].tot_relacoes);
		while(tmp != NULL){
			// if(DEBUG == 1) printf(" %d (%d anos)", tmp->fulano.id, tmp->fulano.idade);
			tmp = tmp->prox;
		}
		printf("\n");
	}
}

void Inserir_Relacao(Relacao *lista, Pessoa a, Pessoa b){
	Relacao * ant;
	Relacao * seg;
	Relacao * nova;
	
	nova = (Relacao*) malloc((int)sizeof(Relacao));
	nova->prox = NULL;
	nova->fulano.id = b.id;
	nova->fulano.idade = b.idade;

	lista[a.id].tot_relacoes++;
	if(lista[a.id].prox == NULL){
		lista[a.id].prox = nova;
	} else {
		ant = lista[a.id].prox;
		seg = ant->prox;

		if(seg == NULL){
			if(ant->fulano.id < b.id){
				ant->prox = nova;
				return;
			} else {
				seg = ant;
				lista[a.id].prox = nova;
				nova->prox = seg;
				return;
			}
		}
		while(seg->prox != NULL && seg->prox->fulano.id < b.id){
			ant = ant->prox;
			seg = seg->prox;
		}
		ant = ant->prox;
		seg = seg->prox;
		ant->prox = nova;
		nova->prox = seg;
	}
}