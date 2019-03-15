#include <stdio.h>
#include <stdlib.h>

void analisa_loop(int * vetor, int tam){
	int i, crista=0, vale=0;
	for(i=0; i<tam; i++){
		if(!i){
			if(vetor[tam-1]<vetor[i] && vetor[i+1]<vetor[i]) crista++; 
			else if(vetor[tam-1]>vetor[i] && vetor[i+1]>vetor[i]) vale++;
		}
		else if(i == tam-1){
			if(vetor[i-1]<vetor[i] && vetor[0]<vetor[i]) crista++; 
			else if(vetor[i-1]>vetor[i] && vetor[0]>vetor[i]) vale++;
		}
		else{
			if(vetor[i-1]<vetor[i] && vetor[i+1]<vetor[i]) crista++; 
			else if(vetor[i-1]>vetor[i] && vetor[i+1]>vetor[i]) vale++;
		}
	}
	printf("%d\n", crista + vale);
}

int main(){
	int *vetor, i, num_casos, nota_musical;
	do{
		scanf("%d", &num_casos);
		vetor = (int *) malloc(num_casos*sizeof(int));
		if(!num_casos) break;
		for(i=0; i<num_casos; i++){
			scanf("%d", &nota_musical);
			vetor[i] = nota_musical;
		}
		analisa_loop(vetor, num_casos);
	}while(num_casos);
	free(vetor);
	return 0;
}