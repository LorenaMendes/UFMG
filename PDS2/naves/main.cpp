#include <iostream>
#include <fstream>
#include <list>
#include "naves.hpp"
using namespace std;

int main(int argc, char const *argv[]){
	if(argc != 3){
		cout << "Parâmetros inválidos";
		return 0;
	}

	string entrada = argv[1];
	string saida = argv[2];

	int vertices, arestas;
	ifstream file;
	file.open(entrada);
	file >> vertices >> arestas;

	Grafo* grafo = new Grafo(vertices, arestas); 
	grafo->lista_vertices = (Vertice**) malloc (vertices*sizeof(Vertice*));

	for (int i = 0; i < vertices; ++i){
		Vertice* v = new Vertice(i+1);
		grafo->lista_vertices[i] = v;
	}
	
	int vertice1, vertice2;
	for (int i = 0; i < arestas; ++i){
		file >> vertice1 >> vertice2;

		Vertice* v1 = new Vertice(vertice1);
		Vertice* v2 = new Vertice(vertice2);

		grafo->InsereAresta(v1, v2);
	}

	int* dados = (int*) malloc (3*sizeof(int));
	int frigata = 0;
	int transportadora = 0;
	int bombardeiro = 0;
	int reconhecimento = 0;

	for (int i = 0; i < vertices; i++){
		if(grafo->lista_vertices[i]->visitado == false){
			dados = grafo->DSF(grafo->lista_vertices[i]->id);
			if(dados[2] == dados[1]) transportadora++;
			else if(dados[0] == 2) reconhecimento++;
			else if(dados[0] >= 3) frigata++;
			else bombardeiro++;
		}
	}

	// cout << reconhecimento << " " << frigata << " " << bombardeiro << " " << transportadora << endl;

	ofstream arquivo_out;
	arquivo_out.open(saida);
	arquivo_out << reconhecimento << " " << frigata << " " << bombardeiro << " " << transportadora << endl;

	file.close();
	arquivo_out.close();
	delete(dados);
	delete(grafo);
	return 0;
}