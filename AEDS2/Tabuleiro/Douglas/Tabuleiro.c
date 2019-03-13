#include "Tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void SetTamanho(Tabuleiro *T, int n){
	T->lado=n;
}

void SetElemento(Tabuleiro *T, int i, int j, char c){
	if(i>=T->lado||j>=T->lado||i<0||j<0){
		printf("tem erro\n");
		return;
	}
	T->caracteres[i][j]=c;
}

char GetElemento(Tabuleiro T, int i, int j){
	if(i>=T.lado||j>=T.lado||i<0||j<0) return 'y';
	else return T.caracteres[i][j];
}

void MarcaTodos(Tabuleiro *T, char c){
	int i,j;
	for(i=0;i<T->lado;i++)
		for(j=0;j<T->lado;j++)
			T->caracteres[i][j]=c;
}

int TestaLinha(Tabuleiro T, int i, char c){
	int k;
	if(i>=T.lado||i<0) return -1;
	for(k=0;k<T.lado;k++){
		if(!(T.caracteres[i][k]==c)) return 0;
	}
	return 1;
}

int TestaColuna(Tabuleiro T, int j, char c){
	int k;
	if(j>=T.lado||j<0) return -1;
	for(k=0;k<T.lado;k++){
		if(!(T.caracteres[k][j]==c)) return 0;
	}
	return 1;
}

int TestaDiagonalED(Tabuleiro T, char c){
	int k;
	for(k=0;k<T.lado;k++){
		if(!(T.caracteres[k][k]==c)) return 0;
	}
	return 1;
}

int TestaDiagonalDE(Tabuleiro T, char c){
	int k;
	for(k=T.lado-1;k>=0;k--){
		if(!(T.caracteres[k][T.lado-k-1]==c)) return 0;
	}
	return 1;
}

int TestaDiferente(Tabuleiro T, int i){
	int k,j;
	for (k=0;k<T.lado;k++){
		for(j=0;j<T.lado;j++){
			if(k==j) j++;
			if(T.caracteres[i][k]==T.caracteres[i][j]) return 0;
		}
	}
	return 1;
}

void Imprime(Tabuleiro T){
	int i,j;
	for(i=0;i<T.lado;i++){
		for(j=0;j<T.lado;j++)
			printf("%c ", T.caracteres[i][j]);
		printf("\n");
	}
}