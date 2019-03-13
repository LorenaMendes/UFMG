#ifndef GRAFO
#define GRAFO

struct Aresta{
	int vertice1;
	int vertice2;
	int peso;
};

struct Vertice{
	struct Vertice * pai;
	struct Vertice * filho;
	int peso_relativo;
	int buscado;
	int valor;
};

struct Grafo{
	struct Aresta * arestas;
};

void Insere(struct Vertice * lista_adjacencia, int vertice1, int vertice2, int peso);
void ImprimeAdj(struct Vertice * ajd, int vertices);
int Busca(struct Vertice * lista_adjacencia, int vertice1, int vertice2);
int Busca2(struct Vertice * lista_adjacencia, int vertice1, int vertice2);
int Compara(const void *p, const void *q);

#endif