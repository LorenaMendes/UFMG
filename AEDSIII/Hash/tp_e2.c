#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct Hashtable Hashtable;
typedef void(*sm_enum_func)(const char *chave, const char *valor, const void *obj);

const int DEBUG = 0;

// Estrutura que permite encadear multiplos
// Valores para a mesma chave
struct palavraEncadeada {
	char *palavra; // String com a palavra do dicionario
	struct palavraEncadeada *proximo; // Ponteiro para a proxima string
};

typedef struct palavraEncadeada palavraEncadeada;

// Construtor para o ELEMENT acima
// recebe uma String representando uma palavra
palavraEncadeada * PalavraEncadeada(const char * string) {

	// Alocando memoria para a PalavraEncadeada
	palavraEncadeada *palavra = malloc(sizeof(palavraEncadeada));

	// Setando o ponteiro para o proximo elemento
	palavra->proximo = 0;
	
	// Alocando memoria para a String
	palavra->palavra = malloc(100);

	//Copiando a string
	strcpy(palavra->palavra, string);

	if(DEBUG) printf("Criada %s!\n",palavra->palavra);
	return palavra;
}

// Par chave-valor:
struct Par {
	char *chave;
	palavraEncadeada *palavraEncadeada;
};

typedef struct Par Par;

// Balde com os pares
struct Balde {
	unsigned int count;
	Par *pares;
};

typedef struct Balde Balde;

// Instanciacao da Hashtable
// Contendo um contador e o balde de pares
struct Hashtable {
	unsigned int count;
	Balde *balde;
};

/*
 * Calcula e retorna o codigo Hash para a String passada
 */
static unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c;
	}
	// if(DEBUG) printf("Hash de %s: %ld\n", str, hash);
	return hash;
}


/*
 * Cria um mapa de objetos, que armazenara os pares
 */
Hashtable * sm_novo(unsigned int capacity)
{
	if(DEBUG) printf("Criando novo SM de capacidade %d\n", capacity);
	Hashtable *map;
	
	map = malloc(sizeof(Hashtable));
	if (map == NULL) {
		return NULL;
	}
	map->count = capacity;
	map->balde = malloc(map->count * sizeof(Balde));
	if (map->balde == NULL) {
		free(map);
		return NULL;
	}
	memset(map->balde, 0, map->count * sizeof(Balde));
	if(DEBUG) printf("Criado novo SM!\n");
	return map;
}

/*
 * Retorna um par do balde que bate com a chave,
 * ou NULL se o par nao for encontrado
 */
static Par * get_par(Balde *balde, const char *chave)
{
	if(DEBUG) printf("Buscando par da chave %s...\n", chave);
	unsigned int i, n;
	Par *par;

	n = balde->count;
	if (n == 0) {
		return NULL;
	}
	par = balde->pares;
	i = 0;
	while (i < n) {
		if (par->chave != NULL && par->palavraEncadeada != NULL) {
			if (strcmp(par->chave, chave) == 0) {
				if(DEBUG) printf("Encontrei!\n");
				return par;
			}
		}
		par++;
		i++;
	}
	if(DEBUG) printf("Nao encontrei.\n");
	return NULL;
}

palavraEncadeada* sm_get(const Hashtable *map, char *chave, palavraEncadeada *out_buf, unsigned int n_out_buf)
{
	if(DEBUG) printf("Funcao sm_get --------------\n ");
	unsigned int index;
	Balde *balde;
	Par *par;
	palavraEncadeada * retorno = malloc(sizeof(PalavraEncadeada));
	
	index = hash(chave) % map->count;
	balde = &(map->balde[index]);
	par = get_par(balde, chave);

	if (par == NULL) {
		if(DEBUG) printf("Nao achei...\n");
		return NULL;
	}
	
	if(DEBUG) printf("Achei %s!\n",par->palavraEncadeada->palavra);
	return par->palavraEncadeada;
}

/*
 * Associa um valor a chave fornecida. Se a chave ja tiver um valor, 
 * encadeia os dois valores na mesma chave.
 */
int sm_put(Hashtable *map, char *chave, char *valor)
{
	if(DEBUG) printf("Inserindo (%s,%s) na Hashtable...\n", chave, valor);
	unsigned int chave_len, valor_len, index;
	Balde *balde;
	Par *tmp_pares, *par;
	char *new_chave;

	if (map == NULL) {
		return 0;
	}
	if (chave == NULL || valor == NULL) {
		return 0;
	}
	chave_len = strlen(chave);
	valor_len = strlen(valor);

	// Pega o ponteiro para o balde referente a chave
	index = hash(chave) % map->count;
	balde = &(map->balde[index]);

	
	/* Check if we can handle insertion by simply replacing
	 * an existing value in a key-value pair in the bucket.
	 */
	if ((par = get_par(balde, chave)) != NULL) {
		/* O balde possui um par que bate com a chave fornecida,
		 * encadeie o novo valor aqui
		 */
		if(DEBUG) printf("Tentei inserir %s, mas ja tem %s...\n", valor, par->palavraEncadeada->palavra);
		palavraEncadeada *aux = malloc(sizeof(palavraEncadeada));
		aux = par->palavraEncadeada;

		while(aux->proximo != 0) {
			if(DEBUG) printf("%s nao eh a ultima chave...\n",aux->palavra);
			aux = aux->proximo;
		} 

		if(DEBUG) printf("Ultima chave da cadeia: %s\n",aux->palavra);
		aux->proximo = PalavraEncadeada(valor);

		if(DEBUG) printf("Inseri %s no final.\n", valor);
		
		return 1;
	}
	
	// Alocando espaco para uma nova chave e um novo valor
	new_chave = malloc((chave_len + 1));
	if (new_chave == NULL) {
		return 0;
	}

	// Criando novo par chave-valor
	if (balde->count == 0) {
		/*
		 * O balde esta vazio, alocando espaco
		 * para um unico par chave-valor
		 */
		balde->pares = malloc(sizeof(Par));
		if (balde->pares == NULL) {
			free(new_chave);
			return 0;
		}
		balde->count = 1;
	}
	else {
		/* O balde nao estava vazio
		 * Realocando memoria para caber mais um novo par chave-valor
		 */
		tmp_pares = realloc(balde->pares, (balde->count + 1) * sizeof(Par));
		if (tmp_pares == NULL) {
			free(new_chave);
			return 0;
		}
		balde->pares = tmp_pares;
		balde->count++;
	}
	// Pega o ultimo par da corrente 
	par = &(balde->pares[balde->count - 1]);
	par->chave = new_chave;
	if(DEBUG) printf("Chamando construtor para %s...\n",valor);
	par->palavraEncadeada = PalavraEncadeada(valor);
	/* Copy the chave and its valor into the chave-valor par */
	if(DEBUG) printf("Criei palavra encadeada!\n");
	strcpy(par->chave, chave);
	strcpy(par->palavraEncadeada->palavra, valor);
	return 1;
}

