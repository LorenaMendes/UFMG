#include "Servers.h"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

int sortstring (const void * a, const void * b){
	Server *A = (Server *)a;
	Server *B = (Server *)b;
	return ( B->degree - A->degree );
}

int main(){
	int num_servers, conections, i;
	scanf("%d\n", &num_servers);
	scanf("%d\n", &conections);

	Server * vec_servers = (Server *)malloc(num_servers * sizeof(Server));
	for(i=0; i<num_servers; i++) vec_servers[i].id = i+1;
	
	int s1, s2;
	for(i=0; i<conections; i++){
		scanf("%d %d", &s1, &s2);
		InsertConection(vec_servers, s1, s2);
		InsertConection(vec_servers, s2, s1);
	}
	qsort(vec_servers, num_servers, sizeof(Server), sortstring);
	FindColors(vec_servers, num_servers);
	Print(vec_servers, num_servers);

	return 0;
}