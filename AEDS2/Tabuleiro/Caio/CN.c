#include "Tabuleiro.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void random_matrix(Tabuleiro * T, int size){ //creates a random matrix
	int i, j;
	srand(time(NULL)); // makes different sequencies when using rand()
	for (i = 0; i < size; ++i){
		for (j = 0; j < size; ++j){
			int random_number = rand() % (0,5); //it generates random numbers between 0 and 4
			char valor;
			if(random_number == 0){
				valor = '?';
			} else if(random_number == 1){
				valor = '*';
			} else if(random_number == 2){
				valor = '@';
			} else if(random_number == 3){
				valor = '%';
			} else if(random_number == 4){
				valor = '#';
			}

			SetElemento(T, i+1, j+1, valor); //insert symbol defined
		}
	}
}

void reads_file(Tabuleiro * T, int size, const char * file){ //reads a file to create a matriz
	FILE * arq = fopen(file, "r");
	char valor;
	int i, j;
	for (i = 0; i < size; ++i){
		for (j = 0; j < size; ++j){
			if(i == size-1){
				fscanf(arq, "%c\n", &valor);
			} else{
				fscanf(arq, "%c ", &valor);
			}
			SetElemento(T, i+1, j+1, valor);
		}
	}
}

int main(int argc, char const *argv[]){
	int matrix_size = atoi(argv[1]);
	int aux = 0;

	Tabuleiro * T = malloc(sizeof(Tabuleiro)); //creates a matrix
	SetTamanho(T, matrix_size); //set matrix size
	
	if(argc > 3){
		return 0;
	}

	if(argc == 2) { //input without file
		if(!(matrix_size%2)){
			printf("\nSize must be odd!\n\n");
			return 0;
		}
		random_matrix(T, matrix_size);
		Imprime(*T);
	}

	else { //input with file
		if(!(matrix_size%2)){
			printf("\nSize must be odd!\n\n");
			return 0;
		}
		reads_file(T, matrix_size, argv[2]);
		Imprime(*T);
	}

	if(TestaDiagonalED(*T, '*')||TestaDiagonalED(*T, '?')||TestaDiagonalED(*T, '@')||TestaDiagonalED(*T, '%')||TestaDiagonalED(*T, '#')) aux ++;
	if(TestaDiagonalDE(*T, '*')||TestaDiagonalDE(*T, '?')||TestaDiagonalDE(*T, '@')||TestaDiagonalDE(*T, '%')||TestaDiagonalDE(*T, '#')) aux ++;
	if(TestaDiferente(*T, (matrix_size/2)+1)) aux ++;

	if(aux){
		printf("\nBINGO!!!\n");
	} else{
		printf("\nTente outra vez...\n");
	}

	return 0;
}