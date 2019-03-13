#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

int flag = 0;
int DEBUG = 0;

struct element_s {
	char *value;
	struct element_s *nextElement;
};

typedef struct element_s element;

element * Element(char * value) {
	element *T;
	if(!(T = malloc(sizeof(element)))) return NULL;
	T->value = strdup(value);
	T->nextElement = NULL;
	return T;
}

struct entry_s {
	char *key;
	element *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;


/* Create a new hashtable. */
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

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key ) {

	unsigned long int hashval;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 16;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

/* Create a key-value pair. */
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

/* Insert a key-value pair into a hash table. */
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

	/* There's already a pair. Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		element * aux = next->value;

		// encontra ultima string da cadeia
		while(aux->nextElement != NULL) {
			aux = aux->nextElement;
			if(DEBUG) printf("Buscando na cadeia, passando por %s...\n",aux->value);
		}
		if(DEBUG) printf("Achei o final da cadeia apos %s.\n",aux->value);

		// e coloca nova string no final
		aux->nextElement = Element(value);
		if(DEBUG) printf("Coloquei %s na chave %s\n",aux->nextElement->value,next->key);

	/* Nope, could't find it.  Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, value );

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;
	
		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;
	
		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/* Retrieve a key-value pair from a hash table. */
element *ht_get( hashtable_t *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	/* Step through the bin, looking for our value. */
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

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

void printWord(char ** words, int tam){
	int i;
	for (i=0; i<tam; i++){
		printf("Palavra %d: %s\n", i+1, words[i]);
	}
}

int main( int argc, char **argv ) {

	hashtable_t *hashtable = ht_create( 65536 );

	//-------------------------------------------------------------------
	//declara e aloca as variáveis
	int i, j, n=atoi(argv[2]),tam=0;
	if(DEBUG) printf("\n=============================\n");
	FILE * arq = fopen(argv[1], "r");
	char * aux = malloc (100);
	char ** words = malloc (100000 * sizeof(char *));
	for(i=0; i<100000; i++) words[i] = malloc (100 * sizeof(char));
	
	//coloca as palavras num vetor
	while(fgets(aux, 100, arq)){
			// populo a linha lida do arquivo para o meu vetor de palavras a serem tratadas
			strcpy(words[tam], aux);

			// e conserto a palavra substituindo o breakline que veio do arquivo por um finalizador de strings
			words[tam][strlen(words[tam])-1] = '\0';
			tam++;
	}

	//ordena as palavras por ordem alfabética
	qsort (words, tam, sizeof(char *), sortstring);

	//imprime as palavras
	printWord(words, tam);

	printf("Iniciando as insercoes na hashtable...\n");

	// percorro todas as palavras
	for(i=0; i<tam; i++){

		// para cada palavra, uso um vetor temporario para armazenar
		char * aux2 = malloc (100);

		// insiro na tabela hash a chave a ser usada 
		// quando o usuario digitar j caracteres
		for(j=0;(j<n && words[i][j]!='\0');j++) {
			strncpy(aux2,words[i],j+1);
			if(DEBUG) printf("Inserindo %s na chave %s\n",words[i],aux2);
			ht_set( hashtable, aux2, words[i] );
		}
	}
	printf("Terminei as insercoes.\n=============================\n");
	//*/

	/*//
	ht_set( hashtable, "a", "atomo");
	ht_set( hashtable, "ala", "aladdin");
	ht_set( hashtable, "~", "zonafranca");
	//*/

	char * palavra = malloc (100 * sizeof(char));

	printf("\nDigite a palavra (ou $ para sair): ");
	scanf("%s",palavra);

	while(strcmp(palavra,"$")) {
		
		printf("Sugestoes para a chave %s (hash %d): \n",palavra,ht_hash(hashtable,palavra));
		element * teste = ht_get( hashtable, palavra);
		while(teste != NULL) {
			printf( "%s ", teste->value);
			teste = teste->nextElement;
		}

		printf("\n\n");

		printf("Digite a palavra (ou $ para sair): ");
		scanf("%s",palavra);
	}

	//fecha o arquivo
	fclose(arq);
	return 0;
}