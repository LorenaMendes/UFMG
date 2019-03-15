#define _XOPEN_SOURCE 500 // Ativa certas funcoes de biblioteca (strdup) on linux.

#include <stdio.h> 	// Biblioteca basica
#include <stdlib.h>	// Funcoes: 	malloc, qsort, etc.
#include <ctype.h>	// Funcoes: 	tolower
#include <limits.h>	// Datatype:	ULONG_MAX
#include <string.h>	// Funcoes: 	strlen, strcmp, strdup, strcpy

int DEBUG = 0;  	// Ativar modo DEBUG para ver o que esta acontecendo no programa
int debug_counter = 0;

struct ocorrencia_t {
	char *palavra;
	int count;
	struct ocorrencia_t *next;
};

typedef struct ocorrencia_t ocorrencia;

// Estrutura que amarra uma chave a uma palavra e guarda o contador de ocorrencias
struct entry_s {
	char *key;
	int value;
	int count;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

void remove_punct_and_make_lower_case(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
       if (ispunct((unsigned char)*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src))
       {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}

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
entry_t *ht_newpair( char *key, int value ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	newpair->value = value;
	newpair->count = 1;
	newpair->next = NULL;

	return newpair;
}

// Insere um par chave-valor na Hashtable
void ht_set( hashtable_t *hashtable, char *key, int value ) {
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

	// Chave ja contem registro. Vamos somente incrementar o contador
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		// Incrementa o contador
		next->count++;
		if(DEBUG) printf("Incrementando o contador de %s: %d ocorrencias\n",next->key,next->count);

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
int ht_get( hashtable_t *hashtable, char *key ) {
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
		return 0;
	// Se encontrado, retorna o valor
	} else {
		return pair->count;
	}
	
}

void bsort(char *arr[100], int n) 
{ 
    char temp[100]; 
  
    // Sorting strings using bubble sort 
    for (int j=0; j<n-1; j++) 
    { 
        for (int i=j+1; i<n; i++) 
        { 
            if (strcmp(arr[j], arr[i]) > 0) 
            { 
                strcpy(temp, arr[j]); 
                strcpy(arr[j], arr[i]); 
                strcpy(arr[i], temp); 
            } 
        } 
    } 
} 

// Usada pela qsort() e bsort()
int sortstring(const void * a, const void * b){
    char **A = (char **)a;
    char **B = (char **)b;
    return strcmp(*A, *B);
}

ocorrencia *newPalavra(char* palavra) {
	ocorrencia *aux = malloc(sizeof(ocorrencia));

	// E seto seus valores
	aux->next = NULL;
	aux->palavra = malloc(500);
	strcpy(aux->palavra,palavra);
	aux->count = 1;

	return aux;
}

ocorrencia* buscaPalavra(char* palavra, ocorrencia *listaOcorrencias) {
	// Vou andando pela lista de ocorrencias pra ver se acho a palavra
	if(DEBUG) printf("buscando %s...\n",palavra);
	for(ocorrencia *aux = listaOcorrencias;aux != NULL;aux = aux->next) {
		if(DEBUG) printf("Comparando %s e %s...",palavra,aux->palavra);
		if(strcmp(palavra,aux->palavra) == 0) {
			if(DEBUG) printf(" iguais.\n");
			return aux;
		}
		if(DEBUG) printf(" mas nao sao iguais.\n");
	}

	// se terminei a lista e nao achei nada, tem alguma coisa errada...
	printf("ERRO! Palavra nao encontrada.\n");

	// retorno NULL e trato na funcao pai
	return NULL;
}

int main( int argc, char **argv ) {

	// Cria uma hashtable com 2^16 posicoes
	// Cuidado ao alterar o tamanho da tabela!
	hashtable_t *hashtable = ht_create( 65536 );
	ocorrencia *listaOcorrencias = NULL;
	int pesqSeqTamanho = 0,op;

	// CHECA PARAMETROS DE ENTRADA
	if(argc < 5) {
		printf("ERRO! Parametros insuficientes. Use: \n\n");
		printf("\t%s <<INPUT>> <<PESQUISA>> <<ORDENACAO>> <<OUTPUT>>\n\n",argv[0]);
		printf("Parametros:\n");
		printf("\t    <<INPUT>>\tArquivo de input\n");
		printf("\t <<PESQUISA>>\t0 para pesquisa sequencial, 1 para tabela hash\n");
		printf("\t<<ORDENACAO>>\t0 para complexidade O(n^2), 1 para O(n log n) \n");
		printf("\t   <<OUTPUT>>\tArquivo de output\n\n");
		printf("Exemplo:\n\t%s input.txt 0 0 output.txt\n",argv[0]);
		return 1;
	} else if((atoi(argv[2]) == 0) && (atoi(argv[3]) == 0)) {
		printf("Pesquisa sequencial e Ordenacao Bubblesort\n");
		op = 0;
	} else if((atoi(argv[2]) == 0) && (atoi(argv[3]) == 1)) {
		printf("Pesquisa sequencial e Ordenacao Quicksort\n");
		op = 1;
	} else if((atoi(argv[2]) == 1) && (atoi(argv[3]) == 0)) {
		printf("Tabela Hash e Ordenacao Bubblesort\n");
		op = 2;
	} else if((atoi(argv[2]) == 1) && (atoi(argv[3]) == 1)) {
		printf("Tabela Hash e Ordenacao Quicksort\n");
		op = 3;
	} else {
		printf("ERRO!\nOs parametros <<PESQUISA>> e <<ORDENACAO>> devem ser 0 ou 1.\n");
		printf("\t%s <<INPUT>> <<PESQUISA>> <<ORDENACAO>> <<OUTPUT>>\n\n",argv[0]);
		printf("Parametros:\n");
		printf("\t    <<INPUT>>\tArquivo de input\n");
		printf("\t <<PESQUISA>>\t0 para pesquisa sequencial, 1 para tabela hash\n");
		printf("\t<<ORDENACAO>>\t0 para complexidade O(n^2), 1 para O(n log n) \n");
		printf("\t   <<OUTPUT>>\tArquivo de output\n\n");
		printf("Exemplo:\n\t%s input.txt 0 0 output.txt\n",argv[0]);
		return 1;
	}

	// Declara e aloca as variaveis do programa
	int i, j, tam=0;
	FILE * arq = fopen(argv[1], "r"); // usado para controlar onde estou lendo no arquivo INPUT
	char * aux = malloc (500); // usado para armazenar uma palavra vinda do input
	char ** palavras = malloc (100000 * sizeof(char *)); // ponteiro para apontar para o conjunto de palavras do INPUT

	for(i=0; i<100000; i++) palavras[i] = malloc (100 * sizeof(char)); // alocando a memoria de cada palavra do INPUT (tamanho maximo de 100.000 palavras)

	//Enquanto tiver palavras no INPUT, coloca as palavras num vetor
	while(fgets(aux, 500, arq)){
			remove_punct_and_make_lower_case(aux);
			char* token = strtok(aux, " \n\0");
			while (token) {
			    // printf("token %d: %s\n", tam+1, token);

			    // populo a linha lida do arquivo para o meu vetor de palavras a serem tratadas
			    strcpy(palavras[tam], token);

			    tam++;

			    token = strtok(NULL, " \n\0");
			}			
	}

	// Ja terminamos de ler e importar o arquivo de INPUT. Podemos fechar.
	fclose(arq);

	printf("=== Arquivo de input (%d palavras):\n",tam);

	printf("Terminei as adicoes.\n");
	for(int i=0;i<tam;i++) {
		printf("%s\n",palavras[i]);
	}

	// =================================================
	// TRATAMENTO:
	// DEPENDE DOS INPUTS
	// =================================================
	if(op>1) { // se for HashTable
		for(int i=0; i<tam; i++) {
		    ht_set( hashtable, palavras[i], i );
		}
	} else { // se for Pesquisa Sequencial
		if(DEBUG) printf("Pesquisa sequencial:\n");
		for(int i=0; i<tam; i++) {
			if(DEBUG) printf("Adicionando %s...\n",palavras[i]);
			if(listaOcorrencias == NULL) {
				if(DEBUG) printf("Inicializando a lista de ocorrencias...\n");
				listaOcorrencias = newPalavra(palavras[i]);
				if(DEBUG) printf("Palavra %s adicionada na raiz.\n",listaOcorrencias->palavra);
			}
			else {
				ocorrencia *aux;
				// Vou andando pela lista de ocorrencias pra ver se acho a palavra

				// Começo verificando se a palavra esta na primeira ocorrencia da lista
				if(strcmp(palavras[i],listaOcorrencias->palavra) == 0) {
						// se achei a palavra, incremento sua contagem e saio da funcao
						listaOcorrencias->count++;
						if(DEBUG) printf("Palavra %s repetida. Incrementando contador (%d)...\n",palavras[i],listaOcorrencias->count);
				}

				// depois verifico no resto da lista
				for(aux = listaOcorrencias;aux->next != NULL;aux = aux->next) {
					if(strcmp(palavras[i],aux->next->palavra) == 0) {
						// se achei a palavra, incremento sua contagem e saio da funcao
						aux->next->count++;
						if(DEBUG) printf("Palavra %s repetida. Incrementando contador (%d)...\n",palavras[i],aux->next->count);
					}
				}

				// Cheguei ao final da lista e nao achei a palavra
				aux->next = newPalavra(palavras[i]);
				
				if(DEBUG) printf("Palavra %s adicionada.\n",aux->next->palavra);
			}
		}
	}

	// =================================================
	// ORDENACAO:
	// DEPENDE DOS INPUTS
	// =================================================

	char ordenacao[30];
	// Ordena as palavras por ordem alfabética
	if(atoi(argv[3]) == 1) { // Se algoritmo de ordenacao for QuickSort
		strcpy(ordenacao,"QuickSort");
		qsort (palavras, tam, sizeof(char *), sortstring);
	} else { // Ja se for bubblesort
		strcpy(ordenacao,"BubbleSort");
		bsort (palavras, tam); 
	}

	printf("=== Arquivo de input ordenado por %s:\n",ordenacao);
	strcpy(aux,"\0");


	// Imprime todas as palavras e suas recorrencias
	if(op > 1) {
		for(int i=0;i<tam;i++) {
			if(strcmp(palavras[i],aux) != 0) {
				printf("%s (%d)\n",palavras[i],ht_get( hashtable, palavras[i]));
			}
			strcpy(aux,palavras[i]);
		}
	} else {
		for(int i=0;i<tam;i++) {
			if(strcmp(palavras[i],aux) != 0) {
				printf("%s (%d)\n",palavras[i],(buscaPalavra(palavras[i],listaOcorrencias))->count);
			}
			strcpy(aux,palavras[i]);
		}
	}
	return 0;
}
