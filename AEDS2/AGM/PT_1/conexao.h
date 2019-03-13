#ifndef __conexoes__
#define __conexoes__


typedef struct Vertice{
	int id;
	int visitado;
	struct Vertice * prox;
} Vertice;

typedef struct Aresta{
	int v1;
	int v2;
	int peso;
} Aresta;

Vertice * NovaLista(int tam);
void ImprimeAdj(Vertice * ajd, int vertices);
void OrdenaVertices(Aresta * vetor_inicial, int arestas);
void ImprimeArestas(Aresta * lista, int arestas);
int Compara(const void *p, const void *q);
int ComparaVertice(const void *p, const void *q);
void Insere(Vertice * adjacencia_lista, Aresta E);
void Add(Vertice * lista_adj, int v1, int v2);
int Pesquisa(Vertice * AGM, int v1, int v2, int tamanho);
int PesquisaInterna(Vertice * AGM, int v1, int v2);
void LimpaPesquisa(Vertice * AGM, int tam);
Aresta * GeraVetorAgm(Vertice * AGM, int vertices, Aresta * vetor_agm, int cont);
void DefinePeso(Aresta * vetor_inicial, int arestas, Aresta * vetor_agm, int tam);
int BuscaPeso(Aresta * vetor_inicial, int arestas, Aresta vertice);

#endif
