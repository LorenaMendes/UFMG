#include "Servers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

Server * NewServer(int id){
	Server * new = (Server*)malloc(sizeof(Server));
	new->id = id;
	new->updated = 0;
	new->color = 0;
	new->degree = 0;
	new->next = NULL;
	return new;
}

void InsertConection(Server * vec_servers, int s1, int s2){
	Server * aux;
	//cria uma pessoa com as características da que será inserida
	Server * new = NewServer(s1);
	vec_servers[s2-1].degree ++;
	//se não tiver ninguém na lista, adiciona a nova ali
	if(vec_servers[s2-1].next == NULL) vec_servers[s2-1].next = new;
	else {
		aux = vec_servers[s2-1].next;
		vec_servers[s2-1].next = new;
		new->next = aux;
	}
}

void Print(Server * vec_servers, int num_servers){
	int i;
	Server * aux;
	if(DEBUG) printf("\n");
	for(i=1; i<=num_servers; i++){
		aux = vec_servers[i-1].next;
		if(DEBUG) printf("Server %d (Color %d, updated %d): ==> ", vec_servers[i-1].id, vec_servers[i-1].color, vec_servers[i-1].updated);
		while(aux != NULL){
			if(DEBUG) printf(" %d", aux->id);
			aux = aux->next;
		}
		if(DEBUG) printf("\n");
	}
}

int SearchColor(Server * vec_servers, int num_servers, int pos){
	if(DEBUG) printf("Pesquisando no vértice %d..\n", vec_servers[pos].id);
	Server * aux = vec_servers[pos].next;
	int color = 1;
	for (int i=0; i<vec_servers[pos].degree; i++){
		// int id = SearchVertex(vec_servers, num_servers,aux->id);
		int id = vec_servers[aux->id].pos;
		if(DEBUG) printf("Cor do %d: %d\n", vec_servers[id].id, vec_servers[id].color);
		if(vec_servers[id].color == color){
			if(DEBUG) printf("%d tem a cor %d\n", vec_servers[id].id, color);
			color++;
			aux = vec_servers[pos].next;
			i = -1;
			continue;
		}
		aux = aux->next;
	}
	if(DEBUG) printf("color vale %d\n", color);
	return color;
}

void ChangeColor(Server * vec_servers, int pos, int num_servers, int color){
	Server * aux = vec_servers[pos].next;
	for (int i=0; i<vec_servers[pos].degree; i++){
		int id = aux->id+1;
		if(!vec_servers[id].updated){
			vec_servers[id].color = color;
			if(DEBUG) printf("Colorindo %d de %d\n", vec_servers[id].id, color);
		}
		aux = aux->next;
	}
}

int FindColors(Server * vec_servers, int num_servers){
	int i, total = 0;
	for (i=0; i<num_servers; i++){
		char bul = vec_servers[i].updated ? ' ' : 'n';
		if(DEBUG) printf("\nEstou analisando o vértice %d.\nEle %c está atualizado\n", vec_servers[i].id, bul);
		if(!vec_servers[i].updated){
			int color = SearchColor(vec_servers, num_servers, i);
			// printf("color :%d >> %d\n", color,vec_servers[i].color);
			if(color > total) total = color;
			vec_servers[i].color = color;
			vec_servers[i].updated = 1;
			if(DEBUG) printf("Agora %d possui a cor %d\n", vec_servers[i].id, color);
			ChangeColor(vec_servers, i, num_servers, color);
		}
	} return total;
}

int SearchVertex(Server * vec_servers, int num_servers, int id){
	for (int i=0; i<num_servers; i++) if(vec_servers[i].id == id) return i;
}
void InsertPos(Server * vec_servers, int num_servers){
	for(int i=1;i<=num_servers;i++) vec_servers[i].pos = SearchVertex(vec_servers,num_servers,i);
}