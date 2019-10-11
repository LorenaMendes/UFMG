#include <stdio.h>

//estrutura de dados que representa um banco
typedef struct Banco{
	int group;
} Banco;

//função para fundir dois bancos, colocando-os no mesmo grupo
void funde_bancos(int g1, int g2, Banco *bancos, int tam){
	int min = g1 < g2 ? g1 : g2; //define o menor valor
	int max = min == g1 ? g2 : g1; //define o maior valor

	for (int i = 0; i < tam; ++i){
		if(bancos[i].group == max) bancos[i].group = min; //define todos do mesmo grupo com o menor valor
	}
}

int main(){
	
	int n; //número de bancos
	int k; //número de operações
	char command; //comando (F para fusão, C para consulta)
	int b1, b2; //bancos a serem fundidos ou consultados
	
	while(1){
		scanf("%d %d\n", &n, &k); //pega os valores de n e k
		if(n == 0 && k == 0){ //condição de parada do programa
			return 0;
		}

		Banco bancos[n]; // cria uma lista de bancos

		for (int i = 0; i < n; ++i) bancos[i].group = i; //define o grupo de cada banco

		for (int i = 0; i < k; ++i){
			scanf("%c %d %d\n", &command, &b1, &b2); //pega o comando e os bancos

			if(command == 'F'){ //caso de fusão
				funde_bancos(bancos[b1-1].group, bancos[b2-1].group, bancos, n);
			} else { //caso de consulta
				if(bancos[b1-1].group == bancos[b2-1].group) printf("S\n");
				else printf("N\n");
			}
		}
		printf("\n");
	}

	return 0;
}