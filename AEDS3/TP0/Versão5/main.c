/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS
DEPARTAMENTO DE CIÊNCIA DA COMPUTAÇÃO
ALGORITMOS E ESTRUTURAS DE DADOS III
======================================
TP0: HIT DO VERÃO
ALUNA:			Lorena Mendes Peixoto
======================================

Módulo: main.c
*/

#include "ListaDeAdjacencia.h"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0


int main(){
	int num_pessoas, num_relacoes, i;
	scanf("%d %d", &num_pessoas, &num_relacoes);

	Pessoa * pessoa;
	pessoa = (Pessoa *) malloc(num_pessoas * sizeof(Pessoa));

	for (int i = 0; i < num_pessoas; ++i){
		pessoa[0].pesquisa = 0;
	}

	int * vetor_pessoas, lixo;
	vetor_pessoas = (int *) malloc (num_pessoas * sizeof(int)); 

	for(i=0; i<num_pessoas; i++){
		scanf("%d %d", &lixo, &vetor_pessoas[i]);
	}

	int p1, p2;
	for(i=0; i<num_relacoes; i++){
		scanf("%d %d", &p1, &p2);
		if(vetor_pessoas[p2-1] < 35 && vetor_pessoas[p1-1] < 35){
			Inserir_Relacao(pessoa, p1, p2, vetor_pessoas[p2-1]);
			Inserir_Relacao(pessoa, p2, p1, vetor_pessoas[p1-1]);
		}
	}	

	if(DEBUG) Imprimir_Lista(pessoa, num_pessoas);

	int primeira;
	scanf(" %d", &primeira);

	int cont = 0;
	ProcuraLista(pessoa, num_pessoas, primeira, &cont);
	printf("%d\n", cont);

	LiberaEspaco(pessoa, num_pessoas);
	
	// free(pessoa);
	// free(vetor_pessoas);

	return 0;
}