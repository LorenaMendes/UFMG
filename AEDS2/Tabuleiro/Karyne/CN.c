#include "Tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define DEBUG 1

void LeArquivo(const char * arq, Tabuleiro * T);
void NovoTabuleiro(Tabuleiro * T);
void ChecaCN(Tabuleiro * T);

int main(int argc, char const *argv[]){
	int tamanho = atoi(argv[1]);
	Tabuleiro T[tamanho];
	SetTamanho(T, tamanho);
	
	if(argc == 3){
		LeArquivo(argv[2], T);
	} else if(argc == 2){
		if(!(atoi(argv[1]) % 2)){
			printf("Crie um CN de tamanho ímpar.\n");
			return 0;
		}
		NovoTabuleiro(T);
	} else printf("Erro nos parâmetros\n");
	
	Imprime(*T);
	ChecaCN(T);
	return 0;
}

void LeArquivo(const char * arq, Tabuleiro * T){
	FILE * arquivo;
	//abre o arquivo
	arquivo = fopen(arq, "r");
	char simbolo;
	//itera da posição 0 até o tamanho do tabuleiro
	int pos = 0;
	do{
		//itera em cada linha do arquivo
		for(int i = 0; i < T->dimensao; ++i){
			//lê caractere
			fscanf(arquivo, "%c ", &simbolo);
			if(DEBUG) printf("Inserindo %c em (%d, %d)\n", simbolo, pos, i);
			//insere caractere no tabuleiro
			SetElemento(T, pos, i, simbolo);
		}
		if(DEBUG) printf("\n");
		pos ++;
	//faz a leitura enquanto o arquivo não acabar
	} while(!feof(arquivo));
	//fecha o arquivo
	fclose(arquivo);
}

void NovoTabuleiro(Tabuleiro * T){
	srand(time(NULL));
	char simbolo;
	int linha = 0;
	do{
		for (int i = 0; i < T->dimensao; ++i){
			int aleatorio = rand() % 5;
			//define símbolo de forma aleatória
			switch(aleatorio){
				case 0:
					simbolo = '*';
					break;
				case 1:
					simbolo = '#';
					break;
				case 2:
					simbolo = '?';
					break;
				case 3:
					simbolo = '%';
					break;
				case 4:
					simbolo = '@';
					break;
			}
			//coloca elemento no tabuleiro
			SetElemento(T, linha, i, simbolo);
		}
		linha ++;
	} while(linha < T->dimensao);
}

void ChecaCN(Tabuleiro * T){
	char simbolo;
	int tam = T->dimensao;
	//testa o caso de linha central com elementos diferentes
	if(TestaDiferente(*T, (tam/2+1))){
		printf("Bingo!\n");
		return;
	} else {
		//testa diagonais
		for (int i = 0; i < 5; ++i){
			//define o valor de cada simbolo
			switch(i){
				case 0:
					simbolo = '*';
					break;
				case 1:
					simbolo = '#';
					break;
				case 2:
					simbolo = '?';
					break;
				case 3:
					simbolo = '%';
					break;
				case 4:
					simbolo = '@';
					break;
			}
			if(TestaDiagonalED(*T, simbolo) || TestaDiagonalDE(*T, simbolo)){
				printf("Bingo!\n");
				return;
			}
		}
	} printf("Tente outra vez...\n");
}