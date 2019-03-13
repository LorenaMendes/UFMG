#include "conexao.h"
#include <stdio.h>
#include <stdlib.h>

//cria uma lista de adjacências
Vertice * NovaLista(int tam){
	Vertice * new = (Vertice*)malloc(tam*sizeof(Vertice));
	for (int i = 0; i < tam; ++i){
		new[i].id = i;
		new[i].visitado = 0;
		new[i].prox = NULL;
	}
	return new;
}

//imprime uma lista de adjacências
void ImprimeAdj(Vertice * ajd, int vertices){
	Vertice * aux = malloc(sizeof(Vertice));
	for(int i=0; i<vertices; i++){
		aux = ajd[i].prox;
		printf("Vértice %d: ==> ", i);
		while(aux != NULL){
			printf(" %d", aux->id);
			aux = aux->prox;
		}
		printf("\n");
	}
}

int Pesquisa(Vertice * AGM, int destino, int origem, int tamanho) {
	int retorno = PesquisaInterna(AGM, destino, origem);
	LimpaPesquisa(AGM,tamanho);
	// printf("Resultado: %d -- ",retorno);
	return retorno;
}

int PesquisaInterna(Vertice * AGM, int destino, int origem) {
	// printf("===== Teste: %d e %d... =====\n",origem, destino);
	
	if(AGM[origem].visitado == 1) {
		return 0;
	} else { // se ja passou pelo vertice, aborta

		AGM[origem].visitado = 1; // se nao, marca o vertice como visitado

		int sucesso = 0;	// comecamos setando o retorno como pesquisa falhou.
							// se conseguirmos achar por algum no, setamos sucesso = 1
		
		Vertice * aux = AGM[origem].prox;
		Vertice * aux2 = aux;

		// Dividimos a pesquisa em duas etapas:
		// 1) vemos se o vertice destino eh filho do vertice atual.
		// se sim, ja retornamos verdadeiro.
		while(aux != NULL){
			if(aux->id == destino) return 1;
			else aux = aux->prox;
		}

		// 2) se nao, pesquisamos nos filhos. Se algum for sucesso, acabou.
		while(aux2 != NULL) {
			if(sucesso = PesquisaInterna(AGM,destino,AGM[aux2->id].id)) return sucesso;
			else aux2 = aux2->prox;
		}

		// Se nenhum dos filhos eh sucesso, retornamos aquele zero do inicio (que foi retornado por todos os filhos tambem).
		return sucesso;
	} 

}

//função para ordenar os vértices de acordo com o segundo
void OrdenaVertices(Aresta * vetor_inicial, int arestas) {
	Aresta *inicio_lista = vetor_inicial;
	Aresta *aux = vetor_inicial;
	int limite = 0, id_atual = 0, counter = 0;
	for (int j = 0; j <= arestas; ++j){
		if(aux[j].v1 != id_atual) {
			id_atual = aux[j].v1;
			//usa o qsort para ordenar parte da lista
			qsort(inicio_lista, counter, sizeof(Aresta), ComparaVertice);
			inicio_lista = &aux[j];
			counter = 0;
			
		}
		counter++;
	}
}

//função para imprimir as arestas e seus pesos
void ImprimeArestas(Aresta * lista, int arestas){
	printf("\nV1|V2|Peso\n");
	for (int i = 0; i < arestas; ++i){
		printf(" %d  %d  %d\n", lista[i].v1, lista[i].v2, lista[i].peso);
	}
}

//função usada no qsort para comparar os objetos
int Compara(const void *p, const void *q){
    int l = ((struct Aresta *)p)->peso;
    int r = ((struct Aresta *)q)->peso;
    return (l - r); 
}

//função usada no qsort para comparar os objetos
int ComparaVertice(const void *p, const void *q){
    int l = ((struct Aresta *)p)->v2;
    int r = ((struct Aresta *)q)->v2;
    return (l - r); 
}

void Insere(Vertice * lista_adj, Aresta E){
	//insere v1 em v2 e v2 em v1
	Add(lista_adj, E.v1, E.v2);
	Add(lista_adj, E.v2, E.v1);
}

void Add(Vertice * lista_adj, int v1, int v2){
	//crio um vértice auxiliar
	Vertice * aux = malloc(sizeof(Vertice));

	//crio um novo vértice com o valor do que é inserido
	Vertice * new = malloc(sizeof(Vertice));
	new->id = v2;
	new->prox = NULL;

	//o primeiro não tem filhos
	if(lista_adj[v1].prox == NULL){
		lista_adj[v1].prox = new;
		return;
	}

	//percorre a lista até chegar no último ponteiro
	aux = lista_adj[v1].prox;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	//adiciona o novo vértice
	aux->prox = new;
}

void LimpaPesquisa(Vertice * AGM, int tam){
	for (int i = 0; i < tam; ++i){
		AGM[i].visitado = 0;
	}
}

Aresta * GeraVetorAgm(Vertice * AGM, int vertices, Aresta * vetor_agm, int cont){
	int j = 0;
	for (int i = 0; i < vertices; ++i){
		Vertice * aux = AGM[i].prox;
		AGM[i].visitado = 1;
		while(aux != NULL){
			if(AGM[aux->id].visitado != 1){
				vetor_agm[j].v1 = i;
				vetor_agm[j].v2 = aux->id;
				vetor_agm[j].peso = 0;
				j++;
			} aux = aux->prox;
		}
	}
	return vetor_agm;
}

//define o peso de cada aresta
void DefinePeso(Aresta * vetor_inicial, int arestas, Aresta * vetor_agm, int tam){
	for (int i = 0; i < tam; ++i){
		vetor_agm[i].peso = BuscaPeso(vetor_inicial, arestas, vetor_agm[i]);
	}
}

//busca o peso de cada aresta no vetor inicial
int BuscaPeso(Aresta * vetor_inicial, int arestas, Aresta vertice){
	for (int i = 0; i < arestas; ++i){
		if((vetor_inicial[i].v1 == vertice.v1 || vetor_inicial[i].v1 == vertice.v2) &&
			(vetor_inicial[i].v2 == vertice.v1 || vetor_inicial[i].v2 == vertice.v2))
			return vetor_inicial[i].peso;
	}
}
