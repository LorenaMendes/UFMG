#include <stdio.h>
#include <stdlib.h>

void conta_trocas(int * vetor, int tamanho){
	int i, cont = 0;
	for(i=0; i<tamanho; i++){
		if(vetor[i] == i)
			cont ++;
	}
	printf("%d\n", cont);
}

void ordena_vetor(int vet_alunos[], int tamanho){
	int aux, i, j;
	int vet_aux[tamanho];
	for(i=0; i<tamanho; i++) vet_aux[i] = i;
	for(j=tamanho-1; j>=1; j--){
		for(i=0; i<j; i++){
			if(vet_alunos[i] < vet_alunos[i+1]){
				aux=vet_alunos[i];
                vet_alunos[i]=vet_alunos[i+1];
                vet_alunos[i+1]=aux;
                aux = vet_aux[i];
                vet_aux[i] = vet_aux[i+1];
                vet_aux[i+1] = aux;
            }
        }
    }
    conta_trocas(vet_aux, tamanho);
}

int main(){
	int i, j, casos, alunos;
	scanf("%d", &casos);
	for(i=0; i<casos; i++){
		scanf("%d", &alunos);
		int vet_alunos[alunos];
		for(j=0; j<alunos; j++){
			scanf("%d", &vet_alunos[j]);
		}
		ordena_vetor(vet_alunos, alunos);
	}
}
