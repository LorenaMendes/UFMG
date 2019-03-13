#include "Servers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	// printf("Connecting %d to %d... \n", s1, s2);
	Server * aux;
	//cria uma pessoa com as características da que será inserida
	Server * new = NewServer(s1);
	vec_servers[s2].degree ++;
	//se não tiver ninguém na lista, adiciona a nova ali
	if(vec_servers[s2-1].next == NULL) vec_servers[s2-1].next = new;
	else {
		aux = vec_servers[s2-1].next;
		vec_servers[s2-1].next = new;
		new->next = aux;
	}
	// printf("Successfully connected!\n");
}

void Print(Server * vec_servers, int num_servers){
	int i;
	Server * aux;
	printf("\n");
	for(i=1; i<=num_servers; i++){
		aux = vec_servers[i-1].next;
		printf("Server %d (Color %d, updated %d): ==> ", i, vec_servers[i-1].color, vec_servers[i-1].updated);
		while(aux != NULL){
			printf(" %d", aux->id);
			aux = aux->next;
		}
		printf("\n");
	}
}

int SearchColor(Server * vec_servers, int pos){
	printf("Pesquisando no vértice %d..\n", vec_servers[pos].id);
	Server * aux;
	printf("pos vale %d\n", vec_servers[pos].id);
	aux = vec_servers[pos].next;
	printf("aux vale %d\n", aux->id);
	int color = 1;
	for (int i=0; i<vec_servers[pos].degree; i++){
		printf("A cor do %d é %d\n", vec_servers[aux->id-1].id, vec_servers[aux->id-1].color);
		if(vec_servers[aux->id].color == color){
			color++;
			aux = vec_servers[pos].next;
			i = -1;
			break;
		}
		aux = aux->next;
	}
	printf("color vale %d\n", color);
	return color;
}

void ChangeColor(Server * vec_servers, int pos, int color){
	Server * aux = vec_servers[pos].next;
	for (int i=0; i<vec_servers[pos].degree; i++){
		if(!vec_servers[aux->id].updated) vec_servers[aux->id].color = color;
	}
}

int FindColors(Server * vec_servers, int num_servers){
	int i;
	for (i=0; i<num_servers; i++){
		printf("\nEstou analisando o vértice %d\n", vec_servers[i].id);
		if(!vec_servers[i].updated){
			printf("%d não está atualizado\n", vec_servers[i].id);
			printf("chamando a função SearchColor passando a posição %d\n", i);
			int color = SearchColor(vec_servers, i);
			vec_servers[i].color = color;
			vec_servers[i].updated = 1;
			ChangeColor(vec_servers, i, color);
			// printf("A cor do %d é %d\n", vec_servers[i].id, vec_servers[i].color);
		}
	}
}