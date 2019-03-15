#define _XOPEN_SOURCE 500 // Ativa certas funcoes de biblioteca (strdup) on linux.

#include <stdio.h> 	// Biblioteca basica
#include <stdlib.h>	// Funcoes: 	malloc, qsort, etc.
#include <ctype.h>	// Funcoes: 	tolower
#include <limits.h>	// Datatype:	ULONG_MAX
#include <string.h>	// Funcoes: 	strlen, strcmp, strdup, strcpy

int DEBUG = 0;  	// Ativar modo DEBUG para ver o que esta acontecendo no programa

// Quando ha varias palavras com um mesmo prefixo, eh necessario encadear todas
// usando o TAD abaixo, chamado ELEMENT
struct element_s {
	char *value;
	struct element_s *nextElement;
};

typedef struct element_s element;


// Construtor para o ELEMENT acima
element * Element(char * value) {
	element *T;
	if(!(T = malloc(sizeof(element)))) return NULL;
	T->value = strdup(value);
	T->nextElement = NULL;
	return T;
}

// Estrutura que amarra um prefixo (chamado de chave) a uma palavra (ELEMENT)
// Nao foi possivel amarrar um prefixo diretamente a uma string porque ha casos em que ha diversas strings 
// para uma mesma chave, e o ELEMENT permite amarrar uma palavra na outra, criando uma lista
struct entry_s {
	char *key;
	element *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

// Estrutura que suporta a tabela hash, ou Hashtable
// (que, na verdade, nada mais eh do que uma lista de ENTRIES)
struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;


// Funcao que cria nova hashtable
hashtable_t *ht_create( int size ) {

	hashtable_t *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;	
}

// Funcao de hash, que transforma uma string em uma chave numerica
int ht_hash( hashtable_t *hashtable, char *key ) {

	unsigned long int hashval;
	int i = 0;

	// Converte string em inteiro, explorando shift de bits
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 16;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

// Cria um par chave-valor
entry_t *ht_newpair( char *key, char *value ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->value = Element( value ) ) == NULL ) {
		return NULL;
	}

	newpair->next = NULL;

	return newpair;
}

// Insere um par chave-valor na Hashtable
void ht_set( hashtable_t *hashtable, char *key, char *value ) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key );
	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	// Chave ja contem registro(s). Vamos encadear o novo registro no atual(is)
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		element * aux = next->value;

		// Encontra ultimo registro da cadeia
		while(aux->nextElement != NULL) {
			aux = aux->nextElement;
			if(DEBUG) printf("Buscando na cadeia, passando por %s...\n",aux->value);
		}
		if(DEBUG) printf("Achei o final da cadeia apos %s.\n",aux->value);

		// Coloca novo registro no final de todo mundo
		aux->nextElement = Element(value);
		if(DEBUG) printf("Coloquei %s na chave %s\n",aux->nextElement->value,next->key);

	// Chave nao contem nenhum registro. Vamos inserir diretamente na chave.
	} else {
		newpair = ht_newpair( key, value );

		// Se estamos no inicio da lista encadeada, ajustar so o proximo elemento
		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;
	
		// Se estamos no final da lista encadeada, ajustar so o elemento anterior
		} else if ( next == NULL ) {
			last->next = newpair;
	
		// Caso contrario, se nem no inicio e nem no final...
		// ...entao, necessario ajustar ambos elementos: proximo e anterior
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

// Encontra um par chave-valor dentro da hashtable
element *ht_get( hashtable_t *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	// Procurando o valor
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	// Caso nao encontrado, retorna NULL
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

	// Se encontrado, retorna o valor
	} else {
		return pair->value;
	}
	
}

// Usada pela qsort()
int sortstring(const void * a, const void * b){
    char **A = (char **)a;
    char **B = (char **)b;
    return strcmp(*A, *B);
}

// Imprime na tela todas as palavras do dicionario
void printWord(char ** words, int tam){
	int i;
	for (i=0; i<tam; i++){
		printf("Palavra %d: %s\n", i+1, words[i]);
	}
}

