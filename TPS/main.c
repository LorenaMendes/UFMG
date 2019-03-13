#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flag = 0;
int DEBUG = 1;

typedef struct no {
	struct no * key[27]; 
	struct no * pai; 
	char letra;
	int last; //finalizador de uma palavra (amo, amor, amora)
}node;

//função construtora
node * Trie(){
	node *T;
	int i;
	if(!(T = malloc(sizeof(node)))) return NULL;
	for(i=0; i<27; i++) T->key[i] = NULL; //inicializa todas as posições com NULL
	T->pai = NULL;
	return T;
}

//insere uma palavra na estrutura
void insere(node * raiz, char * word){
	int i, pos;
	node * aux, * pointer = raiz;
	for (i = 0; (word[i] != '\0' && word[i] != '\n'); i++){
		pos = word[i] - 'a'; //pos recebe a posição da letra (se for a, recebe 0; se for b, recebe 1...)
		// printf("Tratando %c de %s...", word[i], word);
		if (pointer->key[pos]){
			pointer = pointer->key[pos]; //se o nó já tem um filho, aponta para seu filho na posição da letra analisada
		} else { //senão, cria um nó e aponta para seu filho na posição analisada
			aux = Trie();
			if (!aux) {
				return;
			}
			pointer->letra = word[i];
			pointer->key[pos] = aux;
			aux->pai = pointer;
			pointer = aux;
		}
	}
	pointer->pai->last = 1; //a última letra é definida como finalizadora de palavra
}

void procuraPalavras(node * raiz, char * palavra, int pos){
	int i;
	node * pointer = raiz;
	for (i=0; i<27; i++){
		if(!pointer->key[i] || pointer->last){ //se chegou na folha ou a palavra acabou, encontrei a palavra
			printf("Palavra: %s\n", palavra);
			return;
		}
		else{
			pos ++;
			palavra[pos] = pointer->key[i]->letra;
			printf("Palavra atual: %s\n", palavra);
			procuraPalavras(pointer, palavra, pos);
		}
	}
}

// Função que imprime a Trie inteira, com todas as suas palavras
// Usada quando eu tenho o conteúdo do nó pai (String AUX)
void printTrieComPai(node * raiz, char * pai) {

	// Copio o conteudo do pai
	char * aux = malloc (100);
	strcpy(aux,pai);
	printf("Copiei: %s\n",aux);

	// Node auxiliar, a ser usado para percorrer a Trie
	node * nodeAux = raiz;
	int i,j;

	// Checo o tamanho da String
	int tam = strlen(aux);

	// E acrescento o ultimo caractere na String
	aux[tam] = raiz->letra;
	// E coloco de volta o caractere finalizador da String
	aux[tam+1] = '\0';

	// Se nó for uma palavra valida, imprimo
	if(raiz->last == 1) printf("Sugestao: %s",aux);

	// Para cada filho válido, chamo a função de imprimir
	for(j=0;j<27;j++) {
		if(raiz->key[j] != NULL) printTrieComPai(raiz->key[j],aux);
	}
}

// Função que imprime a Trie inteira, com todas as suas palavras
// Usada quando eu NÃO tenho o conteúdo do nó até aqui
void printTrie(node * inicioImpressao, int tamanho) {
	printf("==========================================\nPrint Trie:\n");
	// Node auxiliar, a ser usado para percorrer a Trie
	node * nodeAux = inicioImpressao;

	// Começo reservando uma variavel String, 
	// a ser preenchida com tudo o que tenho até aqui
	char * aux = malloc (100);
	int i,j;

	// A ultima posição é o finalizador de string \0
	aux[tamanho] = '\0';
	
	// Devo ir subindo a Trie e copiando para a String
	for(i=tamanho-1;i>=0;i--) {
		// Copio o char atual para a String
		printf("acrescentando letra %c\n",nodeAux->letra);
		aux[i] = nodeAux->letra;
		// E subo para o nó pai
		nodeAux = nodeAux->pai;
	}

	//-----------------------------------------------------
	if(DEBUG) printf("\t=== Flag %d\n",flag); flag++;

	// Se nó for uma palavra valida, imprimo
	if(inicioImpressao->last == 1) printf("Sugestao: %s",aux);

	// Para cada filho válido, chamo a função de imprimir
	for(j=0;j<27;j++) {
		if(inicioImpressao->key[j] != NULL) printTrieComPai(inicioImpressao->key[j],aux);
	}
}

void conferePrefixo(node * raiz, char * prefixo){
	int i, pos;
	node * pointer = raiz;
	int tam = strlen(prefixo)-1;
	printf("Prefixo: %s\n", prefixo);
	for(i=0; i<=tam; i++){
		printf("Prefixo[%d]: %c\n", i, prefixo[i]);
		pos = prefixo[i] - 'a';
		if (!pointer->key[pos]){ //se a posição da letra analisada é NULL
			printf("Não existe palavra com esse prefixo!\n");
			return;
		} else { //senão, olho pra posição filha
			pointer = pointer->key[pos];
		}
	}
	if(pointer->last){ //acaber de pesquisar o prefixo e achei um finalizador
		printf("O prefixo é a própria palavra\n");
	}
	char * palavra = malloc(100);
	strcpy(palavra, prefixo);
	procuraPalavras(pointer, palavra, tam);
	printf("Achei o prefixo!! Imprimindo a partir da letra %c, na posicao %d\n",pointer->pai->letra,tam+1);
	printTrie(pointer->pai, tam+1);
}

void printWord(char ** words, int tam){
	int i;
	for (i=0; i<tam; i++){
		printf("Palavra %d: %s", i+1, words[i]);
	}
}

//essa função é usada pela qsort(), não precisa mexer nem entender
int sortstring(const void * a, const void * b){
    char **A = (char **)a;
    char **B = (char **)b;
    return strcmp(*A, *B);
}

int main(int argc, char const *argv[]){
	//confere os parâmetros
	// printf("Arquivo: %s\n", argv[1]);
	// printf("Número: %s\n", argv[2]);

	//declara e aloca as variáveis
	if(DEBUG) printf("\n=============================\n");
	int i, tam=0;
	FILE * arq = fopen(argv[1], "r");
	char * aux = malloc (100);
	char ** words = malloc (100000 * sizeof(char *));
	for(i=0; i<100000; i++) words[i] = malloc (100 * sizeof(char));
	
	//coloca as palavras num vetor
	while(fgets(aux, 100, arq)){
		//if((int)strlen(aux)-1 >= atoi(argv[2])){
			strcpy(words[tam], aux);
			tam++;
		//}
	}

	//ordena as palavras por ordem alfabética
	qsort (words, tam, sizeof(char *), sortstring);

	//imprime as palavras
	printWord(words, tam);

	node * raiz = Trie();

	for(i=0; i<tam; i++){
		insere(raiz, words[i]);
	}

	conferePrefixo(raiz, "amo");

	//fecha o arquivo
	fclose(arq);
	return 0;
}