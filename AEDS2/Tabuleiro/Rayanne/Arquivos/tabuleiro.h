#ifndef TABULEIRO.H
#define TABULEIRO.H


typedef struct{
char matriz [11][11];
int tamanho;

}Tabuleiro;

//Definir o tamanho do tabuleiro que vai ser utilizado
void SetTamanho(Tabuleiro *T, int n);

//Colocar um elemento c em uma posição (i,j) do tabuleiro.
void SetElemento(Tabuleiro *T, int i, int j, char c);

//Recuperar o elemento de uma posição (i,j) o tabuleiro:
char GetElemento(Tabuleiro *T, int i, int j);

//Colocar um mesmo elemento c em todas as posições do tabuleiro
void MarcaTodos(Tabuleiro *T, char c);

//Testar se uma linha i do tabuleiro possui todos os elementos iguais a c, retornando true(1) ou false 0
int TestaLinha(Tabuleiro *T, int i, char c);

//Testar se uma coluna j do tabuleiro possui todos os elementos iguais a c, retornando true(1) ou false (0)
int TestaColuna(Tabuleiro *T, int j, char c);

//Testar se a diagonal esq-dir possui todos os elementos iguais a c, retornando true(1) ou false (0)
int TestaDiagonalED(Tabuleiro *T, char c);

//Testar se a diagonal dir-esq possui todos os elementos iguais a c, retornando true(1) ou false (0)
int TestaDiagonalDE(Tabuleiro *T, char c);

//Testar se uma linha i do tabuleiro possui todos os elementos diferentes, retornando true(1) ou false (0)
int TestaDiferente(Tabuleiro *T, int i);
//Imprime Tabuleiro
void Imprime(Tabuleiro *T);

#endif













