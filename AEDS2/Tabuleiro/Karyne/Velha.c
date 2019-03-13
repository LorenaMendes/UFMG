#include "Tabuleiro.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int Vencedor(Tabuleiro * T);
void LeArquivo(const char * arq, Tabuleiro * T);
void JogadorXJogador(Tabuleiro * T);
void JogadorXComputador(Tabuleiro * T);

int main(int argc, char const *argv[]){
	Tabuleiro T[3];
	SetTamanho(T, 3);
	//coloca todas as posições com underline
	MarcaTodos(T, '_');

	if(argc == 3){
		//leitura de arquivo
		LeArquivo(argv[2], T);
		Imprime(*T);
		if(Vencedor(T) == 1){
			printf("Deu velha!\n");
		}
	} else if(argc == 2){
		//entradas sem arquivo
		if(atoi(argv[1]) == 1) JogadorXComputador(T);
		else if(atoi(argv[1]) == 2) JogadorXJogador(T);
		else{
			printf("Ńúmero inválido\n");
			return 0;
		}
	//número inválido de parâmetros
	} else printf("Erro nos parâmetros\n");
	
	// Imprime(*T);
	return 0;
}

int Vencedor(Tabuleiro * T){
	int auxiliar = -1;
	char jogador;
	do{
		auxiliar ++;
		//define o jogador atual
		if(auxiliar == 0) jogador = 'O';
		else jogador = 'X';
		//verifica se as diagonais são iguais
		if(TestaDiagonalED(*T, jogador) || TestaDiagonalDE(*T, jogador)){
			printf("O vencedor foi %c!\n\n", jogador);
			return 0;
		}
		//verifica se as linhas ou colunas são iguais
		for (int i = 0; i < 3; ++i){
			if(TestaLinha(*T, i, jogador) || TestaColuna(*T, i, jogador)){
				printf("O vencedor foi %c!\n\n", jogador);
				return 0;
			}
		}
	//faz o processo 2 vezes (para o e para x)
	} while(auxiliar < 2);
	//retorna 1 caso ninguém ganhe
	return 1;
}

void LeArquivo(const char * arq, Tabuleiro * T){
	FILE * arquivo;
	//abre o arquivo
	arquivo = fopen(arq, "r");
	int linha, coluna;
	char elemento;
	//contador para mudar o jogador
	int contador = 0;
	do{
		//contador ímpar, xizinho
		if(contador % 2) elemento = 'O';
		//contador par, bolinha
		else elemento = 'X';
		fscanf(arquivo, "%d ", &linha);
		fscanf(arquivo, "%d ", &coluna);
		SetElemento(T, linha, coluna, elemento);
		contador ++;
	} while(!feof(arquivo));
	//fecha o arquivo
	fclose(arquivo);
}

void JogadorXJogador(Tabuleiro * T){
	int linha, coluna;
	char elemento;
	int contador = 0;
	for (int i = 0; i < 10; ++i){
		Imprime(*T);
		if(Vencedor(T) == 0) return;
		//dá velha caso ninguém ganhe
		if(i == 9){
			printf("Deu velha!\n");
			return;
		}
		//contador ímpar, xizinho
		if(contador % 2) elemento = 'O';
		//contador par, bolinha
		else elemento = 'X';
		printf("\nDigite a posição: ");
		scanf("%d %d", &linha, &coluna);
		//posição é inválida
		if(GetElemento(*T, linha, coluna) != '_' || GetElemento(*T, linha, coluna) == 'e'){
			printf("\nPosição inválida. Digite outra: \n");
			i--;
		} else SetElemento(T, linha, coluna, elemento);
		printf("\n");
		contador ++;
	}
}

void JogadorXComputador(Tabuleiro * T){
	srand(time(NULL));
	int linha, coluna;
	int linha_computador, coluna_computador;
	char elemento;
	int contador = 0;
	for (int i = 0; i < 10; ++i){
		Imprime(*T);
		if(Vencedor(T) == 0) return;
		if(i == 9){
			printf("Deu velha!\n");
			return;
		}
		//contador ímpar, xizinho
		if(contador % 2){
			elemento = 'O';
			do{
				//gera posição aleatória
				linha_computador = rand() % 3;
				coluna_computador = rand() % 3;
			} while(GetElemento(*T, linha_computador, coluna_computador) != '_');
			printf("\nVez do computador. Ele escolheu %d %d\n\n", linha_computador, coluna_computador);
			SetElemento(T, linha_computador, coluna_computador, elemento);
		//contador par, bolinha
		} else {
			elemento = 'X';
			printf("\nDigite a posição: ");
			do{
				scanf("%d %d", &linha, &coluna);
				//posição inválida
				if(GetElemento(*T, linha, coluna) != '_' || GetElemento(*T, linha, coluna) == 'e'){
					printf("\nPosição inválida. Digite outra: ");
				}
			} while(GetElemento(*T, linha, coluna) != '_');
			//define elemento
			SetElemento(T, linha, coluna, elemento);
		}
		contador ++;
	}
}