#include <stdio.h>
#define LEN 50
typedef struct endereco {
	char rua[LEN];
	char cidade[15];
	char estado[3];
	char cep[10];
} endereco;
endereco obtem_endereco(void) {
	endereco ender;
	printf("\t Entre rua: ");
	gets(ender.rua);
	printf("\t Entre cidade: ");
	gets(ender.cidade);
	printf("\t Entre estado: ");
	gets(ender.estado);
	printf("\t Entre cpf: ");
	gets(ender.cep);
	return ender;
}
void imprime_endereco (endereco ender) {
	printf("\t%s\n", ender.rua);
	printf("\t%s\n\t%s\n\t%s\n", ender.cidade,ender.estado,ender.cep);
}
void main(void) {
	endereco residencia;
	printf("Entre seu endereco residencial:\n");
	residencia = obtem_endereco();
	printf("\nSeu endereco eh:\n");
	imprime_endereco(residencia);
}
