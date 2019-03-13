#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tabuleiro.h"
#define DEBUG 0

void GeraTabuleiroPorArquivo(Tabuleiro * T, int modo, const char * arquivo);
int AvaliaJogo(Tabuleiro * T);
void JogaContraAmigo(Tabuleiro * T);
void JogaContraComputador(Tabuleiro * T);

int main(int argc, char const *argv[]){
	if(DEBUG) printf("Argumentos: %d.\n------------------\n", argc);
	for (int i = 0; i < argc; i++) if(DEBUG) printf("Argumento %d: %s\n", i, argv[i]);
	
	//cria um objeto do tipo Tabuleiro
	Tabuleiro * T = malloc(sizeof(Tabuleiro));
	//define a dimensão da matriz
	SetTamanho(T, 3);
	//inicializa todas as posições com _
	MarcaTodos(T, '_');
	
	//confere se não há problema de parâmetros a mais
	if(argc > 3){
		printf("### ERRO NOS PARÂMETROS! ###\nDigite o tamanho da matriz e,\nse desejar, o nome do arquivo de entrada.\n");
		return 0;
	}

	//caso single player
	if(argc == 2) {
		if(atoi(argv[1]) == 1){
			printf("### MODO SINGLE PLAYER ###\n");
			JogaContraComputador(T);
		}
		//caso multiplayer
		else{
			printf("### MODO MULTIPLAYER ###\n");
			JogaContraAmigo(T);
		}
	}

	//caso de entrada por arquivo
	else {
		printf("### MODO LEITURA DE ARQUIVO ###\n");
		GeraTabuleiroPorArquivo(T, atoi(argv[1]), argv[2]);
		if(!(AvaliaJogo(T))){
			printf("\n*** Deu velha! ***\n");
		}
	}
	return 0;
}

//função que define se algum jogador venceu a partida
int AvaliaJogo(Tabuleiro * T){
	char jogador = 'x';
	int cont = 2;
	//while itera duas vezes para testar o caso do x e do o
	while(cont){
		//testa as diagonais
		if(TestaDiagonalED(*T, jogador) || TestaDiagonalDE(*T, jogador)){
			printf("\n*** O vencedor foi %c! ***\n", jogador);
				return 1;
		}
		for (int i = 1; i <= 3; ++i){
			//testa as linhas e coolunas
			if(TestaLinha(*T, i, jogador) || TestaColuna(*T, i, jogador)){
				printf("\n*** O vencedor foi %c! ***\n", jogador);
				return 1;
			}
		}
		//troca para jogador o e testa se ele ganhou (no caso de o x não ter ganhado)
		jogador = 'o';
		cont --;
	}
	//se ninguém ganhou, retorna 0
	return 0;
}

void GeraTabuleiroPorArquivo(Tabuleiro * T, int modo, const char * arquivo){
	FILE * arq = fopen(arquivo, "r");
	int linha, coluna;
	int cont = 0;
	//lê o arquivo até o fim
	while(!feof(arq)){
		//lê a linha e a coluna
		fscanf(arq, "%d %d\n", &linha, &coluna);
		cont ++;
		//a operação em módulo 2 serve para alternar o que será escrito no tabuleiro
		//sempre começa com o(a) jogador(a) x
		//coloca o caractere em questão na posição atual
		if(cont % 2) SetElemento(T, linha+1, coluna+1, 'x');
		else SetElemento(T, linha+1, coluna+1, 'o');
	}
	printf("\n");
	Imprime(*T);
}

//função que gera a resposta do computador no caso single player
void MaquinaResponde(Tabuleiro * T){
	printf("\n> Vez do jogador: o\n");
	int linha, coluna;
	//faz com que cada sequência gerada pela rand() seja diferente
	srand(time(NULL));
	//gera, aleatoriamente, uma posição do tabuleiro até que seja encontrada uma não repetida
	do{
		//gera um valor aleatório de 0, inclusive, a 9
		int posicao = rand() % 9;
		//cada número representa uma posição do tabuleiro
		switch(posicao){
			case 0: linha = 0, coluna = 0; break;
			case 1: linha = 0, coluna = 1; break;
			case 2: linha = 0, coluna = 2; break;
			case 3: linha = 1, coluna = 0; break;
			case 4: linha = 1, coluna = 1; break;
			case 5: linha = 1, coluna = 2; break;
			case 6: linha = 2, coluna = 0; break;
			case 7: linha = 2, coluna = 1; break;
			case 8: linha = 2, coluna = 2; break;
		}
	} while(GetElemento(*T, linha+1, coluna+1) != '_');
	printf("Digite a posição: %d %d\n", linha, coluna);
	//coloca o caractere em questão na posição atual
	SetElemento(T, linha+1, coluna+1, 'o');
}

void JogaContraAmigo(Tabuleiro * T){
	Imprime(*T);
	int linha, coluna;
	char jogador;
	for (int i = 0; i <= 9; ++i){
		//verifica se já existe algum ganhador e, se sim, encerra
		if(AvaliaJogo(T)) return;
		//se chegar ao fim da rodada e ninguém tiver ganhado, dá velha e encerra
		if(i == 9){
			printf("\n*** Deu velha! ***\n");
			return;
		}
		//alterna entre x e o, começando sempre pelo x
		jogador = i%2 ? 'o' : 'x';
		//pede uma posição até que seja digitada uma não repetida
		do{
			printf("\n> Vez do jogador %c\nDigite a posição: ", jogador);
			scanf("%d %d", &linha, &coluna);
		} while(GetElemento(*T, linha+1, coluna+1) != '_');
		//coloca o caractere em questão na posição atual
		SetElemento(T, linha+1, coluna+1, jogador);
		Imprime(*T);
	}
}

void JogaContraComputador(Tabuleiro * T){
	Imprime(*T);
	int linha, coluna;
	for (int i = 0; i <= 9; ++i){
		//verifica se já existe algum ganhador e, se sim, encerra
		if(AvaliaJogo(T)) return;
		//se chegar ao fim da rodada e ninguém tiver ganhado, dá velha e encerra
		if(i == 9){
			printf("\n*** Deu velha! ***\n");
			return;
		}
		//alterna entre x e o, começando sempre pelo x
		char jogador = i%2 ? 'o' : 'x';
		//caso em que o jogador é humano
		if(jogador == 'x'){
			//pede uma posição até que seja digitada uma não repetida
			do{
				printf("\n> Vez do jogador: x\nDigite a posição: ");
				scanf("%d %d", &linha, &coluna);
			} while(GetElemento(*T, linha+1, coluna+1) != '_');
			//coloca o caractere em questão na posição atual
			SetElemento(T, linha+1, coluna+1, 'x');
		//caso em que o jogador é o computador
		} else MaquinaResponde(T);
		Imprime(*T);
	}
}