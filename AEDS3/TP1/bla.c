#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//função para comparar dois caracteres de acordo com a ordem lexicográfica
int a_menor_que_b(char* a, char* b, int size) {
	int i;
	for(i=0; i<size && a[i]; i++){
		if(a[i]<b[i]) return 1;
		if(a[i]>b[i]) return 0;
	}
}
// função para imprimir uma lista
void printList(char * linhas[], unsigned size){
    int i;
    for (i=0 ; i < size; i++)
        printf("%s", linhas[i]);
}
// função para trocar duas posições de lugar
void switchPositions(char **pos1, char **pos2){
    char *tmp = *pos1;
    *pos1 = *pos2;
    *pos2 = tmp;
}

// função para ordenar o vetor
void quicksort(char *linhas[], unsigned int size){
    unsigned int i, pivo=0;

    // retorna 1 se só houver uma linha para ordenar
    if (size <= 1)
        return;

    // troco uma posição escolhida aleatoriamente (método quicksort) com a última posição relativa
    switchPositions(linhas+((unsigned int)rand() % size), linhas+size-1);

    // comparo duas posições e as troca, se o pivô for relativamente maior
    for (i=0;i<size-1;++i){
        if (a_menor_que_b(linhas[i], linhas[size-1], size))
            switchPositions(linhas+i, linhas+pivo++);
    }

    // troco dois elementos do vetor de lugar
    switchPositions(linhas+pivo, linhas+size-1);

    // chamo a função recursivamente para cada lado do pivô
    quicksort(linhas, pivo++);
    quicksort(linhas+pivo, size - pivo);
}

void montaFita(const char * intercalacao_file, char ** vetor_ordenado, int quantidade){
	int i;
	FILE * INTERCALACAO = fopen(intercalacao_file, "a");
	for(i=0; i<quantidade; i++){
		// printf("Coloquei no novo arquivo ordenado: %s", vetor_ordenado[i]);
		fprintf(INTERCALACAO, "%s", vetor_ordenado[i]);
	}
	fclose(INTERCALACAO);
	return;
}

int criaVetor(const char * input_file, int tamanho, int quantidade, const char * intercalacao_file){
	int i, conta_linhas = 0, linhas_vec = 0;
	int cpy = quantidade;
	
	// aqui, eu aloco dinamicamente o vetor que conterá as strings
	char ** vetor = (char **)malloc(quantidade * sizeof(char *));
	for(i=0; i<quantidade; i++) vetor[i] = (char *)malloc(tamanho * sizeof(char));
	
	// essa row + o vetor ocupam a memória máxima que posso gastar
	char * row = (char *)malloc(sizeof(char));

	FILE * INPUT = fopen(input_file, "r");
	int lixo;
	fscanf(INPUT, "%d\n", &lixo);

	FILE * TEMP = fopen("temp.txt", "w");
	fprintf(TEMP, "%d\n", tamanho);
	
	size_t teste = tamanho+3;
	while(getline(&row, &teste, INPUT) > 0){
		if(quantidade > 0){
			strcpy(vetor[conta_linhas], row);
			quantidade--;
			linhas_vec++;
		} else fprintf(TEMP, "%s", row);
		conta_linhas++;
	}
	quicksort(vetor, linhas_vec);
	montaFita(intercalacao_file, vetor, linhas_vec);
	fclose(TEMP);
	fclose(INPUT);
	for(i=0; i<cpy; i++) free(vetor[i]);
	free(vetor);
	free(row);
	return linhas_vec;
}

int linhas_arq(const char * arq_name, int tamanho){
	char * row = (char *)malloc(sizeof(char));
	FILE * ARQUIVO = fopen(arq_name, "r");
	int contador = 0;
	while(!feof(ARQUIVO)){
		fgets(row, tamanho+3, ARQUIVO);
		contador++;
	}
	// printf("quantidade de linhas: %d\n", contador-1);
	free(row);
	return contador-1;
}

int divideFitas(int num_blocos, int tam_linha, const char * intercalacao_file, const char * fita1_file, const char * fita2_file){
	FILE * ARQ0 = fopen(intercalacao_file, "r");
	FILE * ARQ1 = fopen(fita1_file, "w");
	FILE * ARQ2 = fopen(fita2_file, "w");
	char * row1 = (char *)malloc(sizeof(char));
	char * row2 = (char *)malloc(sizeof(char));
	int i;
	while(!feof(ARQ0)){
		for(i=0; i<num_blocos; i++)
			if(fgets(row1, tam_linha+3, ARQ0)) fprintf(ARQ1, "%s", row1);
			else break;
		for(i=0; i<num_blocos; i++)
			if(fgets(row2, tam_linha+3, ARQ0)) fprintf(ARQ2, "%s", row2);
			else break;
	}
	fclose(ARQ0);
	fclose(ARQ1);
	fclose(ARQ2);
	free(row1);
	free(row2);
	return num_blocos+1;
}

