#include "Tabuleiro.h"

#include <stdlib.h>
#include <stdio.h>

void Imprime(Tabuleiro T){ //print matrix
	int size = T.size;
	int i, j;
	for (i=0; i<size; ++i){
		printf("| ");
		for (j=0; j<size; ++j){
			printf("%c ", T.symbol[i][j]);
		}
		printf("|\n");
	}
}

void insertionSort(char * vetor, int tam){ //Function to sort an array using insertion sort
   	int i, key, j;
   	for (i = 1; i < tam; i++){
       	key = vetor[i];
       	j = i-1;
 
       //Move elements of vetor[0..i-1], that are greater than key, to one position ahead of their current position
      	while (j >= 0 && vetor[j] > key){
           	vetor[j+1] = vetor[j];
           	j = j-1;
       	}
       	vetor[j+1] = key;
   	}
}

void SetTamanho(Tabuleiro *T, int n){ //define matrix's size
	int i;
	T->size=n;
	T->symbol=(char**)malloc(sizeof(char*)*n);
	for(i=0; i<n; i++){
		T->symbol[i] = (char *)malloc(sizeof(char) * n);
	}
	return;
}

void SetElemento(Tabuleiro *T, int i, int j, char c){ //set a value in a specific position
	if(!(i>T->size || j>T->size || i<=0 || j<=0)){
		T->symbol[i-1][j-1] = c;
		return;
	} else {
		return;
	}
}

char GetElemento(Tabuleiro T, int i, int j){ //get an element from specific position 
	if(i>T.size || j>T.size || i<0 || j<0){
		return 'e'; //returning "e" means that the element to get doesn't exist
	} else {
		return T.symbol[i-1][j-1];
	}
}

void MarcaTodos(Tabuleiro *T, char c){ //set the entire matrix with the same symbol
	int i, j;
	for(i = 0; i < T->size; i++){
        for (j = 0; j < T->size; ++j){
        	T->symbol[i][j] = c;
        }
    }
}

int TestaLinha(Tabuleiro T, int i, char c){ //returns 1 if all the symbols in a row are different
	int y;
	if(i>T.size || i<=0) return 0;
	for (y = 0; y < T.size; ++y){
		if(T.symbol[i-1][y] != c){
			return 0;
		}
	}
	return 1;
}

int TestaColuna(Tabuleiro T, int j, char c){ //returns 1 if all symbols in a column are equal to a specific symbol
	int i;
	if(j>T.size || j<=0){
		return 0;
	}
	for (i = 0; i < T.size; ++i){
		if (T.symbol[i][j-1] != c){
			return 0;
		}
	}
	return 1;
}

int TestaDiagonalED(Tabuleiro T, char c){ //returns 1 if all the elements in ED diagonal are equal to a specific symbol
	int size = T.size;
	for (int i = 0; i < size; ++i){
		if(T.symbol[i][i] != c){
			return 0;
		}
	}
	return 1;
}

int TestaDiagonalDE(Tabuleiro T, char c){ //returns 1 if all the elements in DE diagonal are equal to a specific symbol
	int size = T.size;
	int i;
	for (i = 0; i < size; ++i){
		if(T.symbol[i][size-1-i] != c){
			return 0;
		}
	}
	return 1;
}

int TestaDiferente(Tabuleiro T, int i){ //returns 1 if all the symbols in a specific row are different
	if(i>T.size || i<=0) return 0;
	int j;
	char * vetor = (char*) malloc(T.size*sizeof(char));
	for (j = 0; j < T.size; ++j){
		vetor[j] = T.symbol[i-1][j];
	}
	insertionSort(vetor, T.size);
	for (j = 0; j < T.size-1; ++j){
		if(vetor[j] == vetor[j+1]){
			return 0;
		}
	}
	return 1;
}