#include <stdio.h>
#include <stdlib.h>
#define TAM_VET 4
// declaracao do modelo data
struct data{
	int dia, mes, ano;
};
// declaracao do modelo funcionario
struct aluno{
	char nome[50];
	double mediaFinal;
	struct data nascimento;
};

int main(){
	int i;
	// declaracao e inicialização do vetor de estruturas vet

struct aluno faculdade[TAM_VET]={
	for(i=1;i<4;i++){
		printf("Nome do aluno: \n");
		scanf("%s",&faculdade[i].nome);
		printf("Media final do aluno: \n");
		scanf("%s",&faculdade[i].mediaFinal);
		printf("Nascimento: \n",);
		scanf("%s%s%s",&faculdade[i].nascimento.dia,&faculdade[i].nascimento.mes,&faculdade[i].nascimento.ano);
}};

puts("Imprimindo os dados.\n");

for(i=0; i<TAM_VET; i++){
	puts(faculdade[i].nome);
	printf("Media Final: %.2f", faculdade[i].mediaFinal);
	printf("\n%d/%d/%d\n\n", faculdade[i].nascimento.dia,faculdade[i].nascimento.mes,faculdade[i].nascimento.ano );
}
return (0);
}



