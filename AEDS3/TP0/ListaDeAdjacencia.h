/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS
DEPARTAMENTO DE CIÊNCIA DA COMPUTAÇÃO
ALGORITMOS E ESTRUTURAS DE DADOS II
======================================
TP0: HIT DO VERÃO
ALUNA:			Lorena Mendes Peixoto
======================================

Módulo: ListaDeAdjacencia.h

Este cabeçalho contém a declaração dos métodos do módulo ListaDeAdjacencia.c, bem
como a definição das estruturas a serem utilizadas nesse trabalho.
*/

#ifndef __LISTA_DE_ADJACENCIA__
#define __LISTA_DE_ADJACENCIA__

typedef struct pessoa{
	int id;
	int idade;
	int pesquisa;
} Pessoa;

typedef struct relacao{
	int tot_relacoes;
	struct relacao *prox;
	Pessoa fulano;
} Relacao;

void ProcuraLista(Relacao * lista, int tam_lista, Pessoa pessoa, int *cont);
void Imprimir_Lista(Relacao *lista, int num_pessoas);
void Inserir_Relacao(Relacao *lista, Pessoa a, Pessoa b);


#endif