#include <stdio.h>
#include <stdlib.h>

void converteParaBinario(float numero){
	int parteInteira = (int) numero, aux, vetor[9], i=0;
	float parteFracionaria = numero - parteInteira;
	printf("Número: %f\nParte inteira: %d\nParte fracionária: %f\n",numero,parteInteira,parteFracionaria);
	while(parteFracionaria || i<9){
		aux = (int) (parteFracionaria * 2);
		// printf("Aux vale %d\n", aux);
		parteFracionaria = (parteFracionaria * 2) - aux;
		// printf("Parte fracionária vale %f\n", parteFracionaria);
		vetor[i] = aux;
		i++;
	}
	printf("%d,\n", parteInteira);
	for(i=9; i>=0; i--){
		printf("%d", vetor[i]);
	}
}

int main(){
	float numero = 0.1;
	converteParaBinario(numero);
	return 0;
}