#include <iostream>
#include <fstream>
#include <list>
#include "naves.hpp"
using namespace std;

int num_arestas = 0;
int num_vertices = 0;
int num_folhas = 0;

Grafo::Grafo(int num_arestas, int num_vertices){
	this->num_vertices = num_vertices;
	this->num_arestas = num_arestas;
	this->num_folhas = 0;
}

void Grafo::ImprimeGrafo(int vs){
	cout << "LISTA DE ADJACÊNCIAS ------------------" << endl;
	Vertice* aux;
	for (int i = 0; i < vs; i++){
		cout << this->lista_vertices[i]->id << "--> ";
		aux = this->lista_vertices[i]->prox;
		while(aux != NULL){
			cout << aux->id << " ";
			aux = aux->prox;
		}
		cout << endl;
	}
	cout << "---------------------------------------" << endl;
}

void Grafo::InsereAresta(Vertice* v1, Vertice* v2){
	this->Insere(v1, v2);
	this->Insere(v2, v1);
}

// insere v1 na lista de v2
void Grafo::Insere(Vertice* v1, Vertice* v2){
	Vertice* aux = this->lista_vertices[(v2->id)-1]->prox;
	if(aux == NULL){
		this->lista_vertices[(v2->id)-1]->prox = v1;
	} else if (aux->id > v1->id) {
		this->lista_vertices[(v2->id)-1]->prox = v1;
		v1->prox = aux;
	} else {
		Vertice* aux2 = aux->prox;
		if(aux2 == NULL) aux->prox = v1;
		else{
			while (aux2) {
				if (aux2->id > v1->id) {
					aux->prox = v1;
					v1->prox = aux2;
					return;
				}
				aux = aux->prox;
				aux2 = aux2->prox;
			}
			aux->prox = v1;
		}
	}
}

int* Grafo::DSF(int id){
	
	num_arestas = num_vertices = num_folhas = 0;
	this->DSF_visit(id);

	int* dados = (int*) malloc (3*sizeof(int));
	dados[0] = num_folhas;
	dados[1] = num_arestas/2;
	dados[2] = num_vertices;
	
	num_arestas = num_vertices = num_folhas = 0;
	
	return dados;
}

void Grafo::DSF_visit(int id){

	// retorna se já tiver visitado aquele vértice
	Vertice * it = this->lista_vertices[id-1];
	if(it->visitado == true) return;
	
	// se ainda não tiver visitado, visita e o marca como visitado
	else{
		num_vertices++;
		it->visitado = true;
	}
	
	if(it->prox->prox == NULL){
		num_folhas++;
	}
	
	Vertice* filho = it->prox;
	while(filho){
		num_arestas++;
		DSF_visit(filho->id);
		filho = filho->prox;
	}
}

Vertice::Vertice(int id){
	this->id = id;
	this->prox = NULL;
	this->visitado = false;
}