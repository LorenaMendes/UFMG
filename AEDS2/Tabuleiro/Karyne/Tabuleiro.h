typedef struct Tabuleiro{
	char ** caracter;
	int dimensao;
} Tabuleiro;

void SetTamanho(Tabuleiro *T, int n);

void SetElemento(Tabuleiro *T, int i, int j, char c);

char GetElemento(Tabuleiro T, int i, int j);

void MarcaTodos(Tabuleiro *T, char c);

int TestaLinha(Tabuleiro T, int i, char c);

int TestaColuna(Tabuleiro T, int j, char c);

int TestaDiagonalED(Tabuleiro T, char c);

int TestaDiagonalDE(Tabuleiro T, char c);

int TestaDiferente(Tabuleiro T, int i);

void Imprime(Tabuleiro T);