int main( int argc, char **argv ) {

	// Cria uma hashtable com 2^16 posicoes
	// Cuidado ao alterar o tamanho da tabela!
	hashtable_t *hashtable = ht_create( 65536 );

	// Declara e aloca as variaveis do programa
	int i, j, n=atoi(argv[2]),tam=0;
	FILE * arq = fopen(argv[1], "r"); // usado para controlar onde estou lendo no arquivo INPUT
	char * aux = malloc (100); // usado para armazenar uma palavra vinda do input
	char ** words = malloc (100000 * sizeof(char *)); // ponteiro para apontar para o conjunto de palavras do INPUT
	for(i=0; i<100000; i++) words[i] = malloc (100 * sizeof(char)); // alocando a memoria de cada palavra do INPUT (tamanho maximo de 100.000 palavras)
	
	//Enquanto tiver palavras no INPUT, coloca as palavras num vetor
	while(fgets(aux, 100, arq)){

			// populo a linha lida do arquivo para o meu vetor de palavras a serem tratadas
			strcpy(words[tam], aux);

			// e conserto a palavra substituindo o breakline que veio do arquivo por um finalizador de strings
			words[tam][strlen(words[tam])-1] = '\0';

			// e incremeno o contador
			tam++;
	}

	// Ja terminamos de ler e importar o arquivo de INPUT. Podemos fechar.
    fclose(arq);

	// Ordena as palavras por ordem alfabética
	qsort (words, tam, sizeof(char *), sortstring);

	// Imprime todas as palavras
	printWord(words, tam);

	// Necessario imprimir na tela que estamos fazendo as insercoes
	// ja que dicionarios maiores que 10^4 comecam a ficar com a fase de processamento perceptivel
	// e 10^5 demora varios segundos, e algum usuario pode achar que travou se nao houver mensagem
	printf("Aguarde: Iniciando as insercoes na hashtable...\n");

	// percorro todas as palavras
	for(i=0; i<tam; i++){

		// para cada palavra, uso um vetor temporario para armazenar
		char * aux2 = malloc (100);

		// insiro na tabela hash a chave a ser usada 
		// quando o usuario pesquisar por j caracteres
		for(j=0;(j<n && words[i][j]!='\0');j++) {
			strncpy(aux2,words[i],j+1);
			if(DEBUG) printf("Inserindo %s na chave %s\n",words[i],aux2);
			ht_set( hashtable, aux2, words[i] );
		}
	}
	printf("Terminei as insercoes.\n=============================\n");

	// criando variavel auxiliar para receber o que o usuario ja digitou ate agora
	char * chave = malloc (100 * sizeof(char));

	for (int i=0; i<100; i++){
		chave[i] = '\0';	// limpando a string
	}

	// char que recebera o ultimo caractere digitado pelo usuario
	char ch;

    for (int i=0; i<100; i++){

    	//Converte os caracteres para minusculas
    	for(int j=0;j<i;j++) chave[j] = tolower(chave[j]);
    	
    	// limpa a tela
    	printf("\e[1;1H\e[2J");
    	
    	printf("Sugestoes chave '%s' (hash %d): \n\n",chave,ht_hash(hashtable,chave));
		
		// retorna o encadeamento de palavras para uma respectiva chave
		element * resultado = ht_get( hashtable, chave);

		// enquanto nao chegar a ultima palavra do encadeamento
		while(resultado != NULL) {
			// imprimo cada palavra
			printf( "%s ", resultado->value);

			// e passo pra proxima
			resultado = resultado->nextElement;
		}

		// se quantidade de caracteres (i) for maior que o maximo informado (n),
		// nao mostrar sugestoes e dar um aviso
		if(i > n) printf("\t---> AVISO: MAXIMO PERMITIDO DE %d CARACTERES ESTOURADO! <---",n);

		printf("\n\nDigite algo:\n(Ou pressione ENTER para sair)\n");
		
		// para debug: mostrar quais caracteres (em formato INT) estao no buffer da chave
		for (int i=0; i<n; i++) printf("%d ",chave[i]);

    	// tira o sistema do modo de "armazenamento" para ser possivel controlar onde aparecem 
    	// os caracteres digitados
    	system ("/bin/stty raw");	
		
		// Escreve o que o usuario digitou ate agora
		printf("\n");
    	printf("%s", chave);

    	// E recebe o caractere digitado, e armazena dentro da chave
    	// independente de qual caractere for
    	// OBS.: verificaremos se foi o ENTER ou o BACKSPACE depois
    	chave[i] = getchar();

    	// Limpa a tela
    	printf("\e[1;1H\e[2J");

    	// Verifica se a tecla digitada foi o backspace.
    	// OBS.: se esta na primeira casa, so ignora o backspace. 
    	// Se esta depois da primeira, ignora o backspace e apaga um caractere
    	if(chave[i] == 127){
    		// Se sim, remove o codigo do backspace que acabou de entrar na chave
    		chave[i] = 0;

    		// Verifica se o backspace foi digitado depois do primeiro caractere
    		if(i>=1) {
    			// Se sim, remove o caractere anterior e volta o cursor uma casa extra 
    			// pra compensar o caractere que o usuario apagou
    			chave[i-1] = 0;
    			i--;
    		}

    		// Finalmente, volta o cursor uma casa, pra compensar o backspace por si só
    		i--;
    	} 


    	// Verifica se o caractere digitado foi o ENTER
    	else if(chave[i] == 13) {
    		// Se sim,
    		// volta o sistema pro modo de "armazenamento" para que o sistema 
    		// volte a controlar automaticamente onde os caracteres digitados aparecem
    		system ("/bin/stty cooked");

    		// E sai do programa
    		return 0;
    	}

    	else if(chave[i] > 127) {
    		printf("Favor nao usar teclas especiais!\n");

    	}

    	// Ao terminar de processar o caractere
		printf("\n\n");

		// Volta o sistema pro modo de "armazenamento"
		// Para que os caracteres voltem a ser posicionados automaticamente
		system ("/bin/stty cooked");

    }

	return 0;
}