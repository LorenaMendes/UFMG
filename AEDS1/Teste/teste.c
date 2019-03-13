#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
int main(){
	char *nome=(char*)malloc(MAX*sizeof(char));
	FILE *arq;
	arq = fopen("teste.txt","r");
	if(arq == NULL) printf("ERRO!\n"); 
	fgets(nome,MAX,arq);
	puts(nome);
	return 0;
}
