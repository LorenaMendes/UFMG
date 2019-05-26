#ifndef __LISTA_DE_ADJACENCIA__
#define __LISTA_DE_ADJACENCIA__

typedef struct vertice{
	int id;
	int pesquisa;
	struct vertice *prox;
} Pessoa;

void LiberaEspaco(Pessoa *lista, int tam_lista);
void ProcuraLista(Pessoa * lista, int tam_lista, int vertice, int *cont);
void Imprimir_Lista(Pessoa *lista, int num_pessoas);
void Inserir_Relacao(Pessoa *lista, int a, int b, int idade_b);


#endif