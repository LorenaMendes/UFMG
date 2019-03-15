#include <stdio.h>
#include <string.h>
typedef struct tipo_endereco {
	char rua [50];
	float numero;
	char bairro [20];
	char cidade [30];
	char sigla_estado [3];
	float CEP;
} tipo_endereco;
typedef struct ficha_pessoal {
	char nome [50];
	float telefone;
	tipo_endereco endereco;
} ficha_pessoal;
main (void) {
	ficha_pessoal ficha;
	strcpy (ficha.nome,"Luiz Osvaldo Silva");
	ficha.telefone=4921234;
	strcpy (ficha.endereco.rua,"Rua das Flores");
	ficha.endereco.numero=10;
	strcpy (ficha.endereco.bairro,"Cidade Velha");
	strcpy (ficha.endereco.cidade,"Belo Horizonte");
	strcpy (ficha.endereco.sigla_estado,"MG");
	ficha.endereco.CEP=31340230;

	printf("\n%s",ficha.nome);
	printf("\n%.0f",ficha.telefone);
	printf("\n%.0f",ficha.endereco.numero);
	printf("\n%s",ficha.endereco.bairro);
	printf("\n%s",ficha.endereco.cidade);
	printf("\n%s",ficha.endereco.sigla_estado);
	printf("\n%.0f\n\n",ficha.endereco.CEP);
	return 0;
}
