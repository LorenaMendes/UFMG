#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tabuleiro.h"
#define DEBUG 0

void GeraTabuleiroAleatorio(Tabuleiro * T, int tamanho);
void GeraTabuleiroPorArquivo(Tabuleiro * T, int tamanho, const char * arquivo);

int main(int argc, char const *argv[]){
	if(DEBUG) printf("Argumentos: %d.\n------------------\n", argc);
	for (int i = 0; i < argc; i++) if(DEBUG) printf("Argumento %d: %s\n", i, argv[i]);
	
	//cria um objeto do tipo tabuleiro
	Tabuleiro * T = malloc(sizeof(Tabuleiro));
	SetTamanho(T, atoi(argv[1])); //define sua dimensão com  valor passado por parâmetro
	
	//confere se não há problema de parâmetros a mais
	if(argc > 3){
		printf("### ERRO NOS PARÂMETROS! ###\nDigite o tamanho da matriz e,\nse desejar, o nome do arquivo de entrada.\n");
		return 0;
	}

	//caso em que não tem arquivo
	if(argc == 2) {
		if(!(atoi(argv[1])%2)){
			printf("\nO tamanho do tabuleiro deve ser ímpar.\n\n");
			return 0;
		}
		if(DEBUG) printf("Deve gerar aleatório.\n");
		GeraTabuleiroAleatorio(T, atoi(argv[1]));
		Imprime(*T);
	}

	//caso em que há arquivo
	else {
		if(DEBUG) printf("Deve pegar do arquivo.\n");
		GeraTabuleiroPorArquivo(T, atoi(argv[1]), argv[2]);
		Imprime(*T);
	}

	int casos = 0;

	//confere se os elementos da diagonal ED são iguais
	if( TestaDiagonalED(*T, '#') || TestaDiagonalED(*T, '@') || 
		TestaDiagonalED(*T, '%') || TestaDiagonalED(*T, '?') || 
		TestaDiagonalED(*T, '*')) casos ++;

	//confere se os elementos da diagonal DE são iguais
	if( TestaDiagonalDE(*T, '#') || TestaDiagonalDE(*T, '@') || 
		TestaDiagonalDE(*T, '%') || TestaDiagonalDE(*T, '?') || 
		TestaDiagonalDE(*T, '*')) casos ++;

	//confere se os elementos da linha central são iguais
	if(TestaDiferente(*T, (atoi(argv[1]))/2+1)) casos ++;

	//se alguma das condições foi atendida, imprime "bingo"
	if(casos) printf("\n Bingo!!!\n");
	//se não, imprime "tente outra vez"
	else printf("\n Tente outra vez...\n");

	return 0;
}

void GeraTabuleiroAleatorio(Tabuleiro * T, int tamanho){
	//faz com que cada sequência gerada pela rand() seja diferente
	srand(time(NULL));
	int cont = 0;
	for (int i = 0; i <= tamanho; ++i){
		//i volta para a primeira coluna e incrementa o contador de linhas
		if(i == tamanho) i = 0, cont ++;

		// gerando valores aleatórios entre zero, inclusive, e 5
		int num_rand = rand() % 5;
		char valor;
		//associa um número a um caractere
		switch(num_rand){
			case 0: valor = '#'; break;
			case 1: valor = '@'; break;
			case 2: valor = '%'; break;
			case 3: valor = '?'; break;
			case 4: valor = '*'; break;
		}
		//coloca o caractere em questão na posição atual
		SetElemento(T, cont+1, i+1, valor);
		//termina o processo quando chega na última posição da matriz
		if(cont == tamanho-1 && i == cont) return;
	}
}

void GeraTabuleiroPorArquivo(Tabuleiro * T, int tamanho, const char * arquivo){
	FILE * arq = fopen(arquivo, "r");
	char valor;
	int cont = 0;
	for (int i = 0; i <= tamanho; ++i){
		//i volta para a primeira coluna e incrementa o contador de linhas
		if(i == tamanho) i = 0, cont ++;
		//leitura no caso de caracteres no final da linha
		if(i == tamanho-1) fscanf(arq, "%c\n", &valor);
		//leitura no caso de caracteres no meio da linha
		else fscanf(arq, "%c ", &valor);
		//coloca o caractere em questão na posição atual
		SetElemento(T, cont+1, i+1, valor);
		//termina o processo quando chega na última posição da matriz
		if(cont == tamanho-1 && i == cont) return;
	}
}