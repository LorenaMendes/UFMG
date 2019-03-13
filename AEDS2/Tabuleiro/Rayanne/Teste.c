#include "Tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	Tabuleiro * tab = malloc(sizeof(Tabuleiro));
	SetTamanho(tab, 3);
	MarcaTodos(tab, '.');
	// SetElemento(tab, 1, 1, 'y');
	char elemento = GetElemento(tab, 1, 1);
	
	SetElemento(tab, 0, 0, 'a'); // a p a
	SetElemento(tab, 0, 1, 'p');
	SetElemento(tab, 0, 2, 'a');
	Imprime(*tab);

	SetElemento(tab, 1, 0, 't'); // t a a
	SetElemento(tab, 1, 1, 'a');
	SetElemento(tab, 1, 2, 'a');
	Imprime(*tab);
	
	SetElemento(tab, 2, 0, 'a'); // a y a
	SetElemento(tab, 2, 1, 'y');
	SetElemento(tab, 2, 2, 'a');
	Imprime(*tab);
	
	// int result = TestaDiferente(tab, 1);
	int result = TestaDiagonalDE(tab,'y');
	int result2 = TestaDiagonalDE(tab,'a');
	printf("%d\n", result);
	printf("%d\n", result2);
	return 0;
}