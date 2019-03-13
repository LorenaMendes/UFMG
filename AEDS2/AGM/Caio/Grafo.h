struct GrafoAresta
{
	int vertice_a;
	int vertice_b;
	int valor;
};

struct GrafoVertice
{
	struct GrafoVertice * seg;
	struct GrafoVertice * ant;
	int id;
};

int AdicionaNaLista(struct GrafoAresta aresta, int numero_a, struct GrafoVertice * lista_de_adjacencias, int numero_v);
int FazBuscaEmProfundidade(struct GrafoVertice * lista_de_adjacencias, int vertice_a, int vertice_b);