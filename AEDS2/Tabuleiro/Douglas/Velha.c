#include "Tabuleiro.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int TestaJogo(Tabuleiro*tab,char jogador){
	int i;
	int auxiliar=0;
	for(i=0;i<3;i++){
		auxiliar+=TestaLinha(*tab,i,jogador);
		auxiliar+=TestaColuna(*tab,i,jogador);
		auxiliar+=TestaDiagonalED(*tab,jogador);
		auxiliar+=TestaDiagonalDE(*tab,jogador);
	}
	if(auxiliar==0) return 0;
	else return 1;
}

int main(int argc, char const *argv[]){
	int i, j;
	srand(time(NULL));
	//definindo os parâmetros
	printf("Número de parâmetros: %d\n", argc);
	if(argc>3||argc<2){
		printf("Parâmetros errados!\n");
		return 0;
	}
	for(i=0;i<argc;i++){
		printf("Parâmetro %d: %s\n",i+1,argv[i]);
	}

	int tipo_jogo=atoi(argv[1]);

	//jogador versus computador
	if(tipo_jogo==1){
		//crio um tabuleiro
		Tabuleiro*tab=malloc(sizeof(Tabuleiro));
		SetTamanho(tab,3);
		tab->caracteres=malloc(3*sizeof(char*));
		for(i=0;i<3;i++) tab->caracteres[i]=malloc(3*sizeof(char));
		MarcaTodos(tab,'_');

		int auxiliar=-1;
		int x,y;
		for(i=0;i<=9;i++){
			Imprime(*tab);
			if(TestaJogo(tab,'O')){
				printf("O vencedor foi O\n");
				return 0;
			}
			if(TestaJogo(tab,'X')){
				printf("O vencedor foi X\n");
				return 0;
			}
			if(i==9){
				printf("Deu velha!\n");
				return 0;
			}
			if(auxiliar<0){
				do{
					printf("Sua vez: ");
					scanf("%d%d",&x,&y);
				}while(GetElemento(*tab,x,y)!='_');
				SetElemento(tab,x,y,'X');
			} else {
				printf("Vez do computador: ");
				do{
					int random=rand() % 9;
					if(random==0) x=0,y=0;
					if(random==1) x=0,y=1;
					if(random==2) x=0,y=2;
					if(random==3) x=1,y=0;
					if(random==4) x=1,y=1;
					if(random==5) x=1,y=2;
					if(random==6) x=2,y=0;
					if(random==7) x=2,y=1;
					if(random==8) x=2,y=2;
				}while(GetElemento(*tab,x,y)!='_');
				SetElemento(tab,x,y,'O');
				printf("%d %d\n", x,y);
			}
			auxiliar*=-1;
		}
	}

	//jogador versus jogador
	if(tipo_jogo==2){
		//crio um tabuleiro
		Tabuleiro*tab=malloc(sizeof(Tabuleiro));
		SetTamanho(tab,3);
		tab->caracteres=malloc(3*sizeof(char*));
		for(i=0;i<3;i++) tab->caracteres[i]=malloc(3*sizeof(char));
		MarcaTodos(tab,'_');

		int auxiliar=-1;
		int x,y;
		for(i=0;i<=9;i++){
			Imprime(*tab);
			if(TestaJogo(tab,'O')){
				printf("O vencedor foi O!\n");
				return 0;
			}
			if(TestaJogo(tab,'X')){
				printf("O vencedor foi X!\n");
				return 0;
			}
			if(i==9){
				printf("Deu velha!\n");
				return 0;
			}
			if(auxiliar<0){
				do{
					printf("Jogador X, sua vez: ");
					scanf("%d%d",&x,&y);
				}while(GetElemento(*tab,x,y)!='_');
				SetElemento(tab,x,y,'X');
			} else {
				do{
					printf("Jogador O, sua vez: ");
					scanf("%d%d",&x,&y);
				}while(GetElemento(*tab,x,y)!='_');
				SetElemento(tab,x,y,'O');
			}
			auxiliar*=-1;
		}
	}

	//leitura de arquivo
	if(tipo_jogo==3){
		//crio um tabuleiro
		Tabuleiro*tab=malloc(sizeof(Tabuleiro));
		SetTamanho(tab,3);
		tab->caracteres=malloc(3*sizeof(char*));
		for(i=0;i<3;i++) tab->caracteres[i]=malloc(3*sizeof(char));
		MarcaTodos(tab,'_');

		const char*arquivo;
		arquivo = argv[2];

		int x,y;
		char elemento;
		int auxiliar=-1;
		FILE*file=fopen(arquivo,"r");
		while(!feof(file)){
			fscanf(file,"%d %d",&x,&y);
			if(auxiliar<0) elemento='X';
			else elemento='O';
			SetElemento(tab,x,y,elemento);
			auxiliar*=-1;
		}
		fclose(file);
		
		//imprime tabuleiro
		Imprime(*tab);

		//testa jogo
		if(TestaJogo(tab,'O')){
			printf("O vencedor foi O!\n");
			return 0;
		}
		else if(TestaJogo(tab,'X')){
			printf("O vencedor foi X!\n");
			return 0;
		} else printf("Deu velha!\n");
	}

	return 0;
}