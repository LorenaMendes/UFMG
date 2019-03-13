#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int search(char * txt, char * key, int key_size, int position){
   int i;
   for(i=1; i<key_size; i++){
      if(key[i] != txt[position]){
         return 0;
      }
      position ++;
   }
   return 1;
}

int a_menor_que_b(char* a, char* b, int len) {
    int i;
    int tam_a = strlen(a);
    int tam_b = strlen(b);
	return tam_a < tam_b ? 1 : 0;
	// return tam_a < tam_b ? 0 : 1;
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

int find_smaller(int a, int b){
    int smaller = a;
    if(smaller > b) smaller = b;
    return smaller;
}

int main(){
   	int i, j, k, counter = 0, zizi = 0;
   	int num_lines, num_emo, lola = 1;
   	char * line = malloc(10000 * sizeof(char));
   	char * line_cpy = malloc(10000 * sizeof(char));
   
  	while(!feof(stdin)){
	    scanf("%d %d\n", &num_emo, &num_lines);
	    if(num_emo == 0 && num_lines == 0) break;
	    if(DEBUG) printf("\n############################### THIS IS THE CASE %d\n", lola);
	    lola++;
	    if(DEBUG) printf("%d EMOTICONS e %d LINHAS\n", num_emo, num_lines);
	     
	    char ** emoticons = malloc(num_emo * sizeof(char *));
	    for(i=0; i<num_emo; i++) emoticons[i] = malloc(sizeof(char));
	      
	    //allocates emoticons in a vector
	    for(i=0; i<num_emo; i++){
	        fgets(emoticons[i], 16, stdin);
	    }

	    quicksort(emoticons, num_emo);

	    for(i=0; i<num_lines; i++){
		    fgets(line, 10000, stdin);
		    strcpy(line_cpy, line);
		    int tam_linha = strlen(line)-1;
		    if(DEBUG) printf("Linha %d de tamanho %d: %s\n", i+1, tam_linha, line);
		    if(DEBUG) printf("LINHA %d: %s", i+1, line);
		    
		    for(k=0; k<num_emo; k++){
		    	for(j=0; j<tam_linha; j++){
		    		if(line[j] == emoticons[k][0]){
		    			int tam_emo = strlen(emoticons[k])-1;
		    			if(search(line, emoticons[k], tam_emo, j+1)){
		    				line[j+tam_emo-1] = ' ';
		    				if(DEBUG) printf("Nova linha: %s", line);
		    				counter++;
		    				j=0;
		    			}
		    		}
		    	}
		    }

		    
		   	for(j=0; j<tam_linha; j++){
		    	for(k=0; k<num_emo; k++){
		    		if(line_cpy[j] == emoticons[k][0]){
		    			int tam_emo = strlen(emoticons[k])-1;
		    			if(search(line_cpy, emoticons[k], tam_emo, j+1)){
		    				line_cpy[j+tam_emo-1] = ' ';
		    				if(DEBUG) printf("Nova linha: %s", line_cpy);
		    				zizi++;
		    				j=0;
		    			}
		    		}
		    	}
		    }
	    }

	    if(DEBUG) printf("\nTotal number of emoticons found: %d\n", counter);
	    int smaller = find_smaller(counter, zizi);
	    // printf("%d\n", zizi);
	    // printf("%d\n", counter);
	    printf("%d\n", smaller);
	    if(DEBUG) printf("\n");
	    counter = 0;
	    zizi = 0;
	}
}