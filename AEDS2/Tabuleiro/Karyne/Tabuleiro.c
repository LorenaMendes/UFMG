#include <stdlib.h>
#include <stdio.h>
#include "Tabuleiro.h"

void SetTamanho(Tabuleiro *T, int n){
	T->dimensao = n;
	T->caracter = malloc (T->dimensao * sizeof(char*));
	for(int i = 0; i < n; i++){
		T->caracter[i] = malloc(T->dimensao * sizeof(char));
	}
	return;
}

void SetElemento(Tabuleiro *T, int i, int j, char c){
	T->caracter[i][j] = c;
	return;
}

char GetElemento(Tabuleiro T, int i, int j){
	if(i < 0 || j < 0) return 'e';
	if(i >= T.dimensao || i >= T.dimensao) return 'e';
	return T.caracter[i][j];
}

void MarcaTodos(Tabuleiro *T, char c){
	int tam = T->dimensao;
	for(int i = 0; i < tam; i++){
        for (int j = 0; j < tam; ++j){
        	T->caracter[i][j] = c;
        }
    }
}

int TestaLinha(Tabuleiro T, int i, char c){
	for (int j = 0; j < T.dimensao; ++j){
		if(T.caracter[i][j] != c) return 0;
	} return 1;
}

int TestaColuna(Tabuleiro T, int j, char c){
	for (int i = 0; i < T.dimensao; ++i){
		if (T.caracter[i][j] != c) return 0;
	} return 1;
}

int TestaDiagonalED(Tabuleiro T, char c){
	for (int i = 0; i < T.dimensao; ++i){
		if(T.caracter[i][i] != c){
			return 0;
		}
	} return 1;
}

int TestaDiagonalDE(Tabuleiro T, char c){
	for (int i = 0; i < T.dimensao; ++i){
		if(T.caracter[i][T.dimensao-1-i] != c){
			return 0;
		}
	} return 1;
}

int TestaDiferente(Tabuleiro T, int i){
	for (int x = 0; x < T.dimensao; ++x){
		for (int j = 0; j < T.dimensao && x != j; ++j){
			if(T.caracter[i-1][x] == T.caracter[i-1][j]){
				return 0;
			}
		}
	} return 1;
}

void Imprime(Tabuleiro T){
	for (int i = 0; i < T.dimensao; ++i){
		printf("->| ");
		for (int j = 0; j < T.dimensao; ++j){
			printf("%c ", T.caracter[i][j]);
		}
		printf("|<-\n");
	}
}