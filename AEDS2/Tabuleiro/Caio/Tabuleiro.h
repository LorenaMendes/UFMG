#ifndef MATRIZ
#define MATRIZ

typedef struct Tabuleiro{ //define TAD for a matrix
	char ** symbol;
	int size;
}Tabuleiro;

void Imprime(Tabuleiro T); //print matrix
void SetTamanho(Tabuleiro *T, int n); //define matrix's size
void SetElemento(Tabuleiro *T, int i, int j, char c); //set a value in a specific position
char GetElemento(Tabuleiro T, int i, int j); //get an element from specific position 
void MarcaTodos(Tabuleiro *T, char c); //set the entire matrix with the same symbol
int  TestaLinha(Tabuleiro T, int i, char c); //returns 1 if all the symbols in a row are different
int  TestaColuna(Tabuleiro T, int j, char c); //returns 1 if all symbols in a column are equal to a specific symbol
int  TestaDiagonalED(Tabuleiro T, char c); //returns 1 if all the elements in ED diagonal are equal to a specific symbol
int  TestaDiagonalDE(Tabuleiro T, char c); //returns 1 if all the elements in DE diagonal are equal to a specific symbol
int  TestaDiferente(Tabuleiro T, int i); //returns 1 if all the symbols in a specific row are different
int OrdenaVetor(char * vetor, int tam);


#endif