void ordenaFitas(int num_blocos, int tam_linha, const char * fita1_file, const char * fita2_file, const char * fita3_file){
	FILE * ARQ1 = fopen(fita1_file, "r");
	FILE * ARQ2 = fopen(fita2_file, "r");
	FILE * ARQ3 = fopen(fita3_file, "w");
	char * row1 = (char *)malloc(sizeof(char));
	char * row2 = (char *)malloc(sizeof(char));
	int i;

	fgets(row1, tam_linha+3, ARQ1);
	fgets(row2, tam_linha+3, ARQ2);
	
	if(row1 && row2){
		while(!feof(ARQ2) && !feof(ARQ1)){
			if(row1 && row2){
				switch(a_menor_que_b(row1, row2, tam_linha)){
					case 1:
						fprintf(ARQ3, "%s", row1);
						fgets(row1, tam_linha+3, ARQ1);
						break;
					case 0:
						fprintf(ARQ3, "%s", row2);
						fgets(row2, tam_linha+3, ARQ2);
						break;
				}
			}
		}
		if(!feof(ARQ2)){
			printf("a ultima palavra digitada foi %s\n", row1);
			fprintf(ARQ3, "%s", row2);
		}
		else if(!feof(ARQ1)){
			printf("a ultima palavra digitada foi %s\n", row2);
			fprintf(ARQ3, "%s", row1);
		}
		if(fgets(row1, tam_linha+3, ARQ1)){
			while(!feof(ARQ1)){
				fprintf(ARQ3, "%s", row1);
				fgets(row1, tam_linha+3, ARQ1);
			}
		}
		if(fgets(row2, tam_linha+3, ARQ2)){
			while(!feof(ARQ2)){
				fprintf(ARQ3, "%s", row2);
				fgets(row2, tam_linha+3, ARQ2);
			}
		}
	}
	fclose(ARQ1);
	fclose(ARQ2);
	fclose(ARQ3);
	free(row1);
	free(row2);
}

void intercalacaoBalanceada(int num_blocos, int tam_linha, const char * intercalacao_file){
	const char* fita1_file = "fita1.txt";
	const char* fita2_file = "fita2.txt";
	const char* fita3_file = "fita3.txt";
	
	do{
		num_blocos = divideFitas(num_blocos, tam_linha, intercalacao_file, fita1_file, fita2_file);
		ordenaFitas(num_blocos, tam_linha, fita1_file, fita2_file, intercalacao_file);
	}while(num_blocos<=linhas_arq(intercalacao_file, tam_linha));
}

int main(){
	const char* input_file = "input.txt";
	const char* output_file = "output.txt";
	const char* temp_file = "temp.txt";
	const char* intercalacao_file = "intercalacao.txt";
	unsigned int memory = 10;

	int tamanho, i;

	FILE * INPUT = fopen(input_file, "r");
	fscanf(INPUT, "%d\n", &tamanho);

	fclose(INPUT);

	int quantidade = memory/tamanho;
	printf("posso ler %d linhas por vez\n", quantidade-1);

	int linhas_vec = 0;
	linhas_vec += criaVetor(input_file, tamanho, quantidade-1, intercalacao_file);

	FILE * TEMP = fopen(temp_file, "r");
	char * row = (char *)malloc(tamanho * sizeof(char));
	while(!feof(TEMP)){
		fgets(row, tamanho+3, TEMP);
		linhas_vec += criaVetor(temp_file, tamanho, quantidade-1, intercalacao_file);
	}
	free(row);
	intercalacaoBalanceada(quantidade-1, tamanho, intercalacao_file);

	FILE * INTERCALACAO = fopen(intercalacao_file, "r");
	FILE * OUTPUT = fopen(output_file, "w");
	fprintf(OUTPUT, "%d\n", tamanho);
	for(i=0; i<linhas_vec-1; i++){
		fgets(row, tamanho+3, INTERCALACAO);
		fprintf(OUTPUT, "%s", row);
	}
	fclose(OUTPUT);
	fclose(INTERCALACAO);
	fclose(TEMP);
	free(row);
	return 0;
}