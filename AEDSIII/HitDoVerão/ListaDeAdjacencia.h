/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS
DEPARTAMENTO DE CIÊNCIA DA COMPUTAÇÃO
ALGORITMOS E ESTRUTURAS DE DADOS III
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
	struct pessoa *prox;
} Pessoa;

void LiberaEspaco(Pessoa *lista, int tam_lista);
void ProcuraLista(Pessoa * lista, int tam_lista, int pessoa, int *cont);
void Imprimir_Lista(Pessoa *lista, int num_pessoas);
void Inserir_Relacao(Pessoa *lista, int a, int b, int idade_b);


#endif