int sm_enum(const Hashtable *map, sm_enum_func enum_func, const void *obj)
{
	unsigned int i, j, n, m;
	Balde *balde;
	Par *par;

	if (map == NULL) {
		return 0;
	}
	if (enum_func == NULL) {
		return 0;
	}
	balde = map->balde;
	n = map->count;
	i = 0;
	while (i < n) {
		par = balde->pares;
		m = balde->count;
		j = 0;
		while (j < m) {
			enum_func(par->chave, par->palavraEncadeada->palavra, obj);
			par++;
			j++;
		}
		balde++;
		i++;
	}
	return 1;
}

static int cmpstringp(const void *p1, const void *p2) {
    /* The actual arguments to this function are "pointers to
       pointers to char", but strcmp(3) arguments are "pointers
       to char", hence the following cast plus dereference */
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int main(int argc, char **argv ) {

	Hashtable *sm;
	palavraEncadeada * buf = malloc(sizeof(palavraEncadeada));

	FILE * input = fopen(argv[1], "r+w");
	char * chave,* palavra_input = malloc (200);
	char ** dicionario = malloc(1000000 * 200);
	int palavras=0, final_arquivo = 1,N=atoi(argv[2]);

	//Enquanto tiver palavras no INPUT, coloca as palavras num vetor
	while(fgets(palavra_input, 200, input)){
		palavras++;

		// inserindo palavras no dicionario
		dicionario[palavras-1] = strdup(palavra_input);

		// acertando ultimo caractere de breakline para EndOfString
		dicionario[palavras-1][strlen(dicionario[palavras-1])-1] = '\0';
	}

	// Cria uma Hashtable que suporte a quantidade de palavras lidas
	sm = sm_novo(palavras);

	// Ordena as palavras por ordem alfabética
	qsort (dicionario, palavras, sizeof(char *), cmpstringp);

	printf("Dicionario: \n");

	// Passa por todas as palavras ordenadas
	for(int i=0; i<palavras; i++) {
		// Imprime
		printf("%d) %s\n", i+1, dicionario[i]);

		// E adiciona cada palavra em todas as chaves respectivas
		// (chaves de 1 caractere ate chaves de N caracteres)
		// Ex.: Palavra ACRE sera adicionada nas chaves A, AC, ACR e ACRE
		for(int j=1;(j<=N && dicionario[i][j-1]!='\0');j++) {
			chave = malloc (200);
			strncpy(chave,dicionario[i],j);
			sm_put( sm, chave, dicionario[i] );
		}
	}

	char ch;
	chave = malloc (200);
	int contador_de_char=0;

	// Loop infinito. O programa só sai quando o usuario aperta ENTER
	while(1) {
		// Convertendo tudo pra lower case
		for(int j=0;j<contador_de_char;j++)
			chave[j] = tolower(chave[j]);
		
		// busca o valor
		buf = sm_get(sm, chave, buf, sizeof(buf));

		printf("\n\nAuto-complete: \n");
		while(buf != 0) {
			printf("%s ", buf->palavra);
			buf = buf->proximo;
		}
		printf("\n");
		printf("\n-------------------------------\n");
		printf("Digite a chave:\n");
		printf("%s", chave);

		system ("/bin/stty raw");
		chave[contador_de_char] = getchar();
		system ("/bin/stty cooked");


    	// Verifica se o caractere digitado foi o ENTER
    	if(chave[contador_de_char] == 13) {
    		// Se sim, ja sai do programa
    		printf("\n");
    		return 0;
    	}
		// Verifica se o digitado foi DEL ou BKSP
		else if(chave[contador_de_char] == 127){

    		// Se estamos depois do primeiro caractere, volta duas casas
    		if(contador_de_char > 0) {
    			chave[contador_de_char] = '\0';
    			chave[contador_de_char-1] = '\0';
    			contador_de_char-=2;
    		} else {
    			// Se estamos no primeiro caractere, apenas compensamos o incremento 
    			// do caractere, permanecendo no mesmo lugar.
    			chave[contador_de_char] = '\0';
    			contador_de_char--;
    		}
    	} 

    	contador_de_char++;

	}

	// fecha o arquivo no final
    fclose(input);

    return 0;
}