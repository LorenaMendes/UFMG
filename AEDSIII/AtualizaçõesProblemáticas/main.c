#include "Servers.h"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

int sort_by_degree (const void * a, const void * b){
	Server *A = (Server *)a;
	Server *B = (Server *)b;
	return (B->degree - A->degree);
}

int sort_by_id (const void * a, const void * b){
	Server *A = (Server *)a;
	Server *B = (Server *)b;
	return (A->id - B->id);
}

int main(){
	int num_servers, conections;
	scanf("%d\n", &num_servers);
	scanf("%d\n", &conections);

	Server * vec_servers = (Server *)malloc(num_servers * sizeof(Server));
	for(int i=0; i<num_servers; i++) vec_servers[i].id = i+1;
	
	int s1, s2;
	for(int i=0; i<conections; i++){
		scanf("%d %d", &s1, &s2);
		InsertConection(vec_servers, s1, s2);
		InsertConection(vec_servers, s2, s1);
	}
	qsort(vec_servers, num_servers, sizeof(Server), sort_by_degree);
	InsertPos(vec_servers, num_servers);
	Print(vec_servers, num_servers);
	
	FILE * rodada = fopen("rodada.txt", "w");
	fprintf(rodada, "%d", FindColors(vec_servers, num_servers));
	fclose(rodada);

	qsort(vec_servers, num_servers, sizeof(Server), sort_by_id);
	FILE * alocacao = fopen("alocacao.txt", "w");
	for (int i=0; i<num_servers; i++) fprintf(alocacao, "%d %d\n", vec_servers[i].id, vec_servers[i].color);		
	fclose(alocacao);

	Print(vec_servers, num_servers);
	return 0;
}