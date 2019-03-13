#include "Tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int maior(int num1,int num2,int num3){
	int maior=num1;
	if(num2>maior) maior=num2;
	if(num3>maior) maior=num3;
	return maior;
}

void TestaTabuleiro(Tabuleiro*tab,int dimensao_tabuleiro){
		int auxiliar=0;
		//no caso de tabuleiros de tamanho menor ou igual a 5
		if(dimensao_tabuleiro<=5){
			//descubro se a linha central é toda diferente
			if(TestaDiferente(*tab,dimensao_tabuleiro/2)){
				printf("Bingo!\n");
				return;
			}
		}
		auxiliar=maior(auxiliar,TestaDiagonalED(*tab,'?'),TestaDiagonalDE(*tab,'?'));
		auxiliar=maior(auxiliar,TestaDiagonalED(*tab,'*'),TestaDiagonalDE(*tab,'*'));
		auxiliar=maior(auxiliar,TestaDiagonalED(*tab,'#'),TestaDiagonalDE(*tab,'#'));
		auxiliar=maior(auxiliar,TestaDiagonalED(*tab,'%'),TestaDiagonalDE(*tab,'%'));
		auxiliar=maior(auxiliar,TestaDiagonalED(*tab,'@'),TestaDiagonalDE(*tab,'@'));

		if(!auxiliar) printf("Tente outra vez...\n");
		else printf("Bingo!\n");
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
	int dimensao_tabuleiro=atoi(argv[1]);

	if(argc==2){
		if(atoi(argv[1])%2==0){
			printf("Tamanho do caça níqueis deve ser par!\n");
			return 0;
		}
		//crio um tabuleiro
		Tabuleiro*tab=malloc(sizeof(Tabuleiro));
		SetTamanho(tab,dimensao_tabuleiro);
		tab->caracteres=malloc(dimensao_tabuleiro*sizeof(char*));
		for(i=0;i<dimensao_tabuleiro;i++) tab->caracteres[i]=malloc(dimensao_tabuleiro*sizeof(char));

		//preencho o tabuleiro de modo aleatório
		char elemento;
		for(i=0;i<dimensao_tabuleiro;i++){
			for(j=0;j<dimensao_tabuleiro;j++){
				int random=rand() % 5;
				if(random==0) elemento='?';
				if(random==1) elemento='#';
				if(random==2) elemento='%';
				if(random==3) elemento='*';
				if(random==4) elemento='@';
				SetElemento(tab,i,j,elemento);
			}
		}

		//imprime tabuleiro
		Imprime(*tab);

		//testa tabuleiro
		TestaTabuleiro(tab,dimensao_tabuleiro);
	} else {
		//crio um tabuleiro
		Tabuleiro*tab=malloc(sizeof(Tabuleiro));
		SetTamanho(tab,dimensao_tabuleiro);
		tab->caracteres=malloc(dimensao_tabuleiro*sizeof(char*));
		for(i=0;i<dimensao_tabuleiro;i++) tab->caracteres[i]=malloc(dimensao_tabuleiro*sizeof(char));
		
		const char*arquivo;
		arquivo = argv[2];

		char elemento;
		FILE*file=fopen(arquivo,"r");
		for(i=0;i<dimensao_tabuleiro;i++){
			for(j=0;j<dimensao_tabuleiro;j++){
				fscanf(file,"%c ",&elemento);
				SetElemento(tab,i,j,elemento);
			}
		}
		fclose(file);
		//imprime tabuleiro
		Imprime(*tab);

		//testa tabuleiro
		TestaTabuleiro(tab,dimensao_tabuleiro);
	}

	return 0;
}