#include <stdio.h>
typedef char Labirinto[20][20];

int resolve_labirinto(Labirinto labirinto, int i, int j){
	
	printf("%d,%d\n",i,j);
	
	if(labirinto[i][j] == '|' || labirinto[i][j] == '=' || labirinto[i][j] == '.'){
		printf("\"%c\" é uma parede.\n\n",labirinto[i][j]);
		return 0;
	}
	else if(labirinto[i][j] == 'C'){
		printf("sou o queijo!\n");
		labirinto[i][j] = '*';
		return 1;
	}
	else if(labirinto[i][j] == ' ' || labirinto[i][j] == 'M'){
		labirinto[i][j] = '.';
		if(resolve_labirinto(labirinto, i-1, j) != 0){
			printf("Sou o caminho: %d %d\n",i,j);
			labirinto[i][j] = '*';
			return 1;
		}
		if(resolve_labirinto(labirinto, i+1, j) != 0){
			printf("Sou o caminho: %d %d\n",i,j);
			labirinto[i][j] = '*';
			return 1;
		}
		if(resolve_labirinto(labirinto, i, j-1) != 0){
			printf("Sou o caminho: %d %d\n",i,j);
			labirinto[i][j] = '*';
			return 1;
		}
		if(resolve_labirinto(labirinto, i, j+1) != 0){
			printf("Sou o caminho: %d %d\n",i,j);
			labirinto[i][j] = '*';
			return 1;
		}
	} else {
		printf("\"%c\"  não é um espaço.\n\n",labirinto[i][j]);
		return 0;
	}
}

int main(int argc, char *argv[]){
	Labirinto labirinto;
	FILE *f;
	f = fopen("labirinto_01.txt","r");
	if(f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
	int i, j;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			fscanf(f, "%c", &labirinto[i][j]);

	int x=-1, y=-1;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			if(labirinto[i][j] == 'M'){
				x=i;
				y=j;
			break;
			}
		}
	}

	printf("%c",labirinto[12][13]);

	printf("%d %d\n",x,y);

	resolve_labirinto(labirinto, x, y);
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			printf("%c", labirinto[i][j]);
}
