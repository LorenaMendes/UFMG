#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

// função que cria e retorna um banco
Banco CriaBanco(int a){
	Banco x;
	x.id = a - 1; // a-1 para inserir no array (pois começa na posição zero)
	x.tipo = a - 1; // define o tipo do banco como o próprio valor

	return x; // retorna o banco criado
}

void FundeBancos(Banco* lista, int n, int a, int b){
	for (int i = 0; i < n; ++i){
		if(lista[i].tipo == a-1) lista[i].tipo = b-1;
	}
}
