#include <stdlib.h>
#include <stdio.h>
#include "Tabuleiro.h"

// 1. Definir o tamanho do tabuleiro que vai ser utilizado
void SetTamanho(Tabuleiro *T, int n){
	T->dimensao = n;
	T->caracter = (char**)malloc(sizeof(char*) * n);
	for(int x = 0; x < n; x++) T->caracter[x] = (char*)calloc(n, sizeof(char));
	return;
}

// 2. Colocar um elemento c em uma posição (i,j) do tabuleiro.
void SetElemento(Tabuleiro *T, int i, int j, char c){
	if(i>T->dimensao || i<=0 || j<=0 || j>T->dimensao) return;
	else T->caracter[i-1][j-1] = c;
	return;
}

// 3. Recuperar o elemento de uma posição (i,j) o tabuleiro:
char GetElemento(Tabuleiro T, int i, int j){
	if(!(i>T.dimensao || i<0 || j<0 || j>T.dimensao)) return T.caracter[i-1][j-1];
	return '1';
}

// 4. Colocar um mesmo elemento c em todas as posições do tabuleiro.
void MarcaTodos(Tabuleiro *T, char c){
	for(int i = 0; i < T->dimensao; i++){
        for (int j = 0; j < T->dimensao; ++j) T->caracter[i][j] = c;
    }
}

// 5. Testar se uma linha i do tabuleiro possui todos os elementos iguais a c, retornando true (1) ou false (0)
int TestaLinha(Tabuleiro T, int i, char c){
	if(i>T.dimensao || i<=0) return 0;
	for (int x = 0; x < T.dimensao; ++x) if(!(T.caracter[i-1][x] == c)) return 0;
	return 1;
}

// 6. Testar se uma coluna j do tabuleiro possui todos os elementos iguais a c, retornando true (1) ou false (0)
int TestaColuna(Tabuleiro T, int j, char c){
	if(j>T.dimensao || j<=0) return 0;
	for (int x = 0; x < T.dimensao; ++x) if (!(T.caracter[x][j-1] == c)) return 0;
	return 1;
}

// 7. Testar se a diagonal esq-dir possui todos os elementos iguais a c, retornando true (1) ou false (0)
int TestaDiagonalED(Tabuleiro T, char c){
	int dimensao = T.dimensao;
	for (int i = 0; i < dimensao; ++i) if(!(T.caracter[i][i] == c)) return 0;
	return 1;
}

// 8. Testar se a diagonal dir-esq possui todos os elementos iguais a c, retornando true (1) ou false (0)
int TestaDiagonalDE(Tabuleiro T, char c){
	int dimensao = T.dimensao;
	for (int i = 0; i < dimensao; ++i) if(!(T.caracter[i][dimensao-1-i] == c)) return 0;
	return 1;
}

// Função que ordena por bubble sort
int OrdenaVetor(char * vetor, int tam){
	char temp;
	for(int i=1; i<tam; ++i){
        for(int j=0; j<(tam-i); ++j){
            if((int)vetor[j]>(int)vetor[j+1]){
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

// 9. Testar se uma linha i do tabuleiro possui todos os elementos diferentes, retornando true (1) ou false (0)
int TestaDiferente(Tabuleiro T, int i){
	if(i>T.dimensao || i<=0) return 0;
	char * vetor = (char*) malloc(T.dimensao*sizeof(char));
	//monto um vetor com os caracteres da linha em questão
	for (int x = 0; x < T.dimensao; ++x){
		vetor[x] = T.caracter[i-1][x];
	}
	//ordeno este vetor
	OrdenaVetor(vetor, T.dimensao);
	//pesquiso, a cada par de posições, se tem elemento igual
	for (int y = 0; y < T.dimensao-1; ++y) if(vetor[y] == vetor[y+1]) return 0;
	return 1;
}

// 10. Imprimir tabuleiro
void Imprime(Tabuleiro T){
	int dimensao = T.dimensao;
	for (int i=0; i<dimensao; ++i){
		for (int j=0; j<dimensao; ++j) printf(" %c ", T.caracter[i][j]);
		printf("\n");
	}
}