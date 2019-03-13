#ifndef Tabuleiro_h
#define Tabuleiro_h

typedef struct Tabuleiro{
	int dimensao;
	char ** caracter;
} Tabuleiro;

// 1. Definir o tamanho do tabuleiro que vai ser utilizado.
void SetTamanho(Tabuleiro *T, int n);
// 2. Colocar um elemento c em uma posição (i,j) do tabuleiro.
void SetElemento(Tabuleiro *T, int i, int j, char c);
// 3. Recuperar o elemento de uma posição (i,j) o tabuleiro:
char GetElemento(Tabuleiro T, int i, int j);
// 4. Colocar um mesmo elemento c em todas as posições do tabuleiro.
void MarcaTodos(Tabuleiro *T, char c);
// 5. Testar se uma linha i do tabuleiro possui todos os elementos iguais a c, retornando true (1) ou false (0).
int TestaLinha(Tabuleiro T, int i, char c);
// 6. Testar se uma coluna j do tabuleiro possui todos os elementos iguais a c, retornando true (1) ou false (0).
int TestaColuna(Tabuleiro T, int j, char c);
// 7. Testar se a diagonal esq-dir possui todos os elementos iguais a c, retornando true (1) ou false (0).
int TestaDiagonalED(Tabuleiro T, char c);
// 8. Testar se a diagonal dir-esq possui todos os elementos iguais a c, retornando true (1) ou false (0).
int TestaDiagonalDE(Tabuleiro T, char c);
// 9. Testar se uma linha i do tabuleiro possui todos os elementos diferentes, retornando true (1) ou false (0).
int TestaDiferente(Tabuleiro T, int i);
// 10. Imprimir tabuleiro.
void Imprime(Tabuleiro T);
// 11. Ordena um vetor.
int OrdenaVetor(char * vetor, int tam);

#endif