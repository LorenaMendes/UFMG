#include <iostream>
#include <fstream>
#include <list>
using namespace std;

typedef struct Vertice{
	int id;
	struct Vertice* prox;
	bool visitado;

	Vertice(int id);
} Vertice;

typedef struct Grafo{
	int num_arestas;
	int num_vertices;
	int num_folhas;
	Vertice** lista_vertices;
	list<Grafo*> lista_naves;
	
	void InsereAresta(Vertice* v1, Vertice* v2);
	void Insere(Vertice* v1, Vertice* v2);
	int* DSF(int id);
	void ImprimeGrafo(int vs);
	void DSF_visit(int id);
	
	Grafo(int num_arestas, int num_vertices);
} Grafo;
