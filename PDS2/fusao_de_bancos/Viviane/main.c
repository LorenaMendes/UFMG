#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

int main(){

	int n, k; // número de bancos, número de operações
	int a, b; // bancos lidos
	char tipo; // tipo de operação realizada
	Banco b_a, b_b; // bancos auxiliares

	for (int i = 0;; ++i){ // faz o procedimento sem condição de parada
		
		scanf("%d %d\n", &n, &k); // lê número de bancos e número de operações
		
		if(n == 0 && k == 0) break; // para quando ler 0 0

		Banco lista_bancos[n]; // cria uma lista de bancos de tamanho n
		for (int j = 0; j < n; ++j) lista_bancos[j].id = -1; // inicializa toda a lista com bancos de id -1

		// realiza um bloco de operações
		for (int x = 0; x < k; ++x){
			scanf("%c %d %d\n", &tipo, &a, &b); // lê tipo de operação e bancos
			
			// cria um novo banco se ele ainda não existir na lista
			if(lista_bancos[a-1].id == -1){
				b_a = CriaBanco(a);
				lista_bancos[b_a.id] = b_a; // insere o banco na lista
			}
			
			// cria um novo banco se ele ainda não existir na lista
			if(lista_bancos[b-1].id == -1){
				b_b = CriaBanco(b);
				lista_bancos[b_b.id] = b_b; // insere o banco na lista
			}
			
			// operação de fusão
			if (tipo == 'F'){
				// redefine os tipos dos bancos de acordo com o menor dos tipos
				if(lista_bancos[a-1].tipo < lista_bancos[b-1].tipo){
					lista_bancos[b-1].tipo = lista_bancos[a-1].tipo;
					FundeBancos(lista_bancos, n, b, a);
				}
				else{
					lista_bancos[a-1].tipo = lista_bancos[b-1].tipo;
					FundeBancos(lista_bancos, n, a, b);
				}

			}

			// operação de consulta
			else if(tipo == 'C'){
				// imprime S para bancos de mesmo tipo e N para bancos de tipos diferentes
				if (lista_bancos[a-1].tipo == lista_bancos[b-1].tipo)
					printf("S\n");
				else
					printf("N\n");
			}
		}
		// imprime uma linha após cada conjunto de operações
		printf("\n");
	}
}