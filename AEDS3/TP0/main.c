#include "ListaDeAdjacencia.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	int num_pessoas, num_relacoes, i;
	scanf("%d %d", &num_pessoas, &num_relacoes);

	Relacao * nova;
	nova = (Relacao*) malloc(2 * num_relacoes * sizeof(Relacao));
	Pessoa * pessoa;
	pessoa = (Pessoa *) malloc(num_pessoas * sizeof(Pessoa));

	for(i=0; i<num_pessoas; i++){
		scanf("%d %d", &pessoa[i].id, &pessoa[i].idade);
		pessoa[i].pesquisa = 0;
		nova[i].tot_relacoes = 0;
		nova[i].prox = NULL;
	}

	int p1, p2;
	for(i=0; i<num_relacoes; i++){
		scanf("%d %d", &p1, &p2);
		Inserir_Relacao(nova, pessoa[p1-1], pessoa[p2-1]);
		Inserir_Relacao(nova, pessoa[p2-1], pessoa[p1-1]);
	}	

	// Imprimir_Lista(nova, num_pessoas);

	Pessoa primeira;
	scanf(" %d", &primeira.id);

	int cont = 0;
	ProcuraLista(nova, num_pessoas, primeira, &cont);
	printf("%d\n", cont);

	return 0;
}