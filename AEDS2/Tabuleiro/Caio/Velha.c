#include "Tabuleiro.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_result(char player){
	printf("\n\"%c\" is the winner\n", player);
}

//generates a computer's answer
void generate_anwser(Tabuleiro * T){
	srand(time(NULL)); 
	printf("\nComputer's turn!\n");
	int row, column;
	do{ //chose randomicaly one matrix's position
		int posicao = rand() % 9;
		if(posicao == 0){ //representates 0 (0,0)
			row = 0;
			column = 0;
		} else if(posicao == 1){ //representates 1 (0,1)
			row = 0;
			column = 1;
		} else if(posicao == 2){ //representates 3 (0,2)
			row = 0;
			column = 2;
		} else if(posicao == 3){ //representates 4 (1,0)
			row = 1;
			column = 0;
		} else if(posicao == 4){ //representates 5 (1,1)
			row = 1;
			column = 1;
		} else if(posicao == 5){ //representates 6 (1,2)
			row = 1;
			column = 2;
		} else if(posicao == 6){ //representates 7 (2,0)
			row = 2;
			column = 0;
		} else if(posicao == 7){ //representates 8 (2,1)
			row = 2;
			column = 1;
		} else if(posicao == 8){ //representates 9 (2,2)
			row = 2;
			column = 2;
		} //makes it while choosing one invalid position
	} while(!(GetElemento(*T, row+1, column+1) == '_'));
	printf("Position: %d %d\n", row, column);
	//coloca o caractere em questão na posição atual
	SetElemento(T, row+1, column+1, 'O');
}

int find_winner(Tabuleiro * T){ //find a winner in the match
	char player;
	int i, j;
	for(i = 0; i<2; i++){
		if(i == 0) player = 'X';
		else player = 'O';
		if(TestaDiagonalDE(*T, player)||TestaDiagonalED(*T, player)){ //finds out if diagonals are equals
			print_result(player);
			return 1;
		}
		for (j = 1; j <= 3; j++){
			if(TestaColuna(*T, j, player)||TestaLinha(*T, j, player)){ //finds out if rows and columns are equals
				print_result(player);
				return 1;
			}
		}
	}
	return 0;
}

void single_player(Tabuleiro * T){
	char player;
	int row, column, i;
	for(i = 0; i <= 9; i++){
		if(find_winner(T)){ //if foud a winner, the process is over
			return;
		}
		if(i == 9){ //if no winners found, process is over
			printf("\nDeu velha\n");
			return;
		}
		if(i%2 == 0){
			player = 'X';
		} else{
			player = 'O';
		}
		if(player == 'X'){
			do{
				printf("\nPlayer X, it's your turn!\nChoose position: ");
				scanf("%d %d", &row, &column);
				if(!(GetElemento(*T, row+1, column+1) == '_')) printf("Invalid position! Choose another one.\n");
			} while(GetElemento(*T, row+1, column+1) != '_');
			SetElemento(T, row+1, column+1, 'X');
		} else generate_anwser(T);
		Imprime(*T);
	}
}

void multiplayer(Tabuleiro * T){
	char player;
	int row, column;
	int i;
	for (i = 0; i < 10; i++){
		if(find_winner(T)){
			return;
		}
		if(i == 9){
			printf("\nDeu velha\n");
			return;
		}
		if(i%2 != 0){ //changes for each turn (even, odd, even, odd, even, ...)
			player = 'O';
		} else {
			player = 'X';
		}
		do{
			printf("\nPlayer %c, it's your turn!\nChoose position: ", player);
			scanf("%d %d", &row, &column);
			//invalid position's case
			if(!(GetElemento(*T, row+1, column+1) == '_')) printf("Invalid position! Choose another one.\n");
		} while(GetElemento(*T, row+1, column+1) != '_');
		SetElemento(T, row+1, column+1, player);
		Imprime(*T);
	}
}

int main(int argc, char const *argv[]){
	Tabuleiro * T = malloc(sizeof(Tabuleiro));
	SetTamanho(T, 3); //set matrix's size
	MarcaTodos(T, '_'); //set all positions with "_"
	
	if(argc > 3){
		printf("ERRO NOS PARÂMETROS!\n");
		return 0;
	}
	if(argc == 3) { //with a file
		FILE * file = fopen(argv[2], "r");
		int row, column;
		int aux = 0;
		while(!feof(file)){
			//lê a row e a column
			fscanf(file, "%d %d\n", &row, &column);
			aux ++;
			if(aux % 2){ //alternates for each player
				SetElemento(T, row+1, column+1, 'X');
			} else{
				SetElemento(T, row+1, column+1, 'O');
			}
		}
		printf("\n");
		Imprime(*T);
		if(find_winner(T) == 0) printf("\nDeu velha\n");
	} else if(argc == 2) { //without a file
		Imprime(*T);
		if(atoi(argv[1]) == 2){
			multiplayer(T);
		} else{
			single_player(T);
		}
	} else{
		printf("Fail\n");
		return 0;
	}
	return 0;
}