#include <stdio.h>
typedef char Labirinto[20][20];

int resolve_labirinto(Labirinto labirinto, int i, int j){

	if(labirinto[i][j] == '|' || labirinto[i][j] == '=' || labirinto[i][j] == '.'){
		return 0;	//valida se a posição atual é "parede". Se for, retorna 0.
	}
	else if(labirinto[i][j] == 'C'){	//se a posição atual for o queijo, coloca um asterisco e retorna 1.
		labirinto[i][j] = '*';
		return 1;
	}
	else {	//não sendo nem "parede" nem o queijo, só pode ser o a largada (M) ou um espaço.
		labirinto[i][j] = '.';
		if(resolve_labirinto(labirinto, i-1, j) == 1){	//coloca um . na posição atual e chama a função recursiva, passando por parâmetro a uma das 4 posições vizinhas.
			labirinto[i][j] = '*';	//caso a função retorne o queijo, coloca um asterisco na posição atual e retorna 1.
			return 1;
		}
		else if(resolve_labirinto(labirinto, i+1, j) == 1){//coloca um . na posição atual e chama a função recursiva, passando por parâmetro a uma das 4 posições vizinhas.
			labirinto[i][j] = '*';	//caso a função retorne o queijo, coloca um asterisco na posição atual e retorna 1.
			return 1;
		}
		else if(resolve_labirinto(labirinto, i, j-1) == 1){//coloca um . na posição atual e chama a função recursiva, passando por parâmetro a uma das 4 posições vizinhas.
			labirinto[i][j] = '*';	//caso a função retorne o queijo, coloca um asterisco na posição atual e retorna 1.
			return 1;
		}
		else if(resolve_labirinto(labirinto, i, j+1) == 1){//coloca um . na posição atual e chama a função recursiva, passando por parâmetro a uma das 4 posições vizinhas.
			labirinto[i][j] = '*';	//caso a função retorne o queijo, coloca um asterisco na posição atual e retorna 1.
			return 1;
		}else return 0;	//caso nenhum dos caminhos leve ao queijo, retorna 0.
	}
}

int main(int argc, char *argv[]){
	printf("Argumentos: %d.\n------------------\n",argc);
	for(int i=0;i<argc;i++) printf("Argumento %d: %s\n",i,argv[i]);	//mostra o número de argumentos informados.
	printf("\n");
	if(argc != 2) {	//se forem informados mais ou menos que 2 argumentos, dá uma mensagem de erro.
		printf("ERRO DE INPUT!\nDigite o nome do programa e o nome do arquivo!\n");
		return 0;
	}

	Labirinto labirinto;	//cria um objeto do tipo labirinto.
	FILE *arq_labirinto;	//inicializa um ponteiro para arquivo.
	arq_labirinto = fopen(argv[1],"r");	//abre o arquivo escolhido pelo usuário no modo de leitura.
	if(arq_labirinto == NULL) {
        printf("Erro ao abrir o arquivo.\n");	//se o arquivo não for encontrado, mostra mensagem de erro.
        return 0;
    }

	int i,j;	
	for(i=0;i<20;i++){
	      for (j = 0; ; j++) {
	            char c; fscanf(arq_labirinto, "%c", &c);	//faz uma cópia do arquivo para o objeto criado.
	            if (c == '\n') break;	//para este loop em caso de fim de linha para começar a imprimir a linha seguinte.
	            labirinto[i][j] = c;
	      }
	}

	int mx=-1, my=-1;	//variáveis que armazenam as posições de largada e de chegada.
	int cx=-1, cy=-1;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			if(labirinto[i][j] == 'M'){	//procura pela posição da largada.
				mx=i;
				my=j;
				break;
			} else if (labirinto[i][j] == 'C'){	//procura pela posição do queijo (chegada).
				cx=i;
				cy=j;
				break;
			}
		}
	}

	printf("\n\nLabirinto original\n");	//imprime o labirinto original.
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			printf("%c", labirinto[i][j]);
		}
		printf("\n");
	}

	printf("Posição da largada: %dx%d\nPosição do queijo: %dx%d\n",mx,my,cx,cy);	//imprime as posições de largada e chegada.

	if(resolve_labirinto(labirinto, mx, my) == 1){	//chama a função recursiva passando por parâmetro a posição da largada.
		printf("\n\nLabirinto resolvido!\n");	//se a função retornar 1, é porque foi bem sucedida.
	} else {
		printf("\nO labirinto não possui solução!\n");	//se retornar 0, o labirinto não tem solução.
	}
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			printf("%c", labirinto[i][j]);	//imprime o labirinto resolvido.
		}
		printf("\n");
	}
}